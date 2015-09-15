import sys
import re

#helper method to deterministic
def nodups(ls):
	#from first to 2nd to last element
	for i in range(0, len(ls)-1):
		for x in range(i+1, len(ls)):
			if(ls[i] == ls[x]):
				return 0
	return 1

def deterministic(ls):
	for sublist in ls:
		first_chars = []
		for item in sublist:
			first_chars.append(item[0])
		if(nodups(first_chars)==0): return 0
	return 1

#removes newline from last item in list
def clean(ls):
	item = ls[len(ls)-1]
	ls[len(ls)-1] = item[:len(item)-1]
	return ls;

def fill_states(fileadd):
	#makes assumption that start and end are first/second to last in names respectively
	fi = open(fileadd)
	li = []
	begin_read = 0
	for line in fi:
		if("[states]" in line):
			begin_read = 1
			continue
		elif("[transitions]" in line):
			begin_read = 0
			continue
		elif(begin_read == 0):
			continue
		elif("names:" in line):
			temp = re.split(r": *",line)
			els = re.split(r", *", temp[1])
			for item in els:
				li.append(item)
		# elif("end:" in line):
		# 	li = clean(li)
		# 	temp = re.split(r": *", line)
		# 	temp = clean(temp)
		# 	end = temp[1]
		# 	li.remove(end)
		# 	li.append(end)
		else:
			continue
	return li


#stores transitions in 2D array in format: 'a:1'
def fill_trans(fileadd):
	#assumes transitions listed in order of names
	fi = open(fileadd)
	trans = []
	begin_read = 0
	for line in fi:
		if("[transitions]" in line):
			begin_read=1
			continue
		elif(begin_read==0):
			continue
		elif("[states]" in line):
			begin_read = 0
			continue
		else:
			#extract name
			temp = line.split(":")
			name = temp[0]
			#get and store transitions
			temp2 = re.findall(r".:\w+",line)
			#temp2 = temp2[1:]
			trans.append(temp2);
	return trans;

fi = sys.argv[1]
states = clean(fill_states(fi))
trans = fill_trans(fi)
instr = sys.argv[2]

print("states=")
print(states)
print("Trans = ")
print(trans)
#print("determ = ",deterministic(trans))

if(deterministic(trans)==0):
	print("Error: nondeterministic function given.")
	sys.exit()

state = states[0]
for char in instr:
	#for each transition matching current state
	match = 0;
	for t in trans[states.index(state)]:
		#if exact match on state
		if(t[0] == char):
			temp = t.split(":")
			state = temp[1]
			match = 1
			break
	#if no match found, use wildcard
	if(match==0):
		for t in trans[states.index(state)]:
			if(t[0] == '*'):
				temp = t.split(":")
				state = temp[1]
				match = 1
				break
		#if cases were non-exhaustive
		if(match==0):
			print("Error: non-exhautive function given.")
			sys.exit()

if(state == states[len(states)-2]):
	print("Accept")
else:
	print("Reject. Ended in state", state)


