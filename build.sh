#!/bin/sh
# g++ $1 -lgtest -L. -I. -pthread -DGTEST_LEAK_TEST
g++ $1 -lgtest -L. -I. -pthread
