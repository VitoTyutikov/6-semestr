clc, clear;
A=randi([-10 11], 4)
B=randi([-5 6], 3)
C=randi([1 4], 5)
D=randi([-2 2], 3)
E=randi([-7 7], 2)
Res=blkdiag(A,B,C,D,E)
spy(Res)