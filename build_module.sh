#!/bin/bash

gcc -fPIC -fno-stack-protector -c src/rc522.cpp

sudo ld -x --shared -o /lib/security/rc522.so rc522.o

rm rc522.o