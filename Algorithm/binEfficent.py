import sys
input = sys.stdin.readline

N, K = map(int, input().split())

pascal = [0]
for depth in range(2, N+2):
    pascal.append([0]*depth)

pascal[1] = [1, 3]
pascal[2] = [1, 3, 3]
for depth in range(3, N):
    pascal[depth][0] = 1
    pascal[depth][1] = 3
    for idx in range(3, depth):
        pascal[depth][idx] = (pascal[depth-1][idx-1] + 2*pascal[depth-1][idx])%10000
    pascal[depth][-1] = 3

print((pascal[N-1][K-1] + 2*pascal[N-1][K])%10000)