%Задание 15
clc;clear;

day = 1:31;

price1=randi([10, 50], 1 ,31);
price2=randi([5, 55], 1 ,31);

plot(day, price1,'color','blue');
hold on
plot(day, price2, 'color','black');

xlabel('day');
ylabel('price');


grid on;
title('price/day')
legend('price1', 'price2', 'Location','northwest');