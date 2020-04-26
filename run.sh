#!/bin/bash

echo 'enter language:'
result=$(python3 translator.py)

RESULT="$?"
if [ "$RESULT" != "0" ]; then
	echo $result
	exit 1
else
	langKey=$(echo $result | awk '{print $1}')
	lang=$(echo $result | awk '{print $2}')
fi

./dictionary $langKey $lang && kindlegen dictionary.opf

RESULT="$?"
if [ "$RESULT" == "1" ]; then
    exit 0
fi
