#include <QMouseEvent>
#include <QGuiApplication>

#include <iostream>
#include "NGLScene.h"
#include <ngl/NGLInit.h>
#include <iostream>
#include <vector>
#include <ngl/Light.h>
#include "flock.h"




NGLScene::NGLScene(QWidget *_parent) : QOpenGLWidget(_parent)
{

  // re-size the widget to that of the parent (in this case the GLFrame passed in on construction)

  setFocus();

  // re-size the widget to that of a parent
  this->resize(_parent->size());

  m_mode=false;
}


NGLScene::~NGLScene()
{
  std::cout<<"Shutting down NGL, removing VAO's and Shaders\n";
}

void NGLScene::resizeGL(QResizeEvent *_event)
{
  m_width=_event->size().width()*devicePixelRatio();
  m_height=_event->size().height()*devicePixelRatio();
}

void NGLScene::resizeGL(int _w , int _h)
{
  m_width=_w*devicePixelRatio();
  m_height=_h*devicePixelRatio();
}


void NGLScene::initializeGL()
{
  // we need to initialise the NGL lib which will load all of the OpenGL functions, this must
  // be done once we have a valid GL context but before we call any GL commands. If we dont do
  // this everything will crash
  ngl::NGLInit::instance();
  glClearColor(0.7f, 0.7f, 0.7f, 1.0f);			   // Grey Background
  // enable depth testing for drawing
  glEnable(GL_DEPTH_TEST);
  // enable multisampling for smoother drawing
  glEnable(GL_MULTISAMPLE);

  //create the camera
  m_camera.set(ngl::Vec3(0,0,200),ngl::Vec3(0,0,0),ngl::Vec3(0,1,0));
  m_camera.setShape(45.0f,float(width()/height()),0.5f,100.0f);

  for(int i = 0; i<1000; ++i)
  {
    m_boidList.push_back(new boid(ngl::Vec3(0.0f, 0.0f, 0.0f), &m_camera));


  }



  startTimer(1);

  ngl::VAOPrimitives::instance()->createSphere("sphere",1.0,20);



}



void NGLScene::paintGL()
{
  // clear the screen and depth buffer
  glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
  glViewport(0,0,m_width,m_height);

  if(m_mode == true)
  {

  for(auto *p : m_boidList)
  {
    p->draw();
  }
  }

}

//----------------------------------------------------------------------------------------------------------------------
void NGLScene::mouseMoveEvent (QMouseEvent * _event)
{

}


//----------------------------------------------------------------------------------------------------------------------
void NGLScene::mousePressEvent ( QMouseEvent * _event)
{

}

//----------------------------------------------------------------------------------------------------------------------
void NGLScene::mouseReleaseEvent ( QMouseEvent * _event )
{

}

//----------------------------------------------------------------------------------------------------------------------
void NGLScene::wheelEvent(QWheelEvent *_event)
{

}
//----------------------------------------------------------------------------------------------------------------------

void NGLScene::keyPressEvent(QKeyEvent *_event)
{
  // this method is called every time the main window recives a key event.
  // we then switch on the key value and set the camera in the GLWindow
  switch (_event->key())
  {
  // escape key to quite
  case Qt::Key_Escape : QGuiApplication::exit(EXIT_SUCCESS); break;
  default : break;
  }
  // finally update the GLWindow and re-draw

    update();
}


void NGLScene::timerEvent(QTimerEvent * _event)
{
  for(auto *p : m_boidList)
  {
    p->updateBoid();
  }
  update();
}


void NGLScene::toggleOption(bool _mode
                           )
{
  m_mode = _mode;
  update();
}
