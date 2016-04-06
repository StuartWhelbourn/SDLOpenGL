#ifndef BOID_H__
#define BOID_H__

#include <ngl/Vec3.h>
#include <ngl/Colour.h>
#include <ngl/Camera.h>
#include <array>


class boid
{
  public:
    boid(ngl::Vec3 _startLoc, const ngl::Camera *_cam); //contruct the boid
    ~boid() = default; //default constructor
    void neighbourFind(); //finds the 3 closest boids and adds them to array
    void updateBoid();
    void draw() const;
     int m_id;

  private:
    ngl::Vec3 m_loc; //location
    ngl::Vec3 m_vel; //velocity
    ngl::Vec3 m_accel; //acceleration
    ngl::Vec3 m_startLoc; //starting location
    ngl::Colour m_colour;  //colour of boid

    int m_life=0;
    int m_maxLife;
    int m_maxNeighbourDist;
    int neighbourList[3]; //array of 3 closest neighbours

    const ngl::Camera *m_camera; //tell boid about the camera

};

#endif
