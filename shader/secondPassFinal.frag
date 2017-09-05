precision mediump int;
precision mediump float;
varying vec4 frontColor;
varying vec4 pos;
uniform sampler2D uBackCoord;
uniform sampler3D uSliceMaps;
uniform sampler3D normalx;
uniform sampler3D normaly;
uniform sampler3D normalz;
uniform int uSetViewMode;
uniform int uFilterType;
uniform float uMinGrayVal;
uniform float uMaxGrayVal;
uniform float uSteps;
uniform float uCylRad;
uniform float zBottom;
uniform float zTop;
uniform vec3 LightPosition[3];

// uniform float uValue1;
// uniform float uValue2;
uniform int uValue3;

// float xw = 449.0;
// float yw = 449.0;
// float zw = 449.0;

float xw = 256.0;
float yw = 256.0;
float zw = 256.0;

// float xw = 512.0;
// float yw = 512.0;
// float zw = 512.0;

// float xw = 1536.0;
// float yw = 1536.0;
// float zw = 1152.0;

// float xw = 1024.0;
// float yw = 1024.0;
// float zw = 1024.0;

// Compute the Normal around the current voxel
vec3 getNormal(vec3 at) {
    // float x0 = at.x - 5.0/xw;
    // float x1 = at.x + 5.0/xw;
    //
    // float y0 = at.x - 5.0/yw;
    // float y1 = at.x + 5.0/yw;
    //
    // float z0 = at.x - 5.0/zw;
    // float z1 = at.x + 5.0/zw;
    // return vec3(x0 - x1, y0 - y1, z0 - z1);

    vec3 texpos1;

    // float w0 = (at.z - (1.0/zw)) - floor(at.z);
    // float w1 = at.z - floor(at.z);
    // float w2 = (at.z + (1.0/zw)) - floor(at.z);
    float w0 = at.z - (1.0/zw);
    float w1 = at.z;
    float w2 = at.z + (1.0/zw);

    float fx, fy, fz;

    float L[9];
    float H[9];

    // float xdir[3][9] = (float[](-1.0, -3.0, -1.0, 0.0, 0.0, 0.0, 1.0, 3.0, 1.0),
    //                     float[](-1.0, -3.0, -1.0, 0.0, 0.0, 0.0, 1.0, 3.0, 1.0),
    //                     float[](-1.0, -3.0, -1.0, 0.0, 0.0, 0.0, 1.0, 3.0, 1.0));

    texpos1.z = at.z - 1.0/zw;
    for (int i = 2, k = 0; i > -1; --i) {
      for (int j = 0; j < 3; j++) {
        texpos1.x = at.x + (j - 1)/xw;
        texpos1.y = at.y + (i - 1)/yw;
        L[k] = texture(uSliceMaps, texpos1).x;
        H[k++] = texture(uSliceMaps, vec3(texpos1.x, texpos1.y, at.z + 1.0/zw)).x;
      }
    }

    // we need to get interpolation of 2 x points
    // x direction
    // -1 -3 -1   0  0  0   1  3  1
    // -3 -6 -3   0  0  0   3  6  3
    // -1 -3 -1   0  0  0   1  3  1
    // y direction
    //  1  3  1   3  6  3   1  3  1
    //  0  0  0   0  0  0   0  0  0
    // -1 -3 -1  -3 -6 -3  -1 -3 -1
    // z direction
    // -1  0  1   -3  0  3   -1  0  1
    // -3  0  3   -6  0  6   -3  0  3
    // -1  0  1   -3  0  3   -1  0  1

    fx =  ((w0 * (H[0] - L[0])) + L[0]) * -1.0;
    fx += ((w1 * (H[0] - L[0])) + L[0]) * -3.0;
    fx += ((w2 * (H[0] - L[0])) + L[0]) * -1.0;

    fx += ((w0 * (H[3] - L[3])) + L[3]) * -3.0;
    fx += ((w1 * (H[3] - L[3])) + L[3]) * -6.0;
    fx += ((w2 * (H[3] - L[3])) + L[3]) * -3.0;

    fx += ((w0 * (H[6] - L[6])) + L[6]) * -1.0;
    fx += ((w1 * (H[6] - L[6])) + L[6]) * -3.0;
    fx += ((w2 * (H[6] - L[6])) + L[6]) * -1.0;

    fx += ((w0 * (H[1] - L[1])) + L[1]) * 0.0;
    fx += ((w1 * (H[1] - L[1])) + L[1]) * 0.0;
    fx += ((w2 * (H[1] - L[1])) + L[1]) * 0.0;

    fx += ((w0 * (H[4] - L[4])) + L[4]) * 0.0;
    fx += ((w1 * (H[4] - L[4])) + L[4]) * 0.0;
    fx += ((w2 * (H[4] - L[4])) + L[4]) * 0.0;

    fx += ((w0 * (H[7] - L[7])) + L[7]) * 0.0;
    fx += ((w1 * (H[7] - L[7])) + L[7]) * 0.0;
    fx += ((w2 * (H[7] - L[7])) + L[7]) * 0.0;

    fx += ((w0 * (H[2] - L[2])) + L[2]) * 1.0;
    fx += ((w1 * (H[2] - L[2])) + L[2]) * 3.0;
    fx += ((w2 * (H[2] - L[2])) + L[2]) * 1.0;

    fx += ((w0 * (H[5] - L[5])) + L[5]) * 3.0;
    fx += ((w1 * (H[5] - L[5])) + L[5]) * 6.0;
    fx += ((w2 * (H[5] - L[5])) + L[5]) * 3.0;

    fx += ((w0 * (H[8] - L[8])) + L[8]) * 1.0;
    fx += ((w1 * (H[8] - L[8])) + L[8]) * 3.0;
    fx += ((w2 * (H[8] - L[8])) + L[8]) * 1.0;

    fy =  ((w0 * (H[0] - L[0])) + L[0]) * 1.0;
    fy += ((w1 * (H[0] - L[0])) + L[0]) * 3.0;
    fy += ((w2 * (H[0] - L[0])) + L[0]) * 1.0;

    fy += ((w0 * (H[3] - L[3])) + L[3]) * 0.0;
    fy += ((w1 * (H[3] - L[3])) + L[3]) * 0.0;
    fy += ((w2 * (H[3] - L[3])) + L[3]) * 0.0;

    fy += ((w0 * (H[6] - L[6])) + L[6]) * -1.0;
    fy += ((w1 * (H[6] - L[6])) + L[6]) * -3.0;
    fy += ((w2 * (H[6] - L[6])) + L[6]) * -1.0;

    fy += ((w0 * (H[1] - L[1])) + L[1]) * 3.0;
    fy += ((w1 * (H[1] - L[1])) + L[1]) * 6.0;
    fy += ((w2 * (H[1] - L[1])) + L[1]) * 3.0;

    fy += ((w0 * (H[4] - L[4])) + L[4]) * 0.0;
    fy += ((w1 * (H[4] - L[4])) + L[4]) * 0.0;
    fy += ((w2 * (H[4] - L[4])) + L[4]) * 0.0;

    fy += ((w0 * (H[7] - L[7])) + L[7]) * -3.0;
    fy += ((w1 * (H[7] - L[7])) + L[7]) * -6.0;
    fy += ((w2 * (H[7] - L[7])) + L[7]) * -3.0;

    fy += ((w0 * (H[2] - L[2])) + L[2]) * 1.0;
    fy += ((w1 * (H[2] - L[2])) + L[2]) * 3.0;
    fy += ((w2 * (H[2] - L[2])) + L[2]) * 1.0;

    fy += ((w0 * (H[5] - L[5])) + L[5]) * 0.0;
    fy += ((w1 * (H[5] - L[5])) + L[5]) * 0.0;
    fy += ((w2 * (H[5] - L[5])) + L[5]) * 0.0;

    fy += ((w0 * (H[8] - L[8])) + L[8]) * -1.0;
    fy += ((w1 * (H[8] - L[8])) + L[8]) * -3.0;
    fy += ((w2 * (H[8] - L[8])) + L[8]) * -1.0;


    fz =  ((w0 * (H[0] - L[0])) + L[0]) * -1.0;
    fz += ((w1 * (H[0] - L[0])) + L[0]) * 0.0;
    fz += ((w2 * (H[0] - L[0])) + L[0]) * 1.0;

    fz += ((w0 * (H[3] - L[3])) + L[3]) * -3.0;
    fz += ((w1 * (H[3] - L[3])) + L[3]) * 0.0;
    fz += ((w2 * (H[3] - L[3])) + L[3]) * 3.0;

    fz += ((w0 * (H[6] - L[6])) + L[6]) * -1.0;
    fz += ((w1 * (H[6] - L[6])) + L[6]) * 0.0;
    fz += ((w2 * (H[6] - L[6])) + L[6]) * 1.0;

    fz += ((w0 * (H[1] - L[1])) + L[1]) * -3.0;
    fz += ((w1 * (H[1] - L[1])) + L[1]) * 0.0;
    fz += ((w2 * (H[1] - L[1])) + L[1]) * 3.0;

    fz += ((w0 * (H[4] - L[4])) + L[4]) * -6.0;
    fz += ((w1 * (H[4] - L[4])) + L[4]) * 0.0;
    fz += ((w2 * (H[4] - L[4])) + L[4]) * 6.0;

    fz += ((w0 * (H[7] - L[7])) + L[7]) * -3.0;
    fz += ((w1 * (H[7] - L[7])) + L[7]) * 0.0;
    fz += ((w2 * (H[7] - L[7])) + L[7]) * 3.0;

    fz += ((w0 * (H[2] - L[2])) + L[2]) * -1.0;
    fz += ((w1 * (H[2] - L[2])) + L[2]) * 0.0;
    fz += ((w2 * (H[2] - L[2])) + L[2]) * 1.0;

    fz += ((w0 * (H[5] - L[5])) + L[5]) * -3.0;
    fz += ((w1 * (H[5] - L[5])) + L[5]) * 0.0;
    fz += ((w2 * (H[5] - L[5])) + L[5]) * 3.0;

    fz += ((w0 * (H[8] - L[8])) + L[8]) * -1.0;
    fz += ((w1 * (H[8] - L[8])) + L[8]) * 0.0;
    fz += ((w2 * (H[8] - L[8])) + L[8]) * 1.0;
    vec3 n = vec3( fx/27.0 , fy/27.0 , fz/27.0 );
    return n;
}
// returns intensity of reflected ambient lighting
const vec3 lightColor = vec3(1.0, 0.88, 0.74);
const vec3 u_intensity = vec3(0.1, 0.1, 0.1);

