clc; clear;

yder2 = @(x, y) [y(2); acos(0) + 2*y(2) - x];
y0 = [0, 1];
rangex = [0, 10];

[x,y] = ode45(yder2, rangex, y0);

plot(x,y(:,1));
xlabel('x');
ylabel('y');
title('Solution');