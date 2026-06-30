import random
import math
import numpy as np
import csv


datos=10 #aprox 1 min
i=0

r=3 #Radio de la rueda [cm]
R=11.666  #Radio de la plataforma [cm]

title=[]
title.append(['Vx','Vy','wp','w1','w2','w3'])
RD=1.4279 #RAD/s
RU=21.3628 #RAD/s

while(i<datos):

    if(i<=datos/8):        
        w1 = random.uniform(RD,RU) #w1
        w2 = random.uniform(RD,RU) #w2
        w3 = random.uniform(RD,RU) #w3
    if(i>datos/8 and i<=(datos*2)/8):
        w1 = random.uniform(RD,RU) #w1
        w2 = random.uniform(RD,RU) #w2
        w3 = -random.uniform(RD,RU) #w3
    if(i>(datos*2)/8 and i<=(datos*3)/8):
        w1 = random.uniform(RD,RU) #w1
        w2 = -random.uniform(RD,RU) #w2
        w3 = random.uniform(RD,RU) #w3
    if(i>(datos*3)/8 and i<=(datos*4)/8):
        w1 = random.uniform(RD,RU) #w1
        w2 = -random.uniform(RD,RU) #w2
        w3 = -random.uniform(RD,RU) #w3
    if(i>(datos*4)/8 and i<=(datos*5)/8):
        w1 = -random.uniform(RD,RU) #w1
        w2 = random.uniform(RD,RU) #w2
        w3 = random.uniform(RD,RU) #w3
    if(i>(datos*5)/8 and i<=(datos*6)/8):
        w1 = -random.uniform(RD,RU) #w1
        w2 = random.uniform(RD,RU) #w2
        w3 = -random.uniform(RD,RU) #w3
    if(i>(datos*6)/8 and i<=(datos*7)/8):
        w1 = -random.uniform(RD,RU) #w1
        w2 = -random.uniform(RD,RU) #w2
        w3 = random.uniform(RD,RU) #w3
    if(i>(datos*7)/8):
        w1 = -random.uniform(RD,RU) #w1
        w2 = -random.uniform(RD,RU) #w2
        w3 = -random.uniform(RD,RU) #w3
    
    Vx = r*(w1-(w2/2)-(w3/2))
    Vy = r*(((math.sqrt(3)*w2)/2)-((math.sqrt(3)*w3)/2))
    Wp = r*((w1+w2+w3)/R)

    w1 = w1*165/math.pi #pps
    w2 = w2*165/math.pi #pps
    w3 = w3*165/math.pi #pps
    title.append([Vx,Vy,Wp,w1,w2,w3])

    i=i+1



# Crear y guardar en un archivo CSV
with open("datos.csv", mode="w", newline="", encoding="utf-8") as archivo:
    escritor = csv.writer(archivo)
    escritor.writerows(title)

print("Archivo CSV creado exitosamente.")
