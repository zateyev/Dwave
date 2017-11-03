#include "Dwave.hpp"

using namespace std;
using glm::mat4;
using glm::vec3;

namespace dwave {

  Dwave::Dwave() {
    g_winWidth = 1920; //900;
    g_winHeight = 1135; //800;

    scr_width = 1135;
    scr_height = 1135;

    g_angle = 0;

    // maxTexturesNumber = 8;
    uSetViewMode = 0;
    uFilterType = 1;

    g_stepSize = 256.0;
    g_MinGrayVal = 103.0;
    g_MaxGrayVal = 255.0;
    // g_OpacityVal = 1.0;
    // g_ColorVal = 1.0;
    cyl_rad = 0.5;

    // tr_width = 256;
    // tr_height = 10;

    rotationX = 0.0;
    rotationY = 0.0;
    // FoV = 48.482f;
    FoV = 45.0f;

    ww = 0;
    hh = 0;

    angleX = 0;
    angleY = 0;

    lastCam_pos = 3.0f;
    is_image_ready = false;

    cam_pos_x = 0.0f;
    cam_pos_y = 0.0f;
    cam_pos_z = 3.0f;

    cam_up_x = 0.0f;
    cam_up_y = 1.0f;
    cam_up_z = 0.0f;

    // cam_pos_x = 0.0f;
    // cam_pos_y = 0.0f;
    // cam_pos_z = -3.0f;
    //
    // cam_up_x = 0.0f;
    // cam_up_y = -1.0f;
    // cam_up_z = 0.0f;

    xmin = 0.0;
    xmax = 1.0;
    ymin = 0.0;
    ymax = 1.0;
    zmin = 0.0;
    zmax = 1.0;

    lights[0] = 1.0;
    lights[1] = 1.0;
    lights[2] = 1.0;
    lights[3] = -1.0;
    lights[4] = -1.0;
    lights[5] = -1.0;
    lights[6] = 1.0;
    lights[7] = 1.0;
    lights[8] = -1.0;

    value1 = 0.0;
    value2 = 0.0;
    value3 = 3;
    value4 = 0.0;
  }

  Dwave::~Dwave() {
    // delete glui;
    // delete fps_val;
    // delete min_gr_label;
  }

  void Dwave::screenshot_png(const char *filename, unsigned int width, unsigned int height,
    GLubyte **pixels, png_byte **png_bytes, png_byte ***png_rows) {
      size_t i, nvals;
      const size_t format_nchannels = 4;
      FILE *f; // = fopen(filename, "wb");
      if (!(f = fopen(filename, "wb"))) {
          printf("Error: failed creating file %s. Error at line %d in file %s\n", filename, __LINE__, __FILE__);
          exit(EXIT_FAILURE);
      }
      nvals = format_nchannels * width * height;
      *pixels = (GLubyte*)realloc(*pixels, nvals * sizeof(GLubyte));
      *png_bytes = (png_byte*)realloc(*png_bytes, nvals * sizeof(png_byte));
      *png_rows = (png_byte**)realloc(*png_rows, height * sizeof(png_byte*));
      glReadPixels(0, 0, width, height, GL_RGBA, GL_UNSIGNED_BYTE, *pixels);
      for (i = 0; i < nvals; i++)
      (*png_bytes)[i] = (*pixels)[i];
      for (i = 0; i < height; i++)
      (*png_rows)[height - i - 1] = &(*png_bytes)[i * width * format_nchannels];
      png_structp png = png_create_write_struct(PNG_LIBPNG_VER_STRING, NULL, NULL, NULL);
      if (!png) abort();
      png_infop info = png_create_info_struct(png);
      if (!info) abort();
      if (setjmp(png_jmpbuf(png))) abort();
      png_init_io(png, f);
      png_set_IHDR(
        png,
        info,
        width,
        height,
        8,
        PNG_COLOR_TYPE_RGBA,
        PNG_INTERLACE_NONE,
        PNG_COMPRESSION_TYPE_DEFAULT,
        PNG_FILTER_TYPE_DEFAULT
      );
      png_write_info(png, info);
      png_write_image(png, *png_rows);
      png_write_end(png, NULL);
      fclose(f);
  }

  int Dwave::model_finished(void) {
    return nframes >= max_nframes;
  }

  double Dwave::getTickCount(void) {
    struct timespec now;
    if (clock_gettime(CLOCK_MONOTONIC, &now))
      return 0;
    return now.tv_sec * 1000.0 + now.tv_nsec / 1000000.0;
  }

