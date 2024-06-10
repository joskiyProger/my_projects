import matplotlib.pyplot as plt

# Создание графика
x = [1, 2, 3, 4, 5]
y1 = [1, 2, 3, 4, 5]
y2 = [5, 4, 3, 2, 1]
plt.plot(x, y1, label='Линия 1')
plt.plot(x, y2, label='Линия 2')

# Установка легенды в определенное место за пределами графика
plt.legend(bbox_to_anchor=(1.02, 1))

# Отображение графика
plt.savefig('график.png')