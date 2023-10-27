#include <string.h>
#include <stdlib.h>
#include <stdio.h>
#include <GL/glut.h>
#include <vector>
#include <chrono>
#include <thread>
#include <random>
#include <ctime>


const int WIDTH = 1200;
const int HEIGHT = 1200;
const float ASPECT = float(WIDTH) / HEIGHT;
double max_fps = 60;
double freq = 1 / max_fps;
auto seed = time(NULL);
auto color_prob = 100;
int num_cells = 10000;



struct Cell {
    float x;
    float y;
    bool alive;
    std::vector<int> colors;
};

std::vector<Cell> cellarray;
std::vector<Cell> nextgenarray;

void drawSquare(double x1, double y1, bool state, std::vector<int> rgb = { 255,255,255 }, double sidelength = 4)
{
    double halfside = sidelength / 2;

    if (state) {
        auto r = rgb[0];
        glColor3d((double)rgb[0], (double)rgb[1], (double)rgb[2]);

        glBegin(GL_POLYGON);
        glVertex2d(x1 - halfside, y1 - halfside);
        glVertex2d(x1 - halfside, y1 + halfside);
        glVertex2d(x1 + halfside, y1 + halfside);
        glVertex2d(x1 + halfside, y1 - halfside);
        glEnd();
    }
}



void game() {



    for (int i = 0; i <= 9999; i++) {
        //get neighbors
        int alive_neighbors = 0;
        std::vector<int> neighbors{ i - 101, i - 100, i - 99, i - 1, i + 1, i + 99, i + 100, i + 101 };

        for (auto neighbor : neighbors) {
            if (neighbor >= 0 && neighbor <= 9999) {
                if (cellarray[neighbor].alive) {
                    alive_neighbors++;
                }
            }
        }


        //game rules
        if (alive_neighbors < 2 && cellarray[i].alive == true) {
            nextgenarray[i].alive = false;
        }
        else if (alive_neighbors == 3 || alive_neighbors == 2 && cellarray[i].alive == true) {
            nextgenarray[i].alive = true;
        }
        else if (alive_neighbors > 3 && cellarray[i].alive == true) {
            nextgenarray[i].alive = false;
        }
        else if (alive_neighbors == 3 && cellarray[i].alive == false) {
            nextgenarray[i].alive = true;
        } 

        //nextgenarray[i].colors = random_cols;

    }

    cellarray = nextgenarray;
    for (auto i : nextgenarray) {
        i.alive = false;
        i.colors = {};
    }
}

void draw() {
        clock_t start = 0;
        double duration;
        
        start = clock();


        glClear(GL_COLOR_BUFFER_BIT);
        //glLoadIdentity();
        glBegin(GL_POLYGON);

        for (auto const& square : cellarray) {
            drawSquare(square.x, square.y, square.alive, square.colors);
        }

        //auto adj_width = glutGet(GLUT_WINDOW_WIDTH);
        //auto adj_height = glutGet(GLUT_WINDOW_HEIGHT);

        //drawSquare(adj_width/2, adj_height / 2, true, {255,255,255}, 50);


        glEnd();
        glFlush();


        clock_t end = clock();
        duration = (end - start) / (double)CLOCKS_PER_SEC;

        if (duration < freq) {
            long timeneeded = (freq - duration) * 1000;
            std::chrono::milliseconds timespan(timeneeded); 
            std::this_thread::sleep_for(timespan);
        }
        start = 0;

        //control the speed
        //std::chrono::milliseconds timespan(85); // or whatever
        //std::this_thread::sleep_for(timespan);



        glutPostRedisplay();


}

void reshapeScene(GLint width, GLint height)
{
    glMatrixMode(GL_PROJECTION);
    glLoadIdentity();

    int w = height * ASPECT;           // w is width adjusted for aspect ratio
    int left = (width - w) / 2;
    glViewport(left, 0, w, height);       // fix up the viewport to maintain aspect ratio
    gluOrtho2D(0, WIDTH, HEIGHT, 0);   // only the window is changing, not the camera
    glMatrixMode(GL_MODELVIEW);

    glutPostRedisplay();
}



void Initialize() {

    glClearColor(0.0, 0.0, 0.0, 1.0);
    glColor3f(0.0, 0.0, 0.0);

    // Set width of point to one unit
    glPointSize(1.0);
    glMatrixMode(GL_PROJECTION);
    glLoadIdentity();

    // Set window size in X- and Y- direction
    gluOrtho2D(-250, 250, -250, 250);
}

void InitCells() {
    for (float posy = 247.5; posy >= -247.5; posy -= 5) {
        for (float posx = -247.5; posx <= 247.5; posx += 5) {
            //randomize colors
            std::vector<int> random_cols{ 0,0,0 };
            for (int c = 0; c <= 2; c++) {
                if (rand() % 100 < color_prob) {
                    random_cols[c] = 255;
                }
                else {
                    random_cols[c] = 0;
                }
            }
            if (random_cols[0] == 0 && random_cols[1] == 0 && random_cols[2] == 0) {
                random_cols[rand() % 3] = 255;
            }

            Cell tempcell = { posx, posy, false, random_cols };

            cellarray.push_back(tempcell);
            nextgenarray.push_back(tempcell);
        }
    }



    //cellarray[400].alive = true;
    //cellarray[850].alive = true;

    //cellarray[400].colors = {43,34,255};
    //cellarray[850].colors = {255,0,0};
    //cellarray[211].alive = true;
    //cellarray[192].alive = true;
    //cellarray[213].alive = true;
    //cellarray[234].alive = true;
    srand(seed);
    for (int i = 0; i <= 9999; i++) {
        if (rand() % 100 < 35) {
            cellarray[i].alive = true;
        }
    }

}

int main(int argc, char** argv) {

    //create the cell array
    InitCells();
    glutInit(&argc, argv);
    glutInitDisplayMode(GLUT_SINGLE | GLUT_RGB);
    glutInitWindowSize(WIDTH, HEIGHT);
    //Declares window position which is (0, 0)
    //means lower left corner will indicate position (0, 0)
    //glutInitWindowPosition(0, 0);

    glutCreateWindow("Game of Life");

    Initialize();

    glutDisplayFunc(draw);
    //glutReshapeFunc(reshapeScene);
    glutIdleFunc(game);
    glutMainLoop();
}