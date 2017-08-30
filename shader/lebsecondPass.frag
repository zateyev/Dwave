#version 300 es

precision mediump float;
precision highp sampler3D;

in vec3 worldSpaceCoords;
in vec4 projectedCoords;
out vec4 fragColor;

uniform sampler3D uSliceMaps;
uniform sampler2D uBackCoord;
uniform float uMinGrayVal;
uniform float uMaxGrayVal;
uniform float uSteps;

const int MAX_STEPS = 887;
void main( void ) {
	vec2 texc = vec2(((projectedCoords.x / projectedCoords.w) + 1.0 ) / 2.0,
					((projectedCoords.y / projectedCoords.w) + 1.0 ) / 2.0 );
	vec3 backPos = texture(uBackCoord, texc).xyz;
	vec3 frontPos = worldSpaceCoords;
	vec3 dir = backPos - frontPos;
	float rayLength = length(dir);
	float delta = 1.0 / uSteps;
	vec3 deltaDirection = normalize(dir) * delta;
	float deltaDirectionLength = length(deltaDirection);
	vec3 currentPosition = frontPos;
	vec4 accumulatedColor = vec4(0.0);
	float accumulatedAlpha = 0.0;
	float accumulatedLength = 0.0;
	float alphaScaleFactor = 25.6 * delta;
	// vec4 colorSample;
	float alphaSample;

  vec4 colorSample = texture(uSliceMaps, currentPosition);
  // vec4 sampletmp = vec4(0.0);
	// for(int i = 0; i < MAX_STEPS; i++)
	// {
  //   // colorSample = texture(uSliceMaps, currentPosition);
  //   // if (colorSample.x > uMaxGrayVal || colorSample.x < uMinGrayVal) {
  //   //   colorSample = vec4(0.0);
  //   // }
  //   // sampletmp.rgb = (1.0 - accumulatedColor.a) * colorSample.xxx * sampletmp.a;
  //   // sampletmp.a = colorSample.a * 0.5 * (1.0 / uSteps);
  //   // accumulatedColor += sampletmp;
  //   // currentPosition += deltaDirection;
  //   // if (accumulatedColor.a >= 1.0) break;
  //
	// 	// colorSample = texture(uSliceMaps, currentPosition);
	// 	// alphaSample = colorSample.a;
	// 	// alphaSample *= (1.0 - accumulatedAlpha);
	// 	// alphaSample *= alphaScaleFactor;
	// 	// accumulatedColor += colorSample;
	// 	// accumulatedAlpha += alphaSample;
	// 	// currentPosition += deltaDirection;
	// 	// accumulatedLength += deltaDirectionLength;
	// 	// if(accumulatedLength >= rayLength || accumulatedAlpha >= 1.0 )
	// 	// 	break;
  //   // }
	// }
  // fragColor  = accumulatedColor;
  fragColor  = colorSample;
  // fragColor  = vec4(backPos, 1.0);
	// fragColor  = vec4(frontPos, 1.0);
}
