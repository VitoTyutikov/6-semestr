clc;clear;
%размерность блоков от 4 до 8
n = randi([4 8]);
A = [];
%построение б-д матрицы
for i = n : 2*n-1
   a = rand(i);
   A = blkdiag(A, a);
end
spy(A);