##############################################################################################################
# File: /Users/leonexxe/code/JSIS/makefile                                                                   #
# Project: /Users/leonexxe/code/JSIS                                                                         #
# Created Date: Friday, August 26th 2022, 12:27:05 pm                                                        #
# Author: Leonexxe (Leon Marcellus Nitschke-Höfer)                                                           #
# -----                                                                                                      #
# Copyright (c) 2022 Leon Marcellus Nitschke-Höfer (Leonexxe)                                                #
# -----                                                                                                      #
# You may not remove or alter this copyright header.                                                         #
##############################################################################################################
all: main cppCompare

main:
	clang++ ./main.cpp -o ./bin/JSIS -std=c++20 -Wno-return-type

cppCompare:
	clang++ ./cppCompare.cpp -o ./bin/JSIS_CPPCompare -std=c++20 -Wno-return-type

compare: cppCompare main
	~/code/JSIS-engine/bin/JSIS_CPPCompare
	cd ~/JSIS_test;~/code/JSIS-engine/bin/JSIS;
	clear
	cat ./compare/JSIS.txt
	cat ./compare/cpp.txt