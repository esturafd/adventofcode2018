#!/usr/bin/env bash

FREQUENCY=0
SAVEF=0

while [ -z "$VALID" ]; do
   while read line && [ -z "$VALID" ]; do
      SIGN=${line:0:1}
      NUMBER=${line:1}
      if [[ $SIGN == "+" ]]; then
         FREQUENCY=$((FREQUENCY + NUMBER))
      else
         FREQUENCY=$((FREQUENCY - NUMBER))
      fi
      if echo -e "$SAVEF" | grep "^$FREQUENCY\$" &>/dev/null; then
         VALID=false
      else
         SAVEF="$SAVEF\n$FREQUENCY"
         printf "\033[2K%s\r" "$FREQUENCY"
      fi
   done < input.txt
done

echo "The resulting frequency is $FREQUENCY"
