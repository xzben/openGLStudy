#import<shader/common/fs_head.fs>

in vec3 ourColor;
in vec2 TexCoord;

uniform sampler2D texture1;
uniform sampler2D texture2;

void main()
{
    FragColor = mix(texture(texture1, TexCoord),texture(texture2, TexCoord), 0.2) * vec4(ourColor, 1.0);
}