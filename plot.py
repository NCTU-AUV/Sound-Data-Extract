import csv
import numpy as np
import pandas as pd
import matplotlib.pyplot as plt

pre_dir = "./blue/data/first/"
ext = ".csv"
pos = ["bl", "br"]
direction = ["pos", "neg"]
angle = ["45", "90"]

def load_data(filename):
	data = []
	with open(filename, 'r', encoding='utf-8') as fin:
		for row in fin:
			if len(row.split(",")) >= 2:
				f = row.split(",")[0]
				s = row.split(",")[1][:-1]
				f = int(f) if f != '' and f.isdigit() else 0
				s = int(s) if s != '' and s.isdigit() else 0
				data.append([f, s])
			else:
				data.append([0, 0])

	data = np.array(data)
	result = pd.DataFrame([])
	result['A'] = data[:, 0]
	result['B'] = data[:, 1]

	return filename, result

def plot(filename, data):
	a = list(data['A'].values)
	b = list(data['B'].values)

	plt.plot(np.arange(len(a)), a, label='A')
	plt.plot(np.arange(len(b)), b, label='B')

	plt.title(filename)

	#plt.savefig(filename.replace("blue", "blue/img").replace("csv", "png"))
	plt.show()
	plt.clf()

def exec():
	for p in pos:
		for d in direction:
			for a in angle:
				data = load_data(pre_dir+p+"_"+d+"_"+a+ext)
				plot(data[0], data[1])

	for p in pos:
		data = load_data(pre_dir+p+"_0"+ext)
		plot(data[0], data[1])

exec()