//Geethanjali Jeevanatham, Anupa Prudhivi, Sindhusha Dhulipala, Arko Basu
#version 410 core

uniform sampler2D tex; //this is the texture

in vec2 pass_TexCoord; //this is the texture coord
in vec4 pass_Color;
out vec4 color;

uniform int texture_blend;



//-----------------------------------------------------------------------------
// FOR ENVIRONMENT MAPPING
// the vector from which we fetch our color component for environment mapping.
in vec2 vN;


void main(void)                                                   
{
    // This function finds the color component for each texture coordinate. 
    vec4 tex_color =  texture(tex, vN);
    vec4 tex_color1 = texture(tex,pass_TexCoord);
    color = tex_color + pass_Color;
    //texture_blend = 0;
    // This mixes the background color with the texture color.
    // The GLSL shader code replaces the former envrionment. It is now up to us
    // to figure out how we like to blend a texture with the background color.
    
}