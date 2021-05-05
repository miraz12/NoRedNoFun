# NoRedNoFun

## Build instructions:
git submodule init
git submodule update

make a folder where you wan't build files to end up, for example "build"
cd build
cmake ../
cmake --build .

## Notes:
If the shaders does not compile (error outputs to console during runtime) go into SimpleShaderProgram and change the paths to match your setup.