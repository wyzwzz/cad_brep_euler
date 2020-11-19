//
// Created by wyz on 20-11-14.
//
#include<glad/glad.h>
#include "controller.h"
#include<iostream>
Camera Controller::camera=Camera(glm::vec3(0.0f,8.0f,12.0f));
bool Controller::is_first_mouse=true;
float Controller::last_x;
float Controller::last_y;
bool Controller::keys[1024];
void Controller::framebuffer_size_callback(GLFWwindow *window, int width, int height)
{
    glViewport(0,0,width,height);
}

void Controller::keyboard_callback(GLFWwindow *window, int key, int scancode, int action, int mods)
{
    if(key==GLFW_KEY_ESCAPE && action==GLFW_PRESS){
        glfwSetWindowShouldClose(window,GL_TRUE);
    }
    else if(key>=0 && key<1024){
        std::cout<<"key click: "<<key<<std::endl;
        if(action==GLFW_PRESS)
            keys[key]=!keys[key];

    }
}

void Controller::mouse_callback(GLFWwindow *window, double xpos, double ypos)
{
    if(is_first_mouse){
        last_x=xpos;
        last_y=ypos;
        is_first_mouse=false;
    }
    float dx=xpos-last_x;
    float dy=ypos-last_y;
    last_x=xpos;
    last_y=ypos;
    if(glfwGetMouseButton(window,GLFW_MOUSE_BUTTON_LEFT)==GLFW_PRESS){
        camera.processMouseMovement(dx,dy);
    }
}

void Controller::mouse_button_callback(GLFWwindow *window, int button, int action, int mods)
{

}

void Controller::scroll_callback(GLFWwindow *window, double xoffset, double yoffset)
{
    camera.processMouseScroll(yoffset);
}

bool Controller::IsWireFrameMode()
{

    if(keys[76]){// l
        return true;
    }
    return false;
}
