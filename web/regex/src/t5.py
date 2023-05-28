import random
import re

pattern = r'^[2468][02468]{3,4}$'
count = 0
right = 0
while right < 10:
    num = str(random.randint(0, 1000000))
    if re.fullmatch(pattern, num):
        right+=1
        print(num)
    count+=1
print('all = ',count)