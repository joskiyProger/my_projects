def print_columns(need_columns_nums, output_file_list, col_XPos, step):
    string_num = 0
    difference_is_set = 0
    need_columns_nums_index = 0
    col_XPos_index = 0
    next_millimeter = 0.0
    last_nums = [0.0, 0.0]
    last_strings = [0, 0] #нужен изза того что без него программа печатает строку следующую за нужной строкой позиции х
    while need_columns_nums_index < len(need_columns_nums): #определяет индекс столбца позиции х 
        if need_columns_nums[need_columns_nums_index] == col_XPos: #в исходящем списке всех нужных столбцов
            col_XPos_index = need_columns_nums_index
        need_columns_nums_index += 1
    while string_num < len(output_file_list)-1:
        break_status = 0
        last_strings[0] = last_strings[1]
        last_strings[1] = output_file_list[string_num].split("\t")  # создание поэлементного списка
        this_column = 0
        if last_strings[1][0] == 0: 
            next_millimeter = 0
            difference_is_set = 0
            print(last_strings[1][0])
        if difference_is_set == 0: #это нужно чтоб столбец позиции х начинался не с -1.9 а с 0
            difference = abs(float(last_strings[1][need_columns_nums[col_XPos_index]-1]))
            difference_is_set = 1
        while this_column < len(need_columns_nums):
            if need_columns_nums[this_column] == col_XPos:
                last_nums[0] = last_nums[1] # сохраняет последние два числа чтоб потом подобрать наиболее подходящее
                last_nums[1] = float(last_strings[1][need_columns_nums[col_XPos_index]-1])
                last_nums[1] += difference  #добавляет ко всем -1.9 чтоб нчиналась позиция х с нуля
                if next_millimeter - last_nums[0] < last_nums[1] - next_millimeter:
                    #относительно идеального next_millimeter подбираем наиболее подходящее из имеющихся чисел 
                    input_file.write(str(f'{last_nums[0]:.5e}')) #печатает столбец позиции х
                    input_file.write("\t")                       
                    next_millimeter += step #с указанным шагом
                    for i in range(0, len(need_columns_nums) - 1): #выводит остальные столбцы
                        input_file.write(str(last_strings[0][need_columns_nums[this_column + i + 1]-1])) #+ i + 1 чтоб пропустить повторный вывод XPos
                        input_file.write("\t")
                else:
                    break_status = 1
                    break
            this_column += 1
        if break_status == 0:
            input_file.write("\n")
        string_num += 1
    while this_column < len(need_columns_nums):
        if need_columns_nums[this_column] == col_XPos:
            input_file.write(str(f'{last_nums[0]:.5e}'))
            input_file.write("\t")
            this_column += 1
        input_file.write(str(last_strings[1][need_columns_nums[this_column]-1]))
        input_file.write("\t")
        this_column += 1
    
file_out_is_found = False
while file_out_is_found == False: 
    file_out = input("Введите имя файла откуда брать данные: ") 
    try: 
        with open(file_out, 'r') as output_file: 
            file_in = input("Куда поместить резульат: ")
            file_out_is_found= True
            with open(file_in, 'w') as input_file:
                output_file_string = output_file.read()
                column_XPos_num = int(output_file_string[output_file_string.find("XPos")-17])
                
                need_columns_nums = []
                need_columns_nums_is_set = False
                step_is_set = False
                count_of_cols = int(output_file_string[output_file_string.find("COLUMNS") + 9]) #определяет количество столбцов
                while not step_is_set:
                    try:
                        step = float(input("Укажите шаг: "))  
                        step_is_set = True
                    except:
                        print("Это не число!")
                        step_is_set = False
                header_last_index = output_file_string.find("+") - 9 #вывод шапки и её удаление
                for i in range(46, header_last_index):
                    print(output_file_string[i], end="")
                for i in range(header_last_index+1):  
                    output_file_string = output_file_string[1:]   
                output_file_list = output_file_string.split("\n") # создание построчного списка
                
                while not need_columns_nums_is_set:
                    need_columns_nums_string = input("Ведите номера нужных столбцов через пробел: ")
                    need_columns_nums = need_columns_nums_string.split(" ")
                    try: 
                        need_columns_nums = list(map(int, need_columns_nums))
                        need_columns_nums_is_set = True
                        if count_of_cols < max(need_columns_nums) and min(need_columns_nums) < 1:
                            print("Данные введены неверно!")
                            need_columns_nums_is_set = False
                    except:
                        print("Данные введены неверно! try")
                        need_columns_nums_is_set = False
                print_columns(need_columns_nums, output_file_list, column_XPos_num, step)    
    except FileNotFoundError:
        print("Такой файл не найден!")
print("Готово!")