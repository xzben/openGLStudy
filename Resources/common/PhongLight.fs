uniform float ambientStrength;
uniform vec4 ligthColor;
uniform vec3 lightPos;

// 漫反射光
vec3 computDiffuse(vec3 normal, vec3 fragPos)
{
	vec3 norm = normalize(normal);
	vec3 lightDir = normalize(lightPos - fragPos);

	float diff = max(dot(norm, lightDir), 0.0);
	vec3 diffuse = diff*ligthColor.rgb;

	return diffuse;
}

vec4 computLightObject(vec4 objectColor, vec3 normal, vec3 fragPos)
{
	//环境光计算，根据全局光颜色结合环境光强度结算
	vec3 ambient = ambientStrength*ligthColor.rgb; 
	vec3 diffuse = computDiffuse(normal, fragPos);

	vec4 result = vec4(ambient+diffuse, 1.0f) * objectColor;

	return result;
}