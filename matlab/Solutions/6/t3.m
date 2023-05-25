clc;clear;
xspan = [-10, 10];
y0 = [0, 1];
[x,y] = ode45(@(x,y) odefun(x,y), xspan, y0);

plot(x,y(:,1))
xlabel('x')
ylabel('y')
title('Solution');

function yder = odefun(x,y)
    yder = zeros(2,1);
    yder(1) = y(2)+x^2;
    yder(2) = -y(1);
end