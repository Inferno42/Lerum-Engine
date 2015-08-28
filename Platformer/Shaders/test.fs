#version 130
uniform sampler2D webcam;
uniform float TimeFrac;
uniform int MaxTime;
void main() {
  vec4 Tex = texture2D(webcam, gl_TexCoord[0].st);
  float MaxR, MaxG, MaxB, MaxA;
  
  
  if(TimeFrac >= 0.0 && TimeFrac < 0.1501) //Go slightly over switch to avoid conflicts
  {
	MaxR = 1.6 * (TimeFrac * 15) * (TimeFrac / 2);
	MaxG = 1.4 * (TimeFrac * 30) * (TimeFrac / 2);
	MaxB = 1.30 * (TimeFrac * 60) * (TimeFrac / 2);
	MaxA = 0.6;
  }
  if(TimeFrac < 0.50 && TimeFrac > 0.15) //Standard Rising Sun effect until Mid-Day.
  {
	MaxR = 1.6 * TimeFrac;
	MaxG = 1.4 * TimeFrac;
	MaxB = 1.6 * TimeFrac;
	MaxA = 1.0;
  }
  if(TimeFrac > 0.50)
  {
	float diff = 0.50 - TimeFrac; //Lowering Sun
	float fin = 1.0 + diff;
	MaxR = 1.6 * fin;
	MaxG = 1.4 * fin;
	MaxB = 1.6 * fin;
	MaxA = 1.0 * fin;
  }
  
  vec4 TimeVec = vec4(MaxR, MaxG, MaxB, MaxA);
  gl_FragColor = Tex * TimeVec;
}
