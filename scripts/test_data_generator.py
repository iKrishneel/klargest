#!/usr/bin/env python

import os
import sys
import random
import string

TEST_FOLDER = 'tests'
test_dir_ = None

def random_string(size=10, chars=string.digits):
    return ''.join(random.choice(chars) for _ in range(size))

def generate(size):
    val_size = random.randint(2, 1e3)
    
    filename = 'test_' + str(size).zfill(8) + '.txt'
    result_fn = filename[:-4] + '_actual.txt'

    filename = os.path.join(test_dir_, filename)
    result_fn = os.path.join(test_dir_, result_fn)

    d_list = []
    with open(filename, 'w') as outfile:
        for i in range(size):
            idd = str(i).zfill(12) # random_string(size=10)
            value = random.randint(-val_size, val_size)
            d_list.append([idd, value])

            outfile.write('{} {}\n'.format(idd, value))
    outfile.close()

    # get the result    
    # sort and get top k result
    d_list = sorted(d_list, key=lambda x: x[1], reverse=True)

    # write the results
    with open(result_fn, 'w') as outfile:
        for d in d_list:
            idd, value = d
            outfile.write('{} {}\n'.format(idd, value))
    outfile.close()

    
def main(argv):
    try:
        dir_path = os.path.dirname(os.path.realpath(__file__))
        dir_path = os.path.abspath(os.path.join(dir_path, os.pardir))

        global test_dir_
        test_dir_ = os.path.join(dir_path, TEST_FOLDER)
        
        if not os.path.isdir(test_dir_):
            os.mkdir(test_dir_)
        
        gen_size = int(argv[1])
        generate(gen_size)
    except (IndexError, ValueError):
        print ('Enter the size of data to be generate: eg. 5')

    return

if __name__ == '__main__':
    main(sys.argv)
