//
// Created by wyz on 20-11-14.
//

#ifndef EULEROPERATION_CONTROLLER_H
#define EULEROPERATION_CONTROLLER_H
#include<GLFW/glfw3.h>
#include "camera.h"
/*
 * 按下鼠标左键移动，物体旋转
 * todo 按下鼠标右键，显示菜单？
 * L键控制线框还是实体绘制
 * 滚轮控制相机缩放大小
 */
class Controller {
public:
    static void framebuffer_size_callback(GLFWwindow* window,int width,int height);
    static void keyboard_callback(GLFWwindow *window, int key, int scancode, int action, int mods);
    static void mouse_callback(GLFWwindow* window,double xpos,double ypos);
    static void mouse_button_callback(GLFWwindow* window,int button,int action,int mods);
    static void scroll_callback(GLFWwindow *window, double xoffset, double yoffset);
    static Camera camera;
    static bool keys[1024];
    static float last_x;
    static float last_y;
    static bool is_first_mouse;
public:
    bool IsWireFrameMode() const;
};


#endif //EULEROPERATION_CONTROLLER_H
