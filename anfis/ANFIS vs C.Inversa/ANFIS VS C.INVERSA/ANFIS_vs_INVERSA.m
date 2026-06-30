% % COMPARACION MODELOS ANFIS VS C.INVERSA
% %https://la.mathworks.com/help/fuzzy/modeling-inverse-kinematics-in-a-robotic-arm.html
% % w1, w2 y w3 pps
% 
% clear; clc;
% 
% % Parámetros
% r = 3;          % radio rueda (cm)
% R = 11.6666;    % radio de la plataforma (cm) 
% 
% % Cargar modelos ANFIS 
% anfis_w1 = readfis('W1_10.fis');
% anfis_w2 = readfis('W2_10.fis');
% anfis_w3 = readfis('W3_10.fis');
% 
% % Velocidades de prueba [Vx Vy Wp] en cm
% trayectorias = [0 22 0;     % y+
%                 0 -22 0;    % y-
%                 22 0 0;     % x+
%                 -22 0 0;    % x-
%                 20 20 0;    % diagonal d+
%                 -20 20 0;   % diagonal i+
%                 20 -20 0;   % diagonal d-
%                 -20 -20 0;  % diagonal i-
%                 0 0 -2;     % giro -
%                 0 0 2];     % giro +
% 
% % Evaluar ANFIS (vx, vy, wp, .fis)
% w1_anfis = evalfis(trayectorias, anfis_w1);
% w2_anfis = evalfis(trayectorias, anfis_w2);
% w3_anfis = evalfis(trayectorias, anfis_w3);
% 
% % Cinemática inversa
% Vx = trayectorias(:,1);
% Vy = trayectorias(:,2);
% Wp = trayectorias(:,3);
% %rad/s
% w1_cm = (1/r) .* ((2*Vx/3) + (R*Wp/3));
% w2_cm = (1/r) .* ((-Vx/3) + (sqrt(3)*Vy/3) + (R*Wp/3));
% w3_cm = (1/r) .* ((-Vx/3) - (sqrt(3)*Vy/3) + (R*Wp/3));
% %Se pasa a pps (ARREGLAR)
% w1_cin = ((w1_cm*165)/pi);
% w2_cin = ((w2_cm*165)/pi);
% w3_cin = ((w3_cm*165)/pi);
% 
% % Crear tabla comparativa
% T = table(Vx, Vy, Wp, ...
%           w1_cin, w1_anfis, ...
%           w2_cin, w2_anfis, ...
%           w3_cin, w3_anfis, ...
%           'VariableNames', {'Vx','Vy','Wp','w1_CIN','w1_ANFIS','w2_CIN','w2_ANFIS','w3_CIN','w3_ANFIS'});
% disp(T);
% 
% % Generar archivo excel
% writetable(T, 'comparacion_ANFIS_vs_CIN.xlsx');
% 
% % Calcular métricas de error
% % rmse_w1 = sqrt(mean((w1_anfis - w1_cin).^2));
% % rmse_w2 = sqrt(mean((w2_anfis - w2_cin).^2));
% % rmse_w3 = sqrt(mean((w3_anfis - w3_cin).^2));
% % 
% % fprintf('\nMétricas de comparación ANFIS vs CIN:\n');
% % fprintf('RMSE w1: %.4f\n', rmse_w1);
% % fprintf('RMSE w2: %.4f\n', rmse_w2);
% % fprintf('RMSE w3: %.4f\n', rmse_w3);
% 
% % Grafica C.in vs ANFIS
% 
% figure;
% 
% subplot(3,1,1);
% plot(w1_cin,'-o','LineWidth',1.5); hold on;
% plot(w1_anfis,'-s','LineWidth',1.5);
% title('Comparación rueda 1');
% xlabel('Trayectoria');
% ylabel('Velocidad (pps)');
% legend('Cinemática Inversa','ANFIS','Location','best');
% grid on;
% 
% subplot(3,1,2);
% plot(w2_cin,'-o','LineWidth',1.5); hold on;
% plot(w2_anfis,'-s','LineWidth',1.5);
% title('Comparación rueda 2');
% xlabel('Trayectoria');
% ylabel('Velocidad (pps)');
% legend('Cinemática Inversa','ANFIS','Location','best');
% grid on;
% 
% subplot(3,1,3);
% plot(w3_cin,'-o','LineWidth',1.5); hold on;
% plot(w3_anfis,'-s','LineWidth',1.5);
% title('Comparación rueda 3');
% xlabel('Trayectoria');
% ylabel('Velocidad (pps)');
% legend('Cinemática Inversa','ANFIS','Location','best');
% grid on;
%% COMPARACION DE TODOS LOS DATESETS

