clc;clear;
str='ЭТОТ.ТЕКСТ.НАБРАН.КАПСОМ.';
newStr="";
flag=false;
for i=1:strlength(str)
    if str(i)=='.'
        flag=true;
        newStr=newStr+str(i);
    end
    if(str(i)>='А'&&str(i)<='Я')
        if flag
            newStr=newStr+str(i);
        else
            newStr=newStr+lower(str(i));
        end
    flag=false;
    end
    
end
display(newStr);