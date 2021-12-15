#!/bin/bash

g++ -fPIC -fno-stack-protector -shared -rdynamic src/PAM/rc522.cpp -o rc522.so -lpam -lpam_misc -lserial

mv rc522.so /lib/x86_64-linux-gnu/security/pam_rc522.so