vec3 ambientLighting() {
    const vec3 u_matAmbientReflectance = lightColor;
    const vec3 u_lightAmbientIntensity = u_intensity;
    // const vec3 u_lightAmbientIntensity = vec3(0.6, 0.3, 0.0);

    return u_matAmbientReflectance * u_lightAmbientIntensity;
}

// returns intensity of diffuse reflection
vec3 diffuseLighting(in vec3 N, in vec3 L) {
    const vec3 u_matDiffuseReflectance = lightColor;
    const vec3 u_lightDiffuseIntensity = vec3(0.6);

    // calculation as for Lambertian reflection
    float diffuseTerm = dot(N, L);
    if (diffuseTerm > 1.0) {
        diffuseTerm = 1.0;
    } else if (diffuseTerm < 0.0) {
        diffuseTerm = 0.0;
    }
    return u_matDiffuseReflectance * u_lightDiffuseIntensity * diffuseTerm;
}

// returns intensity of specular reflection
vec3 specularLighting(in vec3 N, in vec3 L, in vec3 V) {
    float specularTerm = 0.0;
    const vec3 u_lightSpecularIntensity = vec3(0.3);
    // const vec3 u_lightSpecularIntensity = u_intensity;
    const vec3 u_matSpecularReflectance = vec3(1.0);
    // const vec3 u_matSpecularReflectance = lightColor;
    const float u_matShininess = 5.0;
   // calculate specular reflection only if
   // the surface is oriented to the light source
   if(dot(N, L) > 0.0)
   {
      // half vector
      // vec3 H = normalize(L + V);
      // specularTerm = pow(dot(N, H), u_matShininess);

      vec3 e = normalize(-V);
      vec3 r = normalize(-reflect(L, N));
      specularTerm = pow(max(dot(r, e), 0.0), u_matShininess);
   }
   return u_matSpecularReflectance * u_lightSpecularIntensity * specularTerm;
}

