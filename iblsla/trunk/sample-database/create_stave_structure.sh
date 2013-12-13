#!/bin/bash

if [ $# -lt 1 ] 
then
	echo "Usage: $0 <stave-id>"
	exit 1
fi

echo "Creating stave structure of: $1"
fname="$1"

exec<$fname

IFS=$'\t'

read STAVE chip rce inlink outlink

mkdir -p "staves"
mkdir -p "staves/${STAVE}"
mkdir -p "staves/${STAVE}/before_tc"
mkdir -p "staves/${STAVE}/before_tc/with_hv"
mkdir -p "staves/${STAVE}/before_tc/without_hv"
mkdir -p "staves/${STAVE}/before_tc/IV"
mkdir -p "staves/${STAVE}/after_tc"
mkdir -p "staves/${STAVE}/after_tc/with_hv"
mkdir -p "staves/${STAVE}/after_tc/without_hv"
mkdir -p "staves/${STAVE}/after_tc/IV"