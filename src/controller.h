//
// Created by wyz on 20-11-14.
//

#ifndef EULEROPERATION_CONTROLLER_H
#define EULEROPERATION_CONTROLLER_H
#include<GLFW/glfw3.h>
#include "camera.h"
/*
 * L键用于切换线框模式和shader模式
 * -> 用于切换当前绘制的实体
 * Q和E控制相机上下
 * W和S控制相机前后
 * A和D控制相机左右
 * 鼠标控制相机朝向
 * 按Esc退出程序
 */
class Controller {
public:
    static void framebuffer_size_callback(GLFWwindow* window,int width,int height);
    static void keyboard_callback(GLFWwindow *window, int key, int scancode, int action, int mods);
    static void mouse_callback(GLFWwindow* window,double xpos,double ypos);
    static void mouse_button_callback(GLFWwindow* window,int button,int action,int mods);
    static void scroll_callback(GLFWwindow *window, double xoffset, double yoffset);
    static void process_input(GLFWwindow* window);
    static Camera camera;
    static bool keys[1024];
    static float last_x;
    static float last_y;
    static bool is_first_mouse;
    static float last_frame;
    static float delta_time;
    static uint32 idx;
    static bool update;
public:
    static bool IsWireFrameMode();
};


#endif //EULEROPERATION_CONTROLLER_H
