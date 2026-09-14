cmake -S . -B build-new -DCMAKE_EXPORT_COMPILE_COMMANDS=ON
cmake --build build-new
./build-new/app