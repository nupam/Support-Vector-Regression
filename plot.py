import numpy as np
import matplotlib.pyplot as plt

data = np.genfromtxt('training.dat', delimiter=' ')
X = np.array([1,2,3,4,5,6,7,8,9,10,11,12])
for row in data:
	plt.plot(X, row, linewidth=0.5)
plt.xticks(X,
          ['Jan', 'Feb', 'March', 'April', 'May', 'June', 'July', 'Aug', 'Sep', 'Oct', 'Nov', 'Dec' ])
p = np.genfromtxt('predicted.dat', delimiter=' ')
plt.plot(X, p, color="red",  linewidth=2.5, linestyle="--", label="Next year prediction")
plt.legend(loc='upper left')
plt.xlabel("Months")
plt.ylabel("Rainfall in mm")
plt.show()




