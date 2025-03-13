import sys
input = sys.stdin.readline
N = int(input())
a = input()
b = input()

res = 0
flg = False

for i in range(N):
    if a[i] != b[i]:
        if not flg:
            flg = True
            res += 1
    else:
        flg = False
print(res)