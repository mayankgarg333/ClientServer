#!/usr/bin/python
import csv
import random
import os



for ss in range(1,5):
    directory="data"
    filename= directory+"/session_"+str(ss)+".csv"
    if not os.path.exists(directory):
        os.makedirs(directory)
    if os.path.exists(filename):
        os.remove(filename)
    with open(filename ,'a+b') as csv_file:
        writer = csv.writer(csv_file)
        for i in range(1,11):
			list2=["this is line # " + str(i) +" of session # " + str(ss)]
			writer.writerow(list2)
        csv_file.close()

