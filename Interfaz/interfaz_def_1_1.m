function varargout = interfaz_def_1_1(varargin)

% Last Modified by GUIDE v2.5 18-May-2026 17:03:34

% Begin initialization code - DO NOT EDIT
gui_Singleton = 1;
gui_State = struct('gui_Name',       mfilename, ...
                   'gui_Singleton',  gui_Singleton, ...
                   'gui_OpeningFcn', @interfaz_def_1_1_OpeningFcn, ...
                   'gui_OutputFcn',  @interfaz_def_1_1_OutputFcn, ...
                   'gui_LayoutFcn',  [] , ...
                   'gui_Callback',   []);
if nargin && ischar(varargin{1})
    gui_State.gui_Callback = str2func(varargin{1});
end

if nargout
    [varargout{1:nargout}] = gui_mainfcn(gui_State, varargin{:});
else
    gui_mainfcn(gui_State, varargin{:});
end
% End initialization code - DO NOT EDIT

% --- Executes just before interfaz_def_1_1 is made visible.
function interfaz_def_1_1_OpeningFcn(hObject, eventdata, handles, varargin)

% Choose default command line output for interfaz_def_1_1
handles.output = hObject;

% Update handles structure
guidata(hObject, handles);

% Almacena el handle de la figura en la estructura de datos
handles.figure1 = hObject;

handles.stop = false;
%*********************Imagen en los botones
%Adelante
[a,map]=imread('AA.jpg'); %Leer imagen a mostrar.
[r,c,d]=size(a); 
x=ceil(r/60); 
y=ceil(c/80);
g=a(1:x:end,1:y:end,:);

set(handles.adelante,'CData',g); %Añadir imagen al botón.

%Atras
[a,map]=imread('Ba.jpg'); %Leer imagen a mostrar.
[r,c,d]=size(a); 
x=ceil(r/45); 
y=ceil(c/50); 
g=a(1:x:end,1:y:end,:);
set(handles.atras,'CData',g); %Añadir imagen al botón.

%izquierda
[a,map]=imread('I.jpg'); %Leer imagen a mostrar.
[r,c,d]=size(a); 
x=ceil(r/34); 
y=ceil(c/80); 
g=a(1:x:end,1:y:end,:);
set(handles.izquierda,'CData',g); %Añadir imagen al botón.

%derecha
[a,map]=imread('D.jpg'); %Leer imagen a mostrar.
[r,c,d]=size(a); 
x=ceil(r/34); 
y=ceil(c/80); 
g=a(1:x:end,1:y:end,:);
set(handles.derecha,'CData',g); %Añadir imagen al botón.

%A-derecha
[a,map]=imread('AD.jpg'); %Leer imagen a mostrar.
[r,c,d]=size(a); 
x=ceil(r/34);
y=ceil(c/50); 
g=a(1:x:end,1:y:end,:);
set(handles.AD,'CData',g); %Añadir imagen al botón.

%A-I
[a,map]=imread('AI.jpg'); %Leer imagen a mostrar.
[r,c,d]=size(a); 
x=ceil(r/50); 
y=ceil(c/34); 
g=a(1:x:end,1:y:end,:);
set(handles.AI,'CData',g); %Añadir imagen al botón.

%IB
[a,map]=imread('BI.jpg'); %Leer imagen a mostrar.
[r,c,d]=size(a); 
x=ceil(r/50); 
y=ceil(c/34); 
g=a(1:x:end,1:y:end,:);
set(handles.IB,'CData',g); %Añadir imagen al botón.

%B-derecha
[a,map]=imread('BD.jpg'); %Leer imagen a mostrar.
[r,c,d]=size(a); 
x=ceil(r/34); 
y=ceil(c/50); 
g=a(1:x:end,1:y:end,:);
%g(g==255)=0.8*255;
set(handles.DB,'CData',g); %Añadir imagen al botón.

%GD
[a,map]=imread('GD.jpg'); %Leer imagen a mostrar.
[r,c,d]=size(a); 
x=ceil(r/40); 
y=ceil(c/50); 
g=a(1:x:end,1:y:end,:);
set(handles.GD,'CData',g); %Añadir imagen al botón.

%GI
[a,map]=imread('GI.jpg'); %Leer imagen a mostrar.
[r,c,d]=size(a); 
x=ceil(r/40); 
y=ceil(c/50); 
g=a(1:x:end,1:y:end,:);
set(handles.GI,'CData',g); %Añadir imagen al botón.

%triangulo
[a,map]=imread('Triangulo.jpg'); %Leer imagen a mostrar.
[r,c,d]=size(a); 
x=ceil(r/60); 
y=ceil(c/80); 
g=a(1:x:end,1:y:end,:);
set(handles.triangulo,'CData',g); %Añadir imagen al botón.

%circulo
[a,map]=imread('circulo.jpg'); %Leer imagen a mostrar.
[r,c,d]=size(a); 
x=ceil(r/60); 
y=ceil(c/80); 
g=a(1:x:end,1:y:end,:);
set(handles.circulo,'CData',g); %Añadir imagen al botón.

%cuadro
[a,map]=imread('cuadro.jpg'); %Leer imagen a mostrar.
[r,c,d]=size(a); 
x=ceil(r/60); 
y=ceil(c/80); 
g=a(1:x:end,1:y:end,:);
set(handles.Cuadrado,'CData',g); %Añadir imagen al botón.

%ocho
[a,map]=imread('infinito.jpg'); %Leer imagen a mostrar.
[r,c,d]=size(a); 
x=ceil(r/60); 
y=ceil(c/80); 
g=a(1:x:end,1:y:end,:);
set(handles.Ocho,'CData',g); %Añadir imagen al botón.

