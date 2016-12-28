#!/usr/bin/python
import csv
import random
import os

D={}
ke=65
v=97

for i in range(1):
    for j in range(26):
        for k in range(26):
            key=chr(ke+j)+chr(ke+k)
            value=chr(v+j)+chr(v+k)
            D[key]=value
        

directory="data"    
if not os.path.exists(directory):
	os.makedirs(directory)

with open(directory+'/dict.csv', 'wb') as csv_file:
    writer = csv.writer(csv_file)
    for key, value in D.items():
		writer.writerow([key, value])
#	csv_file.close()

with open(directory+'/dict.csv', 'rb') as csv_file:
    reader = csv.reader(csv_file)
    mylist = list(reader)


for ss in range(10):
    filename= directory+"/session_"+str(ss+1)+".csv"
    if os.path.exists(filename):
        os.remove(filename)
    with open(filename ,'a+b') as csv_file:
        writer = csv.writer(csv_file)
        for i in range(1000):
            index=random.randint(0,len(mylist)-1)
            key=mylist[index][0]
            value=mylist[index][1]
            typ=random.random()
            if typ<float(5)/10:
                list2=["GET", key]
            else:
                list2=["PUT",key, value]
            writer.writerow(list2)
        csv_file.close()
        
for ss in range(1):
    filename= directory+"/all_put.csv"
    if os.path.exists(filename):
        os.remove(filename)
    with open(filename ,'a+b') as csv_file:
        writer = csv.writer(csv_file)
        for i in range(len(mylist)):
            key=mylist[i][0]
            value=mylist[i][1]
            list2=["PUT",key, value]
            writer.writerow(list2)
        csv_file.close()
