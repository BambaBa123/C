#!/bin/sh
gcc -o machine machine.c 
xterm -hold -e "./machine ; $SHELL" &