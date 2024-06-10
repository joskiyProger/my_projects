import pandas as pd
import tkinter as tk
from tkinter import filedialog
from tkinter import ttk
from tkinter import *

# def browseFiles():
#     global PATH_output_file
#     PATH_output_file = filedialog.askopenfilename(initialdir = "/",
#                                           title = "Select a File")
#     # Change label contents
#     label_PATH['text'] = "Выбранный файл: " + PATH_output_file

def check_containing(need_name, name):
    if (len(need_name) > 0 and  need_name in name) or len(need_name) == 0:
        return 1
    else:
        return 0

def find_fio():
    need_name = name_entry.get().strip().capitalize()
    names = list(df['Имя умершего'])
    need_last_name = last_name_entry.get().strip().capitalize()
    last_names = list(df['Фамилия умершего'])
    need_surname = surname_entry.get().strip().capitalize()
    surnames = list(df['Отчество умершего'])

    for i in range(4, len(names)):
        if check_containing(need_name, names[i]) + check_containing(need_last_name, last_names[i]) + check_containing(need_surname, surnames[i]) == 3:
            table.insert('', tk.END, values=list(df.iloc[i]))    



df = pd.read_excel('tab.xlsx', skiprows=4)
df = {key.capitalize(): value for key, value in df.items()}
for i in range(4, len(list(df['Имя умершего']))):
    df['Имя умершего'][i] = df['Имя умершего'][i].capitalize()

for i in range(4, len(list(df['Фамилия умершего']))):
    df['Фамилия умершего'][i] = df['Фамилия умершего'][i].capitalize()

for i in range(4, len(list(df['Отчество умершего']))):
    df['Отчество умершего'][i] = df['Отчество умершего'][i].capitalize()
df = pd.DataFrame(df)
# print(df.head()[:6])

root = tk.Tk()
root.title("Для дяди")
root.geometry("800x336+1500+300")
# root.resizable(False, False)

root.iconphoto(False, tk.PhotoImage(file= 'icon.png'))
label_bg_colors = 0xffffff
PATH_output_file = ''

# tk.Label(root, text='').grid()
# label_output_file = tk.Label(root,
#                  text="Выберите файл",
#                  bg= '#' + str(hex(label_bg_colors))[2:],
#                  font= 20
#                 ).grid(row=1, column=0, sticky='we')
# button_explore = tk.Button(root, 
#                         text = "Выбрать файл",
#                         command = browseFiles,
#                         ) 
# button_explore.grid(row=1, column=1, sticky='we')

last_name_label = tk.Label(root,
                 text="Фамилия",
                 bg= '#' + str(hex(label_bg_colors))[2:],
                 font= 20
                ).grid(row=2, column=0, sticky='we')
last_name_entry = tk.Entry(root)
last_name_entry.grid(row=2, column=1,sticky='we')

name_label = tk.Label(root,
                 text="Имя",
                 bg= '#' + str(hex(label_bg_colors))[2:],
                 font= 20
                ).grid(row=3, column=0, sticky='we')
name_entry = tk.Entry(root)
name_entry.grid(row=3, column=1,sticky='we')

surname_label = tk.Label(root,
                 text="Отчество",
                 bg= '#' + str(hex(label_bg_colors))[2:],
                 font= 20
                ).grid(row=4, column=0, sticky='we')
surname_entry = tk.Entry(root)
surname_entry.grid(row=4, column=1,sticky='we')

# label_PATH = tk.Label(root, 
#                       text = "Выбранный файл: "+str(PATH_output_file),                    
#                       )
# label_PATH.grid(row=5,sticky='we')

button_to_find = tk.Button(root, 
                        text = "Найти",
                        command = find_fio,
                        ).grid(row=6,sticky='we', columnspan=2)

# founded_persons = tk.Label(root, 
#                       text = "Найденные люди",
#                       font= 30                   
#                       )
# founded_persons.grid(row=7, columnspan=2)

headers_list = df.columns.tolist()

table = ttk.Treeview(columns=headers_list, show="headings")
for item in headers_list:
    table.column(item, anchor=W, width=len(item) * 11)
    table.heading(item, text=item, anchor=CENTER)


xscrollbar = ttk.Scrollbar(root,orient=HORIZONTAL,command=table.xview)
xscrollbar.grid(row=9, column=0, sticky=EW, columnspan=2)
table.configure(xscrollcommand=xscrollbar.set)

yscrollbar = ttk.Scrollbar(root,orient=VERTICAL,command=table.yview)
# yscrollbar.grid(row=8, column=1, sticky=NS)
table.configure(yscrollcommand=yscrollbar.set)

root.grid_columnconfigure(0, weight=1)
root.grid_rowconfigure(0, weight=1)
    
table.grid(row=8, column=0, sticky="nsew", columnspan=2)

root.mainloop()