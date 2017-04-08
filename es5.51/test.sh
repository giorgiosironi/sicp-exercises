#!/bin/bash
set -e

echo "Unit"
./runUnitTests

echo "End2end"
python -m unittest tests.test_end2end
