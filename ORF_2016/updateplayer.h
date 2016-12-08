#ifndef UPDATEPLAYER_H
#define UPDATEPLAYER_H

#include "vec3.h"
#include "mesh.h"
#include "gameobject.h"


class updateplayer : public Mesh
{
private:
    float m_radius;
    float m_degrees; //temp
public:

    Vec3 m_position;
    Vec3 m_velocity;
    Vec3 m_rotation;



    updateplayer();
    ~updateplayer();

    Vec3 update(float t=0.017f);
};

#endif // UPDATEPLAYER_H
