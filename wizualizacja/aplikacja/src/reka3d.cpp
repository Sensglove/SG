#include "inc/reka3d.hpp"
#include <iostream>
#include <fstream>
#include <vector>
#include <string>
#include <cstdio>
#include <QDebug>

using namespace std;

class wektor3d
{
    public:
        double x;
        double y;
        double z;
};

class wektor2d
{
    public:
        double x;
        double y;
};

std::vector< unsigned int > vertexIndices, uvIndices, normalIndices;
std::vector< wektor3d > temp_vertices;
std::vector< wektor2d > temp_uvs;
std::vector< wektor3d > temp_normals;
std::vector <int> indeksObiektu;

//kciuk, wskazujacy, srodkowy, serdeczny, maly
double punktyZaczepienia_x[15] = {1.28076, 2.37676, 3.01596, 1.39538, 1.78789, 2.14204, 0.2592, 0.43076, 0.57861, -0.72623, -0.74151, -0.73979, -1.81926, -2.03869, -2.20105};
double punktyZaczepienia_y[15] = {0.02153,-0.95349, -1.82397, 0.34227, 0.35096, 0.35373, 0.28486, 0.29389, 0.29676, 0.28486, 0.29197, 0.29676, 0.28916, 0.29627, 0.30106};
double punktyZaczepienia_z[15] = {-1.22519,-0.46884, 0.70445, 1.97534, 3.50572, 4.64144, 2.30782, 4.11174, 5.31817, 2.06112, 3.56415, 4.74675, 1.61261, 2.76764, 3.58607};

double matrix[16];

void wczytaj()
{
    ifstream plik("cala_reka.obj");
    string znak;
    string line;
    while (!plik.eof() && !plik.fail())
    {
        plik >> znak;
        if (znak == "o")
        {
            getline(plik,line);
            indeksObiektu.push_back(vertexIndices.size()/3);
        }
        else if (znak == "v")
        {
            wektor3d vertex;
            plik >> vertex.x >> vertex.y >> vertex.z;
            temp_vertices.push_back(vertex);

        }
        else if (znak == "vt")
        {
            wektor2d uv;
            plik >> uv.x >> uv.y;
            temp_uvs.push_back(uv);

        }
        else if (znak == "vn")
        {
            wektor3d normal;
            plik >> normal.x >> normal.y >> normal.z;
            temp_normals.push_back(normal);

        }
        else if (znak == "f")
        {
            string vertex1, vertex2, vertex3;
            unsigned int vertexIndex[3], uvIndex[3], normalIndex[3];
            getline(plik,line,'/');
            vertexIndex[0] = atoi(line.c_str());
            getline(plik,line,'/');
            uvIndex[0] = atoi(line.c_str());
            getline(plik,line,' ');
            normalIndex[0] =atoi(line.c_str());

            getline(plik,line,'/');
            vertexIndex[1] = atoi(line.c_str());
            getline(plik,line,'/');
            uvIndex[1] = atoi(line.c_str());
            getline(plik,line,' ');

            normalIndex[1] = atoi(line.c_str());
            getline(plik,line,'/');
            vertexIndex[2] = atoi(line.c_str());
            getline(plik,line,'/');
            uvIndex[2] = atoi(line.c_str());
            getline(plik,line,'\n');
            normalIndex[2] = atoi(line.c_str());

            vertexIndices.push_back(vertexIndex[0]);
            vertexIndices.push_back(vertexIndex[1]);
            vertexIndices.push_back(vertexIndex[2]);
            uvIndices    .push_back(uvIndex[0]);
            uvIndices    .push_back(uvIndex[1]);
            uvIndices    .push_back(uvIndex[2]);
            normalIndices.push_back(normalIndex[0]);
            normalIndices.push_back(normalIndex[1]);
            normalIndices.push_back(normalIndex[2]);

        }
        else
        {
            getline(plik,znak);
        }
    }
}

