# Librerías requeridas
import numpy as np
from matplotlib import pyplot as plt
from fuzzy import *

###------------------------------------------------------------
####1. Definimos las variables linguistica de entrada y salida
##Puntos=181
###-----------| Vx |------------------
### Universo de discurso
##Vx_range = np.linspace(-1461,1442, Puntos)
### Funciones de pertenencia para la entrada
##Vxb = trimf(Vx_range, [-2912,-1461,-9.75])
##Vxm = trimf(Vx_range, [-1461,-9.75,1442])
##VxA = trimf(Vx_range, [-9.75,1442,2893])
###gráfico para Vx
##plt.plot(Vx_range, Vxb, label="Vxb")
##plt.plot(Vx_range, Vxm, label="Vxm")
##plt.plot(Vx_range, VxA, label="VxA")
##plt.legend(loc='best')
##plt.xlabel('Vx')
##plt.ylabel('$\mu (Vx)$')
##plt.show()
##
###-----------| Vy |------------------
### Universo de discurso
##Vy_range = np.linspace(-1299,1291, Puntos)
### Funciones de pertenencia para la entrada
##Vyb = trimf(Vy_range, [-2594,-1299,-3.897])
##Vym = trimf(Vy_range, [-1299,-3.897,1291])
##VyA = trimf(Vy_range, [-3.897,1291,2586])
###gráfico para Vy
##plt.plot(Vy_range, Vyb, label="Vyb")
##plt.plot(Vy_range, Vym, label="Vym")
##plt.plot(Vy_range, VyA, label="VyA")
##plt.legend(loc='best')
##plt.xlabel('Vy')
##plt.ylabel('$\mu (Vy)$')
##plt.show()
##
###-----------| Wp |------------------
### Universo de discurso
##Wp_range = np.linspace(-103.9,103.4, Puntos)
### Funciones de pertenencia para la entrada
##Wpb = trimf(Wp_range, [-207.6,-103.9,-0.2824])
##Wpm = trimf(Wp_range, [-103.9,-0.2824,103.4])
##WpA = trimf(Wp_range, [-0.2824,103.4,207])
###gráfico para Wp
##plt.plot(Wp_range, Wpb, label="Vxb")
##plt.plot(Wp_range, Wpm, label="Vxm")
##plt.plot(Wp_range, WpA, label="VxA")
##plt.legend(loc='best')
##plt.xlabel('Wp')
##plt.ylabel('$\mu (Wp)$')
##plt.show()

#------------------------------------------------------------
##2. Fuzzificacion

#el valor de error actual
Vx=-1.1737
Vy=59.3653
Wp=13.1023

#W1
#Fuzzificar: encontrar la pertenencia de Vx Vy Wp a cada conjunto difuso de entrada
#-----------| Vx |------------------
# Funciones de pertenencia para la entrada
Val_Vxb = trimf(Vx,   [-182.8, -87.95, 6.92])
Val_Vxm = trimf(Vx,   [-87.95, 6.92, 101.8])
Val_VxA = trimf(Vx,   [6.92, 101.8, 196.7])

#-----------| Vy |------------------
# Funciones de pertenencia para la entrada
Val_Vyb = trimf(Vy,   [-191.8, -101.8, -11.7])
Val_Vym = trimf(Vy,   [-101.8, -11.7, 78.38])
Val_VyA = trimf(Vy,   [-11.7, 78.38, 168.5])

#-----------| Wp |------------------
# Funciones de pertenencia para la entrada
Val_Wpb = trimf(Wp,    [-25.72, -12.64, 0.4407])
Val_Wpm = trimf(Wp,    [-12.64, 0.4407, 13.52])
Val_WpA = trimf(Wp,    [0.4407, 13.52, 26.61])




#Visualicemos los valores
print('Val_Vxb='+str(Val_Vxb)+", Val_Vxm= "+str(Val_Vxm)+", Val_VxA= "+str(Val_VxA))
print('Val_Vyb='+str(Val_Vyb)+", Val_Vym= "+str(Val_Vym)+", Val_VyA= "+str(Val_VyA))
print('Val_Wpb='+str(Val_Wpb)+", Val_Wpm= "+str(Val_Wpm)+", Val_WpA= "+str(Val_WpA))

