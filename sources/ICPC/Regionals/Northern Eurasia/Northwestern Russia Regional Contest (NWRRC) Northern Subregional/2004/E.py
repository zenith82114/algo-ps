"""
# ICPC, Regionals, Northern Eurasia,
# Northwestern Russia Regional Contest Northern Subregional 2004 E. Ellipse
# BOJ 7463 - linear algebra
# Date: 2026.1.4
"""

def main() -> None:
    import sys
    rd = lambda: sys.stdin.readline().rstrip()
    import decimal
    EPS = decimal.Decimal('1e-20')
    PI = decimal.Decimal('3.141592653589793')

    def gauss_jordan(A):
        pivot_row = 0
        pivots = []

        for col in range(6):
            if pivot_row >= 5:
                break

            max_val = decimal.Decimal(0)
            max_row = -1
            for row in range(pivot_row, 5):
                if max_val < abs(A[row][col]):
                    max_val = abs(A[row][col])
                    max_row = row
            if max_val < EPS:
                continue

            A[pivot_row], A[max_row] = A[max_row], A[pivot_row]
            pivots.append((pivot_row, col))
            pivot_val = A[pivot_row][col]

            for j in range(col, 6):
                A[pivot_row][j] /= pivot_val

            for i in range(5):
                if i == pivot_row:
                    continue
                factor = A[i][col]
                if abs(factor) < EPS:
                    continue
                for j in range(col, 6):
                    A[i][j] -= factor * A[pivot_row][j]

            pivot_row += 1

        pivot_cols = set(j for _, j in pivots)
        free_col = -1

        for j in reversed(range(6)):
            if j not in pivot_cols:
                free_col = j
                break
        assert free_col != -1

        x = [decimal.Decimal(0)] * 6
        x[free_col] = decimal.Decimal(1)

        for i, j in reversed(pivots):
            for k in range(j + 1, 6):
                x[j] -= A[i][k] * x[k]

        return x

    for _ in range(int(rd())):
        it = iter(map(decimal.Decimal, rd().split()))

        A = []
        for _ in range(5):
            x, y = next(it), next(it)
            A.append([x*x, x*y, y*y, x, y, decimal.Decimal(1)])

        a, b, c, d, e, f = gauss_jordan(A)

        D = 4*a*c - b**2
        if D < EPS:
            print("IMPOSSIBLE")
        else:
            det_M = (2*a) * ( (2*c)*(2*f) - e*e ) \
                    - (b) * ( (b)*(2*f)   - e*d ) \
                    + (d) * ( (b)*e   - (2*c)*d )
            if abs(det_M) < EPS:
                print("IMPOSSIBLE")
            else:
                ans = (PI * abs(det_M)) / (D * D.sqrt())
                print(f"{ans:.10f}")


if __name__ == "__main__":
    main()
