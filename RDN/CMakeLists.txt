cmake_minimum_required(VERSION 3.12)
project(RDN)

set(CMAKE_CXX_STANDARD 14)

include_directories(.)
include_directories(Creation)
include_directories(Lecture)

add_executable(RDN
        Creation/inputs_RDN.txt
        Creation/Makefile
        Creation/RDN_main
        Creation/RDN_main.c
        Creation/RDN_main.h
        Creation/training
        Lecture/inputs_RDN.txt
        Lecture/lecture.c
        Lecture/lecture.h
        Lecture/outputs_RDN.txt
        network.h
        neuron.h
        saved_RDN_LBIW.txt)
