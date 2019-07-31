#!/usr/bin/env python

import os
import sys

actual_filename = 'actual'
result_filename = 'result'

def read_textfile(filename):
    return [line.rstrip('\n').split(' ') for line in open(filename)]

def compare(result_fn, actual_fn):
    result = read_textfile(result_fn)
    actual = read_textfile(actual_fn)

    # sort files by identifier
    sort = lambda x: sorted(x, key = lambda x: x[0], reverse=True)
    # result_s = sorted(result, key = lambda x: x[0], reverse=True)
    # actual_s = sorted(actual, key = lambda x: x[0], reverse=True)
    actual_s = sort(actual)
    result_s = sort(result)

    # compare
    is_same = True
    for i, (r, a) in enumerate(zip(result_s, actual_s)):
        if not (r[0] == a[0] and r[1] == a[1]):
            print ("Not Same: {}".format([i, a, r]))

            is_same = False
    if is_same:
        print ("Files compared and both matches")
    
def main(argv):
    try:
        test_fn = argv[1]
        assert os.path.isfile(test_fn), 'Invalid file path'

        splited = test_fn.split(os.sep)
        name = splited[-1].split('_')[-2]

        result_fn = None
        actual_fn = None
        if name == actual_filename:
            actual_fn = test_fn
            result_fn = test_fn.replace(actual_filename, result_filename)
        elif name == result_filename:
            actual_fn = test_fn.replace(result_filename, actual_filename)
            result_fn = test_fn

        if result_fn is None or actual_fn is None:
            print ('Invalid test file')
            return
        
        assert os.path.isfile(result_fn), 'File name {} not found'.format(result_fn)
        assert os.path.isfile(actual_fn), 'File name {} not found'.format(actual_fn)

        print ('Comparing: \nActual: {} \nResult: {}'.format(actual_fn, result_fn))
        
        compare(result_fn, actual_fn)
        
    except IndexError:
        pass
        

if __name__ == '__main__':
    main(sys.argv)
