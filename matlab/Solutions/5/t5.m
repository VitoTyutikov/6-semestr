clear; clc;
ode = @(x, y) [y(2); (y(2)^2+1)*sin(y(1))*cos(y(2))^2/(sin(y(1))^2)];

y0 = [pi/4, 1];
rangex = [1, 80];
[x, y] = ode45(ode, rangex, y0);

plot(x, y(:,1));
xlabel('x');
ylabel('y');
title('Solution');