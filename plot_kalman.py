import matplotlib.pyplot as plt
import numpy as np
import pandas as pd

pre_dir = "./data/fourth/data/"

def Load_Data(filename):
	data = []
	with open(filename, 'r', encoding='utf-8') as fin:
		for row in fin:
			row = row.split(" ")
			data.append([float(row[0]), float(row[1][:-1])])

	data = np.array(data)
	result = pd.DataFrame([])
	result['before'] = data[:, 0]
	result['after'] = data[:, 1]

	return filename, result

def Plot(filenames):
	for f in filenames:
		fname, data = Load_Data(pre_dir+f)
		
		a = list(data['before'].values)
		b = list(data['after'].values)

		plt.plot(np.arange(len(a)), a, label='before')
		plt.plot(np.arange(len(b)), b, label='after')

		plt.title(fname)

		plt.show()
		plt.clf()
		
Plot(["N_30l_kalman_output.txt", "N_30r_kalman_output.txt"])