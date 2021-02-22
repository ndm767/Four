/**
 * @file camera.h
 * @author Nathan Medros
 * @brief Contains the class definition for the Camera class
 * @version 0.1
 * @date 2021-02-06
 * 
 * @copyright Copyright (c) 2021
 * 
 */
#ifndef CAMERA_H
#define CAMERA_H

#include "object.h"

class Camera : public Object{
public:
    void create();
    glm::mat4 viewMat;
    glm::mat4 projMat;
};

#endif