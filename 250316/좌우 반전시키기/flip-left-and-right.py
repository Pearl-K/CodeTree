import sys
input = sys.stdin.readline
n = int(input())
arr = list(map(int, input().split()))
res =0

for i in range(1, n):
    if arr[i-1]==0:
        res += 1
        arr[i-1] = 1
        arr[i] ^=1 #bit check

        if i+1 <n:
            arr[i+1] ^= 1

# impossible case
if arr[n-1] == 0:
    res = -1
print(res)