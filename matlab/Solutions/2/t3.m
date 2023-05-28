clc;clear;
x=-2*pi:0.05:2*pi;

y=sin(x);
plot(x,y)
hold on
y=cos(x);%переопределяем y, потому что он уже сохранен в plot
plot(x,y)

xlabel('axis x')
ylabel('axis y')
grid on%setka
title('sin, cos')