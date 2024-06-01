#!/bin/bash

./build/test_multiplication &> tmp
grep "^Error:*" tmp | awk '{print $2, $i}' | sort -n | uniq | awk '{for (i=2; i<NF; i++) printf $i " "; print $NF}'
rm tmp
