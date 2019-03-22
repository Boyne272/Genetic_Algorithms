import matplotlib.pyplot as plt
import numpy as np


#its = np.loadtxt("5_cell.txt").astype('int32')
its1 = np.loadtxt("5_cell_pop_100_mu0.015_.txt").astype('int32')
#its2 = np.loadtxt("5_cell_pop_200_mu0.012.txt").astype('int32')
#its3 = np.loadtxt("5_cell_pop_300_mu0.012.txt").astype('int32')
#
#its4 = np.loadtxt("5_cell_pop_100_mu0.02.txt").astype('int32')
#its5 = np.loadtxt("5_cell_pop_200_mu0.02.txt").astype('int32')
#its6 = np.loadtxt("5_cell_pop_300_mu0.02.txt").astype('int32')
#
#its7 = np.loadtxt("5_cell_pop_100_mu0.01.txt").astype('int32')
#its8 = np.loadtxt("5_cell_pop_200_mu0.01.txt").astype('int32')
#its9 = np.loadtxt("5_cell_pop_300_mu0.01.txt").astype('int32')
#
#its10 = np.loadtxt("5_cell_pop_100_mu0.015.txt").astype('int32')
#its11 = np.loadtxt("5_cell_pop_200_mu0.015.txt").astype('int32')
#its12 = np.loadtxt("5_cell_pop_300_mu0.015.txt").astype('int32')

green_diamond = dict(markerfacecolor='g', marker='D')
its1 = sorted(its1)[:-10]
plt.hist(its1, bins = 500)
fig2, ax2 = plt.subplots(figsize = (6,3))
ax2.set_title('pop_100_mu0.015')
ax2.boxplot(its1, vert=False, flierprops=green_diamond)