%recta
[a,map]=imread('AA.jpg'); %Leer imagen a mostrar.
[r,c,d]=size(a); 
x=ceil(r/60); 
y=ceil(c/80); 
g=a(1:x:end,1:y:end,:);
set(handles.recta,'CData',g); %Añadir imagen al botón.

%diagonal
[a,map]=imread('AD.jpg'); %Leer imagen a mostrar.
[r,c,d]=size(a); 
x=ceil(r/60); 
y=ceil(c/80); 
g=a(1:x:end,1:y:end,:);
set(handles.diagonal,'CData',g); %Añadir imagen al botón.

%*************************************************
%************** COMUNICACIÓN SERIAL **************
%*************************************************
oldobj = instrfind;
if not(isempty(oldobj))
    fclose(oldobj);
    delete(oldobj);
end
%1. Indicamos puerto y baudios
handles.bt = serial('COM3', 'BaudRate', 57600);
%2. Abrimos la comunicación
fopen(handles.bt);
% Actualiza la estructura de datos
guidata(hObject, handles);

%***************  FUNCIONES INTERFAZ_DEF_1_1  ******************   

% --- Outputs from this function are returned to the command line.
function varargout = interfaz_def_1_1_OutputFcn(~, eventdata, handles) 

varargout{1} = handles.output;

%***************** CONFIRMACIÓN COMUNICACIÓN SERIAL *******
if ~isvalid(handles.bt) || strcmp(handles.bt.Status, 'closed')
    % Si no está abierta, intenta abrir la comunicación
    try
        fopen(handles.bt);
        fprint(handles.bt,'openbt')
    catch
        errordlg('No se pudo abrir la comunicación Bluetooth.', 'Error', 'modal');
        return;
    end
end

%***+**************** LIMPIAR PANTALLA *****************
% --- Executes c_directa button press in limpiar.
function limpiar_Callback(hObject, eventdata, handles)
set(handles.e_bateria, 'String', '');
%Limpiar tabla
set(handles.uitable1, 'Data', {});
% Limpiar el gráfico
cla(handles.axes1);

guidata(hObject, handles);

% --- Executes c_directa button press in stop.
function stop_Callback(hObject, eventdata, handles)
flushinput(handles.bt); % Limpia basura previa
flushoutput(handles.bt);
handles.stop = true;
guidata(hObject, handles);
%Enviamos el comando por bluetooth
fprintf(handles.bt, 'D');
    
guidata(hObject, handles);

% --- Executes on button press in ANFIS.
function ANFIS_Callback(hObject, eventdata, handles)
%Enviamos el comando por bluetooth
fprintf(handles.bt, 'F');
guidata(hObject, handles);

% --- Executes c_directa button press in c_directa.
function c_directa_Callback(hObject, eventdata, handles)
%Enviamos el comando por bluetooth
fprintf(handles.bt, 'C');
guidata(hObject, handles);


%##############################################################
%#################  TRAYECTORIAS  #############################

%####################### DIAGONAL ################ OK
function diagonal_Callback(hObject, eventdata, handles)
% Reiniciar la bandera 
handles.stop = false; 
guidata(hObject, handles);
flushinput(handles.bt); % Limpia basura previa
cla(handles.axes1); %Limpiar gráfico
set(handles.uitable1, 'Data', {});
axes(handles.axes1);%Seleccionar donde graficar
hold on;
grid on;
axis equal;

xlim([-10 60]);
ylim([-10 60]);
xlabel('X [cm]');
ylabel('Y [cm]');
title('Trayectoria diagonal');

%=================== PUNTOS INICIAL Y FINAL ================
x0=0; y0=0;

xf=50; yf=50;
% ================== VELOCIDADES (cm) ============================
Vx = 20; Vy = 20;  Wp = 0;

%crear arreglo de numeros vx+vy+wp;
    V=[Vx, Vy, Wp];
     % Convertir el arreglo a una cadena separada por comas
    V_str = sprintf('%d+', V);
    V_str = V_str(1:end-1);  % Eliminar la última coma

% ================== TIEMPO DE SIMULACIÓN ===================
tf = (sqrt(xf^2 + yf^2))/(sqrt(Vx^2 + Vy^2));       % Tiempo total (s) t=d/v
dt = 0.05;     % Paso t
t = 0:dt:tf;

% % Enviar los valores vx, vy y wp al Arduino a través del puerto serial
     fprintf(handles.bt, '%s;', V_str);

% ================== INICIALIZACIÓN =========================
x = x0; y = y0;  theta = 0;
trayX = x0;  trayY = y0;

% Puntos inicial y final
plot(x0, y0, 'go', 'MarkerSize', 6, 'LineWidth', 1);
plot(xf, yf, 'ro', 'MarkerSize', 6, 'LineWidth', 1);

% Trayectoria y robot
trayectoria = plot(trayX, trayY, 'b', 'LineWidth', 2);
robot = plot(x, y, 'r^', 'MarkerSize', 8, 'MarkerFaceColor','k');
% ================== ANIMACIÓN ==============================
pause(0.2);
fprintf(handles.bt, 'E');
pause(tf);
fprintf(handles.bt, 'D');
pause(0.05);

for k = 2:length(t)
        % ---- Verificar si se presionó STOP ---
    drawnow; % Permite que MATLAB procese el click del botón stop
    handles = guidata(hObject); % Lee el estado actualizado de la GUI
    
    if isfield(handles, 'stop') && handles.stop == true
        fprintf(handles.bt, 'D'); % Enviar comando de parada al Arduino
        return; % Sale completamente de la función
    end
    % Integración
    x = x + Vx*dt;
    y = y + Vy*dt;
    theta = theta + Wp*dt;

    % Guardar trayectoria
    trayX(end+1) = x;
    trayY(end+1) = y;

    % Actualizar gráficos
    set(trayectoria, 'XData', trayX, 'YData', trayY);
    set(robot, 'XData', x, 'YData', y);
    drawnow;
