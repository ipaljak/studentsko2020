#!/bin/bash

python gen.py

for f in test/*.in.*
do
  ./A < $f > ${f/in/out}
done
