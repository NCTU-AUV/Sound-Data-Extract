from sklearn.preprocessing import normalize

pre_dir = "./data/fourth/data/"
ext = ".txt"

def Normalize(filename):
	X = []
	with open(filename, 'r', encoding='utf-8') as fin:
		for row in fin:
			row = row.split(",")
			X.append([float(row[0]), float(row[1][:-1])])

	Xn = normalize(X)

	return Xn

def Run(filenames):
	for f in filenames:
		Xn = Normalize(pre_dir+f+ext)

		with open(pre_dir+f+"_N"+ext, 'w', encoding='utf-8') as fout:
			for i in range(len(Xn)):
				fout.write(str(Xn[i][0])+","+str(Xn[i][1])+"\n")

Run(["dual_30l_pin0"])