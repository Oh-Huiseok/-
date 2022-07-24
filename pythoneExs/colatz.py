def collatz(n):
    seq = [n]       # 수 들을 담을 리스트
    
    while n > 1:
        if n % 2 == 0:        # n이 짝수일때
            n = n // 2
        else:                 # n이 홀수일때
            n = 3 * n - 1
            
        seq.append(n)
        
    return seq
    
max = 0
c_length = 0

for n in range(1, 1000):
    if len(collatz(n)) > c_length:     # 콜라츠 수열의 길이가 가장 길면
        max = n                        # 가장 긴 수를 바꿔준다.
        c_length = len(collatz(n))     # 길이의 값을 바꿔준다.
    
print('콜라츠 수열의 길이가 가장 긴 수 :', max)
print('길이 :', c_length)