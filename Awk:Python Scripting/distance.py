import math
import sys
import re
from collections import defaultdict

wordls = defaultdict(int)
wordls2 = defaultdict(int)
words_total=defaultdict(int)

f1=sys.argv[1] 
f2=sys.argv[2]

#Fills dictionary d with words from file fileadd
def fill(fileadd, d):
	fi=open(fileadd)
	for line in fi:
		ls=re.split("[^a-z]+",line.lower())
		lsf=[i for i in ls if len(i)>0]
		for word in lsf:
			d[word]+=1
	fi.close()

#Normalizes all of the values in dictionary d
def normalize(d):
	#Compute normalizing factor from dictionary d
	normf = 0
	for k,v in d.items():
		normf+=pow(v,2)
	normf=math.sqrt(normf)
	#Normalize dictionary
	for k,v in d.items():
		d[k]=v/normf

#Adds dictionary d to cumulative list of words
def addToWordList(d):
	for k,v in d.items():
		words_total[k]=1

fill(f1, wordls)
fill(f2, wordls2)

normalize(wordls)
normalize(wordls2)

addToWordList(wordls)
addToWordList(wordls2)

#Compute distance
distance=0
for k,v in words_total.items():
	distance+=pow((wordls[k]-wordls2[k]),2)
distance=math.sqrt(distance)

print(distance)


