clc; clear;
y1y2der = @(x, y) [y(2); ( (x^2 + x + y(1))/(x - y(1)) - 2*y(2)^2) / 2*y(1)];

y0 = [1; 1];
rangex = [-5, 5];
[x,y] = ode45(y1y2der, rangex, y0);

plot(x,y(:,1));
xlabel('x');
ylabel('y');
title('Solution');