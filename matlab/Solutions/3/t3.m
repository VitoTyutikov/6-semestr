clc;clear;
%количество блоков
n=randi([4 8])
%массив n пустых матриц
matrices=cell(1,n);

for i = 1:n
    sizei=2*i-1;
    A=rand(sizei);
    num2str(sizei)
    matrices{i}=A;
end
%строим б-д
blkd=blkdiag(matrices{:});
blkd(1:1,end:end)=blkd(1,1);
blkd(1:1)=0;

subm=blkd(end-(2*n-2):end,end-(2*n-2):end);
blkd(end-(2*n-2):end, 1:2*n-1)=subm;
blkd(end-(2*n-2):end, end-(2*n-2):end)=0;

spy(blkd);