  void Dwave::init() {
    g_texWidth = g_winWidth;
    g_texHeight = g_winHeight;
    initVBO();
    initShader();

    // pngTex = new GLuint[maxTexturesNumber];

    Texture texture;
    // texture.initVol3DTex("../final.screw_joint.raw", &pngTex, 419, 492, 462);
    // texture.initVol3DTex("../eucrib.raw", &pngTex, 1536, 1536, 1152);
    // texture.initVol3DTex("../gamma.raw", &pngTex, 1008, 1008, 1008);
    texture.initVol3DTex("../eucrib512.raw", &pngTex, 512, 512, 512);
    // texture.initVol3DTex("../eucrib256.raw", &pngTex, 256, 256, 256);
    // texture.initVol3DTex("../blArchie.raw", &pngTex, 320, 320, 1151);
    // texture.initVol3DTex("../normalx.raw", &normalx, 256, 256, 256);
    // texture.initVol3DTex("../normaly.raw", &normaly, 256, 256, 256);
    // texture.initVol3DTex("../normalz.raw", &normalz, 256, 256, 256);
    // texture.initVol3DTex("../archie.raw", &pngTex, 1536, 1536, 1152);
    // texture.initVol3DTex("../ant1024.raw", &pngTex, 1024, 1024, 1024);
    // texture.initVol3DTex("../breast2.raw", &pngTex, 256, 256, 256);
    // texture.initVol3DTex("../breast_hsv.raw", &pngTex, 256, 256, 144);
    // texture.initVol3DTex("../wasp.raw", &pngTex, 256, 256, 449);
    // texture.initVol3DTex("../archie256.raw", &pngTex, 256, 256, 256);
    // texture.initVol3DTex("../wasp_3.raw", &pngTex, 449, 449, 449);
    // texture.initVol3DTex("../bonsai_fiji.raw", &pngTex, 256, 256, 256);

    // texture.loadImage2("../cm_BrBG_r.png", &trTex, &tr_width, &tr_height, 1); // cm_Greys_r
    // texture.initTFF1DTex("../tff.dat", &trTex);

    // texture.loadImage2("../cm_BrBG_r.png", &trTex, &tr_width, &tr_height);

    g_bfTexObj = initFace2DTex(g_texWidth, g_texHeight);

    initFrameBuffer(g_bfTexObj, g_texWidth, g_texHeight);
    glutPostRedisplay();
  }

  void Dwave::setAngles(float x, float y) {
    angleX = x;
    angleY = y;
  }

  void Dwave::setCameraSettings(float px, float py, float pz, float ux, float uy, float uz) {
    cam_pos_x = px;
    cam_pos_y = py;
    cam_pos_z = pz;

    cam_up_x = ux;
    cam_up_y = uy;
    cam_up_z = uz;
  }

  void Dwave::setSceneSize(int width, int height) {
    g_winWidth = width;
    g_winHeight = height;

    scr_width = width;
    scr_height = height;

    // if (height < width) {
    //   scr_width = height;
    //   scr_height = height;
    // } else {
    //   scr_width = width;
    //   scr_height = width;
    // }
  }

  void Dwave::setGeometry(float xmin, float xmax, float ymin, float ymax, float zmin, float zmax) {
    this->xmin = xmin;
    this->xmax = xmax;
    this->ymin = ymin;
    this->ymax = ymax;
    this->zmin = zmin;
    this->zmax = zmax;
  }

