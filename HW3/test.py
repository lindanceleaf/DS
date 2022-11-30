import math
e = math.e
RL = 205.47
L = 0.05

def VR_inf(Vs, R):
    V = Vs * (R / (R + RL))
    print(V)

def VL_inf(Vs, R):
    V = Vs * (RL / (R + RL))
    print(V)

def VR(t, Vs, R):
    tau = L / (R + RL)
    temp = e ** (-t / tau)
    V = Vs * (R / (R + RL)) * (1 - temp)
    print(V)

def VL(t, Vs, R):
    tau = L / (R + RL)
    temp = e ** (-t / tau)
    V = Vs * (RL / (R + RL)) * (1 - temp) + Vs * temp
    print(V)

Vs = float(input("Vpp : ")) / 2
R = int(input("R : "))
detect = input("R/L : ")
if detect == "R":
    print("tau = ", end='')
    print((L / (R + RL)) * (10 ** 6))
    print("VRi = ", end='')
    VR(0, Vs, R)
    print("VRf = ", end='')
    VR_inf(Vs, R)
else:
    print("tau = ", end='')
    print((L / (R + RL)) * (10 ** 6))
    print("VLi = ", end='')
    VL(0, Vs, R)
    print("VLf = ", end='')
    VL_inf(Vs, R)
