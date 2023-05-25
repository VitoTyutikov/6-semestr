import random
import re

pattern = r'^.*[02468]{3}.*$'
count = 0
right = 0
while right < 10:
    num = str(random.randint(100, 10000))
    if not re.fullmatch(pattern, num):
        right+=1
        print(num)
    count+=1
print('all = ',count)