void Viewer::Reka()
{

    int ind = 0;

    for (int i = 0, j = 0; i < vertexIndices.size(); i=i+3,j++)
    {
        if (indeksObiektu[ind] == j)
        {
            glPushMatrix();
            ind++;
        }
        glBegin(GL_TRIANGLES);
        glTexCoord2f(  temp_uvs[uvIndices[i]-1].x,1.0 - temp_uvs[uvIndices[i]-1].y);
        glNormal3f(  temp_normals[normalIndices[i]-1].x,temp_normals[normalIndices[i]-1].y ,temp_normals[normalIndices[i]-1].z );
        glVertex3f(  temp_vertices[vertexIndices[i]-1].x,temp_vertices[vertexIndices[i]-1].y ,temp_vertices[vertexIndices[i]-1].z );

        glTexCoord2f(  temp_uvs[uvIndices[i+1]-1].x,1.0 - temp_uvs[uvIndices[i+1]-1].y);
        glNormal3f(  temp_normals[normalIndices[i+1]-1].x,temp_normals[normalIndices[i+1]-1].y ,temp_normals[normalIndices[i+1]-1].z );
        glVertex3f(  temp_vertices[vertexIndices[i+1]-1].x,temp_vertices[vertexIndices[i+1]-1].y ,temp_vertices[vertexIndices[i+1]-1].z );

        glTexCoord2f(  temp_uvs[uvIndices[i+2]-1].x,1.0 - temp_uvs[uvIndices[i+2]-1].y);
        glNormal3f(  temp_normals[normalIndices[i+2]-1].x,temp_normals[normalIndices[i+2]-1].y ,temp_normals[normalIndices[i+2]-1].z );
        glVertex3f(  temp_vertices[vertexIndices[i+2]-1].x,temp_vertices[vertexIndices[i+2]-1].y ,temp_vertices[vertexIndices[i+2]-1].z );
        glEnd();
        if (indeksObiektu[ind] - 1 == j)
        {
            glPopMatrix();

            //palec5 - kciuk
            if (ind == 1)
            {
                glGetDoublev(GL_MODELVIEW_MATRIX, matrix);
                glTranslatef(punktyZaczepienia_x[0],punktyZaczepienia_y[0],punktyZaczepienia_z[0]);
                glRotatef( kat5,0.0,0.0,-1.0);
                glTranslatef(-punktyZaczepienia_x[0],-punktyZaczepienia_y[0],-punktyZaczepienia_z[0]);
            }
            if (ind == 2)
            {
                glTranslatef(punktyZaczepienia_x[1],punktyZaczepienia_y[1],punktyZaczepienia_z[1]);
                glRotatef( kat5/1.5,0.0,0.0,-1.0);
                glTranslatef(-punktyZaczepienia_x[1],-punktyZaczepienia_y[1],-punktyZaczepienia_z[1]);
            }
            if (ind == 3)
            {
                glTranslatef(punktyZaczepienia_x[2],punktyZaczepienia_y[2],punktyZaczepienia_z[2]);
                glRotatef( kat5/2.0,0.0,0.0,-1.0);
                glTranslatef(-punktyZaczepienia_x[2],-punktyZaczepienia_y[2],-punktyZaczepienia_z[2]);

            }
            //palec2 - wskazujacy
            if (ind == 4)
            {
                glLoadMatrixd(matrix);
                glGetDoublev(GL_MODELVIEW_MATRIX, matrix);
                glTranslatef(punktyZaczepienia_x[3],punktyZaczepienia_y[3],punktyZaczepienia_z[3]);
                glRotatef( kat4,1.0,0.0,-0.4);
                glTranslatef(-punktyZaczepienia_x[3],-punktyZaczepienia_y[3],-punktyZaczepienia_z[3]);
            }
            if (ind == 5)
            {
                glTranslatef(punktyZaczepienia_x[4],punktyZaczepienia_y[4],punktyZaczepienia_z[4]);
                glRotatef( kat4/1.5,1.0,0.0,0);
                glTranslatef(-punktyZaczepienia_x[4],-punktyZaczepienia_y[4],-punktyZaczepienia_z[4]);
            }
            if (ind == 6)
            {
                glTranslatef(punktyZaczepienia_x[5],punktyZaczepienia_y[5],punktyZaczepienia_z[5]);
                glRotatef( kat4/2.0,1.0,0.0,0);
                glTranslatef(-punktyZaczepienia_x[5],-punktyZaczepienia_y[5],-punktyZaczepienia_z[5]);
            }
            //palec3 - srodkowy
            if (ind == 7)
            {
                glLoadMatrixd(matrix);
                glGetDoublev(GL_MODELVIEW_MATRIX, matrix);
                glTranslatef(punktyZaczepienia_x[6],punktyZaczepienia_y[6],punktyZaczepienia_z[6]);
                glRotatef( kat3,1.0,0.0,-0.1);
                glTranslatef(-punktyZaczepienia_x[6],-punktyZaczepienia_y[6],-punktyZaczepienia_z[6]);
            }
            if (ind == 8)
            {
                glTranslatef(punktyZaczepienia_x[7],punktyZaczepienia_y[7],punktyZaczepienia_z[7]);
                glRotatef( kat3/1.5,1.0,0.0,0);
                glTranslatef(-punktyZaczepienia_x[7],-punktyZaczepienia_y[7],-punktyZaczepienia_z[7]);
            }
            if (ind == 9)
            {
                glTranslatef(punktyZaczepienia_x[8],punktyZaczepienia_y[8],punktyZaczepienia_z[8]);
                glRotatef( kat3/2.0,1.0,0.0,0);
                glTranslatef(-punktyZaczepienia_x[8],-punktyZaczepienia_y[8],-punktyZaczepienia_z[8]);
            }
            //palec4 - serdeczny
            if (ind == 10)
            {
                glLoadMatrixd(matrix);
                glGetDoublev(GL_MODELVIEW_MATRIX, matrix);
                glTranslatef(punktyZaczepienia_x[9],punktyZaczepienia_y[9],punktyZaczepienia_z[9]);
                glRotatef( kat2,1.0,0.0,0);
                glTranslatef(-punktyZaczepienia_x[9],-punktyZaczepienia_y[9],-punktyZaczepienia_z[9]);
            }
            if (ind == 11)
            {
                glTranslatef(punktyZaczepienia_x[10],punktyZaczepienia_y[10],punktyZaczepienia_z[10]);
                glRotatef( kat2/1.5,1.0,0.0,0);
                glTranslatef(-punktyZaczepienia_x[10],-punktyZaczepienia_y[10],-punktyZaczepienia_z[10]);
            }
            if (ind == 12)
            {
                glTranslatef(punktyZaczepienia_x[11],punktyZaczepienia_y[11],punktyZaczepienia_z[11]);
                glRotatef( kat2/2.0,1.0,0.0,0);
                glTranslatef(-punktyZaczepienia_x[11],-punktyZaczepienia_y[11],-punktyZaczepienia_z[11]);
            }
            //palec5 - maly
            if (ind == 13)
            {
                glLoadMatrixd(matrix);
                glGetDoublev(GL_MODELVIEW_MATRIX, matrix);
                glTranslatef(punktyZaczepienia_x[12],punktyZaczepienia_y[12],punktyZaczepienia_z[12]);
                glRotatef( kat1,1.0,0.0,0.3);
                glTranslatef(-punktyZaczepienia_x[12],-punktyZaczepienia_y[12],-punktyZaczepienia_z[12]);
            }
            if (ind == 14)
            {
                glTranslatef(punktyZaczepienia_x[13],punktyZaczepienia_y[13],punktyZaczepienia_z[13]);
                glRotatef( kat1/1.5,1.0,0.0,0);
                glTranslatef(-punktyZaczepienia_x[13],-punktyZaczepienia_y[13],-punktyZaczepienia_z[13]);
            }
            if (ind == 15)
            {
                glTranslatef(punktyZaczepienia_x[14],punktyZaczepienia_y[14],punktyZaczepienia_z[14]);
                glRotatef( kat1/2.0,1.0,0.0,0);
                glTranslatef(-punktyZaczepienia_x[14],-punktyZaczepienia_y[14],-punktyZaczepienia_z[14]);
            }
        }
    }
}

