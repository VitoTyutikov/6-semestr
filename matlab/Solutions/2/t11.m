clc;clear;

%окружность в полярных координатах (массив из ста элементов в диапазоне от
%0 до 2pi
z = linspace(0, 2*pi);
%единичная матрица
g = ones(size(z));
%график в полярных координатах
polarplot(z, g);
hold on


%роза
n = 6;
d = 4;
z = linspace(0, 2*pi);

g= sin(n*z).*cos(d*z);
polarplot(z, g);

%бабочка
z=linspace(-pi,pi, 500);

g=exp(sin(z))-2*cos(4*z)+sin((2*z-pi)/24).^5;
polarplot(z,g);

%сердце
z=linspace(0,2*pi, 1000);
g=sin(z).*sqrt(abs(cos(z)))./(sin(z)+7/5)-2*sin(z)+2;
polarplot(z,g);

%спираль архимеда
z=linspace(0,3*pi,500);
polarplot(z, z);