#import<common/fs_head.fs>

in vec3 ourColor;

void main()
{
   FragColor = vec4(ourColor, 1.0);
}