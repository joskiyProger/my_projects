# import seaborn as sns 

# # loading dataset 
# data = sns.load_dataset("iris") 
 
# # draw lineplot 
# sns.lineplot(x="sepal_length", y="sepal_width", data=data)

# importing pandas library 
# import pandas as pd 
# importing matplotlib library 
import matplotlib.pyplot as plt 
  
import seaborn as sns

# Создаем набор данных
x = [1, 2, 3, 4, 5]
y = [2, 4, 6, 8, 10]

# Используем функцию lineplot для построения графика
sns.lineplot(x, y)

# Отображаем график
plt.show()