#import<common/vs_head.vs>

void main()
{
	gl_Position = cc_mvp*vec4(aPos, 1.0);
}