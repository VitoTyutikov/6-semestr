clear; clc;
ode = @(x, y) [y(2); y(3); 5 / ((y(1) - 2*y(3)*x)^2 * sqrt(y(3)))];

y0 = [1, 0, 0];
rangex = [-1, 1];
[x, y] = ode45(ode, rangex, y0);

plot(x, y(:, 1), '-o')
xlabel('x')
ylabel('y(x)')
title('Solution');