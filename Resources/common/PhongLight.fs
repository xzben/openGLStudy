uniform float ambientStrength;
uniform float specularStrength;
uniform vec4 ligthColor;
uniform vec3 lightPos;

vec4 computLightObject(vec4 objectColor, vec3 normal, vec3 fragPos)
{
	//环境光计算，根据全局光颜色结合环境光强度结算
	// 环境光直接根据光照颜色和环境光强度得到
	vec3 ambient = ambientStrength*ligthColor.rgb; 

	//计算漫反射光
	// 漫反射通过光线入射角度得到，垂直照射的光强度越大，平行照射的光最暗
	vec3 norm = normalize(normal);
	vec3 lightDir = normalize(lightPos - fragPos);
	float diff = max(dot(norm, lightDir), 0.0);
	vec3 diffuse = diff*ligthColor.rgb;

	//计算镜面反射光
	// 镜面反射根据 光线的反射线和视觉射线的夹角决定光暗强度，
	// 当视角射线和反射光线 垂直镜面光越强，平行则越小
	vec3 viewDir = normalize(cameraPos - fragPos);
	vec3 reflectDir = reflect(-lightDir, norm);
	float spec = pow(max(dot(viewDir, reflectDir), 0.0), 32);
	vec3 specular = specularStrength * spec * ligthColor.rgb;

	vec4 result = vec4(ambient + diffuse + specular, 1.0f) * objectColor;

	return result;
}