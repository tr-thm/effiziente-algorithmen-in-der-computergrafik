#version 330 core
out vec4 FragColor;

in VS_OUT {
    vec3 FragmentPosition;
    vec2 TextureCoordinate;
    vec3 TangentLightDirection;
    vec3 TangentCameraPosition;
    vec3 TangentFragmentPosition;
    mat3 TBN;
} fs_in;

uniform sampler2D AR;
uniform sampler2D NOM;
uniform sampler2D PMDG;

uniform samplerCube CubeMap;

void main()
{           
    //Runtime definable colors
    vec3 color_1 = vec3(0.04, 0.04, 0.04);
    vec3 color_2 = vec3(0.097, 0.097, 0.097);
    vec3 color_3 = vec3(0.573, 0.056, 0.012);
    vec3 color_4 = vec3(1.0, 1.0, 1.0);
    vec3 color_glow = vec3(0.015, 0.253, 0.5);
    vec3 color_dirt = vec3(0.0, 0.0, 0.0);
    vec3 color_paint = vec3(1.0, 1.0, 1.0);
    vec3 color_light = vec3(1.0, 1.0, 1.0);

    // --------------------------------------------------------------------------------------------

    //AR = Albedo, Roughness
    vec3 albedo = texture(AR, fs_in.TextureCoordinate).rgb;
    float roughness = texture(AR, fs_in.TextureCoordinate).a;

    //NOM = Normal, Occlusion
    vec3 normal = (vec3(texture(NOM, fs_in.TextureCoordinate).g, texture(NOM, fs_in.TextureCoordinate).a, 0.5));
    // transform normal vector to range [-1,1]
    normal = normal * 2.0 - 1.0;
    //restore z-component of normal vector
    normal.z = 1 - (normal.x * normal.x + normal.y * normal.y) / 2;
    
    // mirror normal along Y-axis if texture is mirrored
    if (fs_in.TextureCoordinate.x < 0) normal.y = -normal.y;
    
    float occlusion = texture(NOM, fs_in.TextureCoordinate).b;

    //PMDG = Paint, Material, Dirt, Glow
    float paint = texture(PMDG, fs_in.TextureCoordinate).r;
    float material = texture(PMDG, fs_in.TextureCoordinate).g;
    float dirt = texture(PMDG, fs_in.TextureCoordinate).b;
    float glow = texture(PMDG, fs_in.TextureCoordinate).a;

    // --------------------------------------------------------------------------------------------

    //apply material color
    if      (material < 0.25)  albedo *= color_1;
    else if (material < 0.50)  albedo *= color_2;
    else if (material < 0.75)  albedo *= color_3;
    else                       albedo *= color_4;

    vec3 color;

    //apply paint
    color = mix(albedo, color_paint, paint);

    //apply dirt
    color = mix(color, color_dirt, dirt);

    //calculate ambient and diffuse lighting
    vec3 viewDir = normalize(fs_in.TangentCameraPosition - fs_in.TangentFragmentPosition);
    vec3 lightDir = normalize(-fs_in.TangentLightDirection);
    float lightIntensity = occlusion * 0.1 + 0.9 * max(dot(lightDir, normal), 0.0);
    color = color * color_light * lightIntensity;

    //add glow
    color = mix(color, color_glow, glow);

    // calculate specular lighting
    vec3 halfwayDir = normalize(lightDir + viewDir);  
    float specularIntensity = pow(max(dot(normal, halfwayDir), 0.0), 32.0) * roughness;
    color += color_light * specularIntensity;

    FragColor = vec4(color, 1.0);

    //gamma correction
    FragColor = vec4(pow(FragColor.rgb, vec3(1.0/2.2)), FragColor.a);
}

