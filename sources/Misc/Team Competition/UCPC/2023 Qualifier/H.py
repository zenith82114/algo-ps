"""
# UCPC 2023 Qualifier H. 팔찌
# BOJ 28302
#
# ad-hoc
# Date: 2024.1.17
"""

import sys

def merge_bead(x, y):
    return 3-x-y

def split_bead(x):
    return (x+1)%3, (x+2)%3

def reduce(n: int, s: list):
    cmd = []
    while n > 2:
        # case xy
        if s[-2] != s[-1]:
            x, y = s[-2], s[-1]
            s[-2:] = [merge_bead(x, y)]
            cmd.append( (1, n-1, x, y) )
            n -= 1
        # case xxx
        elif s[-3] == s[-1]:
            x = s[-1]
            y, z = split_bead(x)
            s[-3:-2] = [y, z]
            cmd.append( (2, n-2, y, z) )
            n += 1
        # case xyy
        else:
            x, y = s[-3], s[-2]
            s[-3:-1] = [merge_bead(x, y)]
            cmd.append( (1, n-2, x, y) )
            n -= 1
    if n == 2 and s[0] != s[1]:
        x, y = s
        s = [merge_bead(x, y)]
        cmd.append( (1, 1, x, y) )
    return s, cmd

if __name__ == "__main__":
    d = { 'R':0, 'G':1, 'B':2 }
    n, s = input().split()
    n = int(n)
    s = list(d[c] for c in s)
    m, t = input().split()
    m = int(m)
    t = list(d[c] for c in t)

    s, cmd_s = reduce(n, s)
    t, cmd_t = reduce(m, t)

    if len(s) != len(t):
        print("-1\n")
        exit(0)
    if len(s) == 1 and s[0] != t[0]:
        print("-1\n")
        exit(0)
    if len(s) == 2 and s[0] != t[0]:
        x, y = s[0], t[0]
        z = merge_bead(x, y)
        cmd_s.append( (2, 1, y, z) )
        cmd_s.append( (1, 2, z, x) )

    sys.stdout.write(f"{len(cmd_s) + len(cmd_t)}\n")
    for op, a, x, y in cmd_s:
        if op == 1:
            sys.stdout.write(f"1 {a} {a+1}\n")
        else:
            sys.stdout.write(f"2 {a} {'RGB'[x]} {'RGB'[y]}\n")
    for op, a, x, y in reversed(cmd_t):
        if op == 2:
            sys.stdout.write(f"1 {a} {a+1}\n")
        else:
            sys.stdout.write(f"2 {a} {'RGB'[x]} {'RGB'[y]}\n")
