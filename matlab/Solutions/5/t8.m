clc;clear;
yder2 = @(x, y) [y(2); sqrt((1/16)*(y(1)*y(2))^2- log(x))/2 + (1/8)*(y(1)*y(2))^2];

y0 = 1;
z0 = 1;
rangex = [-5, 5];

[x,y] = ode45(yder2, rangex, [y0, z0]);

plot(x,y(:,1));
xlabel('x');
ylabel('y');
title('Solution');