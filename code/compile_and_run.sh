./clean.sh

echo "Compile project"
cmake .
make -j4

echo "Run project"
./bin/MasterThesisWojciechowski
