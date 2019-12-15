from sklearn import preprocessing
import numpy as np

pre_dir = "./data/fourth/data/"
ext = ".txt"

def Normalize(filename):
	X = []
	Y = []
	with open(filename, 'r', encoding='utf-8') as fin:
		for row in fin:
			row = row.split(",")
			X.append(float(row[0]))
			Y.append(float(row[1][:-1]))
	
	X = np.array(X)
	Y = np.array(Y)

	Xn = X / np.linalg.norm(X)
	Yn = Y / np.linalg.norm(Y)

	return Xn, Yn

def Run(filenames):
	for f in filenames:
		Xn, Yn = Normalize(pre_dir+f+ext)

		with open(pre_dir+f+"_N"+ext, 'w', encoding='utf-8') as fout:
			for i in range(len(Xn)):
				fout.write(str(Xn[i])+","+str(Yn[i])+"\n")

Run(["dual_90l_pin0", "dual_90r_pin0"])