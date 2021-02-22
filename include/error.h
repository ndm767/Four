/**
 * @file error.h
 * @author Nathan Medros
 * @brief Contains functions to throw errors
 * @version 0.1
 * @date 2021-02-06
 * 
 * @copyright Copyright (c) 2021
 * 
 */
#ifndef ERROR_H
#define ERROR_H

#include <stdlib.h>
#include <stdio.h>
#include <GLFW/glfw3.h>

/**
 * @brief Throws error and dumps OpenGL information
 *
 * @param msg Error message
 * @param fatal Whether or not the error should bw fatal
 */
inline void throwError(const char* msg, bool fatal){
    printf("Error:\n%s\n", msg);
    printf("Dumping OpenGL info:\n");
    printf("GL_VERSION: %s\n", glGetString(GL_VERSION));
    printf("GLSL_VERSION: %s\n", glGetString(GL_SHADING_LANGUAGE_VERSION));
    printf("GL_VENDOR: %s\n", glGetString(GL_VENDOR));
    printf("GL_RENDERER: %s\n", glGetString(GL_RENDERER));

    if(fatal){
        exit(0);
    }
}

/**
 * @brief Throws error and dumps OpenGL information along with a shader infolog
 * 
 * @param msg Error message
 * @param infoLog shader infolog
 * @param fatal whether or not the error should be fatal
 */
inline void throwError(const char* msg, char* infoLog, bool fatal){
    printf("Error!\n %s\n", msg);
    printf("Infolog here: %s\n", infoLog);
    printf("Dumping OpenGL info:\n");
    printf("GL_VERSION: %s\n", glGetString(GL_VERSION));
    printf("GLSL_VERSION: %s\n", glGetString(GL_SHADING_LANGUAGE_VERSION));
    printf("GL_VENDOR: %s\n", glGetString(GL_VENDOR));
    printf("GL_RENDERER: %s\n", glGetString(GL_RENDERER));

    if(fatal){
        exit(0);
    }
}

#endif