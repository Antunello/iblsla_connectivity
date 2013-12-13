#!/bin/bash

if [ $# -lt 1 ] 
then
	echo "Usage: $0 <module-id>"
	exit 1
fi

MODULE="$1"

set -x
mkdir -p "modules"
mkdir -p "modules/${MODULE}"
mkdir -p "modules/${MODULE}/optinsp"
mkdir -p "modules/${MODULE}/cfg"
mkdir -p "modules/${MODULE}/usb_rt"
mkdir -p "modules/${MODULE}/usb_converted"
mkdir -p "modules/${MODULE}/usb_converted/cfg"
mkdir -p "modules/${MODULE}/usb_converted/with_hv"
mkdir -p "modules/${MODULE}/usb_converted/without_hv"
mkdir -p "modules/${MODULE}/rce_rt"
mkdir -p "modules/${MODULE}/rce_rt/with_hv"
mkdir -p "modules/${MODULE}/rce_rt/without_hv"
## JUst in case we use RCE system for reception test
