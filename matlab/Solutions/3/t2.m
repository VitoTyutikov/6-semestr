clc;clear;
A = rand(5);
obr = A';
sum = A + obr;
issymmetric(A)
issymmetric(obr)
issymmetric(sum)