###Graficamos para visualizar sus posiciones
###-----------| Vx |------------------
##plt.plot(Vx_range, Vxb, label="Vxb")
##plt.plot(Vx_range, Vxm, label="Vxm")
##plt.plot(Vx_range, VxA, label="VxA")
##plt.legend(loc='best')
##plt.plot([Vx, Vx], [0.0, 1.0], linestyle="--")
##plt.plot(Vx, Val_Vxb, 'x')
##plt.plot(Vx, Val_Vxm, 'x')
##plt.plot(Vx, Val_VxA, 'x')
##plt.xlabel('Vx')
##plt.ylabel('$\mu (Vx)$')
##plt.show()
##
###-----------| Vy |------------------
##plt.plot(Vy_range, Vyb, label="Vyb")
##plt.plot(Vy_range, Vym, label="Vym")
##plt.plot(Vy_range, VyA, label="VyA")
##plt.legend(loc='best')
##plt.plot([Vy, Vy], [0.0, 1.0], linestyle="--")
##plt.plot(Vy, Val_Vyb, 'y')
##plt.plot(Vy, Val_Vym, 'y')
##plt.plot(Vy, Val_VyA, 'y')
##plt.xlabel('Vy')
##plt.ylabel('$\mu (Vy)$')
##plt.show()
##
###-----------| Wp |------------------
##plt.plot(Wp_range, Wpb, label="Vxb")
##plt.plot(Wp_range, Wpm, label="Vxm")
##plt.plot(Wp_range, WpA, label="VxA")
##plt.legend(loc='best')
##plt.plot([Wp, Wp], [0.0, 1.0], linestyle="--")
##plt.plot(Wp, Val_Wpb, 'p')
##plt.plot(Wp, Val_Wpm, 'p')
##plt.plot(Wp, Val_WpA, 'p')
##plt.xlabel('Wp')
##plt.ylabel('$\mu (Wp)$')
##plt.show()

#------------------------------------------------------------
##3. Inferencia
#-----------| Rules |------------------
Val_Rules = np.zeros(27)
Val_min_pert = np.zeros(27)
#W1
V_pert=[ -1887, -996.5, -105.9, -1887, -996.5, -105.8, -1887, -996.5, -105.8, -779.9, 110.8, 1001, -779.9, 110.8, 1001, -779.9, 110.8, 1001, 326.9, 1218, 2108, 327.4, 1218, 2109, 327.3, 1218, 2109] 
#W2 
#V_pert=[ -1376, -485.4, 405.1, -465.6, 425, 1316, 444.8, 1335, 2226, -1930, -1039, -148.4, -1019, -128.6, 762, -108.8, 781.8, 1673, -2481, -1593, -701.5, -1573, -682.2, 208.3, -662.2, 228.2, 1119]
#W2 
#V_pert=[ 681.2, 1572, 2462, -229.2, 661.5, 1552, -1140, -249, 641.4, 127.6, 1018, 1909, -782.8, 107.8, 998.5, -1693, -802.6, 88.08, -425.8, 464.7, 1355, -1336, -445.8, 444.9, -2246, -1356, -465.6]

#1
if (Val_Vxb > 0) and  (Val_Vyb > 0) and (Val_Wpb > 0):
    Val_Rules[0]= V_pert[0]
    Val_min_pert[0]=(Val_Vxb*Val_Vyb*Val_Wpb)
#2
if (Val_Vxb > 0) and  (Val_Vyb > 0) and (Val_Wpm > 0):
    Val_Rules[1]= V_pert[1]
    Val_min_pert[1]=(Val_Vxb*Val_Vyb*Val_Wpm)
#3
if (Val_Vxb > 0) and  (Val_Vyb > 0) and (Val_WpA > 0):
    Val_Rules[2]= V_pert[2]
    Val_min_pert[2]=(Val_Vxb*Val_Vyb*Val_WpA)
#4
if (Val_Vxb > 0) and  (Val_Vym > 0) and (Val_Wpb > 0):
    Val_Rules[3]= V_pert[3]
    Val_min_pert[3]=(Val_Vxb*Val_Vym*Val_Wpb)
#5
if (Val_Vxb > 0) and  (Val_Vym > 0) and (Val_Wpm > 0):
    Val_Rules[4]= V_pert[4]
    Val_min_pert[4]=(Val_Vxb*Val_Vym*Val_Wpm)
#6
if (Val_Vxb > 0) and  (Val_Vym > 0) and (Val_WpA > 0):
    Val_Rules[5]= V_pert[5]
    Val_min_pert[5]=(Val_Vxb*Val_Vym*Val_WpA)
#7
if (Val_Vxb > 0) and  (Val_VyA > 0) and (Val_Wpb > 0):
    Val_Rules[6]= V_pert[6]
    Val_min_pert[6]=(Val_Vxb*Val_VyA*Val_Wpb)
#8
if (Val_Vxb > 0) and  (Val_VyA > 0) and (Val_Wpm > 0):
    Val_Rules[7]= V_pert[7]
    Val_min_pert[7]=(Val_Vxb*Val_VyA*Val_Wpm)
#9
if (Val_Vxb > 0) and  (Val_VyA > 0) and (Val_WpA > 0):
    Val_Rules[8]= V_pert[8]
    Val_min_pert[8]=(Val_Vxb*Val_VyA*Val_WpA)
