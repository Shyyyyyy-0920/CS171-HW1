#version 330 core
layout(location = 0)in vec3 p;
layout(location=1)in vec3 n;
uniform mat4 V;
uniform mat4 P;
uniform mat4 M;
out vec3 sampleDirection;

void main()
{
mat3 rotation=mat3(V); 
mat4 Vsky=mat4(rotation);
vec4 worldPosition=vec4(p,1.0);
vec4  clipPosition=P*Vsky*worldPosition;
clipPosition.z=clipPosition.w;//保证是最远深度
sampleDirection=p;
//这里要注意因为gl_Position会自动除以w，因此要让z等于w
gl_Position=clipPosition;
}
