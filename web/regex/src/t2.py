import re

pattern = r'^(0+|1+|(10)+1?|(01)+0?)$'
strings = "010101,11,00,101,0110,001,11101".split(",")
for string in strings:
    if re.fullmatch(pattern, string):
        print(string)