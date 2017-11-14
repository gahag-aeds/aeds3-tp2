#!/usr/bin/env python3

import os, sys

import tptester


tests_dir = os.path.dirname(os.path.realpath(__file__))


tptester.tp_test(
  #[ 1, 2, 3, 4, 5, 6, 7, 8, 9, 10 ],
  [ 2, 3, 4, 5, 6, 7, 8, 9, 10, 11, 12, 13, 14, 15, 16, 17, 18, 19, 20, 21, 22, 23, 24, 25, 26, 27, 28, 29, 30 ],
  
  os.getcwd() + '/' + sys.argv[1],
  
  #valgrind = True,
  
  graph = True,
  
  input_file = lambda ix:  tests_dir + '/data/bench/' + str(ix) + '.in',
  answer_file = lambda ix: None, #tests_dir + '/data/toys/' + str(ix) + '.out',
  
  args = lambda ix: [ ],
  stdin = lambda ifile: ifile,
  output = lambda ofile, stdout: stdout
)
