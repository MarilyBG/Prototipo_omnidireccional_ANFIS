% 1. Definir la función de transferencia: G(s) = 1 / (s^2 + 2s + 1)
sys = tf1;

% 2. Definir el vector de tiempo y señal de entrada (ej. escalón)
t = 0:0.01:1; % De 0 a 10 segundos
u = ones(size(t)); % Entrada escalón unitario
u=u*10000;
% 3. Simular la respuesta
[y, t] = lsim(sys, u, t);

% Graficar resultados
plot(t, y)
title(' Respuesta de la Función de Transferencia')
grid on