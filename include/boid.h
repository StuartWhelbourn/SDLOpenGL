#ifndef BOID_H__
#define boid_H__

#include <ngl/Vec3.h>
#include <ngl/Colour.h>
#include <ngl/Camera.h>

class boid
{
  public:
    boid(ngl::Vec3 _startPos, const ngl::Camera *_cam); //contruct the boid
    ~boid() = default; //default constructor
    void update();
    void draw() const;

  private:
    ngl::Vec3 m_pos; //position
    ngl::Vec3 m_dir; //direction
    ngl::Vec3 m_startPos;
    ngl::Colour m_colour;
    int m_life=0;
    int m_maxLife;

    const ngl::Camera *m_camera; //tell boid about the camera

};

#endif
