#version 330 core
layout(location=0)in vec3 p;
layout(location=1)in vec3 n;
out vec3 normal;
void main()
{
gl_Position=vec4(p,1.0);
normal=n;
}
