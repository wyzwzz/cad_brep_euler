#ifndef CAMERA_H
#define CAMERA_H

#include<glm/glm.hpp>
#include<glm/gtc/matrix_transform.hpp>
#include<vector>

using namespace glm;
enum Camera_Movement{
    FORWARD,
    BACKWARD,
    LEFT,
    RIGHT,
    UP,
    DOWN
};
enum Camera_Type{
    PERSPECTIVE,
    ORTHO
};
const float PITCH=0.0f;
const float YAW=-90.0f;
const float SPEED=2.5f;
const float SENSITIVITY=0.03f;
const float ZOOM=45.0f;

class Camera{
public:
    vec3 Position;//
    vec3 Front;//vector
    vec3 Up;//current up vector
    vec3 Right;
    vec3 WorldUp;//ordinary up vector , used to get right vector,then use right*front to get current changed up vector
    
    float Yaw;//total rotate angle but not delta angle
    float Pitch;

    float MovementSpeed;
    float MouseSensitivity;
    double Zoom;
    Camera_Type type;
    Camera(vec3 pos=vec3(0.0f,0.0f,0.0f),vec3 up=vec3(0.0f,1.0f,0.0f),float yaw=YAW,float pitch=PITCH,Camera_Type type=PERSPECTIVE):Front(vec3(0.0f,0.0f,-1.0f)),MovementSpeed(SPEED),MouseSensitivity(SENSITIVITY),Zoom(ZOOM){
        Position=pos;
        WorldUp=up;
        Yaw=yaw;
        Pitch=pitch;
        updateCameraVectors();
    };

    void updateCameraVectors();//update camera direction not pos
    void processMouseScroll(float yoffset);
    void processMouseMovement(float xoffset,float yoffset,GLboolean constrainPitch=true);
    void processKeyboard(Camera_Movement direction,float deltaTime);
    mat4 getViewMatrix();
};

inline void Camera::updateCameraVectors()
{
    vec3 front;
    front.x=cos(radians(Yaw))*cos(radians(Pitch));
    front.y=sin(radians(Pitch));
    front.z=sin(radians(Yaw))*cos(radians(Pitch));
    Front=normalize(front);
    Right=normalize(cross(Front,WorldUp));
    Up=normalize(cross(Right,Front));

}

inline void Camera::processMouseScroll(float yoffset)
{
    switch (type) {
        case PERSPECTIVE:
            Zoom-=yoffset;
            if(Zoom<1.0f)
                Zoom=1.0f;
            if(Zoom>45.0f)
                Zoom=45.0f;
            break;
        case ORTHO:
            Zoom-=yoffset;
            if(Zoom<0.1f)
                Zoom=0.1f;
            if(Zoom>45.0f)
                Zoom=45.0f;
    }
}

inline void Camera::processMouseMovement(float xoffset,float yoffset,GLboolean constrainPitch)
{

    xoffset*=MouseSensitivity;
    yoffset*=MouseSensitivity;

    Yaw+=xoffset;
    Pitch+=yoffset;

    if(constrainPitch){
		if (Pitch > 89.0f)
			Pitch = 89.0f;
        if(Pitch<-89.0f)
            Pitch=-89.0f;
    }
    updateCameraVectors();
}
inline void Camera::processKeyboard(Camera_Movement direction,float deltaTime)
{
    float ds=MovementSpeed*deltaTime;
    if(direction==FORWARD)
        Position+=Front*ds;
    if(direction==BACKWARD)
        Position-=Front*ds;
    if(direction==LEFT)
        Position-=Right*ds;
    if(direction==RIGHT)
        Position+=Right*ds;
    if(direction==UP)
        Position+=Up*ds;
    if(direction==DOWN)
        Position-=Up*ds;
}
inline mat4 Camera::getViewMatrix()
{
    return lookAt(Position,Position+Front,Up);
}
#endif