end
%Enviar datos a la tabla
T=[x0, y0, xf, yf, Vx, Vy, Wp];
set(handles.uitable1,'Data',T);
handles.d=T;
guidata(hObject, handles);

%####################### CIRCULO ################  OK
function circulo_Callback(hObject, eventdata, handles)
% Reiniciar la bandera 
handles.stop = false; 
guidata(hObject, handles);
flushinput(handles.bt); % Limpia basura previa
cla(handles.axes1); % Limpiar el gráfico
set(handles.uitable1, 'Data', {});
axes(handles.axes1); % Seleccionar el eje donde graficar
hold on; 
grid on;

% limitar grafica
xlim([-60 30]);
ylim([-30 30]);
xlabel('X [cm]');
ylabel('Y [cm]');
title('Trayectoria circulo');

% ================== PARÁMETROS ==================
Radio = 25;          % Radio cm
num_puntos = 18;    
V_lineal = 20;       
dt = 0.02;     

theta = linspace(0, 2*pi, num_puntos);
x_puntos = Radio * cos(theta)-Radio;
y_puntos = Radio * sin(theta);

% ================== INICIALIZACIÓN ==================
x = x_puntos(1);
y = y_puntos(1);
trayX = x;
trayY = y;

trayectoria = plot(trayX, trayY, 'b', 'LineWidth', 2);
robot = plot(x, y, 'r^', 'MarkerSize', 8, 'MarkerFaceColor', 'k');

T = [];           % Matriz para la uitable

fprintf(handles.bt, 'D');

% ==================== TRAYECTORIA ====================        
for i = 1:(num_puntos-1)
    % ---- verificación stop ----
    drawnow; 
    handles = guidata(hObject); 
    if isfield(handles, 'stop') && handles.stop == true
        fprintf(handles.bt, 'D'); 
        return; 
    end

    % Puntos iniciales y finales del segmento actual
    x0 = x_puntos(i);   y0 = y_puntos(i);
    xf = x_puntos(i+1); yf = y_puntos(i+1);

    % Calcular distancias y tiempos
    dx = xf - x0;
    dy = yf - y0;
    distancia_segmento = sqrt(dx^2 + dy^2);
    tf = distancia_segmento / V_lineal;

    % Calcular velocidad (cm/s)
    Vx = (dx / tf);
    Vy = (dy / tf);
    Wp = 0; 

    % Enviar velocidades 
    V = [Vx, Vy, Wp];
    V_str = sprintf('%.2f+', V); 
    V_str = V_str(1:end-1);      
    fprintf(handles.bt, '%s;', V_str);

    fprintf(handles.bt, 'E'); 
    pause(tf);
    %t_pausa = 0;
%     while t_pausa < tf
%         drawnow;
%         handles = guidata(hObject);
%         if isfield(handles, 'stop') && handles.stop == true
%             fprintf(handles.bt, 'D');
%             return;
%         end
%         pause(0.01);
%         t_pausa = t_pausa + 0.01;
%     end
    fprintf(handles.bt, 'D');
    pause(0.02);
end

% ==================== ANIMACIÓN ====================
x_calc = x_puntos(1);
y_calc = y_puntos(1);

for i = 1:(num_puntos-1)
    x0 = x_puntos(i);   y0 = y_puntos(i);
    xf = x_puntos(i+1); yf = y_puntos(i+1);
    
    dx = xf - x0;       dy = yf - y0;
    distancia_segmento = sqrt(dx^2 + dy^2);
    tf = distancia_segmento / V_lineal;
    
    Vx = (dx / tf);     
    Vy = (dy / tf);     
    Wp = 0; 
    
    t = 0:dt:tf;
    for k = 2:length(t)
        x_calc = x_calc + Vx*dt;
        y_calc = y_calc + Vy*dt;
        trayX(end+1) = x_calc;
        trayY(end+1) = y_calc;
    end    
T = [T; x0 y0 xf yf Vx Vy Wp];
end

% Actualizar UITABLE con todos los tramos calculados de una sola vez

set(handles.uitable1, 'Data', T);
handles.d = T;
pause(0.05);

% ==================== SIMULACIÓN ====================
dt = 0.01; 

for m = 1:length(trayX)
    % ---- VERIFICACIÓN STOP ----
    drawnow; 
    handles = guidata(hObject); 
    
    if isfield(handles, 'stop') && handles.stop == true
        return; 
    end

    set(trayectoria, 'XData', trayX(1:m), 'YData', trayY(1:m));
    set(robot, 'XData', trayX(m), 'YData', trayY(m));
    pause(dt); 
end

guidata(hObject, handles);

%###################### CUADRADO ################
function Cuadrado_Callback(hObject, eventdata, handles)
handles.stop = false; 
guidata(hObject, handles);

flushinput(handles.bt); 
cla(handles.axes1); 
set(handles.uitable1, 'Data', {});
axes(handles.axes1); 
grid on;
hold on; 

xlim([-10 80]);
ylim([-10 80]);
xlabel('X [cm]');
ylabel('Y [cm]');
title('Trayectoria cuadrado');
     
% ================== PUNTO INICIAL =======================
L  = 50;   x = 0; y = 0; 
trayX = x; trayY = y;

trayectoria = plot(trayX,trayY,'b','LineWidth',2);
robot = plot(x,y,'r^','MarkerSize',8,'MarkerFaceColor','k');
     
T = []; 
% ==================== TRAYECTORIA  ====================

% ---  X+ ---
x0_0 = x;  y0_0 = y; 
xf_0 = x0_0 + L; yf_0 = y0_0;
Vx_0 = 22; Vy_0 = 0; Wp_0 = 0;
tf = L/Vx_0;

