/**
 * @file camera.cpp
 * @author Nathan Medros
 * @brief Function definitions for the camera class
 * @version 0.1
 * @date 2021-02-06
 * 
 * @copyright Copyright (c) 2021
 * 
 */
#include "camera.h"

/**
 * @brief creates the view matrix (default position 4,3,3 looking at 0,0,0) and the orthographic 3d-2d projection matrix
 * 
 */
void Camera::create(){
    viewMat = glm::lookAt(glm::vec3(4, 3, 3), glm::vec3(0, 0, 0), glm::vec3(0, 1, 0));
    projMat = glm::ortho(-5.0f, 5.0f, -5.0f, 5.0f, 0.0f, 100.0f);
}