import numpy as np

instrFile = open("Instructions.txt", "w+")
logfile = open("logfile77MHzNewStressBN80.log", "r+")
logLines = logfile.readlines()
numLayers = 4
numRows = 128
numCols = 32
locs = []
for i in range(0, numRows):
	locs.append([])
	for j in range(0, numCols):
		locs[i].append(np.zeros(numLayers))
for l in range(0, len(logLines)):
	if ("Loaded" in logLines[l]):
		row = int(logLines[l].split(" ")[7].split(",")[0])
		col = int(logLines[l].split(" ")[9])
		instrFile.write("l " + str(row) + " " + str(col) + " ")
		valuesStr = logLines[l].split("[")[1].split("]")[0]
		for l in range(0, numLayers-1):
			instrFile.write(valuesStr.split(", ")[l] + " ")
			locs[row][col][l] = int(valuesStr.split(", ")[l])
		instrFile.write(valuesStr.split(", ")[numLayers-1] + "\n")
		locs[row][col][numLayers-1] = int(valuesStr.split(", ")[numLayers-1])
	elif ("RUN MODE" in logLines[l]):
		break
for r in range(0, numRows):
	for c in range(0, numCols):
		instrFile.write("l " + str(r) + " " + str(c) + " 32766 32766 32766 32766\n")
		instrFile.write("c " + str(r) + " 32766 32766 32766 32766\n")
		instrFile.write("l " + str(r) + " " + str(c) + " ")
		for l in range(0, numLayers-1):
			instrFile.write(str(int(locs[r][c][l])) + " ")
		instrFile.write(str(int(locs[r][c][numLayers-1])) + "\n")

logfile.close()
instrFile.close()
