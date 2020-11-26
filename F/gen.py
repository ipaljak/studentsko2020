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

PROBLEM = "F"
sys.setrecursionlimit(1000010)

MAXN = 100000

class Test(object):
    def __init__(self, n, r, p):
        self.n = n    # number of points
        self.r = r    # circle radius
        self.p = p    # list of points


    def validate(self):
        assert(1 <= self.n <= MAXN)
        assert(1 <= self.r <= 10**9)
        assert(len(self.p) == self.n)
        assert(len(set(self.p)) == self.n)

        for (x, y) in self.p:
            assert(-10**9 <= x <= 10**9)
            assert(-10**9 <= y <= 10**9)


    def write(self, fd=sys.stdout):
        print>>fd, self.n, self.r
        for (x, y) in self.p:
            print>>fd, x, y


def remove_cases():
    cases = glob.glob('test/%s.dummy.in.*' % PROBLEM)
    cases += glob.glob('test/%s.dummy.out.*' % PROBLEM)
    cases += glob.glob('test/%s.in.*' % PROBLEM)
    cases += glob.glob('test/%s.out.*' % PROBLEM)
    for c in cases:
        print>>sys.stderr, 'Removing ' + c
        os.remove(c)


def gen_rand(n, r, xmin, xmax, ymin, ymax):
    points = set()
    while n > 0:
        x = random.randint(xmin, xmax)
        y = random.randint(ymin, ymax)
        if (x, y) in points: continue
        points.add((x, y))
        n -= 1

    return Test(len(points), r, list(points))


def gen_cases():
    remove_cases()

    real = []
    dummy = []

    dummy.append(Test(
        4, 3,
        [(1, 2), (-2, 3), (-1, -2), (3, 3)]
    ))

    dummy.append(Test(
        9, 2,
        [(1, 1), (-3, 0), (-3, -2), (-2, 1), (1, -2), (3, 3), (-2, 4), (-1, 1), (-2, -2)]
    ))

    for i, test in enumerate(dummy):
        test.validate()
        print>>sys.stderr, 'Generating test/%s.dummy.in.%d' % (PROBLEM, i+1)
        test.write(file('test/%s.dummy.in.%d' % (PROBLEM, i+1), 'wt'))

    real.append(Test(
        1, 3,
        [(-1, 3)]
    ))

    real.append(Test(
        1, 7,
        [(5, -7)]
    ))

    real.append(Test(
        1, 9,
        [(2, -4)]
    ))

    real.append(Test(
        1, 42,
        [(2, -43)]
    ))

    real.append(gen_rand(100000, 100, -100000, 100000, -150, 150))
    real.append(gen_rand(100000, 1000, -100000, 100000, -1500, 1500))
    real.append(gen_rand(100000, 1000, -100, 100, -1500, 1500))
    real.append(gen_rand(100000, 100000, -200000, 200000, 0, 0))
    real.append(gen_rand(100000, 100000, -1000, 1000, -200000, 200000))
    real.append(gen_rand(100000, 100000, -50, 50, -200000, 200000))
    real.append(gen_rand(100000, 100000, -200000, 200000, -200000, 200000))
    real.append(gen_rand(100000, 100000000, -1000, 1000, -200000000, 200000000))
    real.append(gen_rand(100000, 100000000, -100, 100, -200000000, 200000000))
    real.append(gen_rand(100000, 100000000, -100000000, 100000000, -200000000, 200000000))
    real.append(gen_rand(100000, 100000000, -150000000, 150000000, -200000000, 200000000))
    real.append(gen_rand(100000, 100000000, -1000000000, 1000000000, -200000000, 200000000))
    real.append(gen_rand(100000, 1000000000, -1000000000, 1000000000, 0, 0))
    real.append(gen_rand(100000, 1000000000, -1000000000, 1000000000, -1000000000, 1000000000))

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

