"""
# 한국정보올림피아드, KOI 2006, 고등부 3. 마법 구슬
# BOJ 2301
# JUNGOL 1211
#
# DnC
# Date: 2024.3.28
"""

from sys import stdout

def dnc(n, k, arr):
    if n == 2:
        stdout.write(f"{arr[k]} {arr[k^1]} ")
        return k^1
    else:
        n2, n4 = n//2, n//4
        in_arr, out_arr = arr[n4:-n4], arr[:n4] + arr[-n4:]
        def to_in_k(k):
            return k - n4
        def from_in_k(k):
            return k + n4
        def to_out_k(k):
            return k if k < n2 else k - n2
        def from_out_k(k):
            return k if k < n4 else k + n2

        if n4 <= k < n-n4:
            k = from_in_k(dnc(n2, to_in_k(k), in_arr))
            k = k ^ n2
            k = from_out_k(dnc(n2, to_out_k(k), out_arr))
        else:
            k = from_out_k(dnc(n2, to_out_k(k), out_arr))
            k = k ^ n2
            k = from_in_k(dnc(n2, to_in_k(k), in_arr))
        return k

def main():
    n = int(input())
    k = int(input()) - 1
    arr = [i for i in range(1, n+1)]
    dnc(n, k, arr)

if __name__ == "__main__":
    main()
