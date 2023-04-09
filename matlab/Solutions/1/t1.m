clc;clear;
A=randi([-5 5], 3, 3);
display(A);
%1.a
sum(sum(A~=0))
%1.b
display(A+A');
display(issymmetric(A+A'));
%1.c
sum(sum(A==2))
%1.d
A([1 3],:) = A([3 1], :);
display(A);
%1.e
sum(diag(A))