clear; clc;

% Parámetros
r = 3;          % radio rueda (cm)
R = 11.6666;    % radio de la plataforma (cm) 

% Lista de datasets
datasets = [10, 20, 50, 100, 200, 500, 1000, 2000, 5000, 10000];

% Velocidades de prueba [Vx Vy Wp] en cm
trayectorias = [0 22 0;     % y+
                0 -22 0;    % y-
                22 0 0;     % x+
                -22 0 0;    % x-
                20 20 0;    % diagonal d+
                -20 20 0;   % diagonal i+
                20 -20 0;   % diagonal d-
                -20 -20 0;  % diagonal i-
                0 0 -2;     % giro -
                0 0 2];     % giro +

% Cinemática inversa
Vx = trayectorias(:,1);
Vy = trayectorias(:,2);
Wp = trayectorias(:,3);
%rad/s
w1_cm = (1/r) .* ((2*Vx/3) + (R*Wp/3));
w2_cm = (1/r) .* ((-Vx/3) + (sqrt(3)*Vy/3) + (R*Wp/3));
w3_cm = (1/r) .* ((-Vx/3) - (sqrt(3)*Vy/3) + (R*Wp/3));

% Se pasa a pps
w1_cin = ((w1_cm*165)/pi);
w2_cin = ((w2_cm*165)/pi);
w3_cin = ((w3_cm*165)/pi);

%Error
Error_w1 = zeros(length(datasets),1);
Error_w2 = zeros(length(datasets),1);
Error_w3 = zeros(length(datasets),1);

% Tabla base con CIN
T = table(Vx, Vy, Wp, w1_cin, w2_cin, w3_cin, ...
          'VariableNames', {'Vx','Vy','Wp','w1_CIN','w2_CIN','w3_CIN'});

