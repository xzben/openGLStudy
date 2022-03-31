#import<common/fs_head.fs>
#import<common/MaterialLight.fs>

in vec3 ourColor;
in vec2 TexCoord;
in vec3 Normal;
in vec3 FragPos;

uniform sampler2D mainTexture;

void main()
{
	vec4 objectColor = uColor*vec4(ourColor, 1.0);
    FragColor = computLightObject(objectColor, Normal, FragPos);
}