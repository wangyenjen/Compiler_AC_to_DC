# !/usr/bin/bash

cd ..

echo 'Clean src'
cd src
make clean
cd ..

echo 'Remove dc code'
cd test
rm *.dc
