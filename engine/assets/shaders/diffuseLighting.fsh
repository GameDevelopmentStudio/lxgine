uniform vec3 lightColor;
varying vec4 vertexPosEye;
varying vec3 normalEye;
void main() {
    vec4 shadowPos = gl_TextureMatrix[0] * vertexPosEye;

    vec3 N = normalize(normalEye);
    vec3 L = normalize(gl_LightSource[0].position.xyz - vertexPosEye.xyz);
    float diffuse = max(0.0, dot(N, L));
    vec3 shadow = lightColor;
    gl_FragColor = vec4(gl_Color.xyz *diffuse *shadow, 1.0);
}

