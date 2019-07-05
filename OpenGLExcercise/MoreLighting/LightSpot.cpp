#include "LightSpot.h"
LightSpot::LightSpot(glm::vec3 _position,glm::vec3 _angles,glm::vec3 _color):
    position(_position),
    angles(_angles),
    color(_color)
{
    constant = 1.0f;
    linear = 0.1f;
    quadratic = 0.001f;
    UpdateDirection();
}


LightSpot::~LightSpot()
{
}

void LightSpot::UpdateDirection()
{
    direction = glm::vec3(0,0,1.0f);//point to z (forward)
    direction = glm::rotateZ(direction,angles.z);
    direction = glm::rotateX(direction,angles.x);
    direction = glm::rotateY(direction,angles.y);
    direction = -1.0f * direction;
}