#import<common/vs_head.vs>
#import<common/PhongLight.vs>

out vec3 ourColor;
out vec2 TexCoord;
out vec3 Normal;
out vec3 FragPos;

void main()
{
	gl_Position = cc_mvp*vec4(aPos, 1.0);
	ourColor = aColor;
	TexCoord  = aTexCoord;
	//因为模型是可能旋转缩放的，所以法线也需要对应变化
	//但是发现是一个方向向量，不存在位移，所以 这里通过 w 设置为0 消除 模型矩阵中的位移部分
	Normal = vec3(cc_model*vec4(aNormal, 0));
	
	//计算的是面片的世界坐标
	FragPos = vec3(cc_model*vec4(aPos, 1.0));
}