% Bucle para cargar y evaluar cada dataset
for i = 1:length(datasets)
    d = datasets(i);
    % Cargar modelos ANFIS
    anfis_w1 = readfis(['..\' num2str(d) '\W1_' num2str(d) '.fis']);
    anfis_w2 = readfis(['..\' num2str(d) '\W2_' num2str(d) '.fis']);
    anfis_w3 = readfis(['..\' num2str(d) '\W3_' num2str(d) '.fis']);

    % Evaluar ANFIS
    w1_anfis = evalfis(trayectorias, anfis_w1);
    w2_anfis = evalfis(trayectorias, anfis_w2);
    w3_anfis = evalfis(trayectorias, anfis_w3);

    % Agregar columnas a la tabla
    T.(['w1_ANFIS_' num2str(d)]) = w1_anfis;
    T.(['w2_ANFIS_' num2str(d)]) = w2_anfis;
    T.(['w3_ANFIS_' num2str(d)]) = w3_anfis;
    
    % Agregar columnas Error por trayectoria (ANFIS - CIN)
    T.(['Error_w1_' num2str(d)]) = w1_anfis - w1_cin;
    T.(['Error_w2_' num2str(d)]) = w2_anfis - w2_cin;
    T.(['Error_w3_' num2str(d)]) = w3_anfis - w3_cin;
    
    % Agregar columnas Error (diferencia ANFIS - CIN por trayectoria)
    Error_w1(i) =  mean(w1_anfis - w1_cin);
    Error_w2(i) =  mean(w2_anfis - w2_cin);
    Error_w3(i) =  mean(w3_anfis - w3_cin);
end

% **************** METRICAS DE ERROR ******
% RMSE
% Calcular métricas de error para cada dataset
rmse_w1 = zeros(length(datasets),1);
rmse_w2 = zeros(length(datasets),1);
rmse_w3 = zeros(length(datasets),1);

% MAE: A menor MAE mejor ajuste del modelo 
%"En promedio cuanto se equivoca el modelo"
mae_w1 = zeros(length(datasets),1);
mae_w2 = zeros(length(datasets),1);
mae_w3 = zeros(length(datasets),1);

%R^2: Coeficiente de determinación
%Indica que tanto ajuste tiene el modelo entrenado con el real
R2_w1 = zeros(length(datasets),1);
R2_w2 = zeros(length(datasets),1);
R2_w3 = zeros(length(datasets),1);

%STD: Desviación estandar
%Indica la dispersión de los datos
STD_w1 = zeros(length(datasets),1);
STD_w2 = zeros(length(datasets),1);
STD_w3 = zeros(length(datasets),1);

for i = 1:length(datasets)
    d = datasets(i);
    % Extraer columnas correspondientes
    %Cinematica ANFIS
    w1_anfis = T.(['w1_ANFIS_' num2str(d)]);
    w2_anfis = T.(['w2_ANFIS_' num2str(d)]);
    w3_anfis = T.(['w3_ANFIS_' num2str(d)]);
    
    % Calcular RMSE
    rmse_w1(i) = sqrt(mean((w1_cin - w1_anfis).^2));
    rmse_w2(i) = sqrt(mean((w2_cin - w2_anfis).^2));
    rmse_w3(i) = sqrt(mean((w3_cin - w3_anfis).^2));
    
    % Calcular MAE
    mae_w1(i) = mean(w1_cin - w1_anfis);
    mae_w2(i) = mean(w2_cin - w2_anfis);
    mae_w3(i) = mean(w3_cin - w3_anfis);
    
    % Calcular R^2
    ss_res1(i) = sum((w1_cin - w1_anfis).^2);
    ss_res2(i) = sum((w2_cin - w2_anfis).^2);
    ss_res3(i) = sum((w3_cin - w3_anfis).^2);
    
    ss_tot1(i) = sum((w1_cin - (mean(w1_cin))).^2);
    ss_tot2(i) = sum((w2_cin - (mean(w2_cin))).^2);
    ss_tot3(i) = sum((w3_cin - (mean(w3_cin))).^2);
    
    R2_w1(i) = 1 - (ss_res1 / ss_tot1);
    R2_w2(i) = 1 - (ss_res2 / ss_tot2);
    R2_w3(i) = 1 - (ss_res3 / ss_tot3);
    
    % Calcular STD
    STD_w1(i) = std(w1_cin - w1_anfis);
    STD_w2(i) = std(w2_cin - w2_anfis);
    STD_w3(i) = std(w3_cin - w3_anfis);
end


% Crear tabla de errores
Errores = table(datasets', rmse_w1, rmse_w2, rmse_w3, ...
                mae_w1, mae_w2, mae_w3, R2_w1, R2_w2, R2_w3, ...
                STD_w1, STD_w2, STD_w3, ...
    'VariableNames', {'Datos','RMSE_w1','RMSE_w2','RMSE_w3' ...
                'mae_w1', 'mae_w2', 'mae_w3', 'R2_w1', 'R2_w2', 'R2_w3', ...
                'STD_w1', 'STD_w2', 'STD_w3'});
disp(Errores);

% Guardar tabla de errores en Excel
writetable(Errores, 'errores_ANFIS_vs_CIN.xlsx');

% Mostrar tabla
disp(T);

% Guardar en Excel
writetable(T, 'comparacion_ANFIS_vs_CIN_todos.xlsx');