fprintf(handles.bt,'D');
V_str = sprintf('%d+%d+%d', Vx_0, Vy_0, Wp_0);
fprintf(handles.bt, '%s;', V_str);

fprintf(handles.bt,'E');
pause(tf);  
%     t_pausa = 0;
%     while t_pausa < tf
%         drawnow;
%         handles = guidata(hObject);
%         if isfield(handles, 'stop') && handles.stop == true
%             fprintf(handles.bt, 'D');
%             return;
%         end
%         pause(0.01); 
%         t_pausa = t_pausa + 0.01;
%     end
%     
fprintf(handles.bt,'D');
pause(0.05);

% --- Y+ ---
x = xf_0; y = yf_0;
x0_1 = x; y0_1 = y; 
xf_1 = x0_1; yf_1 = y0_1 + L;
Vx_1 = 0; Vy_1 = 22; Wp_1 = 0;
tf = L/Vy_1;

V_str = sprintf('%d+%d+%d', Vx_1, Vy_1, Wp_1);
fprintf(handles.bt, '%s;', V_str);


fprintf(handles.bt,'E');
pause(tf);    
%t_pausa = 0;
    
%     while t_pausa < tf
%         drawnow;
%         handles = guidata(hObject);
%         if isfield(handles, 'stop') && handles.stop == true
%             fprintf(handles.bt, 'D');
%             return;
%         end
%         pause(0.01);
%         t_pausa = t_pausa + 0.01;
%     end 
fprintf(handles.bt,'D');
pause(0.05);

% ---  X- ---
x = xf_1; y = yf_1;
x0_2 = x; y0_2 = y; 
xf_2 = x0_2 - L; yf_2 = y0_2;
Vx_2 = -22; Vy_2 = 0; Wp_2 = 0;
tf = L/(-Vx_2);

V_str = sprintf('%d+%d+%d', Vx_2, Vy_2, Wp_2);
fprintf(handles.bt, '%s;', V_str);

fprintf(handles.bt,'E');
pause(tf);  
%     t_pausa = 0;
%     while t_pausa < tf
%         drawnow;
%         handles = guidata(hObject);
%         if isfield(handles, 'stop') && handles.stop == true
%             fprintf(handles.bt, 'D');
%             return;
%         end
%         pause(0.01); 
%         t_pausa = t_pausa + 0.01;
%     end
fprintf(handles.bt,'D');
pause(0.05);

% ---  Y- ---
x = xf_2; y = yf_2;
x0_3 = x; y0_3 = y; 
xf_3 = x0_3; yf_3 = y0_3 - L;
Vx_3 = 0; Vy_3 = -22; Wp_3 = 0;
tf = L/(-Vy_3);

V_str = sprintf('%d+%d+%d', Vx_3, Vy_3, Wp_3);
fprintf(handles.bt, '%s;', V_str);

fprintf(handles.bt,'E');
pause(tf);  
%     t_pausa = 0;
%     while t_pausa < tf
%         drawnow;
%         handles = guidata(hObject);
%         if isfield(handles, 'stop') && handles.stop == true
%             fprintf(handles.bt, 'D');
%             return;
%         end
%         pause(0.01); 
%         t_pausa = t_pausa + 0.01;
%     end
fprintf(handles.bt,'D');
pause(0.05);

% ==================== ANIMACIÓN ====================
dt = 0.25; 

% X+
t1 = 0:dt:(L/22);
for k = 2:length(t1)
    trayX(end+1) = trayX(end) + 22*dt;
    trayY(end+1) = trayY(end) + 0*dt;
end

% Y+
t2 = 0:dt:(L/22);
for k = 2:length(t2)
    trayX(end+1) = trayX(end) + 0*dt;
    trayY(end+1) = trayY(end) + 22*dt;
end

% X-
t3 = 0:dt:(L/22);
for k = 2:length(t3)
    trayX(end+1) = trayX(end) - 22*dt;
    trayY(end+1) = trayY(end) + 0*dt;
end

% Y-
t4 = 0:dt:(L/22);
for k = 2:length(t4)
    trayX(end+1) = trayX(end) + 0*dt;
    trayY(end+1) = trayY(end) - 22*dt;
end

% Grafica simulación
for i = 1:length(trayX)
        drawnow;
        handles = guidata(hObject);
        if isfield(handles, 'stop') && handles.stop == true
            fprintf(handles.bt, 'D');
            return;
        end

    set(trayectoria, 'XData', trayX(1:i), 'YData', trayY(1:i));
    set(robot, 'XData', trayX(i), 'YData', trayY(i));
    pause(0.1); 
    drawnow;
end
T = [T; x0_0 y0_0 xf_0 yf_0 Vx_0 Vy_0 Wp_0];
set(handles.uitable1,'Data',T);
T = [T; x0_1 y0_1 xf_1 yf_1 Vx_1 Vy_1 Wp_1];
set(handles.uitable1,'Data',T);
T = [T; x0_2 y0_2 xf_2 yf_2 Vx_2 Vy_2 Wp_2];
set(handles.uitable1,'Data',T);
T = [T; x0_3 y0_3 xf_3 yf_3 Vx_3 Vy_3 Wp_3];
set(handles.uitable1,'Data',T);
handles.d = T;

guidata(hObject, handles);

%####################### RECTA ################ OK
function recta_Callback(hObject, eventdata, handles)
% Reinicia la bandera 
handles.stop = false; 
guidata(hObject, handles);

flushinput(handles.bt); % Limpia basura previa
cla(handles.axes1); % Limpiar el gráfico
set(handles.uitable1, 'Data', {});
axes(handles.axes1); % Seleccionar el eje donde graficar
hold on; 
grid on;
% ================== PUNTOS INICIAL Y FINAL =================
x0 = 0;  y0 = 0;       
xf = 0;   yf = 50;      

