#import<shader/light/light_data.fs>

#ifdef MATERIAL_SAMPLE
    #define HAVE_MATERIAL
    #import<shader/light/material_sample_light.fs>
#endif

#ifdef MATERIAL_COLOR
    #define HAVE_MATERIAL
    #import<shader/light/material_color_light.fs>
#endif

#ifndef HAVE_MATERIAL
    #import<shader/light/normal_light.fs>
#endif

vec4 computLightObject(vec4 objectColor, vec3 normal, vec3 fragPos)
{
    vec3 viewDir = normalize(cameraPos - fragPos);
    vec3 result = vec3(0.0, 0.0, 0.0);

    if(lightnums.x > 0)
    {
        result += computDirectionLight(directLight, normal, fragPos, viewDir);
    }

    for(int i = 0; i < lightnums.y; i ++)
    {
        result += computPointLight(pointLights[i], normal, fragPos, viewDir);
    }

    for(int i = 0; i < lightnums.z; i++)
    {
        result += computSpotLight(spotLights[i], normal, fragPos, viewDir);
    }

    return vec4(result, 1.0)*objectColor;
}
