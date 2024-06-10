import tkinter as tk
# from tkinter import *
from tkinter import filedialog

def browseFiles():
    global PATH_output_file
    PATH_output_file = filedialog.askopenfilename(initialdir = "/",
                                          title = "Select a File")
    # Change label contents
    label_PATH['text'] = "File Opened: "+PATH_output_file
    
def set_need_columns_nums():
    need_columns_nums = need_columns_nums_entry.get()
    try:
        need_columns_nums = need_columns_nums.split(' ')
        need_columns_nums = list(map(int, need_columns_nums))
    except:
        print("Неверные символы в поле для шага")

def set_step():
    step = step_entry.get()
    try:
        step = float(step)
        print(step)
    except:
        print('неверно введен шаг')

def match_data():
    if PATH_output_file and not input_file_entry.get():
        output_file = PATH_output_file
        dot_index = None
        for i in range(len(PATH_output_file)):
            if PATH_output_file[i] == '.':
                dot_index = i
        if dot_index != None:
            input_file = PATH_output_file[:dot_index] + '_sorted' + PATH_output_file[dot_index:]  
        else:
            input_file = PATH_output_file + '_sorted'
        set_need_columns_nums() 
        set_step()   
    elif PATH_output_file and input_file_entry.get():
        output_file = PATH_output_file
        for i in range(len(PATH_output_file)):
            if PATH_output_file[i] == '/' or PATH_output_file[i] == '\\':
                slash_index = i
        input_file = PATH_output_file[:slash_index+1] + input_file_entry.get()
        set_need_columns_nums()
        set_step()
    else:
        print("укажите исходящий файл")

root = tk.Tk()
root.title("Сортировка")
root.geometry("500x600+1500+300")
root.resizable(False, False)
root.iconphoto(False, tk.PhotoImage(file= 'icon.png'))
label_bg_colors = 0xffffff
PATH_output_file = ''

tk.Label(root, text='').grid()
label_output_file = tk.Label(root,
                 text="Выберите файл для сортировки",
                 bg= '#' + str(hex(label_bg_colors))[2:],
                 font= 20
                ).grid(row=1, column=0)
button_explore = tk.Button(root, 
                        text = "Выбрать файл",
                        command = browseFiles,
                        ) 
button_explore.grid(row=1, column=1, sticky='we')

label_input_file = tk.Label(root,
                 text="Имя отсортированного файла",
                 bg= '#' + str(hex(label_bg_colors))[2:],
                 font= 20
                ).grid(row=2, column=0, sticky='we')
input_file_entry = tk.Entry(root)
input_file_entry.grid(row=2, column=1)

label_PATH = tk.Label(root, 
                    text = "File Opened: "+str(PATH_output_file),
                    fg = "blue",
                    
                    )
label_PATH.grid(sticky='w')

label = tk.Label(root,
                 text="Введите нужные столбцы",
                 font= 20
                ).grid(row=4, column=0, sticky='w')

need_columns_nums_entry = tk.Entry(root)
need_columns_nums_entry.grid(row=4, column=1)

label = tk.Label(root,
                 text="Введите шаг",
                 font= 20
                ).grid(row=5, column=0, sticky='w')
step_entry = tk.Entry(root)
step_entry.grid(row=5, column=1)

button_to_sort = tk.Button(root, 
                        text = "Сортировать",
                        command = match_data,
                        ).grid(sticky='we')

root.mainloop()