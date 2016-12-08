#ifndef MESH_H
#define MESH_H

#include "gameobject.h"
#include "vertexdata.h"
#include "material.h"
#include "updateplayer.h"
/**
* @brief The Mesh class
*/
class Mesh : public GameObject
{
public:
/**
 * @brief Mesh
 * @param xPos
 * @param yPos
 * @param zPos
 */
Mesh(float xPos = 0.0, float yPos = 0.0, float zPos = 0.0);
~Mesh();
/**
 * @brief drawGeometry
 */
void drawGeometry();
/**
 * @brief initGeometry
 * @return
 */
int initGeometry();
/**
 * @brief setMeshName
 * @param nameOfMesh
 */
void setMeshName(QString nameOfMesh);
/**
 * @brief setMaterial
 * @param materialIn
 */
void setMaterial(Material *materialIn);
/**
 * @brief setRendermode
 * @param mode
 */
void setRendermode(int mode);
private:
/**
 * @brief mVertexBuffer
 */
GLuint mVertexBuffer;
/**
 * @brief mIndexBuffer
 */
GLuint mIndexBuffer;
/**
 * @brief mMaterial
 */
Material *mMaterial;
/**
 * @brief mMVPMatrix
 */
QMatrix4x4 mMVPMatrix;
/**
 * @brief mFileName
 */
QString mFileName;
/**
 * @brief mNoOfTriangles
 */
int mNoOfTriangles;
/**
 * @brief mNoIndices
 */
int mNoIndices;
};

#endif // MESH_H
