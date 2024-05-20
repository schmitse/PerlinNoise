from itertools import product
from rich.progress import track
import numpy as np
import numpy.typing as npt
import matplotlib.pyplot as plt


class RandomGradient:
    def __init__(self, seed=1337) -> None:
        self.rng = np.random.default_rng(seed=seed)
        self.cache = {}
        # self.cache_hits = 0

    def __call__(self, xp: float, yp: float, xx: int, yy: int) -> tuple[float]:
        dx, dy = xp - xx, yp - yy
        gradient = self._get_random_vector(xx, yy)
        return dx * gradient[0] + dy * gradient[1]

    def _get_random_vector(self, xx: int, yy: int) -> tuple[float]:
        key_hash = hash((xx, yy))
        if key_hash not in self.cache:
            self.cache[key_hash] = self._random_gradient()
        # else:
        #     self.cache_hits += 1
        return self.cache[key_hash]

    def _random_gradient(self) -> tuple[float]:
        angle = self.rng.uniform(0, np.pi * 2)
        return np.cos(angle), np.sin(angle)


class PerlinNoise:
    def __init__(self, seed: int = 1337) -> None:
        self.random_vector = RandomGradient(seed=seed)

    @staticmethod
    def fade(val: float) -> float:
        return val**3 * (val * (val * 6 - 15) + 10)

    @staticmethod
    def lerp(v0: float, v1: float, ds: float) -> float:
        return v0 + (v1 - v0) * ds

    # def get_cache_hits(self) -> int:
    #     return self.random_vector.cache_hits

    def __call__(self, xp: float, yp: float) -> float:
        xlower: int = int(xp)
        ylower: int = int(yp)
        xupper: int = xlower + 1
        yupper: int = ylower + 1

        dx: float = self.fade(xp - xlower)
        dy: float = self.fade(yp - ylower)

        rg_lower: float = self.random_vector(xp, yp, xlower, ylower)
        rg_upper: float = self.random_vector(xp, yp, xupper, ylower)
        interp_lower = self.lerp(rg_lower, rg_upper, dx)

        rg_lower: float = self.random_vector(xp, yp, xlower, yupper)
        rg_upper: float = self.random_vector(xp, yp, xupper, yupper)
        interp_upper = self.lerp(rg_lower, rg_upper, dx)

        return self.lerp(interp_lower, interp_upper, dy)


def perlin_noise(width: int, height: int, *, grid_size: float = 400, 
                 octaves: int = 8, seed: int = 1337) -> npt.NDArray:
    values: npt.NDArray = np.zeros((height, width))
    amplitude: float = 1.
    frequency: float = 1.
    noise_creator: PerlinNoise = PerlinNoise(seed=seed)

    for _ in track(range(octaves), description='Processing Octaves..'):
        for x, y in product(range(width), range(height)):
            values[y, x] += noise_creator(x / grid_size * frequency, 
                                          y / grid_size * frequency) * amplitude
        amplitude /= 2.
        frequency *= 2.
    
    # print(f'Used {noise_creator.get_cache_hits()} cache hits.')
    return regularise_output(values)


def regularise_output(values: npt.NDArray) -> npt.NDArray:
    _min: float = np.min(values)
    _max: float = np.max(values)
    if _max == _min:
        return values
    return -1 + (values - _min) / (_max - _min) * 2


def main() -> None:
    import argparse
    parser = argparse.ArgumentParser()
    parser.add_argument('-w', '--width', dest='width', default='800',
                        help='width of the generated noise')
    parser.add_argument('-H', '--height', dest='height', default='600',
                        help='height of the generated noise')
    parser.add_argument('-n', '--name', dest='name', default='Test.pdf',
                        help='the name of the generated image')
    parser.add_argument('-g', '--grid-size', dest='grid_size', default='400',
                        help='the starting grid size for octave 0.')
    parser.add_argument('-o', '--octaves', dest='octaves', default='4',
                        help='the number of octaves to create from.')
    parser.add_argument('-s', '--seed', dest='seed', default='133742069',
                        help='the seed to use for the sampling. ')
    args = parser.parse_args()

    # dimenins of the window to create the noise for
    width: int = int(args.width)
    height: int = int(args.height)

    # starting grid size 
    grid_size: int = float(args.grid_size)
    octaves: int = int(args.octaves)

    # seed for the random number generator
    seed: int = int(args.seed)

    noise = perlin_noise(width, height, grid_size=grid_size,
                         octaves=octaves, seed=seed)

    if args.name is not None and args.name == '':
        print('No name provided, exiting!')
        return None

    if 'txt' in args.name:
        np.savetxt(args.name, noise)
        print(f'saved txt output {args.name}.')
        return noise
    
    fig, ax = plt.subplots()
    mappable = plt.imshow(noise, cmap='gray')
    fig.colorbar(mappable)
    fig.savefig(args.name)
    print(f'saved file with name: {args.name}' )
    return noise


if __name__ == '__main__':
    main()
