import os
import argparse
import numpy as np
import matplotlib.pyplot as plt


def main() -> None:
    parser = argparse.ArgumentParser()
    parser.add_argument('-n', '--name', dest='name', required=True,
                        help='name for the file to load the data from.')
    parser.add_argument('-s', '--save', dest='save', default=None,
                        help='name to save the plot under if desired. ')
    args = parser.parse_args()

    if not os.path.exists(args.name):
        raise FileNotFoundError(f'No such file or directory: {args.name}')

    if args.name.endswith('.txt'):
        data = np.genfromtxt(args.name)
    elif args.name.endswith('.npy'):
        data = np.load(args.name)
    else:
        raise ValueError(f'File type not understood: {args.name}')
    yy, xx = data.shape
    fig, ax = plt.subplots(figsize=(xx / 170, yy / 170), subplot_kw={"projection": "3d"})

    xs = np.linspace(0, xx - 1, xx)
    ys = np.linspace(0, yy - 1, yy)
    xs, ys = np.meshgrid(xs, ys)
    surf = ax.plot_surface(xs, ys, data, cmap='viridis')
    ax.contour(xs, ys, data, 10, cmap='viridis', linestyles='solid', offset=-1)

    ax.set_xticks([])
    ax.set_yticks([])
    ax.set_zticks([])
    fig.colorbar(surf)
    plt.show()
    if args.save is None:
        return None
    fig.savefig(f'plots/{args.save}')
    print(f'saved plots/{args.save}')
    return None


if __name__ == '__main__':
    main()
