varying vec4 vertexPosEye;
varying vec3 normalEye;
void main() {
    gl_Position = gl_ModelViewProjectionMatrix * gl_Vertex;
    gl_TexCoord[0] = gl_MultiTexCoord0;
    vertexPosEye = gl_ModelViewMatrix * gl_Vertex;
    normalEye = gl_NormalMatrix * gl_Normal;
    gl_FrontColor = gl_Color;
}

