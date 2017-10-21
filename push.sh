#!/bin/bash

if [ "$1" != "" ]; then
	res/gendocs.sh silent
	git add -A;
	git commit -m "$1";
	git push;
fi
