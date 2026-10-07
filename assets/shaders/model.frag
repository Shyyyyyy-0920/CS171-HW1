#version 330 core
in vec4 worldPosition;
in vec3 worldNormal;
out vec4 aColor;
uniform float ka;
uniform float ks;
uniform float s;
uniform vec3 eye;
uniform vec3 light;
uniform vec3 material;
uniform vec3 lightPosition;
void main()
{
vec3 N = normalize(worldNormal);
vec3 ambient=ka*light*material;
vec3 L=normalize(lightPosition-worldPosition.xyz);
vec3 V=normalize(eye-worldPosition.xyz);
vec3 R=reflect(-L,N);
float S=pow(max(dot(R,V),0),s);
float d=max(dot(N,L),0);
if(dot(N,L)<=0)
{
    S=0;
}
vec3 specular=ks*S*light;
vec3 diffuse=d*light*material;
vec3 result =diffuse+ambient+specular;
aColor=vec4(result,1.0);
}