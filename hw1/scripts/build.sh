# !/usr/bin/bash

cd ..

echo 'Build src'
cd src
make
cd ..

echo 'Generate dc code'
for f in test/*ac; do
    echo
    echo '['$f']'
    ./src/AcDc $f ${f::-2}dc
done


