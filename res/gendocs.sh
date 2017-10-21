#!/bin/bash

if [ "$1" == "silent" ]; then
	doxygen res/doxygen.conf > /dev/null;
else
	doxygen res/doxygen.conf;
fi
