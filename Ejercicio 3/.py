
#!/usr/bin/python
import random
from math import factorial

file = open('complejidadfactorial.txt', 'w+')

for x in xrange(1, 20, 1):
		file.write(str(float(x**x)/10000) + ' ' +'\n')
file.close()