% ================== VELOCIDADES cm/s ============================
Vx = 0;  Vy = 25;  Wp = 0;        

% ================== TIEMPO DE SIMULACIÓN ===================
tf = yf/Vy;       % Tiempo total (s)
dt = 0.05;     % Paso 
t = 0:dt:tf;

% crear arreglo de numeros
    V=[Vx, Vy, Wp];
     % Convertir el arreglo a una cadena separada por comas
    V_str = sprintf('%d+', V);
    V_str = V_str(1:end-1);  % Eliminar la última coma

% Enviar los números al Arduino a través del puerto serial
    fprintf(handles.bt, '%s;', V_str);
% ================== INICIALIZACIÓN =========================
x = x0;  y = y0;  theta = 0;
trayX = x0;  trayY = y0;
% ================== FIGURA ================================
hold on; grid on; axis equal;
xlim([-30 30]);
ylim([-20 60]);
xlabel('X [cm/s]');
ylabel('Y [cm/s]');
title('Trayectoria recta en el eje Y');

% Puntos inicial y final
plot(x0, y0, 'go', 'MarkerSize', 6, 'LineWidth', 1);
plot(xf, yf, 'ro', 'MarkerSize', 6, 'LineWidth', 1);

% Trayectoria y robot
trayectoria = plot(trayX, trayY, 'b', 'LineWidth', 2);
robot = plot(x, y, 'r^', 'MarkerSize', 8, 'MarkerFaceColor','k');

pause(0.2);
fprintf(handles.bt, 'E');
pause(tf)
fprintf(handles.bt, 'D');
pause(0.05);
% ================== ANIMACIÓN ==============================
for k = 2:length(t)
    % ---- Verificar si se presionó STOP ---
    drawnow; % Permite que MATLAB procese el click del botón stop
    handles = guidata(hObject); % Lee el estado actualizado de la GUI
    
    if isfield(handles, 'stop') && handles.stop == true
        fprintf(handles.bt, 'D'); % Enviar comando de parada al Arduino
        return; % Sale completamente de la función
    end
    
    x = x + Vx*dt;
    y = y + Vy*dt;
    theta = theta + Wp*dt;

    % Guardar trayectoria
    trayX(end+1) = x;
    trayY(end+1) = y;

    % Actualizar gráficos
    set(trayectoria, 'XData', trayX, 'YData', trayY);
    set(robot, 'XData', x, 'YData', y);
    drawnow;
end
%Enviar datos a la tabla
T=[x0, y0, xf, yf, Vx, Vy, Wp];
set(handles.uitable1,'Data',T);
handles.d=T;
guidata(hObject, handles);


%####################### TRIANGULO ################ 
function triangulo_Callback(hObject, eventdata, handles)
%Reiniciar bandera stop
handles.stop = false; 
guidata(hObject, handles);
flushinput(handles.bt); % Limpia basura previa
cla(handles.axes1);% Limpiar el gráfico
set(handles.uitable1, 'Data', {});
axes(handles.axes1); % Seleccionar el eje donde graficar
grid on;
hold on; 
%limitar grafica
xlim([-10 100]);
ylim([-10 100]);
xlabel('X [cm]');
ylabel('Y [cm]');
title('Trayectoria triangulo');

% ================== PUNTO INICIAL =======================
x = 0; y = 0; theta = 0;
trayX = x; trayY = y;

trayectoria = plot(trayX,trayY,'b','LineWidth',2);
robot = plot(x,y,'r^','MarkerSize',8,'MarkerFaceColor','k');
     
T= [];%Arreglo datos tabla

% ============= TRAYECTORIAS =========================
% ================= X+ =============================
L  = 70.72;        % distancia
x0_0 = x;  y0_0 = y;
xf_0 = x0_0 + L;  yf_0 = y0_0;

%cm
Vx_0 = 22; Vy_0 = 0; Wp_0 = 0;
% Tiempo por trayecto
tf = L/Vx_0;          
dt = 0.05;
t  = 0:dt:tf;

% crear arreglo de numeros
    V=[Vx_0, Vy_0, Wp_0];
     % Convertir el arreglo a una cadena separada por comas
    V_str = sprintf('%d+', V);
    V_str = V_str(1:end-1);  % Eliminar la última coma
         
% Enviar 
    fprintf(handles.bt, '%s;', V_str);

fprintf(handles.bt,'E');
pause(tf)
%     t_pausa = 0;
%     while t_pausa < tf
%         drawnow;
%         handles = guidata(hObject);
%         if isfield(handles, 'stop') && handles.stop == true
%             fprintf(handles.bt, 'D');
%             return;
%         end
%         pause(0.01); 
%         t_pausa = t_pausa + 0.01;
%     end
fprintf(handles.bt,'D');
pause(0.05);

x = xf_0; y=yf_0;
    
flushinput(handles.bt); % Limpia basura previa
% ============ Y+ y X- =============================
L1  = 50;        % distancia
x0_1 = x;  y0_1 = y; xf_1 = x0_1;  
yf_1 = y0_1 + L1;

%cm
Vx_1 = -20; Vy_1 = 20; Wp_1 = 0;

tf1 = yf_1/sqrt(Vx_1^2 + Vy_1^2);  % Tiempo por trayecto
t1 = 0:dt:tf1;

% crear arreglo de numeros
    V=[Vx_1, Vy_1, Wp_1];
     % Convertir el arreglo a una cadena separada por comas
    V_str = sprintf('%d+', V);
    V_str = V_str(1:end-1);  % Eliminar la última coma
         
