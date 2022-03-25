#import<common/fs_head.fs>

in vec3 ourColor;
in vec2 TexCoord;
in vec3 Normal;

uniform sampler2D mainTexture;

void main()
{
   FragColor = uColor*texture(mainTexture, TexCoord)*vec4(ourColor, 1.0);
}