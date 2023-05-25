clc;clear;
y0 = [0, 0];
yder = @(x,y)[y(2); -y(1)^3-sin(x)];
xspan = [-10, 10];
[x,y] = ode45(yder, xspan, y0);

plot(x, y(:,1));
xlabel('x')
ylabel('y')
title('Solution');