  void Dwave::render(GLenum cullFace) {
      // glClearColor(1.0f, 1.0f, 1.0f, 1.0f);
      // glClearColor(0.0f, 0.0f, 0.0f, 1.0f);
      glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
      //  transform the box
      glm::mat4 projection = glm::perspective(glm::radians(FoV), (GLfloat)g_winWidth / g_winHeight, 0.01f, 11.f);
      // glm::mat4 projection = glm::perspective(glm::radians(FoV), (GLfloat)g_winWidth / g_winHeight, 0.01f, 11.f);

      // glm::vec3 cam_pos = glm::vec3(cam_pos_x, cam_pos_y, cam_pos_z);
      // glm::vec3 cam_up = glm::vec3(cam_up_x, cam_up_y, cam_up_z);
      // glm::vec3 light_1 = glm::vec3(1.0, 1.0, 1.0);
      // glm::vec3 light_2 = glm::vec3(-1.0, -1.0, -1.0);
      // glm::vec3 light_3 = glm::vec3(1.0, 1.0, -1.0);
      // glm::mat4 rotationMat = mat4(1.0f);
      // rotationMat = glm::rotate(rotationMat, glm::radians(angleX), glm::vec3(0.0, -1.0, 0.0));
      // rotationMat = glm::rotate(rotationMat, glm::radians(angleY), glm::vec3(-1.0, 0.0, 0.0));
      // cam_pos = glm::vec3(rotationMat * glm::vec4(cam_pos, 1.0));
      // cam_up = glm::vec3(rotationMat * glm::vec4(cam_up, 1.0));
      // light_1 = glm::vec3(rotationMat * glm::vec4(light_1, 1.0));
      // light_2 = glm::vec3(rotationMat * glm::vec4(light_2, 1.0));
      // light_3 = glm::vec3(rotationMat * glm::vec4(light_3, 1.0));
      // glm::mat4 view = glm::lookAt(cam_pos, // eye
      //          glm::vec3(0.0f, 0.0f, 0.0f), // center
      //          cam_up); // up

      glm::mat4 view = glm::lookAt(glm::vec3(cam_pos_x, cam_pos_y, cam_pos_z), // eye
               glm::vec3(0.0f, 0.0f, 0.0f), // center
               glm::vec3(cam_up_x, cam_up_y, cam_up_z)); // up

      glm::mat4 model = mat4(1.0f);

      model *= glm::rotate(glm::radians((float)g_angle), glm::vec3(0.0f, -1.0f, 0.0f));

      model *= glm::rotate(glm::radians(angleX), vec3(0.0f, 1.0f, 0.0f));
      model *= glm::rotate(glm::radians(angleY), vec3(1.0f, 0.0f, 0.0f));

      model *= glm::translate(glm::vec3(-0.5f, -0.5f, -0.5f));
      // notice the multiplication order: reverse order of transform
      glm::mat4 mvp = projection * view * model;
      GLuint mvpIdx = glGetUniformLocation(shader.get_programHandle(), "MVP");

      if (mvpIdx >= 0) glUniformMatrix4fv(mvpIdx, 1, GL_FALSE, &mvp[0][0]);
      else cerr << "can't get the MVP" << endl;

      // lights[0] = light_1.x;
      // lights[1] = light_1.y;
      // lights[2] = light_1.z;
      // lights[3] = light_2.x;
      // lights[4] = light_2.y;
      // lights[5] = light_2.z;
      // lights[6] = light_3.x;
      // lights[7] = light_3.y;
      // lights[8] = light_3.z;

      drawBox(cullFace);
  }

  void Dwave::initVBO() {
      GLfloat vertices[24] = {
        0.0, 0.0, 0.0,
        0.0, 0.0, 1.0,
        0.0, 1.0, 0.0,
        0.0, 1.0, 1.0,
        1.0, 0.0, 0.0,
        1.0, 0.0, 1.0,
        1.0, 1.0, 0.0,
        1.0, 1.0, 1.0
      };

      GLuint indices[36] = {
        1,5,7,
        7,3,1,
        0,2,6,
        6,4,0,
        0,1,3,
        3,2,0,
        7,5,4,
        4,6,7,
        2,3,7,
        7,6,2,
        1,0,4,
        4,5,1
      };
      GLuint gbo[2];

      glGenBuffers(2, gbo);
      GLuint vertexdat = gbo[0];
      GLuint veridxdat = gbo[1];
      glBindBuffer(GL_ARRAY_BUFFER, vertexdat);
      glBufferData(GL_ARRAY_BUFFER, 24 * sizeof(GLfloat), vertices, GL_STATIC_DRAW);
      // used in glDrawElement()
      glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, veridxdat);
      glBufferData(GL_ELEMENT_ARRAY_BUFFER, 36 * sizeof(GLuint), indices, GL_STATIC_DRAW);

      GLuint vao;
      glGenVertexArrays(1, &vao);
      // vao like a closure binding 3 buffer object: verlocdat vercoldat and veridxdat
      glBindVertexArray(vao);
      glEnableVertexAttribArray(0); // for vertexloc
      glEnableVertexAttribArray(1); // for vertexcol