% Enviar los números al Arduino a través del puerto serial
    fprintf(handles.bt, '%s;', V_str);

fprintf(handles.bt,'E');
pause(tf1)
%     t_pausa = 0;
%     while t_pausa < tf1
%         drawnow;
%         handles = guidata(hObject);
%         if isfield(handles, 'stop') && handles.stop == true
%             fprintf(handles.bt, 'D');
%             return;
%         end
%         pause(0.01);
%         t_pausa = t_pausa + 0.01;
%     end
fprintf(handles.bt,'D');
pause(0.05);

flushinput(handles.bt); % Limpia basura previa
% ============ X- y Y- =============================
x = x0_1 + Vx_1*tf1; y = y0_1 + Vy_1*tf1;
L2  = 50;        % distancia
x0_2 = x;  y0_2 = y;
xf_2 = x0_2 - L2;  yf_2 = y0_2;

%cm
Vx_2 = -20; Vy_2 = -20; Wp_2 = 0;

tf2 = L2/(sqrt(Vx_2^2 + Vy_2^2));          % Tiempo por trayecto
t2  = 0:dt:tf1;

% crear arreglo de numeros
    V=[Vx_2, Vy_2, Wp_2];
     % Convertir el arreglo a una cadena separada por comas
    V_str = sprintf('%d+', V);
    V_str = V_str(1:end-1);  % Eliminar la última coma
         
% Enviar los números al Arduino a través del puerto serial
    fprintf(handles.bt, '%s;', V_str);

fprintf(handles.bt,'E');
pause(tf2)
%     t_pausa = 0;
%     while t_pausa < tf2
%         drawnow;
%         handles = guidata(hObject);
%         if isfield(handles, 'stop') && handles.stop == true
%             fprintf(handles.bt, 'D');
%             return;
%         end
%         pause(0.01);
%         t_pausa = t_pausa + 0.01;
%     end
fprintf(handles.bt,'D');
pause(0.05);
%################# ANIMACIÓN ###################
Vx1 = 22; Vy1 = 0;
for k = 2:length(t)
    trayX(end+1) = trayX(end) + Vx1*dt;
    trayY(end+1) = trayY(end) + Vy1*dt;
end

%  Y+ y X-
Vx2 = -20; Vy2 = 20;
for k = 2:length(t1)
    trayX(end+1) = trayX(end) + Vx2*dt;
    trayY(end+1) = trayY(end) + Vy2*dt;
end

%  X- y Y-
Vx3 = -20; Vy3 = -20;
for k = 2:length(t2)
    trayX(end+1) = trayX(end) + Vx3*dt;
    trayY(end+1) = trayY(end) + Vy3*dt;
end

% ==================== SIMULACIÓN  ====================

for i = 1:length(trayX)   

        drawnow;
        handles = guidata(hObject);
        if isfield(handles, 'stop') && handles.stop == true
            fprintf(handles.bt, 'D');
            return;
        end

    set(trayectoria, 'XData', trayX(1:i), 'YData', trayY(1:i));
    set(robot, 'XData', trayX(i), 'YData', trayY(i));
    pause(0.01); 
    drawnow;
end
% ================== MOSTRAR EN UITABLE ===================
T = [T; x0_0 y0_0 xf_0 yf_0 Vx_0 Vy_0 Wp_0];
set(handles.uitable1,'Data',T);
T = [T; x0_1 y0_1 xf_1 yf_1 Vx_1 Vy_1 Wp_1];
set(handles.uitable1,'Data',T);
T = [T; x0_2 y0_2 xf_2 yf_2 Vx_2 Vy_2 Wp_2];
set(handles.uitable1,'Data',T);
handles.d = T;
guidata(hObject,handles);

%####################### OCHO ################
function Ocho_Callback(hObject, eventdata, handles)
% Reiniciar la bandera  
handles.stop = false; 
guidata(hObject, handles);
flushinput(handles.bt); % Limpia basura previa
cla(handles.axes1);% Limpiar el gráfico
set(handles.uitable1, 'Data', {});
axes(handles.axes1); % Seleccionar el eje donde graficar
hold on; 
grid on;
%limitar grafica
xlim([-50 50]);
ylim([-50 50]);
xlabel('X [cm]');
ylabel('Y [cm]');
title('Trayectoria Infinito');

% ================== PARÁMETROS ==================
Radio = 12;          % Radio cm 
num_puntos = 10; 
V_lineal = 20;       
dt = 0.03;      

% --- + ---

theta1 = linspace(0, 2*pi, num_puntos);
x_1 = Radio * cos(theta1)- Radio; 
y_1 = Radio * sin(theta1) ;

% ########## -  ###########
theta2 = linspace(pi, -pi, num_puntos); 
x_2 = Radio * cos(theta2)+ Radio; 
y_2 = Radio * sin(theta2) ;

% Concatenar los puntos 
x_puntos = [x_1, x_2(2:end)];
y_puntos = [y_1, y_2(2:end)];
num_puntos = length(x_puntos);

% ================== INICIALIZACIÓN ==================
x = x_puntos(1);
y = y_puntos(1);
trayX = x;
trayY = y;

trayectoria = plot(trayX, trayY, 'b', 'LineWidth', 2);
robot = plot(x, y, 'r^', 'MarkerSize', 8, 'MarkerFaceColor', 'k');

T = [];          
fprintf(handles.bt, 'D');

