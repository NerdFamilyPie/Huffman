#!/bin/tcsh

if ($# < 1) then
	echo "Usage: binaryview.sh <filename>. It will display the file in binary format."
	exit 1;
endif

 xxd -b $1


