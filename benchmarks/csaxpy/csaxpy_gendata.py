#!/usr/bin/env python3

import numpy

size = 10000

info = numpy.finfo(numpy.float32)
nmant = 8 # Limit precision to avoid rounding errors
maxmant = 1 << nmant
minexp = info.minexp / 2
maxexp = (info.maxexp / 2) - nmant

# Generate floating-point values with exact mantissa and exponent
randf = lambda n: numpy.ldexp(
    numpy.random.randint(maxmant, size=n),
    numpy.random.randint(minexp, maxexp, size=n))

c = numpy.random.randint(2, size=size)
a = numpy.float32(randf(None))
X = randf(size).astype(numpy.float32)
Y = randf(size).astype(numpy.float32)

result = numpy.where(c, (a * X) + Y, Y)

def print_scalar(name, data):
    print('float {} = {}f;'.format(name, data))

def print_array(name, data, data_type='float', data_fmt='{}f', fold=10):
    print('{} {}[DATA_SIZE] = {{'.format(data_type, name))
    for i in range(0, len(data), fold):
        print('  ', ', '.join(data_fmt.format(x) for x in data[i:i+fold]), ',', sep='')
    print('};')

print('#define DATA_SIZE {}'.format(size))

print_scalar('input_data_a', a)
print_array('input_cond', c, 'bool', '{}', size)
print_array('input_data_X', X)
print_array('input_data_Y', Y)
print_array('verify_data', result)
