import matplotlib.pyplot as plt
import pandas as pd

data: pd.DataFrame = pd.read_csv("DATA", sep="\t", header=None)

plt.scatter(data[0],data[1])

ax = plt.gca()

ax.grid(True)

plt.xlabel("x")
plt.ylabel("y")

plt.legend()
plt.show()