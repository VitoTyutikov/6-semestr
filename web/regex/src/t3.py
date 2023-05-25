import random
import re

pattern = r'^.*[02468]$'
count = 0
right = 0
while right < 10:
    num = str(random.randint(0, 100))
    if re.fullmatch(pattern, num):
        right+=1
        print(num)
    count+=1
print('all = ',count)
