precision mediump int;
precision mediump float;
varying vec4 frontColor;
varying vec4 pos;
uniform sampler2D uBackCoord;
uniform sampler3D uSliceMaps;
uniform float uMinGrayVal;
uniform float uMaxGrayVal;
uniform float uSteps;

void main(void)
{
    vec2 texC = ((pos.xy/pos.w) + 1.0) / 2.0;
    vec4 backColor = texture2D(uBackCoord, texC);
    vec3 dir = backColor.rgb - frontColor.rgb;
    vec4 vpos = frontColor;
    vec3 Step = dir/uSteps;
    vec4 accum = vec4(0.0);
    vec4 color = vec4(1.0);

    for(int i = 0; i < uSteps; i++) {

      vec4 gray_val = texture(uSliceMaps, vpos.xyz);

      if(gray_val.x > uMinGrayVal && gray_val.x < uMaxGrayVal) {

        color.a = 0.04;
        accum += color;

        if(accum.a >= 1.0) break;
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
