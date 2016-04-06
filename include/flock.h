#ifndef FLOCK_H
#define FLOCK_H

#include <ngl/Vec3.h>
#include <array>
#include <vector>
#include <ngl/Camera.h>
#include "boid.h"



class flock //: public boid
{

public:
  flock();
  ~flock() = default; //default constructor

  void createFlock();

  void addBoid();      //adds boid

  void removeBoid();   //removes boid

  void seperation();

  void alignment();

  void cohesion();

  std::vector <boid *> m_boidList;


private:





};

#endif // FLOCK_H
