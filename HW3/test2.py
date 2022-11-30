import math
e = math.e
RL = 205.47
L = 0.05

Vi = float(input("Vi = "))
Vf = float(input("Vf = "))
V = (Vi + Vf) / 2

Vs = float(input("Vpp = ")) / 2
R = int(input("R = "))
detect = input("R/L : ")

if detect == 'L':
    a = Vs
    b = RL / (R + RL)
    x = (V - a * b) / (a - a * b)
    tau = L / (R + RL)
    t = -tau * math.log(x, e) * (10 ** 6)
    print(t)
else:
    a = Vs
    b = R / (R + RL)
    x = 1 - (V / (a * b))
    tau = L / (R + RL)
    t = -tau * math.log(x, e) * (10 ** 6)
    print(t)