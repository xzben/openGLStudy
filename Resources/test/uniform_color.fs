#import<common/fs_head.fs>

in vec4 vertexColor;

uniform vec4 ourColor;
//uniform float time;

void main()
{
    FragColor = ourColor;
}