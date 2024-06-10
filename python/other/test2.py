def swap(list_1, i):
    temp = list_1[i]
    list_1[i] = list_1[i+1]
    list_1[i+1] = temp
    
def check(list_1):
    ch = False
    for i in range(0, len(list_1)-1):
        if i % 2 == 0 and list_1[i] % 2 != 0:
            ch = True
        elif i % 2 != 0 and list_1[i]+1 % 2 == 0:
            ch = True
        else:
            ch = False
            break            
    return ch
                
        
stud = int(input())
str1 = input()
list_1 = str1.split(" ")
list_1 = list(map(int, list_1))
i = 0
is_set = 0
while i < len(list_1)-1:
    swap(list_1, i)
    if check(list_1):
        print(i+1, i+2)
        is_set = 1
        break
    swap(list_1, i)
    i += 1
if is_set == 0:
    print ("-1 -1")