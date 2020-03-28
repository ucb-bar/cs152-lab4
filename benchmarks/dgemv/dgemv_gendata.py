#!/usr/bin/env python3

import numpy

col_size = 100
row_size = 50

info = numpy.finfo(numpy.float64)
nmant = 8 # Limit precision to avoid rounding errors
maxmant = 1 << nmant
minexp = info.minexp / 2
maxexp = (info.maxexp / 2) - nmant

# Generate floating-point values with exact mantissa and exponent
randf = lambda n: numpy.ldexp(
    numpy.random.randint(maxmant, size=n),
    numpy.random.randint(minexp, maxexp, size=n))

A = randf((row_size, col_size)).astype(numpy.float64)
x = randf(col_size).astype(numpy.float64)
result = numpy.dot(A, x)

def print_array(name, data, data_size, data_type='double', data_fmt='{}', fold=10):
    print('{} {}[{}] = {{'.format(data_type, name, data_size))
    for i in range(0, len(data), fold):
        print('  ', ', '.join(data_fmt.format(x) for x in data[i:i+fold]), ',', sep='')
    print('};')

print('#define ROW_SIZE {}'.format(row_size))
print('#define COL_SIZE {}'.format(col_size))

print_array('input_data_A', A.flatten(), 'ROW_SIZE * COL_SIZE')
print_array('input_data_x', x, 'COL_SIZE')
print_array('verify_data', result, 'ROW_SIZE')
