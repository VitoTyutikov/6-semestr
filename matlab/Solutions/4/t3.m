clc;clear;
str='This предложение не должно exist';
st=['а','у','о','ы','э','я','ю','ё','и','е','a', 'e', 'i', 'o', 'u', 'y'];
count=0;
for i=1:strlength(str)
    if ismember(lower(str(i)),st)
        count=count+1;
    end
end
disp(count);
