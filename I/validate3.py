#!/usr/bin/python3
"""Upotreba ./validate3.py test/*.in*"""

import string


def check(lines):
    nl = []   # ispravno formatirane linije
    E = "\n"  # line ending

    t = int(lines[0])
    assert 1 <= t <= 100, "t kriv"
    nl.append("{}{}".format(t, E))

    n_sum = 0
    for i in range(t):
        n = int(lines[2 * i + 1])
        assert 1 <= n <= 10000, "n kriv"
        nl.append("{}{}".format(n, E))
        n_sum += n
        c = list(map(int, lines[2 * i + 2].split()))
        assert len(c) == n, "duljina liste kriva"
        assert c[0] == 1, "kriva prva kovanica"
        for j in range(1, n):
            assert c[j - 1] < c[j], "kovanice nisu sortane"
            assert 1 <= c[j] <= 10000, "kovanica izvan intervala"
        nl.append("{}{}".format(' '.join(list(map(str, c))), E))

    assert 1 <= n_sum <= 10000, "kriva suma n-ova"

    assert lines == nl, "Krivi format (%s vs %s)" % (lines, nl)
    assert lines[-1][-1] == "\n", "Zadnji red ne zavrsava sa \\n"
    return {'t': t, 'n_sum': n_sum}


# Ocekivani clusteri! Ovo vjerojatno zelis promijeniti!
expected_clusters = {'Normalni': 10}


def what_cluster(data):
    # na temelju povratne informacije iz check(lines)
    # zakljucuje za TP u kojoj je bodovnoj sekciji
    return 'Normalni'


################### Zadatak-specifican kod iznad ove linije #########################

import sys
import glob
import hashlib


def group_in_batches(files):
    # mnozenje.in.1a, mnozenje.in.1b sprema u isti batch

    files.sort()
    B = []
    for f in files:
        if f[-1].islower() and len(B) > 0 and f[:-1] == B[-1][-1][:-1]:
            B[-1].append(f)
        else:
            B.append([f])
    return B


if __name__ == "__main__":
    f = []
    for pattern in sys.argv[1:]:
        for filename in glob.glob(pattern):
            f.append(filename)

    bc = []
    for batch in group_in_batches(f):
        if 'dummy' not in batch[0]:
            bc.append([])
        for filename in batch:
            print("{}: ".format(filename), end="")
            try:
                lines = open(filename).readlines()
                summary = check(lines)
                c = what_cluster(summary)
                if 'dummy' not in batch[0]:
                    bc[-1].append(c)
            except Exception as e:
                print("Greska!", e)
                raise
            else:
                print("Sve ok! (cluster {}, summary = {})".format(c, summary))

    clusters = {}
    for b in bc:
        for c in b:
            assert c == b[0], "Ima razlicitih cluster-a unutar batcha"
        if not b[0] in clusters:
            clusters[b[0]] = 0
        clusters[b[0]] += 1

    assert clusters == expected_clusters, "Kriva raspodjela clustera ({} vs {})".format(clusters, expected_clusters)

    # Buda test - provjeri duplikate
    hashes = set(hashlib.sha1(open(x, 'rb').read()).hexdigest() for x in f)
    assert len(hashes) == len(f), "Ima duplikata!"
