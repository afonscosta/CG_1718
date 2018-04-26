
#include "pugixml/src/pugixml.cpp"
#include <iostream>
#include <vector>
#include <fstream>
#include <stdlib.h>
#include "Group.h"

#ifdef __APPLE__
#include <GLUT/glut.h>
#else
#include <GL/glew.h>
#include <GL/glut.h>
#endif

using std::vector;


/*
 * ============================================================================
 * VARIÁVEIS GLOBAIS ==========================================================
 * ============================================================================
 */
pugi::xml_document doc;

int X_TRANSLATE = 0;
int Y_TRANSLATE = 0;
int Z_TRANSLATE = 0;

int axle = 0;
int mode = GL_LINE;
int mode_aux = 0;

float scale = 1;

int X_ANGLE = 0;
int Y_ANGLE = 0;
int Z_ANGLE = 0;

//Mouse movements
int alpha = 0, beta = 45, r = 50;
float camX = 5, camY=5, camZ = 5;
int startX, startY, tracking = 0;

Group scene;





/*
 * ============================================================================
 * PARSE DO FICHEIRO XML ======================================================
 * ============================================================================
 */
void split(const std::string& s, char delim,vector<std::string>& v) {
    auto i = 0;
    auto pos = s.find(delim);
    while (pos != std::string::npos) {
        v.push_back(s.substr(i, pos-i));
        i = ++pos;
        pos = s.find(delim, pos);

        if (pos == std::string::npos)
            v.push_back(s.substr(i, s.length()));
    }
}

Translate parseTranslate(pugi::xml_node_iterator translate) {

    Point p;
    vector<Point> pts;
    float x = 0, y = 0, z = 0;
    float time = 0;

    for (pugi::xml_attribute_iterator ait = translate->attributes_begin(); ait != translate->attributes_end(); ++ait) {
        if (strcmp(ait->name(), "time") == 0)
            time = strtof(ait->value(), nullptr);
    }

    for (pugi::xml_node_iterator nit = translate->begin() ; nit != translate->end() ; ++nit)
    {
        for (pugi::xml_attribute_iterator ait2 = nit->attributes_begin(); ait2 != nit->attributes_end(); ++ait2) {
            if (strcmp(ait2->name(), "X") == 0)
                x = strtof(ait2->value(), nullptr);
            else if (strcmp(ait2->name(), "Y") == 0)
                y = strtof(ait2->value(), nullptr);
            else if (strcmp(ait2->name(), "Z") == 0)
                z = strtof(ait2->value(), nullptr);

        }
        p.setPoint(x,y,z);
        pts.push_back(p);
    }

    Translate tr;
    tr.setTranslate(time, pts);
    return tr;
}

Point parseRotate(pugi::xml_node_iterator rotate, float *timeDest) {

    Point p;
    float axisX = 0, axisY = 0, axisZ = 0;

    for (pugi::xml_attribute_iterator ait = rotate->attributes_begin(); ait != rotate->attributes_end(); ++ait)
    {
        if (strcmp(ait->name(), "time") == 0) {
            *timeDest = strtof(ait->value(), nullptr);
        }
        else if (strcmp(ait->name(), "axisX") == 0) {
            axisX = strtof(ait->value(), nullptr);
        }
        else if (strcmp(ait->name(), "axisY") == 0) {
            axisY = strtof(ait->value(), nullptr);
        }
        else if (strcmp(ait->name(), "axisZ") == 0) {
            axisZ = strtof(ait->value(), nullptr);
        }
    }

    p.setPoint(axisX, axisY, axisZ);
    return p;
}

Point parseScale(pugi::xml_node_iterator scale) {

    Point p;
    float x = 0, y = 0, z = 0;

    for (pugi::xml_attribute_iterator ait = scale->attributes_begin(); ait != scale->attributes_end(); ++ait)
    {
        if (strcmp(ait->name(), "X") == 0) {
            x = strtof(ait->value(), nullptr);
        }
        else if (strcmp(ait->name(), "Y") == 0) {
            y = strtof(ait->value(), nullptr);
        }
        else if (strcmp(ait->name(), "Z") == 0) {
            z = strtof(ait->value(), nullptr);
        }
    }

    p.setPoint(x,y,z);
    return p;
}

