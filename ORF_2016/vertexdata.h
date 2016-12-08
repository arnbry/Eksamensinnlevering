#ifndef VERTEXDATA_H
#define VERTEXDATA_H



#include <QVector3D>
#include <QVector2D>


struct VertexData
{
    QVector3D position;
    QVector3D normal;
    QVector2D texCoord;
};


/*
#include <qgl.h>


class VertexData
{
    friend std::ostream& operator<< (std::ostream&, const VertexData&);
    friend std::istream& operator>> (std::istream&, VertexData&);
public:
    QVector3D position;
    QVector3D normal;
    QVector2D texCoord;

    VertexData();
    ~VertexData();

    void set_xyz(QVector3D* xyz);
    void set_xyz(GLfloat x, GLfloat y, GLfloat z);
    void set_rgb(QVector3D* rgb);
    void set_rgb(GLfloat r, GLfloat g, GLfloat b);
    void set_normal(QVector3D* normals);
    void set_normal(GLfloat x, GLfloat y, GLfloat z);
    void set_st(QVector2D* st);
    void set_st(GLfloat s, GLfloat t);
    void data(float v[]) const;
};
*/
#endif // VERTEXDATA_H
