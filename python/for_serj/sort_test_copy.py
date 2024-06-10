# import os
# import numpy as np
import pandas as pd
import matplotlib.pyplot as plt
def print_header(need_columns_nums, output_file_string): #печатает шапку в отсортированном файле
    input_file.write("COLUMN\tVARIABLE\n-------------------\n")
    for i in range(0, len(need_columns_nums)):
        input_file.write(str(i+1) + "\t")
        i = output_file_string.find(str(need_columns_nums[i]) + "    ") + 9
        
        while output_file_string[i] != ' ':
            input_file.write(output_file_string[i])
            i += 1
        input_file.write("\n")
    input_file.write("-------------------\n\n")    

def set_orientation(orientations, end, start): #заполняет список, в котором содержатся направления движения частиц  
    if end < start:
        orientations.append(False)
    else:
        orientations.append(True)
    
def sort_data(need_columns_nums, output_file_string, step):
    fig, ax = plt.subplots()
    col_XPos = int(output_file_string[output_file_string.find("XPos")-17])
    col_YPos = int(output_file_string[output_file_string.find("YPos")-17])
    try:
        col_ZPos = int(output_file_string[output_file_string.find("ZPos")-17]) 
    except:
        col_ZPos = None
    col_Velocity = int(output_file_string[output_file_string.find("VelocityMagnitude")-17])
    
    print_header(need_columns_nums, output_file_string)
    for i in range(header_last_index+1):  #удаление шапки
        output_file_string = output_file_string[1:]   
    output_file_list = output_file_string.split("\n") # создание построчного списка
    last_string = output_file_string.count("\n") - 1
    need_axises = []
    string_num = 0
    difference_is_set = 0
    next_millimeter = 0.0
    last_nums = [0.0, 0.0]
    last_strings = [0, 0]
    particle_counter = 0
    orientations = []
    #первичное исследование файла
    #тут определяется в каком направлении движется каждая частица, false - против оси икс, true - по оси икс
    while string_num < len(output_file_list)-1:
        last_strings[0] = last_strings[1]
        last_strings[1] = output_file_list[string_num].split("\t")  # создание поэлементного списка
        if float(last_strings[1][0]) == 0: #если время равно нулю это новая частица
            if col_ZPos != None:
                starts = dict(
                        X=float(last_strings[1][col_XPos-1]), #здесь хранятся начала трёх координат у частицы
                        Y=float(last_strings[1][col_YPos-1]), 
                        Z=float(last_strings[1][col_ZPos-1])
                    )
            else: 
                starts = dict(
                        X=float(last_strings[1][col_XPos-1]), 
                        Y=float(last_strings[1][col_YPos-1])
                    )
            particle_counter += 1

        if float(last_strings[1][0]) == 0 and string_num != 0 or string_num == last_string: #если время равно нулю это новая частица 
            if col_ZPos != None:
                ends = dict(
                        X=float(last_strings[0][col_XPos-1]), #здесь хранятся концы трёх координат у частицы
                        Y=float(last_strings[0][col_YPos-1]), 
                        Z=float(last_strings[0][col_ZPos-1])
                    )
            else: 
                ends = dict(
                        X=float(last_strings[0][col_XPos-1]), 
                        Y=float(last_strings[0][col_YPos-1])
                    )
            if col_ZPos != None: # вычисляется путь по каждой оси
                if ends["Z"] <= 0:
                    way_z = abs(ends["Z"]-starts["Z"])
                else:
                    way_z = ends["Z"]-starts["Z"]
            
            if ends["Y"] <= 0:
                way_y = abs(ends["Y"]-starts["Y"])
            else:
                way_y = ends["Y"]-starts["Y"]
            
            if ends["X"] <= 0:
                way_x = abs(ends["X"]-starts["X"])
            else:
                way_x = ends["X"]-starts["X"]
            
            if col_ZPos != None: # вычисляется какой из путей больше и создается список 
                if way_x > way_y and way_x > way_z:
                    longest_axis = "X"
                    need_axises.append(col_XPos)
                    set_orientation(orientations, ends["X"], starts["X"])
                elif way_y > way_x and way_y > way_z:
                    longest_axis = "Y"
                    need_axises.append(col_YPos)
                    set_orientation(orientations, ends["Y"], starts["Y"])
                else:
                    longest_axis = "Z"
                    need_axises.append(col_ZPos)
                    set_orientation(orientations, ends["Z"], starts["Z"])
            else:
                if way_x > way_y:
                    longest_axis = "X"
                    need_axises.append(col_XPos)
                    set_orientation(orientations, ends["X"], starts["X"])
                elif way_y > way_x:
                    longest_axis = "Y"
                    need_axises.append(col_YPos)
                    set_orientation(orientations, ends["Y"], starts["Y"])                     
        string_num += 1 
    
    #где частица прошла нибольший путь, по той оси и сортируем
    input_file.write(str("total particles: " + str(particle_counter)))           
    particle_counter = 0
    string_num = 0
    last_strings = [0, 0] 
    last_nums = [0.0, 0.0]
    axis_x_data_list = []
    axis_y_data_list = []
    df = {}
    #сама сортировка и вывод    
    while string_num < len(output_file_list)-1:
        last_strings[0] = last_strings[1]
        last_strings[1] = output_file_list[string_num].split("\t")  # создание поэлементного списка
        this_column = 0
        if float(last_strings[1][0]) == 0: #если время равно нулю это новая частица
            difference_is_set = 0
            col_need_axis = need_axises[particle_counter]
            particle_counter += 1
            if string_num > 0:
                axis_x_data_list.append(abs(float(last_nums[0]))) #добавляет данные в список, по которым будет строиться график
                axis_y_data_list.append(float(last_strings[0][col_Velocity-1]))
                #создание грфиков для каждой частицы
                df = pd.DataFrame({'x': axis_x_data_list, 'y': axis_y_data_list})
                plt.plot(df['x'], df['y'], label= particle_counter-1)
                axis_x_data_list.clear()
                axis_y_data_list.clear()
            next_millimeter = 0
            if string_num == 0:
                input_file.write(
                    "\t this started at: "
                    +str(f'{float(last_strings[1][col_need_axis-1]):.5e}')
                    +str("\n" + "her number: " + str(particle_counter)) + "\t"
                )
                if col_need_axis == col_ZPos:
                    input_file.write("sorting at axis: Z\n\n")
                elif col_need_axis == col_YPos:
                    input_file.write("sorting at axis: Y\n\n")
                elif col_need_axis == col_XPos:
                    input_file.write("sorting at axis: X\n\n")
        if difference_is_set == 0: #это нужно чтоб столбец позиции х начинался не с рандомного числа а с 0
            if float(last_strings[1][col_need_axis-1]) < 0:
                difference = abs(float(last_strings[1][col_need_axis-1]))
            elif float(last_strings[1][col_need_axis-1]) > 0:
                difference = 0 - float(last_strings[1][col_need_axis-1])
            else:
                difference = 0
            difference_is_set = 1
        while this_column < len(need_columns_nums):
            if need_columns_nums[this_column] == col_need_axis:
                last_nums[0] = last_nums[1] # сохраняет последние два числа чтоб потом подобрать наиболее подходящее
                last_nums[1] = float(last_strings[1][col_need_axis-1])
                last_nums[1] += difference  #добавляет ко всем difference чтоб нчиналась позиция х с нуля              
                
                if next_millimeter - last_nums[0] > last_nums[1] - next_millimeter and orientations[particle_counter-1] == False: # движение частицы против оси 
                    #относительно идеального next_millimeter подбираем наиболее подходящее из имеющихся чисел 
                    input_file.write(str(f'{abs(last_nums[0]):.5e}') + "\t") #печатает столбец нужной оси
                    next_millimeter -= step #с указанным шагом
                    if float(last_strings[1][0]) != 0:
                        axis_x_data_list.append(abs(float(last_nums[0]))) #добавляет данные в список, по которым будет строиться график
                        axis_y_data_list.append(float(last_strings[0][col_Velocity-1]))
                    
                    for i in range(0, len(need_columns_nums) - 1): #выводит остальные столбцы
                        input_file.write(str(last_strings[0][need_columns_nums[this_column + i + 1]-1]) + "\t") #+ i + 1 чтоб пропустить повторный вывод XPos
                    if float(last_strings[1][0]) == 0: #если время равно нулю это новая частица
                        axis_x_data_list.append(abs(float(last_nums[1]))) #добавляет данные в список, по которым будет строиться график
                        axis_y_data_list.append(float(last_strings[1][col_Velocity-1]))
                        input_file.write(   
                                            "\t"
                                            +"\n\nnew particle!\t started at: "
                                            +str(f'{float(last_strings[1][col_need_axis-1]):.5e}')
                                            +str("\n" + "her number: " + str(particle_counter) + "\t")
                                        )
                        if col_need_axis == col_ZPos:
                            input_file.write("sorting at axis: Z\n\n" + str(f'{last_nums[1]:.5e}' + "\t")) 
                        elif col_need_axis == col_YPos:
                            input_file.write("sorting at axis: Y\n\n" + str(f'{last_nums[1]:.5e}' + "\t")) 
                        elif col_need_axis == col_XPos:
                            input_file.write("sorting at axis: X\n\n" + str(f'{last_nums[1]:.5e}' + "\t"))  
                        for i in range(0, len(need_columns_nums) - 1): #выводит остальные столбцы
                            input_file.write(str(last_strings[1][need_columns_nums[this_column + i + 1]-1]) + "\t") #+ i + 1 чтоб пропустить повторный вывод XPos
                    input_file.write("\n")           
   
                if next_millimeter - last_nums[0] < last_nums[1] - next_millimeter and orientations[particle_counter-1] == True: #движение частицы по оси 
                    # относительно идеального next_millimeter подбираем наиболее подходящее из имеющихся чисел  
                    input_file.write(str(f'{abs(last_nums[0]):.5e}') + "\t") #печатает столбец нужной оси
                    next_millimeter += step #с указанным шагом
                    if float(last_strings[1][0]) != 0:#
                        axis_x_data_list.append(abs(float(last_nums[0]))) #добавляет данные в список, по которыб будет строиться график
                        axis_y_data_list.append(float(last_strings[0][col_Velocity-1]))
                    
                    for i in range(0, len(need_columns_nums) - 1): #выводит остальные столбцы
                        input_file.write(str(last_strings[0][need_columns_nums[this_column + i + 1]-1]) + "\t") #+ i + 1 чтоб пропустить повторный вывод XPos
                    if float(last_strings[1][0]) == 0: #если время равно нулю это новая частица
                        axis_x_data_list.append(abs(float(last_nums[1]))) #добавляет данные в список, по которым будет строиться график
                        axis_y_data_list.append(float(last_strings[1][col_Velocity-1]))
                        input_file.write(   
                                            "\t"
                                            +"\n\nnew particle!\t started at: "
                                            +str(f'{float(last_strings[1][col_need_axis-1]):.5e}')
                                            +str("\n" + "her number: " + str(particle_counter) + "\t")
                                        )
                        if col_need_axis == col_ZPos:
                            input_file.write("sorting at axis: Z\n\n" + str(f'{last_nums[1]:.5e}' + "\t")) 
                        elif col_need_axis == col_YPos:
                            input_file.write("sorting at axis: Y\n\n" + str(f'{last_nums[1]:.5e}' + "\t")) 
                        elif col_need_axis == col_XPos:
                            input_file.write("sorting at axis: X\n\n" + str(f'{last_nums[1]:.5e}' + "\t"))  
                        for i in range(0, len(need_columns_nums) - 1): #выводит остальные столбцы
                            input_file.write(str(last_strings[1][need_columns_nums[this_column + i + 1]-1]) + "\t") #+ i + 1 чтоб пропустить повторный вывод XPos
                    input_file.write("\n")                   
                        
                else:
                    break
            this_column += 1
        string_num += 1
    print("Наибольший путь по оси: ", longest_axis, " (", f'{abs(last_nums[1]):.5e}',")", sep='')
     
    this_column = 0
    while this_column < len(need_columns_nums): #печатает отдельно последнюю строку
        if need_columns_nums[this_column] == col_need_axis:
            input_file.write(str(f'{abs(last_nums[0]):.5e}') + "\t")
            this_column += 1
            axis_x_data_list.append(abs(float(last_nums[0]))) #добавляет данные в список, по которым будет строиться график
            axis_y_data_list.append(float(last_strings[0][col_Velocity-1]))
        input_file.write(str(last_strings[1][need_columns_nums[this_column]-1]) + "\t")
        this_column += 1
    #создание грфика для последней частицы
    df = pd.DataFrame({'x': axis_x_data_list, 'y': axis_y_data_list})
    plt.plot(df['x'], df['y'], label= particle_counter) 
    
    #настройка внешнего вида графика
    plt.legend()
    if col_need_axis == col_ZPos:
        axis_x_name = "Axis Z"
    elif col_need_axis == col_YPos:
        axis_x_name = "Axis Y"
    else:
        axis_x_name = "Axis X" 
    plt.grid(True) 
    plt.xlabel(axis_x_name)
    plt.ylabel('VelocityMagnitude')
    plt.title('График зависимости скорости от положения в пространстве')
    
    ax.spines['left'].set_position('zero')# Установка точки (0, 0) в левый нижний угол
    ax.spines['bottom'].set_position('zero')
    ax.set_xlim(left=0)
    ax.set_ylim(bottom=0)
    
    plt.savefig(input_file.name + ".png", dpi=300)
    
file_out_is_found = False
# PATH = os.getcwd() + "/"
while file_out_is_found == False: 
    file_out = input("Введите имя файла откуда брать данные: ") 
    
    try: 
        with open(file_out, 'r') as output_file: 
            file_in = input("Куда поместить результат: ")
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
                header_last_index = output_file_string.find("+") - 9 #вывод шапки 
                for i in range(46, header_last_index):
                    print(output_file_string[i], end="")
                
                while not need_columns_nums_is_set:
                    need_columns_nums_string = input("Введите номера нужных столбцов через пробел: ")
                    need_columns_nums = need_columns_nums_string.split(" ")
                    try: 
                        need_columns_nums = list(map(int, need_columns_nums))
                        need_columns_nums_is_set = True
                        if count_of_cols < max(need_columns_nums) or min(need_columns_nums) < 1:
                            print("Слишком большие или слишком маленькие числа")
                            need_columns_nums_is_set = False
                    except:
                        print("Данные введены неверно!")
                        need_columns_nums_is_set = False
                sort_data(need_columns_nums, output_file_string, step)    
    except FileNotFoundError:
        print("Такой файл не найден!")
print("Готово!")