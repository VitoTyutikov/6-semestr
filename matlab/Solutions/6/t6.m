clc;clear;
y0 = [0, 2, -6];
[x,y] = ode45(@func, [-1, 1], y0);

plot(x,y(:,1));
xlabel('x')
ylabel('y')
title('Solution');

function yder = func(x,y)
    yder = zeros(3,1);
    yder(1) = y(2);
    yder(2) = y(3);
    yder(3) = (x^2)*y(3)+x*y(2)+y(1);
end