clc;clear;
f = @(t,y) [-sin(t)/(1 + exp(2*t))^(1/2) + y(1)*(y(1)^2 + y(2)^2 - 1); 
            cos(t)/(1 + exp(2*t))^(1/2) + y(2)*(y(1)^2 + y(2)^2 - 1)]; 
y0 = [1; 0]; 
x_range = [0 5]; 
h = 0.01; 
[t, y_runge_kutta] = Runge_Kutta(f, y0, x_range, h); 
y = [cos(t)./(1+exp(2*t)).^(1/2); sin(t)./(1+exp(2*t)).^(1/2)]; 
disp(['Error max: ', num2str(max(max(abs(y_runge_kutta - y)))) ]);
