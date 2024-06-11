import pandas as pd
import matplotlib.pyplot as plt

fig, ax = plt.subplots()

elements = [10000, 20000, 30000, 40000, 50000, 60000, 70000, 80000, 90000, 100000, 110000, 120000, 130000, 140000, 150000, 160000, 170000, 180000, 190000, 200000]
fnv = [3615, 7181, 10858, 14520, 18158, 21803, 25434, 29052, 32730, 36543, 40147, 43841, 47576, 51224, 55050, 58651, 62337, 66042, 69677, 73341]
kp = [3775, 7461, 11194, 14950, 18542, 22230, 25955, 29547, 33163, 36958, 40616, 44280, 47927, 51619, 55354, 59034, 62676, 66320, 70047, 73665]
df = pd.DataFrame({'x': elements, 'y': fnv})
ax.scatter(elements, fnv)
plt.plot(df['x'], df['y'], label= 'FNV')

df = pd.DataFrame({'x': elements, 'y': kp})
ax.scatter(elements, kp)
plt.plot(df['x'], df['y'], label= 'KP')

# df = pd.DataFrame({'x': elements, 'y': selection})
# plt.semilogy(df['x'], df['y'], label= 'Selection Sort')

plt.grid(True)
plt.xlabel("Количество элементов")
plt.ylabel("Количество коллизий")
# ax.spines['left'].set_position('zero')# Установка точки (0, 0) в левый нижний угол
# ax.spines['bottom'].set_position('zero')
# ax.set_xlim(left=0)
# ax.set_ylim(bottom=0)
plt.legend()
 
plt.title('Зависимость количества коллизий от количества элементов')
plt.savefig("graph.png")
