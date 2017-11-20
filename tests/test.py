#!/usr/bin/env python3

import os, sys

import tptester


tests_dir = os.path.dirname(os.path.realpath(__file__))


tptester.tp_test(
  #[ 1, 2, 3, 4, 5, 6, 7, 8, 9, 10 ],
  #[ 2, 3, 4, 5, 6, 7, 8, 9, 10, 11, 12, 13, 14, 15, 16, 17, 18, 19, 20, 21, 22, 23, 24, 25, 26, 27, 28, 29, 30, 31, 32, 33, 34, 35, 36, 37, 38, 39, 40, 41, 42, 43, 44, 45, 46, 47, 48, 49, 50, 51, 52, 53, 54, 55, 56, 57, 58, 59, 60, 61, 62, 63, 64 ],
  #[ 2, 4, 6, 8, 10, 12, 14, 16, 18, 20, 22, 24, 26, 28, 30, 32, 34, 36, 38, 40, 42, 44, 46, 48, 50, 52, 54, 56, 58, 60, 62, 64 ],
  [ 1000, 10000, 100000 ],
  
  os.getcwd() + '/' + sys.argv[1],
  
  #valgrind = True,
  
  graph = True,
  
  input_file = lambda ix:  tests_dir + '/data/bench/big/' + str(ix) + '.in',
  answer_file = lambda ix: None, #tests_dir + '/data/toys/' + str(ix) + '.out',
  
  args = lambda ix: [ ],
  stdin = lambda ifile: ifile,
  output = lambda ofile, stdout: stdout
)
