#!/usr/bin/python2

doc = """
  Cenerate all test cases in test/:  gen.py
"""

import sys
import glob
import os
import random
import subprocess

PROBLEM = "H"
sys.setrecursionlimit(1000010)

MAXN = 100000
MAXK = 3000000

class Test(object):
    def __init__(self, n, c, e):
        self.n = n # number of vertices
        self.c = c # colors of vertices
        self.e = e # list of edges [(1, 2), (4, 5), ...]


    def permute_indexes():
        pass


    def validate(self):
        assert(1 <= self.n <= MAXN)
        assert(len(self.c) == self.n)
        assert(0 <= min(self.c) and max(self.c) <= 1)
        assert(len(self.e) == self.n - 1)
        adj = [[] for x in range(0, self.n + 1)]
        for a, b in self.e:
            assert(1 <= a and a <= self.n)
            assert(1 <= b and b <= self.n)
            assert(a != b)
            adj[a].append(b)
            adj[b].append(a)

        bio = {}
        def dfs(x, dad):
            bio[x] = True
            for y in adj[x]:
                if y == dad:
                    continue
                assert(y not in bio)
                dfs(y, x)
        dfs(1, -1)
        for x in range(1, self.n + 1):
            assert(x in bio)


    def write(self, fd=sys.stdout):
        print>>fd, self.n
        print>>fd, ' '.join(map(str, self.c))
        for a, b in self.e:
            print>>fd, a, b


def remove_cases():
    # cases = glob.glob('test/%s.dummy.in.*' % PROBLEM)
    # cases += glob.glob('test/%s.dummy.out.*' % PROBLEM)
    cases = glob.glob('test/%s.in.*' % PROBLEM)
    cases += glob.glob('test/%s.out.*' % PROBLEM)
    for c in cases:
        print>>sys.stderr, 'Removing ' + c
        os.remove(c)


def gen_random(n):
    c = [random.randint(0, 1) for x in range(n)]
    e = [(x, random.randint(1, x - 1)) for x in range(2, n + 1)]
    return Test(n, c, e)


def gen_deep(n, sw):
    c = [random.randint(0, 1) for x in range(n)]
    e = [(x, random.randint(max(1, x - sw), x - 1)) for x in range(2, n + 1)]
    return Test(n, c, e)


def gen_star(n):
    c = [random.randint(0, 1) for x in range(n)]
    e = [(x, 1) for x in range(2, n + 1)]
    return Test(n, c, e)


def gen_chain(n):
    return gen_deep(n, 1)


def gen_cases():
    remove_cases()

    real = []

    for i in range(5):
        print(i)
        real.append(gen_chain(50000))

    for i in range(5):
        print(i)
        real.append(gen_chain(100000))

    for i in range(15):
        print(i)
        real.append(gen_random(100000))

    for i in range(1, 6):
        print(i)
        real.append(gen_deep(100000, 5*i))

    for i, test in enumerate(real):
        test.validate()
        print>>sys.stderr, 'Generating test/%s.in.%d' % (PROBLEM, i+1)
        input = 'test/%s.in.%d' % (PROBLEM, i+1)
        test.write(file(input, 'wt'))


def main():
    random.seed(293487)
    gen_cases()


if __name__ == "__main__":
    main()
