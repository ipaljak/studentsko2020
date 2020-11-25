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

PROBLEM = "K"
sys.setrecursionlimit(1000010)

MAXN = 500000

class Test(object):
    def __init__(self, n, a, b, p):
        self.n = n    # number of people
        self.a = a    # with mask
        self.b = b    # without mask
        self.p = p    # thresholds


    def validate(self):
        assert(1 <= self.n <= MAXN)
        assert(0 <= self.a <= 10**9)
        assert(0 <= self.b <= 10**9)
        assert(len(self.p) == self.n)
        for i in range(self.n):
            assert(0 <= self.p[i] <= 100)


    def write(self, fd=sys.stdout):
        print>>fd, self.a, self.b
        print>>fd, self.n
        for pi in self.p:
            print>>fd, "{:.2f}%".format(pi)


def remove_cases():
    cases = glob.glob('test/%s.dummy.in.*' % PROBLEM)
    cases += glob.glob('test/%s.dummy.out.*' % PROBLEM)
    cases += glob.glob('test/%s.in.*' % PROBLEM)
    cases += glob.glob('test/%s.out.*' % PROBLEM)
    for c in cases:
        print>>sys.stderr, 'Removing ' + c
        os.remove(c)


def gen_rand(n, a, b):
    p = []
    for i in range(n):
        p.append(random.random() * 100)
    return Test(n, a, b, p)


def gen_cases():
    remove_cases()

    real = []
    dummy = []

    dummy.append(Test(
        1, 5, 5,
        [51.05]
    ))

    dummy.append(Test(
        2, 4, 6,
        [0.00, 45.00]
    ))

    dummy.append(Test(
        6, 11, 19,
        [96.47, 30.66, 77.61, 26.20, 36.54, 60.57]
    ))

    for i, test in enumerate(dummy):
        test.validate()
        print>>sys.stderr, 'Generating test/%s.dummy.in.%d' % (PROBLEM, i+1)
        test.write(file('test/%s.dummy.in.%d' % (PROBLEM, i+1), 'wt'))

    for n in [50, 500, 5000, 50000, 500000]:
        real.append(gen_rand(n, 0, 0))
        for i in range(4):
            real.append(gen_rand(n, random.randint(0, 10**9), random.randint(0, 10**9)))

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

