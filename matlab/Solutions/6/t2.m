clc;clear;
y0 = [0, 1];
dydx = @(x, y) [y(2); -(1/5)*y(2)-y(1)];
xspan = [-10, 10];
[x,y] = ode45(dydx, xspan, y0);

plot(x,y(:,1));
xlabel('x')
ylabel('y')
title('Solution');
