import matplotlib.pyplot as plt
import numpy as np
from math import cos, sin, sqrt
import sys

a = open('E.txt')
e = [float(i.strip()) for i in a.readlines()]

b = open('F.txt')
f = [float(i) for i in b.readlines()]

x, y = np.meshgrid(np.linspace(0, 256, int(sqrt(len(e)))),
                   np.linspace(0, 256, int(sqrt(len(e)))))

u = []
v = []
for i in range(int(sqrt(len(e)))):
    u.append([])
    v.append([])
    for j in range(int(sqrt(len(e)))):
        u[i].append(e[int(sqrt(len(e))) * i + j] * cos(f[int(sqrt(len(f))) * i + j]))
        v[i].append(e[int(sqrt(len(e))) * i + j] * sin(f[int(sqrt(len(f))) * i + j]))



plt.quiver(x, y[::-1], u, v, color='b')
plt.title('Test')

plt.grid()

if sys.argv[1] == 'V':
    plt.show()
else:
    plt.savefig('test_visualisation.png')
