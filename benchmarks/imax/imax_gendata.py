#!/usr/bin/env python3

import numpy

size = 1000
dup = 10

info = numpy.finfo(numpy.float32)
maxmant = 1 << info.nmant
minexp = info.minexp
maxexp = info.maxexp - info.nmant

# Generate floating-point values with exact mantissa and exponent
randf = lambda n: numpy.ldexp(
    numpy.random.randint(maxmant, size=n),
    numpy.random.randint(minexp, maxexp, size=n))

data = randf(size).astype(numpy.float32)
# Duplicate elements to test that routine returns lowest index
data = numpy.repeat(data, dup)
numpy.random.shuffle(data)
index = numpy.argmax(data)

def print_scalar(name, data, data_type='const unsigned int'):
    print('{} {} = {};'.format(data_type, name, data))

def print_array(name, data, data_type='float', data_fmt='{}f', fold=10):
    print('{} {}[DATA_SIZE] = {{'.format(data_type, name))
    for i in range(0, len(data), fold):
        print('  ', ', '.join(data_fmt.format(x) for x in data[i:i+fold]), ',', sep='')
    print('};')

print('#define DATA_SIZE {}'.format(len(data)))

print_scalar('verify_index', index)
print_array('input_data', data)
