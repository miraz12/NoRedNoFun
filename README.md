# NoRedNoFun

## Build instructions:
git submodule init<br/>
git submodule update<br/>
<br/>
make a folder where you wan't build files to end up, for example "build"<br/>
cd build<br/>
cmake ../<br/>
cmake --build .<br/>

## Notes:
If the shaders does not compile (error outputs to console during runtime) go into SimpleShaderProgram and change the paths to match your setup.