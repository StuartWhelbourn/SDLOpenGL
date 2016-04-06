#include "boid.h"
#include <ngl/Random.h>
#include <ngl/NGLStream.h>
#include <ngl/ShaderLib.h>
#include <ngl/Transformation.h>
#include <ngl/VAOPrimitives.h>

boid::boid(ngl::Vec3 _startLoc, const ngl::Camera *_cam)
{
  m_loc = _startLoc;
  m_startLoc = _startLoc;
  ngl::Random *rng = ngl::Random::instance();
  m_maxLife = rng->randomPositiveNumber(200)+100; //life is at least 100
  m_colour = rng->getRandomColour();
  m_vel = rng->getRandomNormalizedVec3();
  m_camera = _cam;
}

void boid::updateBoid()
{
  if(++m_life >= m_maxLife)
  {
    m_loc=m_startLoc;
    m_life=0;
  }
  else
  {
    m_loc += m_vel;
  }

}

void boid::draw() const
{

  ngl::Transformation tx;
  tx.setPosition(m_loc);
  ngl::ShaderLib *shader = ngl::ShaderLib::instance();
  shader->use("nglColourShader");
  shader->setUniform("Colour",m_colour);
  shader->setUniform("MVP",tx.getMatrix()*m_camera->getVPMatrix());
  ngl::VAOPrimitives::instance()->draw("sphere");
}





