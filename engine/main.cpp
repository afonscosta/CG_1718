#ifdef __APPLE__
#include <GLUT/glut.h>
#else
#include <GL/glut.h>
#endif

#include "pugixml/src/pugixml.cpp"
#include <iostream>
#include <vector>
#include <fstream>

using std::vector;

pugi::xml_document doc;

int X_TRANSLATE = 0;
int Y_TRANSLATE = 0;
int Z_TRANSLATE = 0;

int axle = 0;
int mode = GL_FILL;
int mode_aux = 0;

float scale = 1;

int X_ANGLE = 0;
int Y_ANGLE = 0;
int Z_ANGLE = 0;


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
        mode = GL_FILL;
    else if (mode_aux == 1)
        mode = GL_LINE;
    else if (mode_aux == 2)
        mode = GL_POINT;

    glPolygonMode(GL_FRONT_AND_BACK, mode);
}

void parseTranslate(pugi::xml_node_iterator translate) {

    float x = 0, y = 0, z = 0;
    for (pugi::xml_attribute_iterator ait = translate->attributes_begin(); ait != translate->attributes_end(); ++ait)
    {
        if (strcmp(ait->name(), "X") == 0) {
            x = atof(ait->value());
        }
        else if (strcmp(ait->name(), "Y") == 0) {
            y = atof(ait->value());
        }
        else if (strcmp(ait->name(), "Z") == 0) {
            z = atof(ait->value());
        }
    }

    glTranslatef(x,y,z);
}

void parseRotate(pugi::xml_node_iterator rotate) {

    float angle = 0, axisX = 0, axisY = 0, axisZ = 0;
    for (pugi::xml_attribute_iterator ait = rotate->attributes_begin(); ait != rotate->attributes_end(); ++ait)
    {
        if (strcmp(ait->name(), "angle") == 0) {
            angle = atof(ait->value());
        }
        else if (strcmp(ait->name(), "axisX") == 0) {
            axisX = atof(ait->value());
        }
        else if (strcmp(ait->name(), "axisY") == 0) {
            axisY = atof(ait->value());
        }
        else if (strcmp(ait->name(), "axisZ") == 0) {
            axisZ = atof(ait->value());
        }
    }

    glRotatef(angle, axisX, axisY, axisZ);
}

void parseScale(pugi::xml_node_iterator scale) {

    float X = 0, Y = 0, Z = 0;
    for (pugi::xml_attribute_iterator ait = scale->attributes_begin(); ait != scale->attributes_end(); ++ait)
    {
        if (strcmp(ait->name(), "X") == 0) {
            X = atof(ait->value());
        }
        else if (strcmp(ait->name(), "Y") == 0) {
            Y = atof(ait->value());
        }
        else if (strcmp(ait->name(), "Z") == 0) {
            Z = atof(ait->value());
        }
    }

    glScalef(X, Y, Z);
}

void drawModel(const pugi::char_t *string) {
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

                glBegin(GL_TRIANGLES);
                glColor3f(0, 0, 1);
                glVertex3f(buffer_points[0], buffer_points[1], buffer_points[2]);
                glVertex3f(buffer_points[3], buffer_points[4], buffer_points[5]);
                glVertex3f(buffer_points[6], buffer_points[7], buffer_points[8]);
                glEnd();

                i = 0;

            }

        }

        fs.close();
    }
}

void parseModel(pugi::xml_node_iterator model) {
    for (pugi::xml_attribute_iterator ait = model->attributes_begin(); ait != model->attributes_end(); ++ait)
    {
        drawModel(ait->value());
    }
}

void parseModels(pugi::xml_node_iterator models) {
    for (pugi::xml_node_iterator it = models->begin(); it != models->end(); ++it)
    {
        parseModel(it);
    }
}

void parseGroup(pugi::xml_node_iterator group) {

    for (pugi::xml_node_iterator it = group->begin(); it != group->end(); ++it) {
        if (strcmp(it->name(), "translate") == 0) {
            parseTranslate(it);
        }
        else if (strcmp(it->name(), "rotate") == 0) {
            parseRotate(it);
        }
        else if (strcmp(it->name(), "scale") == 0) {
            parseScale(it);
        }
        else if (strcmp(it->name(), "models") == 0) {
            parseModels(it);
        }
        else if (strcmp(it->name(), "group") == 0) {
            glPushMatrix();
            parseGroup(it);
            glPopMatrix();
        }
    }
}


void parseScene() {

    pugi::xml_node groups = doc.child("scene");

    for (pugi::xml_node_iterator it = groups.begin(); it != groups.end(); ++it) {
        if (strcmp(it->name(), "group") == 0) {
            glPushMatrix();
            parseGroup(it);
            glPopMatrix();
        }
    }
}




void parseXML() {

    //Antes de começar a desenhar a cena guardo o referencial
    glPushMatrix();

    parseScene();

    //Reponho o referencial original
    glPopMatrix();

}

void renderScene() {

    // clear buffers
    glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);

    // set the camera
    glLoadIdentity();
    gluLookAt(5.0, 5.0, 5.0,
              0.0, 0.0, 0.0,
              0.0f, 1.0f, 0.0f);

    //Muda o modo de desenho das figuras
    changeMode();

    // movimento no plano XZ
    glTranslatef(X_TRANSLATE ,Y_TRANSLATE ,Z_TRANSLATE);

    // rotações segundo os diversos eixos
    glRotatef(X_ANGLE, 1, 0, 0);
    glRotatef(Y_ANGLE, 0, 1, 0);
    glRotatef(Z_ANGLE, 0, 0, 1);

    //Zoom in & Zoom out
    glScalef(scale, scale, scale);

    //Carrega e desenha o conteúdo do xml
    parseXML();

    // End of frame
    glutSwapBuffers();
}

// write function to process keyboard events

void keyboard(unsigned char key, int x, int y){

    if (key == 'a')
        X_TRANSLATE--;

    if (key == 'd')
        X_TRANSLATE++;

    if (key == 'w')
        Z_TRANSLATE--;

    if (key == 's')
        Z_TRANSLATE++;

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


    if (key == '-')
        scale -= 0.1;


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
    glutReshapeFunc(changeSize);

// Callback registration for keyboard processing
    glutKeyboardFunc(keyboard);
    glutSpecialFunc(rotate);

//  OpenGL settings
    glEnable(GL_DEPTH_TEST);
    glEnable(GL_CULL_FACE);
    glEnable(GL_CULL_FACE);


// enter GLUT's main cycle
    glutMainLoop();

    return 1;
}