void loadModel(const pugi::char_t *string, Model* model) {

    GLuint buffers[1];
    std::vector<float> points;

    int vertexCount;

    std::string buffer;
    float buffer_points[9];
    int i = 0;
    std::string delimiter = " ";

    std::fstream fs;

    fs.open(string, std::fstream::in);

    if (fs.is_open()) {

        while (getline(fs, buffer)) {

            vector<std::string> aux;
            split(buffer, ' ', aux);
            buffer_points[i * 3 + 0] = strtof(aux[0].c_str(),0);
            buffer_points[i * 3 + 1] = strtof(aux[1].c_str(),0);
            buffer_points[i * 3 + 2] = strtof(aux[2].c_str(),0);

            i++;

            if (i == 3) {

                points.push_back(buffer_points[0]);
                points.push_back(buffer_points[1]);
                points.push_back(buffer_points[2]);

                vertexCount++;

                points.push_back(buffer_points[3]);
                points.push_back(buffer_points[4]);
                points.push_back(buffer_points[5]);

                vertexCount++;

                points.push_back(buffer_points[6]);
                points.push_back(buffer_points[7]);
                points.push_back(buffer_points[8]);

                vertexCount++;

                i = 0;

            }

        }

        fs.close();
    }

    //acho que não precisamos do set primitive, apenas temos é de passar o vertexB para a nossa estrutura de dados
    (*model).setPrimitive(points, vertexCount);

}

Model parseModel(pugi::xml_node_iterator model) {

    Model modelDest;

    for (pugi::xml_attribute_iterator ait = model->attributes_begin(); ait != model->attributes_end(); ++ait)
    {
        loadModel(ait->value(), &modelDest);
    }
    return modelDest;
}

vector<Model> parseModels(pugi::xml_node_iterator models) {

    vector<Model> modelsDest;

    for (pugi::xml_node_iterator it = models->begin(); it != models->end(); ++it)
    {
        modelsDest.push_back(parseModel(it));
    }

    return modelsDest;
}

Group* parseGroup(pugi::xml_node_iterator groupSrc) {

    Group * groupDest = new Group();

    for (pugi::xml_node_iterator it = groupSrc->begin(); it != groupSrc->end(); ++it) {
        if (strcmp(it->name(), "translate") == 0) {
            (*groupDest).setTranslate(parseTranslate(it));
            (*groupDest).addOrder('t');
        }
        else if (strcmp(it->name(), "rotate") == 0) {
            float angle = 0;
            Point p = parseRotate(it, &angle);
            (*groupDest).setRotate(angle, p);
            (*groupDest).addOrder('r');
        }
        else if (strcmp(it->name(), "scale") == 0) {
            (*groupDest).setScale(parseScale(it));
            (*groupDest).addOrder('s');
        }
        else if (strcmp(it->name(), "models") == 0) {
            (*groupDest).setModels(parseModels(it));
        }
        else if (strcmp(it->name(), "group") == 0) {
            (*groupDest).addGroup(parseGroup(it));
        }
    }

    return groupDest;
}


void parseXML() {

    Group * groupDest = new Group();

    pugi::xml_node groups = doc.child("scene");

    for (pugi::xml_node_iterator it = groups.begin(); it != groups.end(); ++it) {
        if (strcmp(it->name(), "group") == 0) {
            (*groupDest).addGroup(parseGroup(it));
        }
    }

    scene = *groupDest;
}




/*
 * ============================================================================
 * CÓDIGO =====================================================================
 * ============================================================================
 */
void changeSize(int w, int h) {

    // Prevent a divide by zero, when window is too short
    // (you cant make a window with zero width).
    if(h == 0)
        h = 1;

    // compute window's aspect ratio
    float ratio = w * 1.0 / h;

    // Set the projection matrix as current
    glMatrixMode(GL_PROJECTION);
    // Load Identity Matrix
    glLoadIdentity();

    // Set the viewport to be the entire window
    glViewport(0, 0, w, h);

    // Set perspective
    gluPerspective(45.0f ,ratio, 1.0f ,1000.0f);

    // return to the model view matrix mode
    glMatrixMode(GL_MODELVIEW);
}

void changeMode() {
    if (mode_aux == 0)
        mode = GL_LINE;
    else if (mode_aux == 1)
        mode = GL_FILL;
    else if (mode_aux == 2)
        mode = GL_POINT;

    glPolygonMode(GL_FRONT_AND_BACK, mode);
}


void renderScene() {

    // clear buffers
    glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);

    // set the camera
    glLoadIdentity();
    gluLookAt(camX, camY, camZ,
              0.0,0.0,0.0,
              0.0f,1.0f,0.0f);

    //Muda o modo de desenho das figuras
    changeMode();

    //Eixos
    //glBegin(GL_LINES);
    //glColor3f(1,0,0);
    //glVertex3f(0.0f, 0.0f, 0.0f);
    //glVertex3f(10.0f, 0.0f, 0.0f);

    //glColor3f(0,1,0);
    //glVertex3f(0.0f, 0.0f, 0.0f);
    //glVertex3f(0.0f, 10.0f, 0.0f);

    //glColor3f(0,0,1);
    //glVertex3f(0.0f, 0.0f, 0.0f);
    //glVertex3f(0.0f, 0.0f, 10.0f);
    //glEnd();

    //Coloca a cor como branca para as primitivas
    //glColor3f(1,1,1);

    // movimento no plano XZ
    glTranslatef(X_TRANSLATE ,Y_TRANSLATE ,Z_TRANSLATE);

    // rotações segundo os diversos eixos
    glRotatef(X_ANGLE, 1, 0, 0);
    glRotatef(Y_ANGLE, 0, 1, 0);
    glRotatef(Z_ANGLE, 0, 0, 1);

    //Zoom in & Zoom out
    glScalef(scale, scale, scale);

    //Desenha a cena
    scene.drawGroup();

    // End of frame
    glutSwapBuffers();
}

