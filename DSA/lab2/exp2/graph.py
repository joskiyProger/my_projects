import pandas as pd
import matplotlib.pyplot as plt

fig, ax = plt.subplots()

elements = [10000, 20000, 30000, 40000, 50000, 60000, 70000, 80000, 90000, 100000, 110000, 120000, 130000, 140000, 150000, 160000, 170000, 180000, 190000, 200000]
hashtab = [0.000071, 0.000081, 0.000071, 0.000059, 0.000061, 0.000061, 0.000059, 0.000061, 0.000051, 0.000081, 0.000100, 0.000078, 0.000059, 0.000098, 0.000081, 0.000059, 0.000081, 0.000100, 0.000071, 0.000051]
bstree = [0.000161, 0.000151, 0.000127, 0.000120, 0.000149, 0.000178, 0.000107, 0.000090, 0.000139, 0.000159, 0.000159, 0.000161, 0.000183, 0.000132, 0.000161, 0.000139, 0.000161, 0.000151, 0.000178, 0.000171]
df = pd.DataFrame({'x': elements, 'y': hashtab})
ax.scatter(elements, hashtab)
plt.plot(df['x'], df['y'], label= 'Hastab')

df = pd.DataFrame({'x': elements, 'y': bstree})
ax.scatter(elements, bstree)
plt.plot(df['x'], df['y'], label= 'BST')

plt.grid(True)
plt.xlabel("Количество элементов")
plt.ylabel("Время б(с)")
# ax.spines['left'].set_position('zero')# Установка точки (0, 0) в левый нижний угол
# ax.spines['bottom'].set_position('zero')
# ax.set_xlim(left=0)
# ax.set_ylim(bottom=0)
plt.legend()
 
plt.title('Зависимость времени добаления от количества элементов')
plt.savefig("graph2.png")
