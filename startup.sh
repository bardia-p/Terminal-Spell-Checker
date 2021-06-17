#!/bin/bash
make clean
make

cp -r ./bin /usr/local/bin
cp -r ./bin /usr/local/bin

cd $HOME
echo 'export PATH="$PATH:/usr/local/bin/bin"' >> ./bashrc
source .bashrc