      // the vertex location is the same as the vertex color
      glBindBuffer(GL_ARRAY_BUFFER, vertexdat);
      glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, 0, (GLfloat*)NULL);
      glVertexAttribPointer(1, 3, GL_FLOAT, GL_FALSE, 0, (GLfloat*)NULL);
      glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, veridxdat);
      // glBindVertexArray(0);
      g_vao = vao;
  }

  void Dwave::drawBox(GLenum glFaces) {
      glEnable(GL_CULL_FACE);
      glCullFace(glFaces);
      glBindVertexArray(g_vao);
      glDrawElements(GL_TRIANGLES, 36, GL_UNSIGNED_INT, (GLuint*)NULL);
      glDisable(GL_CULL_FACE);
  }

  GLuint Dwave::initFace2DTex(GLuint bfTexWidth, GLuint bfTexHeight) {
      GLuint backFace2DTex;
      glGenTextures(1, &backFace2DTex);
      glBindTexture(GL_TEXTURE_2D, backFace2DTex);
      glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_S, GL_REPEAT);
      glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_T, GL_REPEAT);
      glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_NEAREST);
      glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_NEAREST);
      glTexImage2D(GL_TEXTURE_2D, 0, GL_RGBA16F, bfTexWidth, bfTexHeight, 0, GL_RGBA, GL_FLOAT, NULL);
      return backFace2DTex;
  }

  void Dwave::checkFramebufferStatus() {
      GLenum complete = glCheckFramebufferStatus(GL_FRAMEBUFFER);
      if (complete != GL_FRAMEBUFFER_COMPLETE)
      {
        cout << "framebuffer is not complete" << endl;
        exit(EXIT_FAILURE);
      }
  }

  void Dwave::initFrameBuffer(GLuint texObj, GLuint texWidth, GLuint texHeight) {
      // create a depth buffer for our framebuffer
      GLuint depthBuffer;
      glGenRenderbuffers(1, &depthBuffer);
      glBindRenderbuffer(GL_RENDERBUFFER, depthBuffer);
      glRenderbufferStorage(GL_RENDERBUFFER, GL_DEPTH_COMPONENT, texWidth, texHeight);

      // attach the texture and the depth buffer to the framebuffer
      glGenFramebuffers(1, &g_frameBuffer);
      glBindFramebuffer(GL_FRAMEBUFFER, g_frameBuffer);
      glFramebufferTexture2D(GL_FRAMEBUFFER, GL_COLOR_ATTACHMENT0, GL_TEXTURE_2D, texObj, 0);
      glFramebufferRenderbuffer(GL_FRAMEBUFFER, GL_DEPTH_ATTACHMENT, GL_RENDERBUFFER, depthBuffer);
      checkFramebufferStatus();
      glEnable(GL_DEPTH_TEST);
  }

  void Dwave::rcSetUinforms() {
    shader.setUniform("uSteps", g_stepSize);
    // shader.setUniform("uCylRad", cyl_rad);
    // shader.setUniform("uTransferFunction", GL_TEXTURE_1D, trTex, 0);
    shader.setUniform("uBackCoord", GL_TEXTURE_2D, g_bfTexObj, 1);

    // string sprites;
    // GLint volumeLoc;
    // for (int i = 0; i < maxTexturesNumber; i++)
    // {
    //   sprites = "uSliceMaps[" + to_string(i) + "]";
    //   volumeLoc = glGetUniformLocation(shader.get_programHandle(), sprites.c_str());
    //   if (volumeLoc >= 0)
    //   {
    //   	glActiveTexture(GL_TEXTURE2 + i); // GL_TEXTURE2
    //   	glBindTexture(GL_TEXTURE_2D, *pngTex + i);
    //   	glUniform1i(volumeLoc, 2 + i);
    //   }
    //   else cout << "uSliceMaps is not bind to the uniform\n";
    // }

    shader.setUniform("uSliceMaps", GL_TEXTURE_3D, pngTex, 2);
    // shader.setUniform("normalx", GL_TEXTURE_3D, normalx, 3);
    // shader.setUniform("normaly", GL_TEXTURE_3D, normaly, 4);
    // shader.setUniform("normalz", GL_TEXTURE_3D, normalz, 5);
    shader.setUniform("uMinGrayVal", (float)(g_MinGrayVal / 255.0));
    shader.setUniform("uMaxGrayVal", (float)(g_MaxGrayVal / 255.0));
    // shader.setUniform("uOpacityVal", g_OpacityVal);
    shader.setUniform("uSetViewMode", uSetViewMode);

    GLint location = glGetUniformLocation(shader.get_programHandle(), "LightPosition");
    if (location >= 0) glUniform3fv(location, 3, lights);
    else cout << "LightPosition is not bind to the uniform\n";

    shader.setUniform("uFilterType", uFilterType);

    shader.setUniform("xmin", xmin);
    shader.setUniform("xmax", xmax);

    shader.setUniform("ymin", ymin);
    shader.setUniform("ymax", ymax);

    shader.setUniform("zmin", zmin);
    shader.setUniform("zmax", zmax);

    // shader.setUniform("uValue1", value1);
    // shader.setUniform("uValue2", value2);
    shader.setUniform("uValue3", value3);

    // struct timespec now;
    // clock_gettime(CLOCK_REALTIME, &now);
    // float curtm = now.tv_nsec / 1000000.0;
    // shader.setUniform("time", curtm);
    // cout << curtm << endl;

    // shader.setUniform("uColorVal", g_ColorVal);
  }

  void Dwave::initShader() {
    // g_bfVertHandle = Shader::initShaderObj("../shader/lebfirstPass.vert", GL_VERTEX_SHADER);
    // g_bfFragHandle = Shader::initShaderObj("../shader/lebfirstPass.frag", GL_FRAGMENT_SHADER);
    // g_rcVertHandle = Shader::initShaderObj("../shader/lebsecondPass.vert", GL_VERTEX_SHADER);
    // g_rcFragHandle = Shader::initShaderObj("../shader/lebsecondPass.frag", GL_FRAGMENT_SHADER);

    // vertex shader object for first pass
    g_bfVertHandle = Shader::initShaderObj("../shader/firstPass.vert", GL_VERTEX_SHADER);
    // fragment shader object for first pass
    g_bfFragHandle = Shader::initShaderObj("../shader/firstPass.frag", GL_FRAGMENT_SHADER);
    // vertex shader object for second pass
    g_rcVertHandle = Shader::initShaderObj("../shader/secondPass.vert", GL_VERTEX_SHADER);
    // fragment shader object for second pass
    g_rcFragHandle = Shader::initShaderObj("../shader/secondPassFinal.frag", GL_FRAGMENT_SHADER);
    // g_rcFragHandle = Shader::initShaderObj("../shader/secondPassCropCylinder.frag", GL_FRAGMENT_SHADER);
    // g_rcFragHandle = Shader::initShaderObj("../shader/secondPassSoebel.frag", GL_FRAGMENT_SHADER);
    // g_rcFragHandle = Shader::initShaderObj("../shader/secondPassDVR.frag", GL_FRAGMENT_SHADER);
    // g_rcFragHandle = Shader::initShaderObj("../shader/secondPassHSVSurface.frag", GL_FRAGMENT_SHADER);
    // g_rcFragHandle = Shader::initShaderObj("../shader/secondPassNormalFusion.frag", GL_FRAGMENT_SHADER);

    // g_rcFragHandle = Shader::initShaderObj("../shader/secondPassNearestNeighbourHSVFusion.frag", GL_FRAGMENT_SHADER);
    // g_rcFragHandle = Shader::initShaderObj("../shader/secondPassMedianFiltering.frag", GL_FRAGMENT_SHADER);
    // g_rcFragHandle = Shader::initShaderObj("../shader/secondPassMeanFiltering.frag", GL_FRAGMENT_SHADER);
    // create the shader program , use it in an appropriate time
    shader.createShaderPgm();
  }

  void Dwave::updateCamera() {
    glMatrixMode(GL_PROJECTION);
    glLoadIdentity();
    glOrtho(0.0f, ww, 0.0f, hh, -1, 1);
    glScalef(1, -1, 1);
    glTranslatef(0, -hh, 0);
  }

  void Dwave::calculateFrameRate() {
    static float framesPerSecond = 0.0f;       // This will store fps
    static float lastTime = 0.0f;       // This will hold the time from the last frame
    float currentTime = getTickCount() * 0.001f;
    //printf("%.1f FPS\n", currentTime);
    ++framesPerSecond;
    if( currentTime - lastTime >= 1.0f )
    {
      stringstream stream;
      stream << fixed << setprecision(2) << framesPerSecond
        << "\nLatency: " << 1000.0/double(framesPerSecond);
      string str = "FPS: " + stream.str();

      // char* cstr = new char[str.length() + 1];
      // strcpy(cstr, str.c_str());
      // fps_val->set_text(cstr);
      // delete [] cstr;

      // lastTime++;
      lastTime = currentTime;
      // if(SHOW_FPS == 1) fprintf(stderr, "\nCurrent Frames Per Second: %d\n\n", (int)framesPerSecond);
      framesPerSecond = 0;
    }
  }

  void Dwave::timerCB(int millisec) {
    calculateFrameRate();
    glutTimerFunc(millisec, timerCBWrapper, millisec);
    glutPostRedisplay();
  }

  void Dwave::reshape(int w, int h) {
    ww = w;
    hh = h;
    glViewport(0, 0, w, h);
    updateCamera();
  }

  void Dwave::keyboard(unsigned char key, int x, int y) {
    switch (key)
    {
      case '\x1B':
        exit(EXIT_SUCCESS);
        break;
    }
  }

  void Dwave::motion(int x, int y) {
    rotationX += (float)(x - last_x);
    rotationY += (float)(y - last_y);

    angleX = 180 * rotationX / g_winWidth;
    angleY = 180 * rotationY / g_winHeight;

    last_x = x;
    last_y = y;

    glutPostRedisplay();
  }

  void Dwave::mouseMove(int button, int button_state, int x, int y) {
    if ( button == GLUT_LEFT_BUTTON && button_state == GLUT_DOWN )
    {
      last_x = x;
      last_y = y;
    }

    if (button == 3)
    {
      if (FoV > 1) FoV -= 1;
    }

    if (button == 4)
    {
      if (FoV < 179) FoV += 1;
    }
    glutPostRedisplay();
  }

  void Dwave::rotateDisplay() {
    g_angle = (g_angle + 1) % 360;
    glutPostRedisplay();
  }

  void Dwave::display() {
    int tx, ty, tw, th;
    GLUI_Master.get_viewport_area(&tx, &ty, &tw, &th);

    glEnable(GL_DEPTH_TEST);

    // glDisable(GL_DEPTH_TEST);
    // glEnable(GL_BLEND);
    // glBlendEquation(GL_FUNC_ADD);
    // glBlendFunc(GL_SRC_ALPHA, GL_ONE);

    // render to texture
    glBindFramebuffer(GL_DRAW_FRAMEBUFFER, g_frameBuffer);
    glViewport(0, 0, g_winWidth, g_winHeight);
    Shader::linkShader(shader.get_programHandle(), g_bfVertHandle, g_bfFragHandle);
    glUseProgram(shader.get_programHandle());
    // cull front face
    render(GL_FRONT);
    glUseProgram(0);
    glBindFramebuffer(GL_FRAMEBUFFER, 0);

    // tx = (g_winWidth - tw) / 2;
    // ty = (g_winHeight - th) / 2;
    // glViewport(-tx, -ty, g_winWidth, g_winHeight);

    tx = (g_winWidth - scr_width) / 2;
    ty = (g_winHeight - scr_height) / 2;
    glViewport(-tx, -ty, g_winWidth, g_winHeight);

    // glViewport(0, 0, g_winWidth, g_winHeight);

    Shader::linkShader(shader.get_programHandle(), g_rcVertHandle, g_rcFragHandle);
    glUseProgram(shader.get_programHandle());
    rcSetUinforms();
    render(GL_BACK);
    glUseProgram(0);

    // string str = "MinGrayVal: " + to_string((int)g_MinGrayVal);
    // char *cstr = new char[str.length() + 1];
    // strcpy(cstr, str.c_str());
    // min_gr_label->set_text(cstr);
    // delete [] cstr;

    // screenshot_png("scrshot.png", WIDTH, HEIGHT, &pixels, &png_bytes, &png_rows);

    // screenshot_png("static/img/scrshot.png", scr_width, scr_height, &pixels, &png_bytes, &png_rows);
    // glutLeaveMainLoop();

<<<<<<< HEAD
    // if (lastCam_pos != cam_pos_x + cam_pos_y + cam_pos_z) {
    //   screenshot_png("static/img/scrshot.png", scr_width, scr_height, &pixels, &png_bytes, &png_rows);
    //   lastCam_pos = cam_pos_x + cam_pos_y + cam_pos_z;
    //   is_image_ready = true;
    // }
=======
    if (lastCam_pos != cam_pos_x + cam_pos_y + cam_pos_z) {
      screenshot_png("static/img/scrshot.png", scr_width, scr_height, &pixels, &png_bytes, &png_rows);
      lastCam_pos = cam_pos_x + cam_pos_y + cam_pos_z;
      is_image_ready = true;
    }
>>>>>>> cb42f7c5408b0e2d049168eb677467dc509ffe47

    // if (value2 != value1) {
    //   screenshot_png("static/img/scrshot.png", WIDTH, HEIGHT, &pixels, &png_bytes, &png_rows);
    //   value2 = value1;
    // }

    // nframes++;
    // if (model_finished) {
    //   exit(EXIT_SUCCESS);
    // }

    glutSwapBuffers();
  }

  void Dwave::displayWrapper() {
    instance->display();
  }

  void Dwave::timerCBWrapper(int millisec) {
    instance->timerCB(millisec);
  }

  void Dwave::reshapeWrapper(int width, int height) {
    instance->reshape(width, height);
  }

  void Dwave::keyboardWrapper(unsigned char key, int x, int y) {
    instance->keyboard(key, x, y);
  }

  void Dwave::motionWrapper(int x, int y ) {
    instance->motion(x, y);
  }

  void Dwave::mouseMoveWrapper(int button, int button_state, int x, int y ) {
    instance->mouseMove(button, button_state, x, y);
  }

  void Dwave::rotateDisplayWrapper() {
    instance->rotateDisplay();
  }

  void Dwave::setInstance() {
    cout << "Dwave::setInstance()" << endl;
    instance = this;
  }

  void Dwave::startDwave(int argc, char** argv) {
    setInstance();

    glutInit(&argc, argv);
    glutInitDisplayMode(GLUT_DOUBLE | GLUT_RGBA | GLUT_DEPTH);
    glutInitWindowPosition(0, 0);
    glutInitWindowSize(scr_width + 100, scr_height); // (900, 800)
    // glutInitWindowSize(1920, 1045); // (900, 800)

    main_window = glutCreateWindow("DWAVE");
    GLenum err = glewInit();
    if (GLEW_OK != err)
    {
      /* Problem: glewInit failed, something is seriously wrong. */
      fprintf(stderr, "Error: %s\n", glewGetErrorString(err));
    }

    // glMatrixMode(GL_PROJECTION);
    // glLoadIdentity();
    // glMatrixMode(GL_MODELVIEW);
    // glLoadIdentity();

    GLUI_Master.set_glutDisplayFunc(displayWrapper);
    GLUI_Master.set_glutTimerFunc(10, timerCBWrapper, 10);
    GLUI_Master.set_glutReshapeFunc(reshapeWrapper);
    glutKeyboardFunc(keyboardWrapper);
    glutMotionFunc(motionWrapper);
    GLUI_Master.set_glutMouseFunc(mouseMoveWrapper);
    // GLUI_Master.set_glutIdleFunc(rotateDisplayWrapper);

    /****************************************/
    /*         Here's the GLUI code         */
    /****************************************/

    printf( "GLUI version: %3.2f\n", GLUI_Master.get_version() );

    /*** Create the side subwindow ***/
    glui = GLUI_Master.create_glui_subwindow(main_window, GLUI_SUBWINDOW_RIGHT);

    // // obj_panel = new GLUI_Rollout(glui, "Properties", false);
    // GLUI_Panel *obj_panel = new GLUI_Panel(glui, "");
    //
    // /***** Control for object params *****/
    //
    // GLUI_Scrollbar *sb;
    // GLUI_Separator *separator;
    //
    // fps_val = new GLUI_StaticText(obj_panel, "120 FPS");
    //
    // // separator = new GLUI_Separator(obj_panel);
    // // GLUI_StaticText *op_label = new GLUI_StaticText(obj_panel, "Opacity:");
    // // sb = new GLUI_Scrollbar(obj_panel, "Opacity", GLUI_SCROLL_HORIZONTAL, &g_OpacityVal);
    // // sb->set_float_limits(0, 40);
    //
    // separator = new GLUI_Separator(obj_panel);
    //
    // min_gr_label = new GLUI_StaticText(obj_panel, "MinGrayVal:");
    // // GLUI_Spinner* spinner = new GLUI_Spinner(obj_panel, "MinGrayVal:", &g_MinGrayVal);
    // // spinner->set_float_limits(0, 256.0);
    // // spinner->set_alignment(GLUI_ALIGN_RIGHT);
    // //
    // // separator = new GLUI_Separator(obj_panel);
    // sb = new GLUI_Scrollbar(obj_panel, "MinGrayVal", GLUI_SCROLL_HORIZONTAL, &g_MinGrayVal);
    // sb->set_float_limits(0, 255.0);
    //
    // separator = new GLUI_Separator(obj_panel);
    // GLUI_StaticText *max_gr_label = new GLUI_StaticText(obj_panel, "MaxGrayVal:");
    // sb = new GLUI_Scrollbar(obj_panel, "MaxGrayVal", GLUI_SCROLL_HORIZONTAL, &g_MaxGrayVal);
    // sb->set_float_limits(0, 255.0);
    //
    // // separator = new GLUI_Separator(obj_panel);
    // // GLUI_StaticText *color_val_label = new GLUI_StaticText(obj_panel, "ColorVal:");
    // // sb = new GLUI_Scrollbar(obj_panel, "ColorVal", GLUI_SCROLL_HORIZONTAL, &g_ColorVal);
    // // sb->set_float_limits(0, 1.0);
    //
    // separator = new GLUI_Separator(obj_panel);
    // GLUI_Spinner* spinner = new GLUI_Spinner(obj_panel, "StepSize:", &g_stepSize);
    // spinner->set_float_limits(0, 2048.0);
    // spinner->set_alignment(GLUI_ALIGN_RIGHT);
    // // sb = new GLUI_Scrollbar(obj_panel, "StepSize", GLUI_SCROLL_HORIZONTAL, &g_stepSize);
    // // sb->set_float_limits(0, 2024.0);
    //
    // // separator = new GLUI_Separator(obj_panel);
    // // spinner = new GLUI_Spinner(obj_panel, "Cylinder rad:", &cyl_rad);
    // // spinner->set_float_limits(0, 0.7);
    // // spinner->set_alignment(GLUI_ALIGN_RIGHT);
    //
    // /**** Add listbox ****/
    // new GLUI_StaticText( glui, "" );
    // GLUI_Listbox *list = new GLUI_Listbox( glui, "View mode:", &uSetViewMode );
    // list->add_item(0, "Blinn-Phong shading");
    // list->add_item(1, "Cook-Torrance");
    //
    // new GLUI_StaticText( glui, "" );
    // GLUI_Listbox *filters = new GLUI_Listbox( glui, "Filter type:", &uFilterType );
    // filters->add_item(0, "None");
    // filters->add_item(1, "Mean Filtering");
    // filters->add_item(2, "Median Filtering");
    //
    // separator = new GLUI_Separator(obj_panel);
    // spinner = new GLUI_Spinner(obj_panel, "Take a screenshot:", &value1);
    // spinner->set_float_limits(0.1, 0.9);
    // spinner->set_alignment(GLUI_ALIGN_RIGHT);
    // //
    // // separator = new GLUI_Separator(obj_panel);
    // // spinner = new GLUI_Spinner(obj_panel, "Reflectance:", &value2);
    // // spinner->set_float_limits(1.0, 10.0);
    // // spinner->set_alignment(GLUI_ALIGN_RIGHT);
    //
    // separator = new GLUI_Separator(obj_panel);
    // GLUI_StaticText *c_rad_label = new GLUI_StaticText(obj_panel, "Cylinder rad:");
    // sb = new GLUI_Scrollbar(obj_panel, "Cylinder rad", GLUI_SCROLL_HORIZONTAL, &cyl_rad);
    // sb->set_float_limits(0, 0.5);
    //
    // separator = new GLUI_Separator(obj_panel);
    // GLUI_StaticText *z_bottom = new GLUI_StaticText(obj_panel, "Z bottom:");
    // sb = new GLUI_Scrollbar(obj_panel, "Z bottom", GLUI_SCROLL_HORIZONTAL, &zmin);
    // sb->set_float_limits(0, 1.0);
    //
    // separator = new GLUI_Separator(obj_panel);
    // GLUI_StaticText *z_top = new GLUI_StaticText(obj_panel, "Z top:");
    // sb = new GLUI_Scrollbar(obj_panel, "Z bottom", GLUI_SCROLL_HORIZONTAL, &zmax);
    // sb->set_float_limits(0, 1.0);
    //
    // separator = new GLUI_Separator(obj_panel);
    // spinner = new GLUI_Spinner(obj_panel, "Lights number:", &value3);
    // spinner->set_int_limits(0, 8);
    // spinner->set_alignment(GLUI_ALIGN_RIGHT);

    init();

    // glui->set_main_gfx_window(main_window);

    // delete obj_panel;
    // delete separator;
    // delete color_val_label;
    // delete sb;
    // delete spinner;

    glutSetOption(GLUT_ACTION_ON_WINDOW_CLOSE, GLUT_ACTION_CONTINUE_EXECUTION);
    glutMainLoop();

    // glutMainLoopEvent();
  }

  void Dwave::stopDwave() {
    cout << "stop Dwave" << endl;
    glutDestroyWindow(main_window);
  }

  void Dwave::reset() {
    is_image_ready = false;
  }

  bool Dwave::isImageReady() {
    return is_image_ready;
  }

  Dwave* Dwave::instance = NULL;
  GLubyte* Dwave::pixels = NULL;
  int Dwave::offscreen = 1;
  unsigned int Dwave::max_nframes = 100;
  unsigned int Dwave::nframes = 0;

  png_byte* Dwave::png_bytes = NULL;
  png_byte** Dwave::png_rows = NULL;
} // namespace dwave


extern "C" {
    dwave::Dwave* Dwave_new() {
      return new dwave::Dwave();
    }

    void Dwave_start(dwave::Dwave* dwave) {
      dwave->startDwave(0, NULL);
    }

    void Dwave_set_cam_settings(dwave::Dwave* dwave, float px, float py, float pz, float ux, float uy, float uz) {
      dwave->setCameraSettings(px, py, pz, ux, uy, uz);
    }

    void Dwave_set_scene_size(dwave::Dwave* dwave, int width, int height) {
      dwave->setSceneSize(width, height);
    }

    void Dwave_set_geometry(dwave::Dwave* dwave, float xmin, float xmax, float ymin, float ymax, float zmin, float zmax) {
      dwave->setGeometry(xmin, xmax, ymin, ymax, zmin, zmax);
    }

    void Dwave_stop(dwave::Dwave* dwave) {
      dwave->stopDwave();
    }

    void Dwave_reset(dwave::Dwave* dwave) {
      dwave->reset();
    }

    bool Dwave_is_image_ready(dwave::Dwave* dwave) {
      dwave->isImageReady();
    }
}
