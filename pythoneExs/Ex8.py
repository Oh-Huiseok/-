
A = []
A.append(3)
n = int(input())

for i in range(0, n):
    A.append(0)
    for j in range(0, i+1):
        A[i+1]+=A[j]*A[i-j]
    A[i+1]%=1000
    print(A[i])

print(A[n])