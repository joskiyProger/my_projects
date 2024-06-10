import pandas as pd
import matplotlib.pyplot as plt
import tkinter as tk
from tkinter import filedialog

def browseFiles():
    global PATH_output_file
    PATH_output_file = filedialog.askopenfilename(initialdir = "/",
                                          title = "Select a File")
    # Change label contents
    last_slash = 0
    for i in range(0, len(PATH_output_file)):
        if PATH_output_file[i] == '/' or PATH_output_file[i] == '\\':
            last_slash = i
    
    label_PATH['text'] = "Выбранный файл: "+PATH_output_file[last_slash + 1:]
    try:  
        with open(PATH_output_file, 'r') as output_file:
            output_file_string = output_file.read()
    except:
        print("неверный out файла")
    header_last_index = output_file_string.find("+") - 9 #вывод шапки 
    for i in range(46, header_last_index):
        print(output_file_string[i], end="")
    
def set_need_columns_nums():
    need_columns_nums = need_columns_nums_entry.get()
    try:
        need_columns_nums = need_columns_nums.split(' ')
        need_columns_nums = list(map(int, need_columns_nums))
        return need_columns_nums
    except:
        print("Неверные символы в поле для шага")

def set_step():
    step = step_entry.get()
    try:
        step = float(step)
        return step
    except:
        print('неверно введен шаг')
        
def open_file(PATH_input_file, need_columns_nums, step):
    # print(PATH_input_file)
    try:  
        with open(PATH_output_file, 'r') as output_file:
            try:  
                with open(PATH_input_file, 'w') as input_file:
                    output_file_string = output_file.read()
                    try:
                        sort_data(need_columns_nums, output_file_string, step, input_file)
                    except:
                        print('sort_data error')
            except:
                print("неверный in файла")
    except:
        print("неверный out файла")
def match_data():
    if PATH_output_file and not input_file_entry.get():
        dot_index = None
        for i in range(len(PATH_output_file)):
            if PATH_output_file[i] == '.':
                dot_index = i
        if dot_index != None:
            PATH_input_file = PATH_output_file[:dot_index] + '_processed' + PATH_output_file[dot_index:]  
        else:
            PATH_input_file = PATH_output_file + '_processed'
        
        need_columns_nums = set_need_columns_nums() 
        step = set_step()
        open_file(PATH_input_file, need_columns_nums, step)
    elif PATH_output_file and input_file_entry.get():
        for i in range(len(PATH_output_file)):
            if PATH_output_file[i] == '/' or PATH_output_file[i] == '\\':
                slash_index = i
        PATH_input_file = PATH_output_file[:slash_index+1] + input_file_entry.get()
        need_columns_nums = set_need_columns_nums()
        step = set_step()
        open_file(PATH_input_file, need_columns_nums, step)
    else:
        print("укажите исходящий файл")

def print_header(need_columns_nums, output_file_string, input_file): #печатает шапку в отсортированном файле
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
    
def sort_data(need_columns_nums, output_file_string, step, input_file):
    fig, ax = plt.subplots()
    col_XPos = int(output_file_string[output_file_string.find("XPos")-17])
    col_YPos = int(output_file_string[output_file_string.find("YPos")-17])
    try:
        col_ZPos = int(output_file_string[output_file_string.find("ZPos")-17]) 
    except:
        col_ZPos = None
    col_Velocity = int(output_file_string[output_file_string.find("VelocityMagnitude")-17])
    
    print_header(need_columns_nums, output_file_string, input_file)
    header_last_index = output_file_string.find("+") - 9 #вывод шапки 
    # for i in range(46, header_last_index):
    #     print(output_file_string[i], end="")
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
                ax.scatter(axis_x_data_list, axis_y_data_list)
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

    ax.scatter(axis_x_data_list, axis_y_data_list)

    plt.plot(df['x'], df['y'], label=particle_counter) 
    
    #настройка внешнего вида графика
    plt.legend()
    if col_need_axis == col_ZPos:
        axis_x_name = "Путь, пройденный частицей, по оси Z (м)"
    elif col_need_axis == col_YPos:
        axis_x_name = "Путь, пройденный частицей, по Y (м)"
    else:
        axis_x_name = "Путь, пройденный частицей, по X (м)" 
    plt.grid(True) 
    plt.xlabel(axis_x_name)
    plt.ylabel('Скорость частицы (м\с)')
    plt.title('График зависимости скорости от положения в пространстве')

    ax.plot(1, 0, '>k', transform=ax.transAxes, clip_on=False)
    ax.plot(0, 1, '^k', transform=ax.transAxes, clip_on=False)

    ax.spines['left'].set_position('zero')# Установка точки (0, 0) в левый нижний угол
    ax.spines['bottom'].set_position('zero')

    ax.set_xlim(left=0)
    ax.set_ylim(bottom=0)
    
    plt.savefig(input_file.name + ".png", dpi=300)

root = tk.Tk()
root.title("Обработка")
root.geometry("430x165")
# root.resizable(False, False)
# root.iconphoto(False, tk.PhotoImage(file= 'icon.png'))
label_bg_colors = 0xffffff
PATH_output_file = ''

# tk.Label(root, text='').grid()
label_PATH = tk.Label(root, 
                    text = "Выбранный файл: "+str(PATH_output_file), 
                    font= 20                   
                    )
label_PATH.grid(sticky='w', columnspan=2)
label_output_file = tk.Label(root,
                 text="Выберите исходный файл",
                #  bg= '#' + str(hex(label_bg_colors))[2:],
                 font= 20
                ).grid(row=1, column=0)
button_explore = tk.Button(root, 
                        text = "Выбрать файл",
                        command = browseFiles,
                        font= 20
                        ) 
button_explore.grid(row=1, column=1, sticky='we')

label_input_file = tk.Label(root,
                 text="Имя выходного файла",
                #  bg= '#' + str(hex(label_bg_colors))[2:],
                 font= 20
                ).grid(row=2, column=0, sticky='w')
input_file_entry = tk.Entry(root, font= 20)
input_file_entry.grid(row=2, column=1)

label = tk.Label(root,
                 text="Введите нужные столбцы",
                 font= 20
                ).grid(row=4, column=0, sticky='w')

need_columns_nums_entry = tk.Entry(root, font= 20)
need_columns_nums_entry.grid(row=4, column=1)

label = tk.Label(root,
                 text="Введите шаг",
                 font= 20
                ).grid(row=5, column=0, sticky='w')
step_entry = tk.Entry(root, font= 20)
step_entry.grid(row=5, column=1)

button_to_sort = tk.Button(root, 
                        text = "Обработать",
                        font= 20,
                        command = match_data,
                        ).grid(sticky='we', columnspan=2)

root.mainloop()