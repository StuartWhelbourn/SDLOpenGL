#include <iostream>
#include "SDLOpenGL.h"
#include <ngl/NGLInit.h>

SDLOpenGl::SDLOpenGl(const std::string &_name,
                     int _x,
                     int _y,
                     int _width,
                     int _height)
{
  m_name=_name;
  m_x=_x;
  m_y=_y;
  m_width=_width;
  m_height=_height;
  init();
}

void SDLOpenGl::init()
{
  if(SDL_Init(SDL_INIT_EVERYTHING) <0)
  {
    errorExit("error calling init");
  }
  m_window=SDL_CreateWindow(m_name.c_str(),m_x,m_y,m_width,m_height,SDL_WINDOW_OPENGL);

  if(!m_window)
  {
    errorExit("Could not open window");
  }
  createGLContext();
}

void SDLOpenGl::createGLContext()
{
  SDL_GL_SetAttribute(SDL_GL_CONTEXT_PROFILE_MASK,SDL_GL_CONTEXT_PROFILE_CORE);
  SDL_GL_SetAttribute(SDL_GL_CONTEXT_MAJOR_VERSION,4);
  SDL_GL_SetAttribute(SDL_GL_CONTEXT_MINOR_VERSION,3);
  SDL_GL_SetAttribute(SDL_GL_MULTISAMPLEBUFFERS,1);
  SDL_GL_SetAttribute(SDL_GL_MULTISAMPLESAMPLES,4);
  SDL_GL_SetAttribute(SDL_GL_DEPTH_SIZE ,16);
  SDL_GL_SetAttribute(SDL_GL_DOUBLEBUFFER,1);

  m_glContext=SDL_GL_CreateContext(m_window);
}

void SDLOpenGl::errorExit(const std::string &_msg) const
{

}
