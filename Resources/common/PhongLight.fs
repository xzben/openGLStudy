uniform float ambientStrength = 0.1f;
uniform vec3 ligthColor;
uniform vec3 lightPos;

vec4 getFragColor(vec4 objectColor)
{
	vec3 ambient = ambientStrength*ligthColor; //环境光计算，根据全局光颜色结合环境光强度结算

	vec4 result = vec4(ambient, 1.0) * objectColor;

	return result;
}