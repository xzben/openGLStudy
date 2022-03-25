#import<common/vs_head.vs>

out vec3 ourColor;
out vec2 TexCoord;

void main()
{
	gl_Position = cc_projection*cc_view*cc_model*vec4(aPos, 1.0);
	ourColor = aColor;
	TexCoord  = aTexCoord;
}