clc;clear;
str='This предложение не должно exist';
words=split(str);
longWord="";
for i=1:length(words)
    word = words{i};
    if(strlength(word)>strlength(longWord))
        longWord = word;
    end
end
disp(longWord);