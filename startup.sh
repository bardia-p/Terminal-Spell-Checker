#!/bin/bash

make clean
make

cp -r ./bin /usr/local/bin
cp -r ./bin /usr/local/bin

sudo echo 'export PATH=":/usr/local/bin/bin:$PATH"' >> ~/.bashrc

source ~/.bashrc
