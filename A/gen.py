#!/usr/bin/python2

doc = """
  Cenerate all test cases in test/:  gen.py
"""

import collections
import sys
import glob
import os
import random
import subprocess
import math

PROBLEM = "A"
sys.setrecursionlimit(1000010)

MAXN = 5000

class Test(object):
    def __init__(self, n, xs, ys):
        self.n = n    # number of points
        self.xs = xs  # x coordinates
        self.ys = ys  # y coordinates


    def validate(self):
        assert(1 <= self.n <= MAXN)
        assert(len(self.xs) == self.n)
        assert(len(self.ys) == self.n)

        points = set()
        for i in range(self.n):
            assert(-500 <= self.xs[i] <= 500)
            assert(-500 <= self.ys[i] <= 500)
            points.add((self.xs[i], self.ys[i]))

        assert(len(points) == self.n)


    def write(self, fd=sys.stdout):
        print>>fd, self.n
        for (x, y) in zip(self.xs, self.ys):
            print>>fd, x, y


def remove_cases():
    cases = glob.glob('test/%s.dummy.in.*' % PROBLEM)
    cases += glob.glob('test/%s.dummy.out.*' % PROBLEM)
    cases += glob.glob('test/%s.in.*' % PROBLEM)
    cases += glob.glob('test/%s.out.*' % PROBLEM)
    for c in cases:
        print>>sys.stderr, 'Removing ' + c
        os.remove(c)


def gen_rand(n, quad, orig):
    points = set()

    if orig == True:
        points.add((0, 0))
        n = n - 1

    while n > 0:
        x = random.randint(1, 500)
        y = random.randint(1, 500)
        k = random.randint(0, len(quad) - 1)
        x *= quad[k][0]
        y *= quad[k][1]
        if (x, y) in points: continue
        points.add((x, y))
        n -= 1

    xs = []
    ys = []
    for (x, y) in points:
        xs.append(x)
        ys.append(y)

    return Test(len(points), xs, ys)


def gen_cases():
    remove_cases()

    real = []
    dummy = []

    dummy.append(Test(
        2,
        [1, -3],
        [1, -1]
    ))

    dummy.append(Test(
        6,
        [-5, -3, -1, 1, 3, 5],
        [0, 0, 0, 0, 0, 0]
    ))

    dummy.append(Test(
        20,
        [-1, -1, -1, -2, -2, -3, -3, -4, -4, -4, 1, 1, 1, 1, 2, 2, 3, 3, 4, 4],
        [1, 2, 3, 2, 4, 2, 4, 1, 2, 3, -1, -2, -3, -4, -1, -4, -1, -4, -1, -4]
    ))

    for i, test in enumerate(dummy):
        test.validate()
        print>>sys.stderr, 'Generating test/%s.dummy.in.%d' % (PROBLEM, i+1)
        test.write(file('test/%s.dummy.in.%d' % (PROBLEM, i+1), 'wt'))

    real.append(Test(
        1,
        [0],
        [0]
    ))

    real.append(Test(
        1,
        [3],
        [7]
    ))

    real.append(Test(
        1,
        [-4],
        [2]
    ))

    real.append(Test(
        1,
        [6],
        [-13]
    ))

    real.append(Test(
        1,
        [-5],
        [-1]
    ))

    # x-os + ishodiste
    real.append(gen_rand(100, [(1, 0), (-1, 0)], True))

    # x-os
    real.append(gen_rand(100, [(1, 0), (-1, 0)], False))

    # y-os + ishodiste
    real.append(gen_rand(100, [(0, 1), (0, -1)], True))

    # y-os
    real.append(gen_rand(100, [(0, 1), (0, -1)], False))

    # osi + ishodiste
    real.append(gen_rand(200, [(1, 0), (-1, 0), (0, 1), (0, -1)], True))

    # osi
    real.append(gen_rand(200, [(1, 0), (-1, 0), (0, 1), (0, -1)], False))

    # po jedan kvadrant
    real.append(gen_rand(5000, [(1, 1)], False))
    real.append(gen_rand(5000, [(-1, 1)], False))
    real.append(gen_rand(5000, [(1, -1)], False))
    real.append(gen_rand(5000, [(-1, -1)], False))

    # po dva kvadranta bez dijagonala
    real.append(gen_rand(5000, [(1, 1), (1, -1)], False))
    real.append(gen_rand(5000, [(1, -1), (-1, -1)], False))
    real.append(gen_rand(5000, [(-1, -1), (-1, 1)], False))
    real.append(gen_rand(5000, [(-1, 1), (1, 1)], False))

    # sve zivo
    for i in range(3):
        real.append(gen_rand(5000, [(1, 1), (1, -1), (-1, 1), (-1, -1), (0, 1), (1, 0), (0, -1), (-1, 0)], True))
        real.append(gen_rand(5000, [(1, 1), (1, -1), (-1, 1), (-1, -1), (0, 1), (1, 0), (0, -1), (-1, 0)], False))

    for i, test in enumerate(real):
        test.validate()
        print>>sys.stderr, 'Generating test/%s.in.%d' \
                % (PROBLEM, i+1)
        input = 'test/%s.in.%d' % (PROBLEM, i+1)
        test.write(file(input, 'wt'))


def main():
    random.seed(293487)
    gen_cases()


if __name__ == "__main__":
    main()

