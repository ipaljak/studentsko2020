#!/bin/bash

python gen.py

for f in test/*.in.*
do
  ./K < $f > ${f/in/out}
done