float beckmannDistribution(float NH, float roughness) {
  float NdotH = max(NH, 0.0001);
  float mSquared = roughness * roughness;
  float r1 = 1.0 / (3.141592653589793 * mSquared * pow(NdotH, 4.0));
  float r2 = (NdotH * NdotH - 1.0) / (mSquared * NdotH * NdotH);
  return r1 * exp(r2);
}

vec3 cookTorranceSpecular(
  vec3 surfaceNormal,
  vec3 lightDirection,
  vec3 viewDirection,
  float roughness,
  float fresnel,
  float k) {

  float NdotL = max(dot(surfaceNormal, lightDirection), 0.0);

  float power = 0.0;

  if (NdotL > 0.0) {
    //Half angle vector
    vec3 H = normalize(lightDirection + viewDirection);

    //Geometric term
    float NdotH = max(dot(surfaceNormal, H), 0.0);
    float NdotV = max(dot(surfaceNormal, viewDirection), 0.0);
    float VdotH = max(dot(viewDirection, H), 0.0);
    float x = 2.0 * NdotH / VdotH;
    float geoAtt = min(1.0, min(x * NdotV, x * NdotL));

    //Distribution term
    float D = beckmannDistribution(NdotH, roughness);

    //Fresnel term
    // float F = pow(1.0 - VdotH, fresnel);
    float F = fresnel + (1 - fresnel) * pow(1.0 - VdotH, 5.0);

    //Multiply terms
    power =  geoAtt * F * D / max(3.14159265 * NdotV * NdotL, 0.000001);
  }

  return lightColor * NdotL * (k + power * (1.0 - k));
}

