#!/bin/sh

programname=$1
#Länge des Arrays, kann angepasst werden, falls das Testarray angepasst werden sollte
len=43
arr=""
i=0
while [ $i -lt $len ]; do
  arr="$arr $i"
  i=$((i + 1))
done

for val in $arr; do
  perf stat -e minor-faults,dTLB-load-misses,dTLB-store-misses ./$programname "$val"
done

