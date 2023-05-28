clc;clear;
y0 = [0, 2.1];
yder = @(x,y) [y(2); -0.01*y(1)-sin(y(2))];
xspan = [-10, 10];
[x,y] = ode45(yder, xspan, y0);

plot(x, y(:,1));
xlabel('x')
ylabel('y')
title('Solution');