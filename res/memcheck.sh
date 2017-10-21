#!/bin/bash

valgrind --tool=memcheck --leak-check=full --suppressions=res/memcheck.supp ./bin/mcalc