% ==================== EJECUCIÓN  ====================
for i = 1:(num_puntos-1)
    drawnow; 
    handles = guidata(hObject); 
    if isfield(handles, 'stop') && handles.stop == true
        fprintf(handles.bt, 'D'); 
        return; 
    end
    
    % Puntos del segmento actual
    x0 = x_puntos(i); y0 = y_puntos(i);
    xf = x_puntos(i+1); yf = y_puntos(i+1);
    
    % Calcular distancias y tiempos
    dx = xf - x0;
    dy = yf - y0;
    distancia_segmento = sqrt(dx^2 + dy^2);
    tf = distancia_segmento / V_lineal;
    
    % Componentes de velocidad
    Vx = (dx / tf);
    Vy = (dy / tf);
    Wp = 0; 
    
    % Envío 
    V = [Vx, Vy, Wp];
    V_str = sprintf('%.2f+', V); 
    fprintf(handles.bt, '%s;', V_str(1:end-1));
    
    %pause(0.2);
    fprintf(handles.bt, 'E'); 
    pause(tf)
%     t_pausa = 0;
%     while t_pausa < tf
%         drawnow;
%         handles = guidata(hObject);
%         if isfield(handles, 'stop') && handles.stop == true
%             fprintf(handles.bt, 'D');
%             return;
%         end
%         pause(0.01);
%         t_pausa = t_pausa + 0.01;
%     end
    fprintf(handles.bt, 'D');
    pause(0.02); 

end

%================  ANIMACIÓN  =========
x_calc = x_puntos(1);
y_calc = y_puntos(1);

for i = 1:(num_puntos-1)

    % Puntos del segmento actual
    x0 = x_puntos(i); y0 = y_puntos(i);
    xf = x_puntos(i+1); yf = y_puntos(i+1);
    
    % Calcular distancias y tiempos
    dx = xf - x0;
    dy = yf - y0;
    distancia_segmento = sqrt(dx^2 + dy^2);
    tf = distancia_segmento / V_lineal;
    
    % Componentes de velocidad
    Vx = (dx / tf);
    Vy = (dy / tf);
    Wp = 0; 
      
    t_tramo = 0:dt:tf;
    for k = 2:length(t_tramo)
        x = x + Vx*dt;
        y = y + Vy*dt;
        trayX(end+1) = x;
        trayY(end+1) = y;
    end
T = [T; x0 y0 xf yf Vx Vy Wp];
end

% Actualizar UITABLE

set(handles.uitable1, 'Data', T);
handles.d = T;

pause(0.2);

% ==================== SIMULACIÓN  ====================
dt= 0.01; 

for m = 1:length(trayX)
    % ---- VERIFICACIÓN STOP ----
    drawnow; 
    handles = guidata(hObject); 
    
    if isfield(handles, 'stop') && handles.stop == true
        return; 
    end
    set(trayectoria, 'XData', trayX(1:m), 'YData', trayY(1:m));
    set(robot, 'XData', trayX(m), 'YData', trayY(m));
    drawnow;
    pause(dt); 
end

guidata(hObject, handles);

%################ FIN TRAYECTORIAS ##################################


% --- Executes during object creation, after setting all properties.
function uitable1_CreateFcn(hObject, eventdata, handles)

function axes1_CreateFcn(hObject, eventdata, handles)
 
function axes1_Callback(hObject, eventdata, handles)
axis equal;
grid on;
guidata(hObject, handles);

%#####################################################################
%################  BOTON CALCULAR BATERIA  ###########################

% --- Executes on button press in calcular_bateria.
function calcular_bateria_Callback(hObject, eventdata, handles)
%Envia una B 
fprintf(handles.bt, 'B');

    if handles.bt.BytesAvailable > 0
        resultado = fscanf(handles.bt, '%s');
        resultado = (str2double(resultado)-3000)*100/1095; 
        %Mostrar en el text
        set(handles.e_bateria, 'String', num2str(resultado));
    end   
guidata(hObject, handles);
       
function e_bateria_Callback(hObject, eventdata, handles)

% --- Executes during object creation, after setting all properties.
function e_bateria_CreateFcn(hObject, eventdata, handles)
if ispc && isequal(get(hObject,'BackgroundColor'), get(0,'defaultUicontrolBackgroundColor'))
    set(hObject,'BackgroundColor','white');
end


%#######################################################################
%#############  BOTONES CINEMATICA DIRECTA  ############################

function adelante_CreateFcn(hObject, eventdata, handles)
if ispc && isequal(get(hObject,'BackgroundColor'), get(0,'defaultUicontrolBackgroundColor'))
    set(hObject,'BackgroundColor','white');
end

% % --- Executes on button press in adelante.
 function adelante_Callback(hObject, eventdata, handles)
flushinput(handles.bt); % Limpia basura previa
flushoutput(handles.bt);
%Definir velocidades (movimiento hacia abajo)
Vx = 0;
Vy = 22;
Wp = 0;

% Convertir a string (formato correcto)
V_str = sprintf('%d+%d+%d', Vx, Vy, Wp);

% Enviar por serial
fprintf(handles.bt, '%s;', V_str);

% Mostrar en consola
fprintf('%s;\n', V_str);

fprintf(handles.bt, 'E');
guidata(hObject, handles);

function atras_CreateFcn(hObject, eventdata, handles)
if ispc && isequal(get(hObject,'BackgroundColor'), get(0,'defaultUicontrolBackgroundColor'))
    set(hObject,'BackgroundColor','white');
end
     
% --- Executes on button press in atras.
function atras_Callback(hObject, eventdata, handles)
flushinput(handles.bt); % Limpia basura previa
flushoutput(handles.bt);
%Definir velocidades (movimiento hacia abajo)
Vx = 0;
Vy = -22;
Wp = 0;

% Convertir a string (formato correcto)
V_str = sprintf('%d+%d+%d', Vx, Vy, Wp);

% Enviar por serial
fprintf(handles.bt, '%s;', V_str);

% Mostrar en consola
fprintf('%s;\n', V_str);

fprintf(handles.bt, 'E');
guidata(hObject, handles);

