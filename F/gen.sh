#!/bin/bash

python gen.py

for f in test/*.in.*
do
  ./F < $f > ${f/in/out}
done