// write function to process keyboard events
void keyboard(unsigned char key, int x, int y){

    if (key == 'a')
        X_TRANSLATE -= 1;

    if (key == 'd')
        X_TRANSLATE += 1;

    if (key == 'w')
        Z_TRANSLATE -= 1;

    if (key == 's')
        Z_TRANSLATE += 1;

    if (key == ' ') {
        axle++;
        axle = axle % 3;
    }

    if (key == 'm') {
        mode_aux++;
        mode_aux = mode_aux % 3;
    }

    if (key == '+')
        scale += 0.1;


    if (key == '-') {
        scale -= 0.1;
        if (scale <= 0.1)
            scale = 0.1;
    }


    glutPostRedisplay();
}

void rotate (int key, int x, int y) {

    if (key == GLUT_KEY_LEFT && axle == 0)
        X_ANGLE += 10;

    if (key == GLUT_KEY_RIGHT && axle == 0)
        X_ANGLE -= 10;



    if (key == GLUT_KEY_LEFT && axle == 1)
        Y_ANGLE += 10;

    if (key == GLUT_KEY_RIGHT && axle == 1)
        Y_ANGLE -= 10;



    if (key == GLUT_KEY_LEFT && axle == 2)
        Z_ANGLE += 10;

    if (key == GLUT_KEY_RIGHT && axle == 2)
        Z_ANGLE -= 10;

    glutPostRedisplay();
}

void processMouseButtons(int button, int state, int xx, int yy) {

    if (state == GLUT_DOWN)  {
        startX = xx;
        startY = yy;
        if (button == GLUT_LEFT_BUTTON)
            tracking = 1;
        else if (button == GLUT_RIGHT_BUTTON)
            tracking = 2;
        else
            tracking = 0;
    }
    else if (state == GLUT_UP) {
        if (tracking == 1) {
            alpha += (xx - startX);
            beta += (yy - startY);
        }
        else if (tracking == 2) {

            r -= yy - startY;
            if (r < 3)
                r = 3.0;
        }
        tracking = 0;
    }

    glutPostRedisplay();
}


void processMouseMotion(int xx, int yy) {

    int deltaX, deltaY;
    int alphaAux, betaAux;
    int rAux;

    if (!tracking)
        return;

    deltaX = xx - startX;
    deltaY = yy - startY;

    if (tracking == 1) {


        alphaAux = alpha + deltaX;
        betaAux = beta + deltaY;

        if (betaAux > 85.0)
            betaAux = 85.0;
        else if (betaAux < -85.0)
            betaAux = -85.0;

        rAux = r;
    }
    else if (tracking == 2) {

        alphaAux = alpha;
        betaAux = beta;
        rAux = r - deltaY;
        if (rAux < 3)
            rAux = 3;
    }
    camX = rAux * sin(alphaAux * 3.14 / 180.0) * cos(betaAux * 3.14 / 180.0);
    camZ = rAux * cos(alphaAux * 3.14 / 180.0) * cos(betaAux * 3.14 / 180.0);
    camY = rAux * 							     sin(betaAux * 3.14 / 180.0);

    glutPostRedisplay();
}

int main(int argc, char **argv) {

    if (!doc.load_file(argv[1])) return -1;

// init GLUT and the window
    glutInit(&argc, argv);
    glutInitDisplayMode(GLUT_DEPTH|GLUT_DOUBLE|GLUT_RGBA);
    glutInitWindowPosition(100,100);
    glutInitWindowSize(1440,800);
    glutCreateWindow("CG@DI-UM");

// Required callback registry
    glutDisplayFunc(renderScene);
    glutIdleFunc(renderScene);
    glutReshapeFunc(changeSize);

// Callback registration for keyboard processing
    glutKeyboardFunc(keyboard);
    glutSpecialFunc(rotate);
    glutMouseFunc(processMouseButtons);
    glutMotionFunc(processMouseMotion);

//  OpenGL settings
    glEnable(GL_DEPTH_TEST);
    glEnable(GL_CULL_FACE);
    glEnableClientState(GL_VERTEX_ARRAY);

#ifndef __APPLE__
    glewInit();
#endif

//  Parse do ficheiro XML
    parseXML();

// enter GLUT's main cycle
    glutMainLoop();

    return 1;
}
