#ifdef __APPLE__
#include <GLUT/glut.h>
#else
#include <GL/glut.h>
#endif

#include "pugixml/src/pugixml.cpp"
#include <iostream>
#include <vector>
#include <fstream>      // std::fstream

using std::vector;


int X_TRANSLATE = 0;
int Y_TRANSLATE = 0;
int Z_TRANSLATE = 0;

int axle = 0;
int mode = GL_FILL;
int mode_aux = 0;
int automatico = 0;

float color1 = 0;
float color2 = 0;
float color3 = 0;

float scale = 1;

int X_ANGLE = 0;
int Y_ANGLE = 0;
int Z_ANGLE = 0;

/*
int main(int argc, char** argv)
{
    std::string buffer;
    double buffer_points[3];
    int i = 0;
    std::string delimiter = " ";

    std::fstream fs;
    fs.open ("box.3d", std::fstream::in);

    if (fs.is_open())
    {

        while ( getline (fs,buffer, ' ' ) ){
            buffer_points[i] = atof(buffer.c_str());
            i++;
        }
        i = 0;


        glBegin(GL_TRIANGLES);
        glVertex3f(buffer_points[0] , buffer_points[1] , buffer_points[2]);
        glEnd();

        fs.close();
    }



    pugi::xml_document doc;

    pugi::xml_parse_result result = doc.load_file("test.xml");

    std::cout << "Load result: " << result.description() << ", mesh name: " << doc.child("mesh").attribute("name").value() << std::endl;





    // controi um ficheiro xml
    pugi::xml_document doc;

    // tag::code[]
    // add node with some name
    pugi::xml_node node = doc.append_child("node");

    // add description node with text child
    pugi::xml_node descr = node.append_child("description");
    descr.append_child(pugi::node_pcdata).set_value("Simple node");

    // add param node before the description
    pugi::xml_node param = node.insert_child_before("param", descr);

    // add attributes to param node
    param.append_attribute("name") = "version";
    param.append_attribute("value") = 1.1;
    param.insert_attribute_after("type", param.attribute("name")) = "float";
    // end::code[]

    doc.print(fs);

    // save document to file
    //std::cout << "Saving result: " << doc.save_file("save_file_output.xml") << std::endl;
}*/

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

void renderScene(void) {

    // clear buffers
    glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);

    // set the camera
    glLoadIdentity();
    gluLookAt(5.0,5.0,5.0,
              0.0,0.0,0.0,
              0.0f,1.0f,0.0f);

    glPolygonMode(GL_FRONT_AND_BACK, GL_FILL);

    // rotações segundo os diversos eixos
    glRotatef(X_ANGLE, 1, 0, 0);
    glRotatef(Y_ANGLE, 0, 1, 0);
    glRotatef(Z_ANGLE, 0, 0, 1);

    //codigo de desenho da figura (ainda muito desorganizado e está constantemente a ler do ficheiro)
    std::string buffer;
    double buffer_points[9];
    int i = 0;
    std::string delimiter = " ";

    std::fstream fs;
    fs.open ("sphere.3d", std::fstream::in);

    if (fs.is_open())
    {

        while ( getline (fs,buffer) ){

            vector<std::string> aux;
            split(buffer, ' ', aux);
            buffer_points[i * 3 + 0] = atof(aux[0].c_str());
            buffer_points[i * 3 + 1] = atof(aux[1].c_str());
            buffer_points[i * 3 + 2] = atof(aux[2].c_str());

            i++;

            if (i == 3){

                printf("INICIO TRIANGULO\n");

                printf("buffer[0] -> %fbuffer[1] -> %fbuffer[2] -> %f\n",buffer_points[0],buffer_points[1],buffer_points[2]);
                printf("buffer[3] -> %fbuffer[4] -> %fbuffer[5] -> %f\n",buffer_points[3],buffer_points[4],buffer_points[5]);
                printf("buffer[6] -> %fbuffer[7] -> %fbuffer[8] -> %f\n",buffer_points[6],buffer_points[7],buffer_points[8]);

                glBegin(GL_TRIANGLES);
                glColor3f(0,0,1);
                glVertex3f(buffer_points[0] , buffer_points[1] , buffer_points[2]);
                glVertex3f(buffer_points[3] , buffer_points[4] , buffer_points[5]);
                glVertex3f(buffer_points[6] , buffer_points[7] , buffer_points[8]);
                glEnd();
                printf("FIM TRIANGULO\n");

                i = 0;

            }

        }

        fs.close();
    }

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

    if (key == 'n') {
        automatico++;
        automatico = automatico % 2;
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

// init GLUT and the window
    glutInit(&argc, argv);
    glutInitDisplayMode(GLUT_DEPTH|GLUT_DOUBLE|GLUT_RGBA);
    glutInitWindowPosition(100,100);
    glutInitWindowSize(800,800);
    glutCreateWindow("CG@DI-UM");

// Required callback registry
    glutDisplayFunc(renderScene);
    glutReshapeFunc(changeSize);
    glutIdleFunc(renderScene);

// Callback registration for keyboard processing
    glutKeyboardFunc(keyboard);
    glutSpecialFunc(rotate);

//  OpenGL settings
    glEnable(GL_DEPTH_TEST);
    glEnable(GL_CULL_FACE);
    //apenas para testar
    glDisable(GL_CULL_FACE);


// enter GLUT's main cycle
    glutMainLoop();

    return 1;
}
