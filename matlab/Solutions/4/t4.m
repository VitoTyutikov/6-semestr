clc;clear;
str1='wireless1';
str2='java';
count = 0;
for i=1:min(strlength(str1),strlength(str2))
    if str1(i)==str2(i)
        count = count+1;
    else
        break;
    end
end
disp(count);
