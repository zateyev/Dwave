#ifndef DWAVE_HPP
#define DWAVE_HPP

#define GLM_FORCE_RADIANS

#include <iostream>
#include <cstdio>
#include <cstdlib>
#include <GL/glew.h>
// #include <GL/glext.h>
// #include <GL/glut.h>
#include <GL/freeglut.h>
#include <glm/glm.hpp>
#include <glm/gtc/matrix_transform.hpp>
#include <glm/gtx/transform2.hpp>
#include <glm/gtc/type_ptr.hpp>
#include <math.h>

#include "texture.hpp"
#include "shader.hpp"

// #pragma comment(lib, "/usr/lib/lib/libglui.so")
#include "glui.h"

#include <iomanip> // setprecision
#include <sstream>

#include <png.h>

namespace dwave {

  class Dwave {
    private:
      static const int SCREENSHOT_MAX_FILENAME = 5;
      static GLubyte *pixels;
      static GLuint fbo;
      static GLuint rbo_color;
      static GLuint rbo_depth;
      // static const unsigned int HEIGHT = 732;
      // static const unsigned int WIDTH = 732;
      static int offscreen;
      static unsigned int max_nframes;
      static unsigned int nframes;
      static unsigned int time0;

      /* Model. */
      static double angle;
      static double delta_angle;

      static png_byte *png_bytes;
      static png_byte **png_rows;

      GLuint g_vao;
      Shader shader;
      GLuint g_winWidth;//900;
      GLuint g_winHeight;//800;
      GLint g_angle;
      GLuint g_frameBuffer;
      // transfer function
      GLuint g_bfTexObj;
      GLuint g_texWidth;
      GLuint g_texHeight;
      GLuint g_rcVertHandle;
      GLuint g_rcFragHandle;
      GLuint g_bfVertHandle;
      GLuint g_bfFragHandle;
      // GLuint *pngTex;
      GLuint pngTex;
      GLuint normalx;
      GLuint normaly;
      GLuint normalz;
      GLuint trTex;

      // int maxTexturesNumber;
      int uSetViewMode;
      int uFilterType;

      float g_stepSize;
      float g_MinGrayVal;
      float g_MaxGrayVal;
      // float g_OpacityVal;
      // float g_ColorVal;
      float cyl_rad;


      // int tr_width;
      // int tr_height;

      int last_x, last_y;
      float rotationX;
      float rotationY;
      float FoV;

      int ww;
      int hh;

      int scr_width;
      int scr_height;

      float angleX;
      float angleY;

      float lastCam_pos;

      float cam_pos_x;
      float cam_pos_y;
      float cam_pos_z;

      float cam_up_x;
      float cam_up_y;
      float cam_up_z;

      float xmin;
      float xmax;
      float ymin;
      float ymax;
      float zmin;
      float zmax;

      float lights[9];

      float value1;
      float value2;
      int value3;
      float value4;

      int main_window;

      /** Pointers to the windows and some of the controls we'll create **/
      GLUI *glui;

      GLUI_StaticText *fps_val;
      GLUI_StaticText *min_gr_label;

      static void screenshot_png(const char *filename, unsigned int width, unsigned int height,
        GLubyte **pixels, png_byte **png_bytes, png_byte ***png_rows);

      static int model_finished(void);

      double getTickCount(void);

      void init();

      void render(GLenum cullFace);

      void initVBO();

      void drawBox(GLenum glFaces);

      GLuint initFace2DTex(GLuint bfTexWidth, GLuint bfTexHeight);

      void checkFramebufferStatus();

      void initFrameBuffer(GLuint texObj, GLuint texWidth, GLuint texHeight);

      void rcSetUinforms();

      void initShader();

      void updateCamera();

    protected:
      static Dwave* instance;

    public:
      Dwave();
      virtual ~Dwave();

      void setAngles(float x, float y);

      void setCameraSettings(float px, float py, float pz, float ux, float uy, float uz);

      void setSceneSize(int width, int height);

      void setGeometry(float xmin, float xmax, float ymin, float ymax, float zmin, float zmax);

      void startDwave(int argc, char** argv);

      void stopDwave();

      void calculateFrameRate();

      void timerCB(int millisec);

      void reshape(int w, int h);

      void keyboard(unsigned char key, int x, int y);

      void motion(int x, int y );

      void mouseMove(int button, int button_state, int x, int y );

      void rotateDisplay();

      void display();

      void setInstance();

      static void displayWrapper();
      static void timerCBWrapper(int millisec);
      static void reshapeWrapper(int width, int height);
      static void keyboardWrapper(unsigned char key, int x, int y);
      static void motionWrapper(int x, int y );
      static void mouseMoveWrapper(int button, int button_state, int x, int y );
      static void rotateDisplayWrapper();
  };
} // namespace dwave

#endif
