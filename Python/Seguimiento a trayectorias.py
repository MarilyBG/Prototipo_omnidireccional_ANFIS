import cv2
import numpy as np
from pynput import mouse
global Out_cal
Out_cal=0
Ncam=0
########################Deteccion de color###################
# Función para obtener el rango HSV al hacer clic
def pick_color(event, x, y, flags, param):
    if event == cv2.EVENT_LBUTTONDOWN:
        hsv_frame = cv2.cvtColor(frame, cv2.COLOR_BGR2HSV)
        pixel = hsv_frame[y, x]

        # Valores HSV del pixel seleccionado
        h, s, v = pixel
        print("Color HSV seleccionado:", pixel)

        # Definir un rango alrededor del color
        global lower
        global upper
        lower = np.array([max(h-10, 0), max(s-40, 0), max(v-40, 0)])
        upper = np.array([min(h+10, 179), min(s+40, 255), min(v+40, 255)])

        print("Rango HSV:")
        print("Lower:", lower)
        print("Upper:", upper)

        # Crear máscara para visualizar el rango
        mask = cv2.inRange(hsv_frame, lower, upper)
        result = cv2.bitwise_and(frame, frame, mask=mask)
        #cv2.imshow("Mascara", mask)
        #cv2.imshow("Resultado", result)
        global Out_cal
        Out_cal=1

def al_hacer_clic(x, y, boton, presionado):
    global imAux
    imAux = np.zeros(frame.shape,dtype=np.uint8)


# Inicializar cámara
cap = cv2.VideoCapture(Ncam)
cv2.namedWindow("Camara",cv2.WND_PROP_FULLSCREEN)
cv2.setWindowProperty("Camara", cv2.WND_PROP_FULLSCREEN, cv2.WINDOW_FULLSCREEN)
cv2.setMouseCallback("Camara", pick_color)

while True:
    ret, frame = cap.read()
    if not ret:
        break

    cv2.imshow("Camara", frame)

    # Presiona ESC para salir
    if ((cv2.waitKey(1) & 0xFF == 27)or Out_cal==1):
        break

cap.release()
cv2.destroyAllWindows()

########################Seguimiento de trayectorias###################


cap = cv2.VideoCapture(Ncam,cv2.CAP_DSHOW)
cv2.namedWindow("frame", cv2.WND_PROP_FULLSCREEN)
cv2.setWindowProperty("frame", cv2.WND_PROP_FULLSCREEN, cv2.WINDOW_FULLSCREEN)


Color_bajo = np.array(lower, np.uint8)
Color_alto = np.array(upper, np.uint8)


color = (0,255,127)  # Color de entrada, y variable que asignará el color del marcador
grosor = 2 # Grosor que tendrá el marcador


x1 = None
y1 = None
imAux = None

oyente = mouse.Listener(on_click=al_hacer_clic)
oyente.start()

while True:

    ret,frame = cap.read()
    if ret==False: break
    
    frameHSV = cv2.cvtColor(frame, cv2.COLOR_BGR2HSV)

    if imAux is None: imAux = np.zeros(frame.shape,dtype=np.uint8)

    # Detección del color celeste
    maskPlatform = cv2.inRange(frameHSV, Color_bajo, Color_alto)
    maskPlatform = cv2.erode(maskPlatform,None,iterations = 1)
    maskPlatform = cv2.dilate(maskPlatform,None,iterations = 2)
    maskPlatform = cv2.medianBlur(maskPlatform, 13)
    cnts,_ = cv2.findContours(maskPlatform, cv2.RETR_EXTERNAL,cv2.CHAIN_APPROX_SIMPLE)
    cnts = sorted(cnts, key=cv2.contourArea, reverse=True)[:1]

    for c in cnts:
        area = cv2.contourArea(c)
        if area > 500:
            x,y,w,h = cv2.boundingRect(c)
            y2 = y + h//2
            x2 = x + w//2
            
            if x1 is not None:
  
                if 0 < y2 < 60 or 0 < y1 < 60 :
                    imAux = imAux
                else:
                    imAux = cv2.line(imAux,(x1,y1),(x2,y2),color,grosor)
            cv2.circle(frame,(x2,y2),grosor,color,3)
            x1 = x2
            y1 = y2
        else:
            x1, y1 = None, None
            
    
    imAuxGray = cv2.cvtColor(imAux,cv2.COLOR_BGR2GRAY)
    _, th = cv2.threshold(imAuxGray,10,255,cv2.THRESH_BINARY)
    thInv = cv2.bitwise_not(th)
    frame = cv2.bitwise_and(frame,frame,mask=thInv)
    frame = cv2.add(frame,imAux)
    
    #cv2.imshow('maskPlatform', maskPlatform)
    #cv2.imshow('imAux',imAux)
    cv2.imshow('frame', frame)
    
    k = cv2.waitKey(1)
    if k == 27:
        imAux = np.zeros(frame.shape,dtype=np.uint8)
        break

cap.release()
cv2.destroyAllWindows()
