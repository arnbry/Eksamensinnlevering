/*#include <QDebug>
#include "vertexdata.h"

VertexData::VertexData()
{

}


VertexData::~VertexData()
{

}

void VertexData::set_xyz(QVector3D* xyz)
{
    position.setX(xyz->x());
    position.setY(xyz->y());
    position.setZ(xyz->z());
}

void VertexData::set_xyz(GLfloat x, GLfloat y, GLfloat z)
{
    position.setX(x); position.setY(y); position.setZ(z);
}

void VertexData::set_rgb(QVector3D* rgb)
{
    normal.setX(rgb->x());
    normal.setY(rgb->y());
    normal.setZ(rgb->z());
}

void VertexData::set_rgb(GLfloat r, GLfloat g, GLfloat b)
{
    normal.setX(r); normal.setY(g); normal.setZ(b);
}

void VertexData::set_normal(QVector3D *normals)
{
    normal.setX(normals->x());
    normal.setY(normals->y());
    normal.setZ(normals->z());
}

void VertexData::set_normal(GLfloat x, GLfloat y, GLfloat z)
{
    normal.setX(x); normal.setY(y); normal.setZ(z);
}

void VertexData::set_st(QVector2D *st)
{
    texCoord.setX(st->x());
    texCoord.setY(st->y());
}

void VertexData::set_st(GLfloat s, GLfloat t)
{
    texCoord.setX(s); texCoord.setY(t);
}

std::ostream& operator<< (std::ostream& os, const VertexData& v)
{
   os << "(" << v.position.x() << ", " << v.position.y() << ", " << v.position.z() << ") ";
   os << "(" << v.normal.x() << ", " << v.normal.y() << ", " << v.normal.z() << ") ";
   os << "(" << v.texCoord.x() << ", " << v.texCoord.y() << ") ";
   return os;
}

std::istream& operator>> (std::istream& is, VertexData& v)
{
// Trenger fire temporære variabler som kun skal lese inn parenteser og komma
   char Temp, Temp2, Temp3, Temp4;
   float x,y,z,nX,nY,nZ,tX,tY;

   is >> Temp >> x >> Temp2 >> y >> Temp3 >> z >> Temp4;
   is >> Temp >> nX >> Temp2 >> nY >> Temp3 >> nZ >> Temp4;
   is >> Temp >> tX >> Temp2 >> tY >> Temp3;

v.set_xyz(x,y,z);
v.set_rgb(nX,nY,nZ);
v.set_st(tX,tY);

   return is;
}

//får ikke til å funke
void VertexData::data(float v[]) const
{
    for (int i=0; i<3; i++)
    {
        if (i == 0)
        {
            v[i] =  position.x();
        }
        else if (i == 1)
        {
            v[i] =  position.y();
        }
        else
        {
            v[i] =  position.z();
        }
    }
    for (int i=3; i<6; i++)
    {
        if (i == 3)
        {
            v[i] =  normal.x();
        }
        else if (i == 4)
        {
            v[i] =  normal.y();
        }
        else
        {
            v[i] =  normal.z();
        }
    }

    for (int i=6; i<8; i++)
    {
        if (i == 6)
        {
            v[i] =  texCoord.x();
        }
        else
        {
            v[i] =  texCoord.y();
        }

    }
}*/

