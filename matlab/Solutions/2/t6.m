clc;clear;
x=-3*pi:0.05:3*pi;
y=sin(x);
plot(x, y)
grid on;
axis([-5, 5, -1, 1]);%границы осей

xlabel('axis x');
ylabel('axis y');

text(3.05, 0.16, "<-sin(x)");