function derecha_CreateFcn(hObject, eventdata, handles)
if ispc && isequal(get(hObject,'BackgroundColor'), get(0,'defaultUicontrolBackgroundColor'))
    set(hObject,'BackgroundColor','white');
end

% --- Executes on button press in derecha.
function derecha_Callback(hObject, eventdata, handles)
flushinput(handles.bt); % Limpia basura previa
flushoutput(handles.bt);
%Definir velocidades (movimiento hacia abajo)
Vx = 22;
Vy = 0;
Wp = 0;

% Convertir a string (formato correcto)
V_str = sprintf('%d+%d+%d', Vx, Vy, Wp);

% Enviar por serial
fprintf(handles.bt, '%s;', V_str);

 % Mostrar en consola
fprintf('%s;\n', V_str);

fprintf(handles.bt, 'E');
guidata(hObject, handles);


function izquierda_CreateFcn(hObject, eventdata, handles)
if ispc && isequal(get(hObject,'BackgroundColor'), get(0,'defaultUicontrolBackgroundColor'))
    set(hObject,'BackgroundColor','white');
end

% --- Executes on button press in derecha.
function izquierda_Callback(hObject, eventdata, handles)
 flushinput(handles.bt); % Limpia basura previa
 flushoutput(handles.bt);
 %Definir velocidades (movimiento hacia abajo)
Vx = -22;
Vy = 0;
Wp = 0;

% Convertir a string (formato correcto)
V_str = sprintf('%d+%d+%d', Vx, Vy, Wp);
% Enviar por serial
fprintf(handles.bt, '%s;', V_str);

% Mostrar en consola
fprintf('%s;\n', V_str);
fprintf(handles.bt, 'E');

guidata(hObject, handles);


% --- Executes on button press in AI.
function AI_Callback(hObject, eventdata, handles)
flushinput(handles.bt); % Limpia basura previa
flushoutput(handles.bt);
%Definir velocidades (movimiento hacia abajo)
Vx = -20;
Vy = 20;
Wp = 0;

% Convertir a string (formato correcto)
V_str = sprintf('%d+%d+%d', Vx, Vy, Wp);

% Enviar por serial
fprintf(handles.bt, '%s;', V_str);

 % Mostrar en consola
fprintf('%s;\n', V_str);

fprintf(handles.bt, 'E');
guidata(hObject, handles);


% --- Executes on button press in AD.
function AD_Callback(hObject, eventdata, handles)
flushinput(handles.bt); % Limpia basura previa
flushoutput(handles.bt);
%Definir velocidades (movimiento hacia abajo)
Vx = 20;
Vy = 20;
Wp = 0;

% Convertir a string (formato correcto)
V_str = sprintf('%d+%d+%d', Vx, Vy, Wp);

% Enviar por serial
fprintf(handles.bt, '%s;', V_str);

 % Mostrar en consola
fprintf('%s;\n', V_str);

fprintf(handles.bt, 'E');
guidata(hObject, handles);


% --- Executes on button press in IB.
function IB_Callback(hObject, eventdata, handles)
flushinput(handles.bt); % Limpia basura previa
flushoutput(handles.bt);
%Definir velocidades (movimiento hacia abajo)
Vx = -20;
Vy = -20;
Wp = 0;

% Convertir a string (formato correcto)
V_str = sprintf('%d+%d+%d', Vx, Vy, Wp);

% Enviar por serial
fprintf(handles.bt, '%s;', V_str);

 % Mostrar en consola
fprintf('%s;\n', V_str);

fprintf(handles.bt, 'E');
guidata(hObject, handles);


% --- Executes on button press in DB.
function DB_Callback(hObject, eventdata, handles)
flushinput(handles.bt); % Limpia basura previa
flushoutput(handles.bt);
%Definir velocidades (movimiento hacia abajo)
Vx = 20;
Vy = -20;
Wp = 0;

% Convertir a string (formato correcto)
V_str = sprintf('%d+%d+%d', Vx, Vy, Wp);

% Enviar por serial
fprintf(handles.bt, '%s;', V_str);

 % Mostrar en consola
fprintf('%s;\n', V_str);

fprintf(handles.bt, 'E');
guidata(hObject, handles);

% --- Executes on button press in GI.
function GI_Callback(hObject, eventdata, handles)
flushinput(handles.bt); % Limpia basura previa
flushoutput(handles.bt);
%Definir velocidades (movimiento hacia abajo)
Vx = 0;
Vy = 0;
Wp = -2;

% Convertir a string (formato correcto)
V_str = sprintf('%d+%d+%d', Vx, Vy, Wp);

% Enviar por serial
fprintf(handles.bt, '%s;', V_str);

 % Mostrar en consola
fprintf('%s;\n', V_str);

fprintf(handles.bt, 'E');
guidata(hObject, handles);

% --- Executes on button press in GD.
function GD_Callback(hObject, eventdata, handles)
flushinput(handles.bt); % Limpia basura previa
flushoutput(handles.bt);
%Definir velocidades (movimiento hacia abajo)
Vx = 0;
Vy = 0;
Wp = 2;

% Convertir a string (formato correcto)
V_str = sprintf('%d+%d+%d', Vx, Vy, Wp);

% Enviar por serial
fprintf(handles.bt, '%s;', V_str);

% Mostrar en consola
fprintf('%s;\n', V_str);

fprintf(handles.bt, 'E');
guidata(hObject, handles);

%************** CIERRE COMUNICACIÓN**************
function interfaz_CloseRequestFcn(hObject, eventdata, handles)
% Cierra la conexión Bluetooth
fclose(handles.bt);
delete(handles.bt);

% Hint: delete(hObject) closes the figure
delete(hObject);
close all;
clear;
clc;

% Actualiza la estructura de datos
guidata(hObject, handles);
