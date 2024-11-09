import math
def funk(k):
    
    return(5*math.sin(k)*math.cos(1)+math.sin(k)**2+k)

a=0.1
y=1
dw=1
wer=3
d=1
u=0
dwlast=0


while (dw)**2>0.0000000000000001:
    grad=(funk(wer+0.001)-funk(wer))/0.001
    dw=-a*grad
    if round(math.fabs(dw)/dw)!=round(d):
        a=a/2
        u+=1
    d=math.fabs(dw)/dw
    wer+=dw
    print(dw,funk(wer),"   ",a,"    ",u)
    dwlast=dw
dw=int( input())