float random(vec2 co) {
    return fract(sin(dot(co.xy ,vec2(12.9898,78.233))) * 43758.5453);
}

void main(void)
{
    vec2 texC = ((pos.xy/pos.w) + 1.0) / 2.0;
    vec4 backColor = texture2D(uBackCoord, texC);
    vec3 dir = backColor.rgb - frontColor.rgb;
    vec4 currentPosition = frontColor;
    vec3 Step = dir/uSteps;
    vec4 accum = vec4(0.0);
    vec4 sample = vec4(0.0);
    // vec3 lightPos[8];
    // lightPos[0] = vec3(1, 1, 1);
    // lightPos[1] = vec3(-1, -1, -1);
    // lightPos[2] = vec3(1, 1, -1);
    //
    // lightPos[3] = vec3(-1, 1, 1);
    // lightPos[4] = vec3(-1, 1, -1);
    // lightPos[5] = vec3(-1, -1, 1);
    // lightPos[6] = vec3(1, -1, -1);
    // lightPos[7] = vec3(1, -1, 1);

    float xsqu;
    float ysqu;
    float distanceFromCenter;

    for(int i = 0; i < uSteps; i++) {
      xsqu = (0.5 - currentPosition.x) * (0.5 - currentPosition.x);
      ysqu = (0.5 - currentPosition.y) * (0.5 - currentPosition.y);
      distanceFromCenter = sqrt(xsqu + ysqu);
      if (distanceFromCenter < uCylRad &&
          currentPosition.z > zBottom && currentPosition.z < zTop) {
        float gray_val = texture(uSliceMaps, currentPosition.xyz);
        if (uFilterType != 0 && gray_val > uMinGrayVal && gray_val < uMaxGrayVal) {
          int mask_size = 3;
          if (uFilterType == 1) { // Mean Filtering
            float sum_gray_val = 0.0;
            vec3 offset;
            vec3 curDotPos;

            for(int i = 0; i < mask_size; ++i) {
              for(int j = 0; j < mask_size; ++j) {
                for(int k = 0; k < mask_size; ++k) {
                  offset = vec3((i - (int)mask_size / 2) / xw,
                      (j - (int)mask_size / 2) / yw,
                      (k - (int)mask_size / 2) / zw);

                  curDotPos = currentPosition.xyz + offset;
                  sum_gray_val += texture(uSliceMaps, curDotPos).x;
                }
              }
            }

            gray_val = sum_gray_val / pow(mask_size, 3);


            // vec3 dirFromCP[14];
            // dirFromCP[0] = vec3(1.0 / xw, 0.0 / yw, 0.0 / zw);
            // dirFromCP[1] = vec3(0.0 / xw, 1.0 / yw, 0.0 / zw);
            // dirFromCP[2] = vec3(0.0 / xw, 0.0 / yw, 1.0 / zw);
            // dirFromCP[3] = vec3(-1.0 / xw, 0.0 / yw, 0.0 / zw);
            // dirFromCP[4] = vec3(0.0 / xw, -1.0 / yw, 0.0 / zw);
            // dirFromCP[5] = vec3(0.0 / xw, 0.0 / yw, -1.0 / zw);

            // dirFromCP[6] = vec3(-1.0 / xw, 1.0 / yw, 1.0 / zw);
            // dirFromCP[7] = vec3(1.0 / xw, 1.0 / yw, 1.0 / zw);
            // dirFromCP[8] = vec3(1.0 / xw, 1.0 / yw, -1.0 / zw);
            // dirFromCP[9] = vec3(-1.0 / xw, 1.0 / yw, -1.0 / zw);
            // dirFromCP[10] = vec3(-1.0 / xw, -1.0 / yw, 1.0 / zw);
            // dirFromCP[11] = vec3(1.0 / xw, -1.0 / yw, 1.0 / zw);
            // dirFromCP[12] = vec3(1.0 / xw, -1.0 / yw, -1.0 / zw);
            // dirFromCP[13] = vec3(-1.0 / xw, -1.0 / yw, -1.0 / zw);
            // for(int i = 0; i < 14; ++i) {
            //   offset = dirFromCP[i];
            //   curDotPos = currentPosition.xyz + offset;
            //   sum_gray_val += texture(uSliceMaps, curDotPos).x;
            // }
            // gray_val = sum_gray_val / 14;
          }
          else { // Median Filtering
            float gray_values[27];
            int neighbour_i = 0;
            vec3 offset;
            vec3 curDotPos;
            for(int i = 0; i < mask_size; ++i) {
              for(int j = 0; j < mask_size; ++j) {
                for(int k = 0; k < mask_size; ++k) {
                  offset = vec3((i - (int)mask_size / 2) / xw,
                      (j - (int)mask_size / 2) / yw,
                      (k - (int)mask_size / 2) / zw);

                  curDotPos = currentPosition.xyz + offset;
                  gray_values[neighbour_i] = texture(uSliceMaps, curDotPos).x;
                  neighbour_i++;
                }
              }
            }

            // bubbleSort(gray_values);
            bool swapped = true;
            int n = 27;
            float tmp;
            while (swapped) {
              swapped = false;
              for (int i = 0; i < n - 1; ++i) {
                if (gray_values[i] > gray_values[i + 1]) {
                  tmp = gray_values[i];
                  gray_values[i] = gray_values[i + 1];
                  gray_values[i + 1] = tmp;
                  swapped = true;
                  }
              }
              n--;
            }

            gray_val = gray_values[13];
          }
        }

        if (gray_val > uMinGrayVal && gray_val < uMaxGrayVal) {
          // normalize vectors after interpolation
          vec3 V = normalize(pos - currentPosition.xyz);
          float tx = texture(normalx, currentPosition.xyz).x * 255.0 - 127.0;
          float ty = texture(normaly, currentPosition.xyz).x * 255.0 - 127.0;
          float tz = texture(normalz, currentPosition.xyz).x * 255.0 - 127.0;
          // vec3 N = normalize(vec3(tx, ty, tz));
          vec3 N = (normalize(getNormal(currentPosition.xyz)) + 1.0) / 2.0;
          // vec3 N = normalize(vec3(1.0));

          // set important material values for cookTorranceSpecular
          float roughnessValue = 0.9; // 0 : smooth, 1: rough
          float F0 = 1.0; // fresnel reflectance at normal incidence
          float k = 0.8; // fraction of diffuse reflection (specular reflection = 1 - k)

          for(int light_i = 0; light_i < uValue3; ++light_i) {
            // vec3 L = normalize(lightPos[light_i] - currentPosition.xyz);
            vec3 L = normalize(LightPosition[light_i] - currentPosition.xyz);
            if (uSetViewMode == 0) { // Blinn-Phong shading mode
              vec3 Iamb = ambientLighting();
              vec3 Idif = diffuseLighting(N, L);
              vec3 Ispe = specularLighting(N, L, V);
              sample.rgb += N;
              // sample.rgb += (Iamb + Idif + Ispe);
              // sample.rgb += Iamb;
              // sample.rgb += Idif;
              // sample.rgb += Ispe;
              // if (uValue3 == 1) {
              //   sample.rgb += Iamb;
              // }
              // else if (uValue3 == 2) {
              //   sample.rgb += Idif;
              // }
              // else if (uValue3 == 3) {
              //   sample.rgb += Ispe;
              // }
              // else if (uValue3 == 4) {
              //   sample.rgb += (Iamb + Idif + Ispe);
              // }
            }
            else if(uSetViewMode == 1) { // Cook-Torrance mode
              sample.rgb += cookTorranceSpecular(N, L, V, roughnessValue, F0, k);
            }
          }

          accum = sample;
          // if(accum.a >= 1.0) break;
          break;
        }
      }

      //advance the current position
      currentPosition.xyz += Step;

      if(currentPosition.x > 1.0 || currentPosition.y > 1.0 || currentPosition.z > 1.0 || currentPosition.x < 0.0 || currentPosition.y < 0.0 || currentPosition.z < 0.0)
          break;
    }
    gl_FragColor = accum;

    // for test
    // gl_FragColor = vec4(frontColor.rgb, 1.0);
    // gl_FragColor = backColor;
}
