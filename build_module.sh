#!/bin/bash

g++ -fPIC -fno-stack-protector -shared -rdynamic src/PAM/rc522.cpp -o rc522.so -lpam -lpam_misc -lserial