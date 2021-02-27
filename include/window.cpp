/**
 * @file Window.cpp
 * @author Nathan Medros
 * @brief Functions for the window class
 * @version 0.1
 * @date 2021-02-06
 * 
 * @copyright Copyright (c) 2021
 * 
 */

#include "window.h"

/**
 * @brief creates a 400x400 window titled "Four"
 *
 */
void Window::create(){
    create(400, 400, "Four");
}
/**
 * @brief creates a w by h window titled "Four"
 * 
 * @param w Window width
 * @param h Window height
 */
void Window::create(int w, int h){
    create(w, h, "Four");
}

/**
 * @brief creates a w by h window titled n
 * 
 * @param w Window width
 * @param h  Window height
 * @param n Window name
 */
void Window::create(int w, int h, const char* n){
    width = w;
    height = h;
    name = n;

    glfwInit();
    //create a context of version 3.3 (minimum possible) and use the core profile
    glfwWindowHint(GLFW_CONTEXT_VERSION_MAJOR, 3);
    glfwWindowHint(GLFW_CONTEXT_VERSION_MINOR, 3);
    glfwWindowHint(GLFW_OPENGL_PROFILE, GLFW_OPENGL_CORE_PROFILE);
    //because apple hates anything that wasn't made in-house
    #ifdef __APPLE__
        glfwWindowHint(GLFW_OPENGL_FORWARD_COMPAT, GLFW_TRUE);
    #endif
    //create the window
    window = glfwCreateWindow(w, h, n, NULL, NULL);
    glfwMakeContextCurrent(window);
    //actually load the core profile
    gl3wInit();

    //initialize z-depth buffering
    glEnable(GL_DEPTH_TEST);
    glDepthFunc(GL_LESS);

    this->createShaders();
}

/**
 * @brief performs all the necessary shutdown operations
 * 
 */
void Window::close(){
    glDeleteProgram(solidProgram);
    glDeleteProgram(wireframeProgram);
    glfwDestroyWindow(window);
    glfwTerminate();
}
/**
 * @brief clear screen with a black background
 * 
 */
void Window::clear(){
    clear(0.0f, 0.0f, 0.0f, 1.0f);
}
/**
 * @brief clear the screen with a background of (r, g, b, 1.0f);
 *
 * @param r red component between 0.0f=1.0f
 * @param g green component between 0.0f-1.0f
 * @param b blue component between 0.0f-1.0f
 */
void Window::clear(float r, float g, float b){
    clear(r, g, b, 1.0f);
}

/**
 * @brief clears the screen with a background of (r, g, b, a)
 * 
 * @param r red component between 0.0f-1.0f
 * @param g green component between 0.0f-1.0f
 * @param b blue component between 0.0f-1.0f
 * @param a alpha component between 0.0f-1.0f
 */
void Window::clear(float r, float g, float b, float a){
    glClearColor(r, g, b, a);
    //clear the color and the depth buffers
    glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
}

/**
 * @brief The window update function
 * 
 * Goes through all of the objects in the scene and renders them, first applying any uniforms needed. It then swaps the buffers and polls events.
 */
void Window::update(){
    GLuint wpLoc = glGetUniformLocation(wireframeProgram, "viewportSize");
    GLuint sLoc = glGetUniformLocation(solidProgram, "viewportSize");
    glUniform2fv(wpLoc, 1, &viewportSize[0]);
    glUniform2fv(sLoc, 1, &viewportSize[0]);
    for(int i = 0; i<objects.size(); i++){
        this->assignUniformMat4(objects[i]->modelMat, "modelMat");
        if(objects[i]->useColor){
            this->assignUniformBool(true, "useColor");
        }else{
            this->assignUniformBool(false, "useColor");
        }
        if(renderSolid){
            this->assignUniformVec4(objects[i]->constColor, "constCol");
            this->useShader(true);
            objects[i]->render(true, perspective);
        }else{
            this->assignUniformVec4(objects[i]->constColor, "constCol");
            this->useShader(false);
            objects[i]->render(false, perspective);
        }
    }

    glfwSwapBuffers(window);
    glfwPollEvents();
}

