#import<common/fs_head.fs>

in vec3 ourColor;
in vec2 TexCoord;

uniform sampler2D mainTexture;

void main()
{
   FragColor = texture(mainTexture, TexCoord);
}