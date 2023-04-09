clc;clear;
n=randi([3 10])
m=randi([3 10])
%единичная матрица
A=ones(n,m);
%чет строка и неч столбец
A(2:2:end,1:2:end) = 0;
%нечет строка и чет столбец
A(1:2:end, 2:2:end) = 0;

subplot(1,2,1);
spy(ones(n,m));
title("source");

subplot(1,2,2);
spy(A);
title("chess");