bool Window::shouldClose(){
    if(glfwWindowShouldClose(window)){
        return true;
    }else{
        return false;
    }
}

void Window::setShouldClose(bool state){
    glfwSetWindowShouldClose(window, (int)state);
}

bool Window::getKeyPress(int key){
    if(glfwGetKey(window, key) == GLFW_PRESS){
        return true;
    }
    return false;
}
bool Window::getKeyUp(int key){
    if(glfwGetKey(window, key) == GLFW_RELEASE){
        return true;
    }
    return false;
}
void Window::createShaders(){
    GLuint vertexShader, fragmentShader, geometryShader;
    const char* vertSrc = R""(
        #version 330 core
        layout (location=0) in vec3 pos;
        layout (location=1) in vec4 col;
        out vec4 gCol;
        out vec4 fCol;
        uniform mat4 modelMat;
        uniform mat4 viewMat;
        uniform mat4 projMat;
        void main(){
            gCol = col;
            fCol = col;
            mat4 mvp = projMat * viewMat * modelMat;
            vec4 pos = mvp * vec4(pos, 1.0);
            gl_Position = pos;
        }
    )"";

    const char* fragSrc = R""(
        #version 330 core
        in vec4 fCol;
        out vec4 outColor;
        uniform bool useColor;
        uniform vec4 constCol;
        void main(){
            if(useColor){
                outColor = fCol;
            }else{
                outColor = constCol;
            }
        }
    )"";

    const char* geomSrc = R""(
        #version 330 core

        layout (lines) in;
        layout (triangle_strip, max_vertices = 4) out;

        uniform vec2 viewportSize;
        uniform float thickness = 2;

        in vec4 gCol[];
        out vec4 fCol;

        void main(){
            vec4 p1 = gl_in[0].gl_Position;
            vec4 p2 = gl_in[1].gl_Position;

            vec2 dir = normalize((p2.xy - p1.xy) * viewportSize);
            vec2 offset = vec2(-dir.y, dir.x) * thickness / viewportSize;

            gl_Position = p1 + vec4(offset.xy * p1.w, 0.0, 0.0);
            fCol = gCol[0];
            EmitVertex();
            gl_Position = p1 - vec4(offset.xy * p1.w, 0.0, 0.0);
            EmitVertex();
            gl_Position = p2 + vec4(offset.xy * p2.w, 0.0, 0.0);
            fCol = gCol[1];
            EmitVertex();
            gl_Position = p2 - vec4(offset.xy * p2.w, 0.0, 0.0);
            EmitVertex();

            EndPrimitive();
        }
        )"";

    int success;
    char infoLog[512];

    vertexShader = glCreateShader(GL_VERTEX_SHADER);
    glShaderSource(vertexShader, 1, &vertSrc, NULL);
    glCompileShader(vertexShader);
    glGetShaderiv(vertexShader, GL_COMPILE_STATUS, &success);
    if(!success){
        glGetShaderInfoLog(vertexShader, 512, NULL, infoLog);
        throwError("vertex shader compile error!", infoLog, false);
    }

    fragmentShader = glCreateShader(GL_FRAGMENT_SHADER);
    glShaderSource(fragmentShader, 1, &fragSrc, NULL);
    glCompileShader(fragmentShader);
    glGetShaderiv(fragmentShader, GL_COMPILE_STATUS, &success);
    if(!success){
        glGetShaderInfoLog(fragmentShader, 512, NULL, infoLog);
        throwError("fragment shader compile error!", infoLog, false);
    }

    geometryShader = glCreateShader(GL_GEOMETRY_SHADER);
    glShaderSource(geometryShader, 1, &geomSrc, NULL);
    glCompileShader(geometryShader);
    glGetShaderiv(geometryShader, GL_COMPILE_STATUS, &success);
    if(!success){
        glGetShaderInfoLog(geometryShader, 512, NULL, infoLog);
        throwError("geometry shader compile error!", infoLog, false);
    }

    solidProgram = glCreateProgram();
    glAttachShader(solidProgram, vertexShader);
    glAttachShader(solidProgram, fragmentShader);
    glLinkProgram(solidProgram);
    glGetProgramiv(solidProgram, GL_LINK_STATUS, &success);
    if(!success){
        glGetProgramInfoLog(solidProgram, 512, NULL, infoLog);
        throwError("solid shader link error!", infoLog, true);
    }

    wireframeProgram = glCreateProgram();
    glAttachShader(wireframeProgram, vertexShader);
    glAttachShader(wireframeProgram, fragmentShader);
    glAttachShader(wireframeProgram, geometryShader);
    glLinkProgram(wireframeProgram);
    glGetProgramiv(wireframeProgram, GL_LINK_STATUS, &success);
    if(!success){
        glGetProgramInfoLog(wireframeProgram, 512, NULL, infoLog);
        throwError("wireframe shader link error!", infoLog, true);
    }

    //set viewport size
    int viewPort[4];
    glGetIntegerv(GL_VIEWPORT, &viewPort[0]);
    viewportSize = glm::vec2(viewPort[2], viewPort[3]);

    glDeleteShader(vertexShader);
    glDeleteShader(fragmentShader);
    glDeleteShader(geometryShader);
}

