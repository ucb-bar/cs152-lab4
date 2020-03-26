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

A_real, A_imag, B_real, B_imag = (randf(size).astype(numpy.float32) for i in range(4))

result_real = (A_real * B_real) - (A_imag * B_imag)
result_imag = (A_imag * B_real) + (A_real * B_imag)

def print_array(name, real, imag):
    print('struct Complex {}[DATA_SIZE] = {{'.format(name))
    for r, i in zip(real, imag):
        print('  {{ {}f, {}f }},'.format(r, i))
    print('};')


print('#define DATA_SIZE {}'.format(size))

print_array('input_data_A', A_real, A_imag)
print_array('input_data_B', B_real, B_imag)
print_array('verify_data',  result_real, result_imag)
