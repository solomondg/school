#!/usr/bin/env python3

import matplotlib.pyplot as plt
from mpl_toolkits.mplot3d import Axes3D
from mpl_toolkits.mplot3d import Axes3D
import matplotlib.pyplot as plt
from matplotlib import cm
from matplotlib.ticker import LinearLocator, FormatStrFormatter
import numpy as np

fig = plt.figure()
import numpy as np
ax = fig.add_subplot(111, projection='3d')


def f(x, y):
    return np.abs(-601*x-y+54)+abs(-579*x-y+46)+abs(-572*x-y+42)+abs(-617*x-y+50)+abs(-566*x-y+43)+abs(-547*x-y+41)+abs(-597*x-y+46)+abs(-580*x-y+39)+abs(-536*x-y+37)+abs(-579*x-y+45)+abs(-576*x-y+45)+abs(-601*x-y+41)+abs(-664*x-y+55)


def f2(x, y):
    a1 = np.abs(584 - 7615*x - 13*y)
    a2 = np.sqrt(np.square(x) + 1)
    return np.divide(a1, a2)

X = np.arange(-4, 4, 0.1)
Y = np.arange(-150, 150, 0.5)
X, Y = np.meshgrid(X, Y)
#  print (X)
#  R = np.sqrt(X**2 + Y**2)
#  Z = np.sin(R)
Z = f2(X, Y)

print(Z)

# Plot the surface.
surf = ax.plot_surface(X, Y, Z, cmap=cm.coolwarm,
                       linewidth=0, antialiased=False)

# Customize the z axis.
ax.set_zlim(0, 7000)
ax.zaxis.set_major_locator(LinearLocator(10))
ax.zaxis.set_major_formatter(FormatStrFormatter('%.02f'))

# Add a color bar which maps values to colors.
fig.colorbar(surf, shrink=0.5, aspect=5)

plt.show()

