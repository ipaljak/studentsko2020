#!/bin/bash

python gen.py

for f in test/H.in.*
do
  ./H < $f > ${f/in/out}
done
