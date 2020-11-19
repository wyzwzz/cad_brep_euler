#version 430 core
in vec3 texCoord;
out vec4 frag_color;
void main()
{
    frag_color=vec4(texCoord,1.0);
}
