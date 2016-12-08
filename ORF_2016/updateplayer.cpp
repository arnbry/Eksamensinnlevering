#include "updateplayer.h"

updateplayer::updateplayer()

{

}

Vec3 updateplayer::update(float t)
{
    if(m_position.x > 70 || m_position.x < -70) //hvis over 40 eller minus 40 på x plan
    {
        m_velocity.y = m_velocity.y * -5; //faller jeg
    }
    if (m_position.z > 70 || m_position.z < -70)
    {
        m_velocity.y = m_velocity.y * -5;
    }
    return m_position;

}

updateplayer::~updateplayer()
{

}