void Window::useShader(bool solid){
    if(solid){
        this->assignUniformMat4(this->c->viewMat, "viewMat");
        this->assignUniformMat4(this->c->projMat, "projMat");
        glUseProgram(solidProgram);
    }else{
        this->assignUniformMat4(this->c->viewMat, "viewMat");
        this->assignUniformMat4(this->c->projMat, "projMat");
        glUseProgram(wireframeProgram);
    }
}

void Window::assignUniformMat4(glm::mat4 uni, const char* name){
    if(renderSolid){
        GLuint loc = glGetUniformLocation(solidProgram, name);
        glUniformMatrix4fv(loc, 1, GL_FALSE, &uni[0][0]);
    }else{
        GLuint loc = glGetUniformLocation(wireframeProgram, name);
        glUniformMatrix4fv(loc, 1, GL_FALSE, &uni[0][0]);
    }
}

void Window::assignUniformVec4(glm::vec4 val, const char* name){
    if(renderSolid){
        GLuint loc = glGetUniformLocation(solidProgram, name);
        glUniform4fv(loc, 1, &val[0]);
    }else{
        GLuint loc = glGetUniformLocation(wireframeProgram, name);
        glUniform4fv(loc, 1, &val[0]);
    }
}

void Window::assignUniformBool(bool val, const char* name){
    if(renderSolid){
        GLuint loc = glGetUniformLocation(solidProgram, name);
        glUniform1i(loc, val);
    }else{
        GLuint loc = glGetUniformLocation(wireframeProgram, name);
        glUniform1i(loc, val);
    }
}

void Window::setActiveCamera(Camera *cam){
    this->c = cam;
}

void Window::addToScene(Object *o){
    objects.push_back(o);
}

void Window::setRenderMode(renderMode mode){
    if(mode == RENDER_SOLID){
        renderSolid = true;
    }
    if(mode == RENDER_WIREFRAME){
        renderSolid = false;
    }
}

Window::renderMode Window::getRenderMode(){
    if(renderSolid){
        return Window::RENDER_SOLID;
    }else{
        return Window::RENDER_WIREFRAME;
    }
}

void Window::set4DProjection(projection proj){
    if(proj == PROJECT_ORTHOGRAPHIC){
        perspective = false;
    }else{
        perspective = true;
    }
}

Window::projection Window::get4DProjection(){
    if(perspective){
        return PROJECT_PERSPECTIVE;
    }else{
        return PROJECT_ORTHOGRAPHIC;
    }
}