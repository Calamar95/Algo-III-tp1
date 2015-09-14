
#!/usr/bin/python
import random

file = open('ejRandom.in', 'w+')

for x in xrange(1,10000, 100):
	i = 0
	while i < x:
		file.write(str(random.randrange(-x,x)) + ' ')
		i = i + 1
	
	file.write('\n')

file.close()


file2 = open('ejPeorCaso.in', 'w+')

for x in xrange(1,10000, 100):
	i = 0
	if random.randrange(0,2) == 0:
		num = random.randrange(-x,0)
		while i < x:
			num = num + (random.randrange(x)+1)
			file2.write(str(num) + ' ')
			i = i + 1
	else:
		num = random.randrange(0,x)
		while i < x:
			num = num - (random.randrange(x)+1)
			file2.write(str(num) + ' ')
			i = i + 1
	file2.write('\n')

file2.close()



file3 = open('ejMejorCaso.in', 'w+')

for x in xrange(1,10000, 100):
	i = 0
	signo = 0
	num = 0
	aux = 0
	aux2 = 0
	while i < x:
		if signo == 0:
			num = aux + (random.randrange(x)+1)
			aux = num
			signo = 1
		else:
			num = aux2 - (random.randrange(x)+1)
			aux2 = num
			signo = 0
		file3.write(str(num) + ' ')
		i = i + 1
	
	file3.write('\n')

file3.close()