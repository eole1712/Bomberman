#version 120

uniform	mat4 projection;
uniform	mat4 view;
uniform	mat4 model;

uniform sampler2D fTexture0;

varying vec4 fColor;
varying vec4 fNormal;
varying vec4 fPosition;
varying vec2 fUv;

const struct light {
  vec4 pos;
  vec4 color;
  float pow;
} mylight = light(vec4(10000.0), vec4(1.0), 1.0);

const float gAmbient = 0.07;
vec4 Color = texture2D(fTexture0, fUv) * fColor;
const float Spec = 16.0;

void main(void) {
    vec4 normal = normalize(fNormal);
    vec4 lightDir = normalize(mylight.pos - fPosition);
    vec4 reflectDir = reflect(-lightDir, normal);
    vec4 viewDir = normalize(-fPosition);
    float diffuse = mylight.pow * max(0.0, dot(lightDir, normal));
    if (diffuse > gAmbient)
    {
      float specAngle = max(dot(reflectDir, viewDir), 0.0);
      float specular = pow(specAngle, Spec);
      gl_FragColor = vec4(diffuse * Color + specular * mylight.color);
    }
    else
    {
      gl_FragColor = vec4(gAmbient * Color);
    }
}
