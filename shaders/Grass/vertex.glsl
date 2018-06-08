#version 330

in vec2 inCoordinates;
in vec2 inTexCoords;
in int inIndex;

in mediump vec4 inModel0;
in mediump vec4 inModel1;
in  mediump vec4 inModel2;
in  mediump vec4 inModel3;

uniform mat4 unModel;
uniform mat4 unOrthogonal;

flat out int InstanceID;
flat out int IndexID;
out  mediump mat4 inModel;
out vec4 gl_Position;
out vec2 TexCoords;

in mediump vec4 inColor;
out mediump vec4 Color;

void main()
{
Color=inColor;
InstanceID=gl_InstanceID;
IndexID=inIndex;
inModel[0]=inModel0;
inModel[1]=inModel1;
inModel[2]=inModel2;
inModel[3]=inModel3;

gl_Position=(unOrthogonal*unModel*inModel)*vec4(inCoordinates.x,inCoordinates.y,0.0f,1.0f);
TexCoords=inTexCoords;

}