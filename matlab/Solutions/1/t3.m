clc, clear;
A=randi([-5 5], 3, 3)
B=randi([-5 5], 3, 3)
%3.a nnz - number nonzero
nnz(A) + nnz(B)
%3.b
nnz(A|B)