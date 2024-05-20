import numpy as np
import matplotlib.pyplot as plt

# Random number generator
rng = np.random.default_rng(seed=1337)

def random_gradient():
    angle = rng.uniform(0, 2 * np.pi)
    return np.array([np.cos(angle), np.sin(angle)])

# Cache for gradient vectors
gradient_cache = {}

def get_gradient(x, y):
    if (x, y) not in gradient_cache:
        gradient_cache[(x, y)] = random_gradient()
    return gradient_cache[(x, y)]

def fade(t):
    return t * t * t * (t * (t * 6 - 15) + 10)

def lerp(a, b, t):
    return a + t * (b - a)

def dot_grid_gradient(ix, iy, x, y):
    gradient = get_gradient(ix, iy)
    dx = x - ix
    dy = y - iy
    return dx * gradient[0] + dy * gradient[1]

def perlin(x, y):
    x0 = int(x)
    x1 = x0 + 1
    y0 = int(y)
    y1 = y0 + 1

    sx = fade(x - x0)
    sy = fade(y - y0)

    n0 = dot_grid_gradient(x0, y0, x, y)
    n1 = dot_grid_gradient(x1, y0, x, y)
    ix0 = lerp(n0, n1, sx)

    n0 = dot_grid_gradient(x0, y1, x, y)
    n1 = dot_grid_gradient(x1, y1, x, y)
    ix1 = lerp(n0, n1, sx)

    value = lerp(ix0, ix1, sy)
    return value

def generate_perlin_noise(width, height, scale, octaves):
    noise = np.zeros((height, width))
    frequency = 1.0
    amplitude = 1.0
    max_value = 0.0
    
    for _ in range(octaves):
        for y in range(height):
            for x in range(width):
                nx = x / scale * frequency
                ny = y / scale * frequency
                noise[y, x] += perlin(nx, ny) * amplitude
        
        max_value += amplitude
        amplitude /= 2
        frequency *= 2
    
    max_noise = np.max(abs(noise))
    noise /= max_noise
    return noise

def display_noise(noise):
    plt.imshow(noise, cmap='gray')
    plt.colorbar()
    plt.show()

def main() -> None:
    # Example usage
    width, height = 800, 600
    scale = 400.0
    octaves = 4
    noise = generate_perlin_noise(width, height, scale, octaves)
    display_noise(noise)
    return None 


if __name__ == '__main__':
    main()