#10
if (Val_Vxm > 0) and  (Val_Vyb > 0) and (Val_Wpb > 0):
    Val_Rules[9]= V_pert[9]
    Val_min_pert[9]=(Val_Vxm*Val_Vyb*Val_Wpb)
#11
if (Val_Vxm > 0) and  (Val_Vyb > 0) and (Val_Wpm > 0):
    Val_Rules[10]= V_pert[10]
    Val_min_pert[10]=(Val_Vxm*Val_Vyb*Val_Wpm)
#12
if (Val_Vxm > 0) and  (Val_Vyb > 0) and (Val_WpA > 0):
    Val_Rules[11]= V_pert[11]
    Val_min_pert[11]=(Val_Vxm*Val_Vyb*Val_WpA)
#13
if (Val_Vxm > 0) and  (Val_Vym > 0) and (Val_Wpb > 0):
    Val_Rules[12]= V_pert[12]
    Val_min_pert[12]=(Val_Vxm*Val_Vym*Val_Wpb)
#14
if (Val_Vxm > 0) and  (Val_Vym > 0) and (Val_Wpm > 0):
    Val_Rules[13]= V_pert[13]
    Val_min_pert[13]=(Val_Vxm*Val_Vym*Val_Wpm)
#15
if (Val_Vxm > 0) and  (Val_Vym > 0) and (Val_WpA > 0):
    Val_Rules[14]= V_pert[14]
    Val_min_pert[14]=(Val_Vxm*Val_Vym*Val_WpA)
#16
if (Val_Vxm > 0) and  (Val_VyA > 0) and (Val_Wpb > 0):
    Val_Rules[15]= V_pert[15]
    Val_min_pert[15]=(Val_Vxm*Val_VyA*Val_Wpb)
#17
if (Val_Vxm > 0) and  (Val_VyA > 0) and (Val_Wpm > 0):
    Val_Rules[16]=V_pert[16]
    Val_min_pert[16]=(Val_Vxm*Val_VyA*Val_Wpm)
#18
if (Val_Vxm > 0) and  (Val_VyA > 0) and (Val_WpA > 0):
    Val_Rules[17]= V_pert[17]
    Val_min_pert[17]=(Val_Vxm*Val_VyA*Val_WpA)
#19
if (Val_VxA > 0) and  (Val_Vyb > 0) and (Val_Wpb > 0):
    Val_Rules[18]= V_pert[18]
    Val_min_pert[18]=(Val_VxA*Val_Vyb*Val_Wpb)
#20
if (Val_VxA > 0) and  (Val_Vyb > 0) and (Val_Wpm > 0):
    Val_Rules[19]= V_pert[19]
    Val_min_pert[19]=(Val_VxA*Val_Vyb*Val_Wpm)
#21
if (Val_VxA > 0) and  (Val_Vyb > 0) and (Val_WpA > 0):
    Val_Rules[20]= V_pert[20]
    Val_min_pert[20]=(Val_VxA*Val_Vyb*Val_WpA)
#22
if (Val_VxA > 0) and  (Val_Vym > 0) and (Val_Wpb > 0):
    Val_Rules[21]= V_pert[21]
    Val_min_pert[21]=(Val_VxA*Val_Vym*Val_Wpb)
#23
if (Val_VxA > 0) and  (Val_Vym > 0) and (Val_Wpm > 0):
    Val_Rules[22]= V_pert[22]
    Val_min_pert[22]=(Val_VxA*Val_Vym*Val_Wpm)
#24
if (Val_VxA > 0) and  (Val_Vym > 0) and (Val_WpA > 0):
    Val_Rules[23]= V_pert[23]
    Val_min_pert[23]=(Val_VxA*Val_Vym*Val_WpA)
#25
if (Val_VxA > 0) and  (Val_VyA > 0) and (Val_Wpb > 0):
    Val_Rules[24]= V_pert[24]
    Val_min_pert[24]=(Val_VxA*Val_VyA*Val_Wpb)
#26
if (Val_VxA > 0) and  (Val_VyA > 0) and (Val_Wpm > 0):
    Val_Rules[25]= V_pert[25]
    Val_min_pert[25]=(Val_VxA*Val_VyA*Val_Wpm)
#27
if (Val_VxA > 0) and  (Val_VyA > 0) and (Val_WpA > 0):
    Val_Rules[26]= V_pert[26]
    Val_min_pert[26]=(Val_VxA*Val_VyA*Val_WpA)

#print(Val_Rules)
#print(Val_min_pert)


Valorx=Val_Rules*Val_min_pert
suma=np.sum(Valorx)
#print(suma)
div=np.sum(Val_min_pert)
#print(div)
OUT=suma/div
print(OUT)
