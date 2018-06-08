#version 330

in vec2 inCoordinates;
in vec2 inTexCoords;
in int inIndex;

uniform mat4 unOrthogonal;
uniform mat4 unModel;
uniform vec2 unFrame;
uniform vec2 unClip;


out vec2 TexCoords;

void main()
{
gl_Position=(unOrthogonal*unModel)*vec4(inCoordinates.x,inCoordinates.y,0.0f,1.0f);
TexCoords=(inTexCoords+unFrame)*unClip;
}