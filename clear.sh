#!/bin/sh
make clean
if [ $? != 0 ]; then
	echo "Something wrong happend when executing command: make clean."
	exit -1
fi
rm -rf core*
if [ $? != 0 ]; then
	echo "Something wrong happend when executing command: make clean."
	exit -1
fi

