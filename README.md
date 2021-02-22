# Four
An (**incomplete**) 4d rendering library written in C++
## What still needs to be done
- Write documentation
- Get rid of flickering bug in solid mode
- hide everything GLFW and GLM related
- proper build system
- Camera Controls
- Dear ImGui integration
- File/model loading
## How to use
Replace the GL3W include in object.h with wherever you gl3w.h file is located.
When compiling, include the C++ files in the include/ directory and use the compiler flags for glfw3 and gl3w.
**This library uses C++11**
More detailed instructions are coming later, but for now, see pchoron.cpp and test.cpp for examples.