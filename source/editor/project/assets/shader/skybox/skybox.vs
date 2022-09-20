#import<shader/common/vs_head.vs>

out vec3 TexCoord;

void main()
{
	TexCoord = aPos;
	mat4 view = mat4(mat3(cc_view)); // 去除摄像机位移信息
	vec4 pos = cc_projection * view * vec4(aPos, 1.0);
	gl_Position = pos.xyww;
}