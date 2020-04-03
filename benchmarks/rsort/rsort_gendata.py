#!/usr/bin/env python

import sys
import random

n = int(sys.argv[1])

l = [random.randint(1, (1 << 31) - 1) for _ in range(n)]

print "#define DATA_SIZE {}".format(n)

def print_arr(t, name, data):
    print "{} {}[{}] = ".format(t, name, n)
    print "{"
    print ", ".join(map(str, data))
    print "};"

print_arr("type", "input_data", l)
l.sort()
print_arr("type", "verify_data", l)
