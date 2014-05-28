#/bin/bash

echo "Script works only when any new files are added to project"

cmake .

echo "Compile project"
make -j4

echo "Run project"
./bin/MasterThesisWojciechowski
