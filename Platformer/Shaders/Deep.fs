#version 130
uniform sampler2D webcam;
void main() {
  vec4 cropcol = vec4(0.4, 0.0, 0.4, 0.0);
  vec4 color = texture2D(webcam, gl_TexCoord[0].st);
  vec4 rimage = round(color);
  vec4 fin = pow((color + rimage), -rimage / 1);
  gl_FragColor = color - (fin / 6);
}
