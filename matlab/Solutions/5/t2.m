clc;clear;

yder2 = @(x, y) [y(2); sqrt(y(1)*y(2)-x^2-1)];
rangex = [-1, 5];
y0 = [1, 0];
[x, y] = ode45(yder2, rangex, y0);

plot(x, y(:, 1));
title('Solution');
xlabel('x');
ylabel('y');