//
// Created by wyz on 20-11-14.
//
#include<glad/glad.h>
#include "controller.h"
#include<iostream>
Camera Controller::camera=Camera(glm::vec3(0.0f,4.0f,15.0f));
bool Controller::is_first_mouse=true;
float Controller::last_x;
float Controller::last_y;
bool Controller::keys[1024];
float Controller::last_frame=0.0f;
float Controller::delta_time=0.0f;
uint32 Controller::idx=0;
bool Controller::update=false;
uint32 solids_num=0;
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
//        std::cout<<"key click: "<<key<<std::endl;
        if(action==GLFW_PRESS)
            keys[key]=!keys[key];
        if(key==GLFW_KEY_RIGHT && action==GLFW_PRESS){
            update=true;
            idx=(idx+1)%solids_num;
        }
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
    float dy=last_y-ypos;
    last_x=xpos;
    last_y=ypos;
//    if(glfwGetMouseButton(window,GLFW_MOUSE_BUTTON_LEFT)==GLFW_PRESS){
        camera.processMouseMovement(dx,dy);
//    }
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

void Controller::process_input(GLFWwindow *window)
{
    if (glfwGetKey(window, GLFW_KEY_W) == GLFW_PRESS)
        camera.processKeyboard(FORWARD, delta_time);
    if (glfwGetKey(window, GLFW_KEY_S) == GLFW_PRESS)
        camera.processKeyboard(BACKWARD, delta_time);
    if (glfwGetKey(window, GLFW_KEY_A) == GLFW_PRESS)
        camera.processKeyboard(LEFT, delta_time);
    if (glfwGetKey(window, GLFW_KEY_D) == GLFW_PRESS)
        camera.processKeyboard(RIGHT, delta_time);
    if (glfwGetKey(window, GLFW_KEY_Q) == GLFW_PRESS)
        camera.processKeyboard(UP, delta_time);
    if (glfwGetKey(window, GLFW_KEY_E) == GLFW_PRESS)
        camera.processKeyboard(DOWN, delta_time);
}
