#version 330

in highp vec2 TexCoords;
in mediump vec4 Color;
uniform sampler2D uSampler;
out mediump vec4 FragColor;
void main()
{
FragColor = texture2D(uSampler, TexCoords)*Color;
}