Viewer::Viewer(QWidget *wRodzic) : QGLViewer(wRodzic)
{
    kat1 = 0.0;
    kat2 = 0.0;
    kat3 = 0.0;
    kat4 = 0.0;
    kat5 = 0.0;
}


void Viewer::draw()
{

    glScalef( 0.3, 0.3, 0.3 );
    Reka();

}

void Viewer::init()
{
    wczytaj();

    restoreStateFromFile();

    camera()->setViewDirection(qglviewer::Vec(0.0, 1.0, 0.0));
    camera()->setPosition(qglviewer::Vec(0.25, -4.0, 0.5));

    //help();
}

void Viewer::aktualizuj(QStringList lista)
{

    kat1 = (2.5 - lista[10].toFloat())/1.0*90;
    if (kat1 < 0.0) kat1 = 0;
    if (kat1 > 90.0) kat1 = 90.0;
    kat2 = (2.5 - lista[11].toFloat())/1.0*90;
    if (kat2 < 0.0) kat2 = 0;
    if (kat2 > 90.0) kat2 = 90.0;
    kat3 = (2.5 - lista[12].toFloat())/1.0*90;
    if (kat3 < 0.0) kat3 = 0;
    if (kat3 > 90.0) kat3 = 90.0;
    kat4 = (2.5 - lista[13].toFloat())/1.0*90;
    if (kat4 < 0.0) kat4 = 0;
    if (kat4 > 90.0) kat4 = 90.0;
    kat5 = (2.5 - lista[14].toFloat())/1.0*90;
    if (kat5 < 0.0) kat5 = 0;
    if (kat5 > 90.0) kat5 = 90.0;

    update();
}
