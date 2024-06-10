from tkinter import Tk, messagebox

def on_close():
    response = messagebox.askyesno('Выход', 'Вы уверены, что хотите выйти?')
    if response:
        root.destroy()

root = Tk()
root.protocol('WM_DELETE_WINDOW', on_close)
root.mainloop()