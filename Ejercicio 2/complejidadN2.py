
#!/usr/bin/python
import random
from math import factorial

file = open('complejidadN2.txt', 'w+')

for x in xrange(1, 20, 1):
		file.write(str(float(factorial(x))/3) + ' ' +'\n')
file.close()
