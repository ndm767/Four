# Four
An (**incomplete**) 4d rendering library written in C++  
Example: An orthographically projected pentachoron (5-cell) rotating about the yw-plane (the code for this can be seen in [`pchoron.cpp`](https://github.com/ndm767/Four/blob/main/pchoron.cpp)):  
<img src="https://raw.githubusercontent.com/ndm767/Four/main/pchoronYW.gif" alt="pchoron" width="201" height="211">  
Example: A 4d-3d perspectively projected and 3d-2d orthographically projected tesseract rotating about the zw-plane (the code for this can be seen in [`hypercube.cpp`](https://github.com/ndm767/Four/blob/main/hypercube.cpp)):  
<img src="https://raw.githubusercontent.com/ndm767/Four/main/hypercube.gif" alt="hcube" width="200" height="200">  
## What still needs to be done  
- Write unit tests  
- Solid and wireframe mode interoperability
- hide everything GLFW and GLM related
- write build instructions for Windows
- Camera Controls
- File/model loading
- Clarify private and public functions  
- Premade geometries (hypercubes and pentachorons)
## How to use
When compiling, include the C++ files in the include/ directory and use the compiler flags for glfw3 and glew.  
**This library uses C++11 features**  
Build examples for `hypercube.cpp`:  
**MacOS (tested on OS X 10.15.7):**  
&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;`g++ hypercube.cpp include/*.cpp -o hypercube -lGLFW -lglew -framework OpenGL -std=c++11`  
**Linux (tested on Fedora 33):**  
&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;`g++ hypercube.cpp include/*.cpp -o hypercube -lGL -lGLEW -lglfw -std=c++11`  
**Please note that GLFW may display strange behavior on Wayland and some versions (>3.2) may not work on Xorg**  
More detailed instructions are coming later, but for now, see `hypercube.cpp`, `pchoron.cpp`, and `test.cpp` for examples.
## Dependencies
- OpenGL 3.3
- [GLFW3](https://www.glfw.org/)
- [GLEW](http://glew.sourceforge.net/)
- [GLM](https://github.com/g-truc/glm)
