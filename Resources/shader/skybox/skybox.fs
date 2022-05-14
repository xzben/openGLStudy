#import<shader/common/fs_head.fs>

in vec3 TexCoord;
uniform samplerCube mainTexture;

void main()
{
	FragColor = texture(mainTexture, TexCoord);
}