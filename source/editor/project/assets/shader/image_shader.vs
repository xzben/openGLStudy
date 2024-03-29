#import<shader/common/vs_head.vs>

out vec3 ourColor;
out vec2 TexCoord;

void main()
{
	gl_Position = cc_mvp*vec4(aPos, 1.0);
	ourColor = aColor;
	TexCoord  = aTexCoord;
}