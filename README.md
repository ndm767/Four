# Four
An (**incomplete**) 4d rendering library written in C++  
Example: An orthographically projected pentachoron (5-cell) rotating about the yw-plane (the code for this can be seen in [`pchoron.cpp`](https://github.com/ndm767/Four/blob/main/pchoron.cpp)):  
<img src="https://raw.githubusercontent.com/ndm767/Four/main/pchoronYW.gif" alt="pchoron" width="201" height="211"> 
## What still needs to be done
- Write documentation
- Get rid of flickering bug in solid mode
- hide everything GLFW and GLM related
- proper build system
- Camera Controls
- Dear ImGui integration
- File/model loading
- Premade geometries (hypercubes and pentachorons)
- Test out perspective projection
- Investigate replacing GL3W with something else like GLEW
## How to use
Replace the GL3W include in object.h with wherever you gl3w.h file is located.  
When compiling, include the C++ files in the include/ directory and use the compiler flags for glfw3 and gl3w.  
**This library uses C++11 features**  
More detailed instructions are coming later, but for now, see pchoron.cpp and test.cpp for examples.
## Dependencies
- OpenGL 3.3
- [GLFW3](https://www.glfw.org/)
- [GL3W](https://github.com/skaslev/gl3w)
- [GLM](https://github.com/g-truc/glm)
- Dear ImGui (planned)  
