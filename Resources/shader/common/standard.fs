#import<shader/common/fs_head.fs>

in vec3 ourColor;
in vec2 TexCoord;
in vec3 Normal;
in vec3 FragPos;

#import<shader/light/light_func.fs>

uniform sampler2D mainTexture;

void main()
{
	vec4 objectColor = uColor*texture(mainTexture, TexCoord)*vec4(ourColor, 1.0);
    FragColor = computLightObject(objectColor, Normal, FragPos);
}