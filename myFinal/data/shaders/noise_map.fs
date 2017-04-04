
//Geethanjali Jeevanatham, Anupa Prudhivi, Sindhusha Dhulipala, Arko Basu
#version 410 core

uniform sampler2D texture_background; //this is the texture
uniform sampler2D texture_foreground; //this is the texture

in vec2 pass_TexCoord; //this is the texture coord
in vec4 pass_Color;
out vec4 color;

uniform int texture_blend;

void main(void)
{
    vec3 noiseVec = normalize(texture(texture_foreground, pass_TexCoord.xy).xyz);
    noiseVec = (noiseVec * 2.0 - 1.0) * 0.8;
    vec4 texcolor = texture(texture_background, pass_TexCoord.xy + noiseVec.xy);
    color = pass_Color + texcolor;
}