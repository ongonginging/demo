#!/bin/sh
make clean
if [ $? != 0 ]; then
	echo "Something wrong happend when executing command: make clean."
	exit -1
fi
make
if [ $? != 0 ]; then
	echo "Something wrong happend when executing command: make."
	exit -1
fi
./program
if [ $? != 0 ]; then
	echo "Something wrong happend when executing command: ./program."
	exit -1
fi

