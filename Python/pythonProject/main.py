import numpy as np
from matplotlib import pyplot as plt
from scipy import optimize
from mpl_toolkits.mplot3d import Axes3D

fig = plt.figure(figsize=(10, 10))
axes = fig.gca(projection='3d')


def f(x, y):
    return (x ** 2 + y ** 2)


y = x = np.linspace(-3, 3, 50)

x, y = np.meshgrid(x, y)
z = f(x, y)

# выполняю оптимизацию
optimize.minimize(f, -3, args=(3))  # возможно здесь что-то не так пишу
optimization = optimize.minimize(f, -3, args=(3))

surf = axes.plot_surface(x, y, z, cmap='coolwarm',
                         linewidth=0, antialiased=False)

surf1 = axes.plot_surface(x, y, f(optimization.x, y), cmap='coolwarm',
                          linewidth=0, antialiased=False)

axes.set_xlabel('Ось X')
axes.set_ylabel('Ось Y')
axes.set_zlabel('Ось Z')

plt.show()