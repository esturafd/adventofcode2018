#!/usr/bin/env bash

FREQUENCY=0

while read line; do
   SIGN=${line:0:1}
   NUMBER=${line:1}
   if [[ $SIGN == "+" ]]; then
      FREQUENCY=$((FREQUENCY + NUMBER))
   else
      FREQUENCY=$((FREQUENCY - NUMBER))
   fi
done < input.txt

echo "The resulting frequency is $FREQUENCY"
