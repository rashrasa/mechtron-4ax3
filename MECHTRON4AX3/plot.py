import matplotlib.pyplot as plt
import pandas as pd

df_cont: pd.DataFrame = pd.read_csv("OUT.tsv", sep="\t")
df_lti: pd.DataFrame = pd.read_csv("OUT_LTI.tsv", sep="\t")

# plt.scatter(df["time"],df["pos_x"], label="x")
# plt.scatter(df["time"],df["pos_y"], label="y")

# plt.scatter(df["time"],df["vel_x"], label="v_x")
# plt.scatter(df["time"],df["vel_y"], label="v_y")

plt.scatter(df_cont["pos_x"],df_cont["pos_y"], label="Position (cont.)")
#plt.scatter(df_lti["pos_x"],df_lti["pos_y"], label="Position (LTI)")
ax = plt.gca()

ax.set_xlim([-10, 150])
ax.set_ylim([-10, 150])
ax.grid(True)

plt.xlabel("x Position")
plt.ylabel("y Position")
plt.title("Plot of Position for ball thrown with v0=35, alpha=Pi/3 (Continuous Version)")

plt.legend()
plt.show()