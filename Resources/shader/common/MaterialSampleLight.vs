struct Light
{
	vec3 pos;  //灯光位置
	
	vec3 ambient;   //环境光颜色
	vec3 diffuse;   //漫反射光颜色
	vec3 specular;  //镜面光颜色

	vec3 strength;  //各个光的强度信息，x ambientStrength y diffuseStrength z specularStrength
};

struct Material
{
	sampler2D  diffuse;  //漫反射光 颜色
	sampler2D  specular; //镜面光 颜色
	
	float shininess; //反光度
};

uniform Light light;
uniform Material material;