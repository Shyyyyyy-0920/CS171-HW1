#version 330 core
in vec3 sampleDirection;
out vec4 aColor;
//表示立方体纹理采样器，从哪个cubemap取颜色
uniform samplerCube skyboxTexture;
void main()
{
//第一个参数表示从哪里采样，第二个参数表示朝哪个方向采样
aColor=texture(skyboxTexture,sampleDirection);
}