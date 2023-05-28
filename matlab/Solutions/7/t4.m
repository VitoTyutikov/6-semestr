clc;clear;
e = 0.1;
a = 0.1:0.01:0.9;
g = 1;
X0 = 3.0;
YO = 1.0;
tspan = [0, 200];

periods = zeros(size(a));
stable_periods = zeros(size(a));
unstable_periods = zeros(size(a));

for i =1:length(a)
    f = @(t, y)ode_func(t, y, e, a(i), g);
    [t, y]=Runge_Kutta(f, [X0, YO], tspan, 0.01);
    [pks, locs] = local_max(y(1,:));
    if length(locs) > 1
        periods (i) = mean (diff(t(locs)));
        disp(10);
    end

    [pks, locs] = local_max(y(1, :), 100);
    if length(locs) > 1
        stable_periods(i) = mean(diff(t(locs)));
    end
    
    [pks, locs] = local_max(y(1,:), 10);
    if length(locs) > 1
        unstable_periods(i) = mean(diff(t(locs)));
    end
    
end
figure(1);
subplot(2, 2, 1);
hold on;
for alpha = a
    [t, xy] = ode45 (@(t, xy) ode_func(t, xy, e, 0.45, g), tspan, [X0, YO]);
    plot(xy(:, 1), xy(:, 2), 'k-', 'LineWidth', 1.2);
end
xlabel('X');
ylabel('Y');
title('Автоколебания');
axis([0, 4, 0, 3]);
hold off;
subplot(2, 2, 2);
[t, y] = ode45(@(t, y) ode_func(t, y, e, 0.45, g), tspan, [X0, YO]); plot(t, y(:, 1), 'r-', 'LineWidth', 1.2);
xlabel('t');
ylabel('X');
title('Динамика колебаний');

hold on;
[t, y] = ode45(@(t, y) ode_func(t, y, e, 0.45, g), tspan, [X0, YO]); plot(t, y(:, 2), 'b-', 'LineWidth', 1.2);
subplot(2, 2, 3);
plot (a, periods, 'r');
title('Фазовый портрет');
subplot(2, 2, 4);
plot(a, stable_periods, 'g'); 
hold on;
plot(a, unstable_periods, 'g');