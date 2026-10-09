#version 330 core
in vec4 worldPosition;
in vec3 worldNormal;
out vec4 aColor;
uniform float ka;
uniform float ks;
uniform float s;
uniform float gCosCutoff;
uniform vec3 eye;
uniform vec3 pointColor;
uniform vec3 material;
uniform vec3 pointPosition;
uniform vec3 ambientColor;
uniform vec3 gDirection;
uniform vec3 glightPosition;
uniform vec3 gColor;
vec3 light(vec3 lightPosition,vec3 lightColor,vec4 worldPosition,vec3 N,vec3 V)
{
    vec3 L=normalize(lightPosition-worldPosition.xyz);
    vec3 R=reflect(-L,N);
    float S=pow(max(dot(R,V),0),s);
    float d=max(dot(N,L),0);
    if(dot(N,L)<=0)
    {
        S=0;
    }
    vec3 specular=ks*S*lightColor;
    vec3 diffuse=d*lightColor*material; 
    return diffuse+specular;
}
void main()
{
vec3 N=normalize(worldNormal);
vec3 V=normalize(eye-worldPosition.xyz);
vec3 a=normalize(gDirection);
vec3 u=normalize(worldPosition.xyz-glightPosition);
float gCosTheta=dot(a,u);
bool inglight=gCosTheta>=gCosCutoff;
vec3 gSpotlight=vec3(0.0);
if(inglight)
{
    gSpotlight=light(glightPosition,gColor,worldPosition,N,V);
}
vec3 ambient=ka*ambientColor*material;
vec3 result =ambient+light(pointPosition,pointColor,worldPosition,N,V)+gSpotlight;
aColor=vec4(result,1.0);
}