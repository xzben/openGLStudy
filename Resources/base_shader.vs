#import<common/vs_head.vs>

out vec3 ourColor;

void main()
{
	gl_Position = cc_mvp*vec4(aPos, 1.0);
	ourColor = vec3(1.0, 1.0, 1.0);
}