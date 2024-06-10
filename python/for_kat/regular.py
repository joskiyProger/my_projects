import re
import os

pattern = '20\d\d_'
testString = '2023 timeweb 34 community 58'
result = []
PATH = os.path.abspath(os.curdir)
all_files = os.listdir(PATH)
for file in all_files:
    if re.findall(pattern + 'Покровское.xlsx', file) or re.findall(pattern + 'Южное.xlsx', file) or re.findall(pattern + 'Покровское.xlsx', file) or re.findall(pattern + 'Покровское_\d.xlsx', file) or re.findall(pattern + 'Южное_\d.xlsx', file):
        result.append(file)

print(result)