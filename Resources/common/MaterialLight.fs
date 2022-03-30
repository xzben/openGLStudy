struct Material
{
	vec3 ambient;  //环境光 颜色
	vec3 diffuse;  //漫反射光 颜色
	vec3 specular; //镜面光 颜色
	
	float shininess; //反光度
};

uniform Material material;