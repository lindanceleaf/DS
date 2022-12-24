def find(t):
    s = 0
    while t // 3 != 0:
        s += t // 3
        t = t // 3 + t % 3
    return [s, t]

t = int(input())
num = find(t)[0]
if t % 3 == 2:
    temp = find(t + 1)
    if temp[1] >= 1 and temp[0] > num:
        num = temp[0]

print(num)