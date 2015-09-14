
#!/usr/bin/python
import random
import math

file = open('complejidadNlogN.txt', 'w+')

for x in xrange(1, 10000, 100):
		file.write(str(x*math.log10(x)/6000) + ' ' +'\n')

file.close()
