# This script cleans all CMake files from project and bin directory

echo "Cleaning..."

rm -f bin/*

makefile_list=$(find . -name Makefile)

for file in $makefile_list
do
	rm -f $file
done

cmake_install_list=$(find . -name cmake_install.cmake)

for file in $cmake_install_list
do
	rm -f $file
done

cmake_cache_list=$(find . -name CMakeCache.txt)

for file in $cmake_cache_list
do
	rm -f $file
done

cmake_files_list=$(find . -name CMakeFiles)

for file in $cmake_files_list
do
	rm -rf $file
done

rm -rf ./resources/output_images/*

echo "Done"
