import pandas as pd
import matplotlib.pyplot as plt

fig, ax = plt.subplots()

elements = [10000, 20000, 30000, 40000, 50000, 60000, 70000, 80000, 90000, 100000, 110000, 120000, 130000, 140000, 150000, 160000, 170000, 180000, 190000, 200000]
bstree = [0.000120, 0.000137, 0.000161, 0.000161, 0.000081, 0.000159, 0.000220, 0.000181, 0.000190, 0.000142, 0.000161, 0.000137, 0.000210, 0.000222, 0.000249, 0.000220, 0.000151, 0.000308, 0.000247, 0.000330]
hashtab = [0.000122, 0.000090, 0.000039, 0.000081, 0.000061, 0.000059, 0.000049, 0.000059, 0.000059, 0.000059, 0.000090, 0.000051, 0.000020, 0.000059, 0.000032, 0.000059, 0.000049, 0.000049, 0.000061, 0.000081]
df = pd.DataFrame({'x': elements, 'y': bstree})
ax.scatter(elements, bstree)
plt.plot(df['x'], df['y'], label= 'BST')

df = pd.DataFrame({'x': elements, 'y': hashtab})
ax.scatter(elements, hashtab)
plt.plot(df['x'], df['y'], label= 'Hashtab')

plt.grid(True)
plt.xlabel("Количество элементов")
plt.ylabel("Время, (c)")
# ax.spines['left'].set_position('zero')# Установка точки (0, 0) в левый нижний угол
# ax.spines['bottom'].set_position('zero')
# ax.set_xlim(left=0)
# ax.set_ylim(bottom=0)
plt.legend()
 
plt.title('Зависимость времени поиска элемента от количества элементов')
plt.savefig("graph.png")
