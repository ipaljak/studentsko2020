#!/usr/bin/python3
"""Upotreba ./validate3.py test/*.in*"""

import string


def check(lines):
    nl = []   # ispravno formatirane linije
    E = "\n"  # line ending

    n, m = map(int, lines[0].split())
    assert 2 <= n <= 10**5, "n kriv"
    assert 1 <= n <= 10**5, "n kriv"
    nl.append("{} {}{}".format(n, m, E))

    d = list(map(int, lines[1].split()))
    assert len(d) == m, "duljina niza d je kriva"
    assert min(d) >= 0 and max(d) <= 10**7, "di kriv"
    nl.append("{}{}".format(' '.join(list(map(str, d))), E))

    pos = []
    cost = []
    for i in range(n):
        pi, ci = map(int, lines[2 + i].split())
        assert 0 <= pi <= 10**7, "pi kriv"
        assert -10**12 <= ci <= 10**12, "ci kriv"
        nl.append("{} {}{}".format(pi, ci, E))

    assert pos == sorted(pos), "pos nije sortiran"
    assert list(set(pos)) == pos, "pos sadrzi duplikate"

    assert lines == nl, "Krivi format (%s vs %s)" % (lines, nl)
    assert lines[-1][-1] == "\n", "Zadnji red ne zavrsava sa \\n"
    return {'n': n, 'm': m}


# Ocekivani clusteri! Ovo vjerojatno zelis promijeniti!
expected_clusters = {'Normalni': 20}


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
