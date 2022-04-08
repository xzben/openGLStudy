#import<shader/common/fs_head.fs>

in vec3 ourColor;
in vec2 TexCoord;
in vec3 Normal;
in vec3 FragPos;

#ifdef MATERIAL_SAMPLE

#import<shader/common/MaterialSampleLight.fs>

#else

#import<shader/common/MaterialLight.fs>

#endif

uniform sampler2D mainTexture;

void main()
{
	vec4 objectColor = uColor*texture(mainTexture, TexCoord)*vec4(ourColor, 1.0);
    FragColor = computLightObject(objectColor, Normal, FragPos);
}