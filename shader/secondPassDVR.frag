precision mediump int;
precision mediump float;
varying vec4 frontColor;
varying vec4 pos;
uniform sampler2D uBackCoord;
uniform sampler3D uSliceMaps;
uniform float uOpacityVal;
uniform float uMinGrayVal;
uniform float uMaxGrayVal;
uniform float uSteps;
uniform float l;

void main(void)
{
    vec2 texC = ((pos.xy/pos.w) + 1.0) / 2.0;
    vec4 backColor = texture2D(uBackCoord, texC);
    vec3 dir = backColor.rgb - frontColor.rgb;
    vec4 vpos = frontColor;
    vec3 Step = dir/uSteps;
    vec4 accum = vec4(0.5);
    vec4 sample = vec4(0.0);
    vec4 colorValue = vec4(0.0);

    for(int i = 0; i < uSteps; i++) {

      vec4 gray_val = texture(uSliceMaps, vpos.xyz);

      if(gray_val.z < 0.05 || gray_val.x < uMinGrayVal || gray_val.x > uMaxGrayVal)
        colorValue = vec4(0.0);
      else {
          colorValue.x = (2.0 - gray_val.x) * l * 0.4;
          colorValue.w = 0.1;

          sample.rgb = (1.0 - accum.a) * colorValue.xxx * sample.a;
          sample.a = colorValue.a * 0.4 * (1.0 / uSteps);

          accum += sample;
          if(accum.a >= 1.0)
             break;
      }

      vpos.xyz += Step;

      if(vpos.x > 1.0 || vpos.y > 1.0 || vpos.z > 1.0 || vpos.x < 0.0 || vpos.y < 0.0 || vpos.z < 0.0)
          break;
    }
    gl_FragColor = accum;

    // for test
    // gl_FragColor = vec4(frontColor.rgb, 1.0);
    // gl_FragColor = backColor;
}
