clear;clc;
ode = @(x, y) [y(2); y(3); y(4)^3*y(1) - y(1)/y(4) - y(2); y(1)*y(3) - y(3)];

y0 = [1, 0, 0, log(1)];
rangex = [-1, 1];
[x, y] = ode45(ode, rangex, y0);

plot(x, y(:, 1), '-o')
xlabel('x')
ylabel('y')
title('Solution')