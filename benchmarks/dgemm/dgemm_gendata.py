#!/usr/bin/env python3

import numpy

size = 43

randf = lambda n: numpy.random.randint(0, 10000, size=n)

A = randf((size, size)).astype(numpy.float64)
B = randf((size, size)).astype(numpy.float64)
result = numpy.matmul(A, B)

def print_array(name, data, data_size, data_type='double', data_fmt='{}', fold=10):
    print('{} {}[{}] = {{'.format(data_type, name, data_size))
    for i in range(0, len(data), fold):
        print('  ', ', '.join(data_fmt.format(x) for x in data[i:i+fold]), ',', sep='')
    print('};')

print('#define DATA_SIZE {}'.format(size))

matrix_size = 'DATA_SIZE * DATA_SIZE'
print_array('input_data_A', A.flatten(), matrix_size)
print_array('input_data_B', B.flatten(), matrix_size)
print_array('verify_data', result.flatten(), matrix_size)
