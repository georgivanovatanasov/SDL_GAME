#version 330

in highp vec2 TexCoords;
uniform sampler2D uSampler;
uniform mediump vec4 unColor;
out mediump vec4 FragColor;
void main()
{
FragColor = texture2D(uSampler, TexCoords)*unColor;
}