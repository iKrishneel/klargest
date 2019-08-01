#!/usr/bin/env python

import os
import sys

actual_filename = 'actual'
result_filename = 'result'

def read_textfile(filename):
    return [line.rstrip('\n').split(' ') for line in open(filename)]

def compare(result_fn, actual_fn):
    print ('Loading actual results into memory. Please wait a moment...')
    
    result = read_textfile(result_fn)
    actual = read_textfile(actual_fn)

    # sort files by identifier
    sort = lambda x: sorted(x, key = lambda x: x[0], reverse=True)
    # actual_s = sort(actual)
    # result_s = sort(result)

    # create dict for actual
    actual_s = {}
    for i, v in actual:
        actual_s[i] = v

    # compare
    # since the result of the algorithm is not sorted, an if all values are same
    # then there is a chance that value with different id is selected.
    # in this for-loop check that value is same
    is_same = True
    for i, (idd, value) in enumerate(result):
        if actual_s[idd] != value:
            print ("Not Same for ID: {} Excepted Value {} Got: {}".format(idd, actual_s[idd], value))
            is_same = False
            
    if is_same:
        print ("Files compared and both matches")
    
def main(argv):
    try:
        result_fn = argv[1]
        assert os.path.isfile(result_fn), 'Invalid file path'
        
        # get the actual sorted result filename
        name = result_fn.split(os.sep)[-1].split('_')[0:2]
        actual_fn = ''
        for n in name:
            actual_fn += (n + '_')

        fname = result_fn.split(os.sep)[0]
        actual_fn = os.path.join(fname, actual_fn + (actual_filename + '.txt'))
        assert os.path.isfile(actual_fn), 'Actual result file name {} not found'.format(actual_fn)
        assert os.path.isfile(result_fn), 'File name {} not found'.format(result_fn)

        print ('Comparing: \nActual: {} \nResult: {}'.format(actual_fn, result_fn))
        
        compare(result_fn, actual_fn)
        
    except IndexError:
        pass
        

if __name__ == '__main__':
    main(sys.argv)
