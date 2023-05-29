clc;clear;
ode = @(x, y) [y(2); y(3); y(2) + sqrt(x^5 * tan(y(1)) - cos(y(1))) / y(2)];

y0 = [0, 1, 0];
rangex = [-1, 1];

[x, y] = ode45(ode, rangex, y0);

plot(x, y(:,1));
xlabel('x');
ylabel('y');
title('Solution');