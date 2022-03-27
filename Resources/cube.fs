#import<common/fs_head.fs>
#import<common/PhongLight.vs>

in vec3 ourColor;
in vec2 TexCoord;
in vec3 Normal;

uniform sampler2D mainTexture;

void main()
{
	vec4 objectColor = uColor*texture(mainTexture, TexCoord)*vec4(ourColor, 1.0);
    FragColor = objectColor;
}