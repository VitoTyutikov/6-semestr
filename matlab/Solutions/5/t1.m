clc;clear;
yder = @(x, y) asin(y^2 + x^2*(1+x)*(1+y)/y);
rangex = [-5, 5];
y0 = 1;
[x, y] = ode45(yder, rangex, y0);

plot(x, y);
title('Solution');
xlabel('x');
ylabel('y');