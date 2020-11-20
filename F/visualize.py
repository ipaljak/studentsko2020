#!/usr/bin/python3

import sys
import matplotlib.pyplot as plt

def main():
    lines = sys.stdin.readlines()
    xc, yc, r = map(float, lines[0].split())
    n = int(lines[1])
    x, y = [], []
    for i in range(n):
        xx, yy = map(float, lines[2 + i].split())
        x.append(xx)
        y.append(yy)

    circle = plt.Circle((xc, yc), r, color='y', alpha=0.35)

    fig, ax = plt.subplots()

    ax.set_aspect('equal', adjustable='box')

    ax.set_xlim((-5, 5))
    ax.set_ylim((-5, 5))

    ax.add_artist(circle)

    rng = range(-5, 6)
    plt.yticks(rng)
    plt.xticks(rng)

    plt.axhline(0, color='black', alpha=0.6)

    plt.scatter(x, y)
    plt.scatter([xc], [yc], color='r')
    plt.show()


if __name__ == "__main__":
    main()
