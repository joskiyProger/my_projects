from numpy import *
import matplotlib.pyplot as plt
from scipy.optimize import fsolve

def DE(v):
        v0=1.04
        return 1+2*abs(v/v0)**3-3*(v/v0)**2 if (v / v0) ** 2 < 1 else 0

def G2(r):
    kj = 2.46
    return (exp(-kj*r**2)-exp(-kj))/(1-exp(-kj)) if (r) ** 2 < 1 else 0

ay=0*pi/180 # angle between nozzle axis and z-axis
fi=-90*pi/180 #angle between projection of nozzle axis on xy-plane and x-axis
L0=30 #distance between nozzle exit and xy-plane along nozzle axis, mm
Re=3.25 #nozzle exit radius, mm
Rm=4 #powder jet radius at the distance Zon1, mm
Zon1=30 #distance from nozzle exit along nozzle axis where powder jet radius is equal to Rm
bx=sin(ay)*cos(fi) #components of nozzle axis vector directed from substrate to nozzle
by=sin(ay)*sin(fi)
bz=cos(ay)
'''def ron(x,y,z):
    return sqrt((x*bz-z*bx)**2+(y*bz-z*by)**2+(x*by-y*bx)**2)
def zon(x,y,z):
    return L0-x*bx-y*by-z*bz
def rj(x,y,z):
    return Re+(Rm-Re)*zon(x,y,z)/Zon1
def Hp3(x,y,z):
    Rj=rj(x,y,z)
    return G2(ron(x,y,z)/Rj)*(Re/Rj)**2'''

def Hp(x,y,z):
    Ron=sqrt((x * bz - z * bx) ** 2 + (y * bz - z * by) ** 2 + (x * by - y * bx) ** 2)
    Zon=L0 - x * bx - y * by - z * bz
    Rj=Re+(Rm-Re)*Zon/Zon1
    return G2(Ron/Rj)*(Re/Rj)**2

def Hp1(x):
    return Hp(x,0,0)
def Hp2(x):
    return Hp(0,x,0)
w2=fsolve(Hp1,Rm)
w3=fsolve(Hp2,Rm)
w1=Rm*sqrt(cos(fi)**2/cos(ay)**2+sin(fi)**2)
print("w1=%f, w2=%f, w3=%f",w1,w2,w3)

def rp(u,v):
    ub=bz-u*bx-v*by
    cb=ub/sqrt(1+u**2+v**2)
    tb=sqrt(1/cb**2-1)
    return DE(tb)*ub

za1=0.04
za2=1.3*za1
def tet(x):
    if za1==0: return 1
    elif x<za1: return 0
    elif x>za2: return 1
    else: return 0.5*(1+sin(pi*(2*(x-za1)/(za2-za1)-1)/2))

'''N2=10
x1=linspace(za1,za2,N2)
g3=linspace(za1,za2,N2)
for i in range (len(x1)):
    g3[i]=tet(x1[i])
plt.plot(x1,g3)
plt.show()
'''
'''N1=100
a=-6
b=6
v=linspace(a,b,N1)
g1=linspace(a,b,N1)
g2=linspace(a,b,N1)
for i in range (len(v)):
    g1[i]=Hp(0,v[i],0)
    g2[i] = Hp(v[i],0, 0)
plt.plot(v,g1)
plt.plot(v,g2)
plt.show()
'''

Mi=351 # number of x-steps
Mj=161 #of y-steps
Lx=35 #calc domain size along x-axis, mm
Ly=16 #domain size along y-axis, mm
dx=Lx/(Mi-1) #step along x and y
#print(dx)
fip=0*pi/180 #angle of substrate inclination around y-axis
yip=8.0 # y-coordinate of substrate inclination axis
xc=10 #initial nozzle axis position along x - axis, mm
yc=8 #along y - axis, mm
Lc=15 #length that the nozzle should do, mm
ker=0.0 #erosion coeff
kd=0.7 #deposition coeff
a=8 #rate of particle flux, mm/s
k3=0.0 #smothing coeff if 0.8 then averaging between 5 closest points
w0=100.0 #nozzle speed along substrate
zmax=1.0 #desired coating thicknes if w0=0
dzmax=0.016 #maximum gain in coating thicknes per time step
dt=min(dx/2/w0,dzmax/a) if w0>0 else dzmax/a #time step
N=int(trunc(Lc/w0/dt)) if w0>0 else zmax/dzmax  #number of time steps
print("w0=%f dt=%f N=%f",w0,dt,N)





x1=linspace(0,Lx,Mi) #service operators
y1=linspace(0,Ly,Mj)
z0=zeros((Mi,Mj))
z=zeros((Mi,Mj))
z1=zeros((Mi,Mj))
z11=zeros((Mi,Mj))
z2=zeros((Mi,Mj))
z4=zeros((Mi,Mj,N))
for i in range (Mi):
    for j in range(Mj):
        z0[i][j]=-tan(fip)*(y1[j]-yip)+0*x1[i]
        z[i][j]=z0[i][j]
        z1[i][j] = z0[i][j]
        z11[i][j] = z0[i][j]
        z4[i][j][0]=z[i][j]

#g4=linspace(0,Ly,len(y1))
#for i in range (len(x1)):
#for j in range(len(y1)):
#    g4[j]=z[100][j]

#plt.plot(y1,g4)
#plt.plot(v,g2)
#plt.show()
# below is the main body
for k in range(N):
    a1=int(trunc((xc+w0*dt*k-w1)/dx)-5)
    Imin=a1 if a1>1 else 1
    b1=int(trunc((xc+w0*dt*k+w1)/dx)+5)
    Imax=b1 if b1<Mi-1 else Mi-1
    for i in range(Imin,Imax):
        for j in range (1,Mj-1):
            u=(z[i+1][j]-z[i-1][j])/2/dx
            v=(z[i][j+1]-z[i][j-1])/2/dx
            z2[i][j]+=a*dt*Hp(x1[i]-(xc+w0*dt*k),y1[j]-yc,z[i][j])
            z1[i][j]+=a*dt*Hp(x1[i]-(xc+w0*dt*k),y1[j]-yc,z[i][j])*(-ker+tet(z2[i][j]))*(ker+kd*rp(u,v))
    for i in range(Imin,Imax):
        for j in range (1,Mj-1):
            if z1[i][j]==z[i][j]:
                z11[i][j]=z[i][j]
            else:
                z11[i][j]=(1-k3)*z1[i][j]+(z1[i-1][j]+z1[i+1][j]+z1[i][j-1]+z1[i][j+1])*k3/4
            z[i][j]=z11[i][j]
    for i in range(1,Mi-1):
        for j in range (1,Mj-1):
            z4[i][j][k]=z[i][j]
# the end of the main body
#results viewing
J1=80
K1=int(N/4)
K2=int(N/2)
K3=int(3*N/4)
g41=linspace(0,Lx,Mi)
g42=linspace(0,Lx,Mi)
g43=linspace(0,Lx,Mi)
g44=linspace(0,Lx,Mi)
#for i in range (len(x1)):
for i in range(Mi):
    g41[i]=z4[i][J1][K1]
    g42[i] = z4[i][J1][K2]
    g43[i] = z4[i][J1][K3]
    g44[i] = z4[i][J1][N - 1]
print("calculation is done!")
plt.plot(x1,g41)
plt.plot(x1,g42)
plt.plot(x1,g43)
plt.plot(x1,g44)
plt.show()

