#!/bin/bash
set -e

g++ -std=c++0x *.cpp -lboost_regex -o main
