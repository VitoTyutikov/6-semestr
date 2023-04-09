clc;clear;
%инициализация вектора x линейным массивом из 100 элементо равномерно
%расскиданных в отрезке -1 1
x=logspace(-1, 1);
f = log(0.5 * x);
g = sin(log(x));
%логарифмический масштаб
semilogx(x, f, 'LineWidth', 1.5);
hold on
semilogx(x, g, 'LineWidth', 1.5);

legend('f=log(0.5*x)', 'g=sin(log(x)','Location','northwest');

xlabel('axis x');
ylabel('axis y');
