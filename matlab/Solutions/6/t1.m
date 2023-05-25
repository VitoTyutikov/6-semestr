clc;clear;
tspan = [-1.5 5];
y0 = 0.01;
[t,y] = ode45(@(t, y) -5*t^3*y, tspan, y0);

plot(t, y);
xlabel('t')
ylabel('y')
title('Solution');
