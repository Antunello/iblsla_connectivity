#!/bin/bash
# Stave loading file,

if [ $# -lt 1 ] 
then
	echo "Usage: $0 <stave-id>"
	exit 1
fi

echo "Creating soft links for: $2"

sname="$1"


exec<$sname

read STAVE chip rce inlink outlink
echo "${STAVE}"
while read MODULE chip rce inlink outlink
do
echo $MODULE
ln -s "../../staves/${STAVE}" "$(pwd)/modules/${MODULE}/stave"
done
