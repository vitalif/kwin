#version 140
uniform sampler2D sampler;

in vec2 texcoord0;

uniform sampler3D clut;

out vec4 fragColor;

uniform vec4 modulation;

uniform float saturation;

void main()
{
    vec4 tex = texture(sampler, texcoord0);

    if (saturation != 1.0) {
        vec3 desaturated = tex.rgb * vec3( 0.30, 0.59, 0.11 );
        desaturated = vec3( dot( desaturated, tex.rgb ));
        tex.rgb = tex.rgb * vec3( saturation ) + desaturated * vec3( 1.0 - saturation );
    }

    tex.rgb = texture(clut, tex.rgb).rgb;
    tex *= modulation;
    tex.rgb *= tex.a;

    fragColor = tex;
}
