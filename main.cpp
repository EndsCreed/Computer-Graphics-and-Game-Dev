#include <GL/glut.h>
#include <complex>
#include <vector>

// Window dimensions
const int WIDTH = 1200;
const int HEIGHT = 900;

// Mandelbrot parameters
const int MAX_ITER = 100;
const double MIN_REAL = -2.0;
const double MAX_REAL = 0.5;
const double MIN_IMAGINARY = -1.25;
const double MAX_IMAGINARY = 1.25;

// Buffer to store pixel colours
std::vector<unsigned char> pixelBuffer(WIDTH * HEIGHT * 3);

// Function to convert the number of iterations to a color
void getColorFromIterations(int iterations, unsigned char &r, unsigned char &g, unsigned char &b) {
    if (iterations == MAX_ITER) {
        // Color for points in the Mandelbrot set (black)
        r = 0;
        g = 0;
        b = 0;
    } else {
        // Color gradient from black to white as we get closer to the Mandelbrot set with speedy data types
        float t = static_cast<float>(iterations) / MAX_ITER;
        r = static_cast<unsigned char>(t * 255);
        g = static_cast<unsigned char>(t * 255);
        b = static_cast<unsigned char>(t * 255);
    }
}

// Function to render a segment the Mandelbrot set
void renderMandelbrot() {
    // PARALLEL THREAD GO BRRR
    #pragma omp parallel for schedule(dynamic)
    for (int px = 0; px < WIDTH; ++px) {
        for (int py = 0; py < HEIGHT; ++py) {
            double real = MIN_REAL + px * (MAX_REAL - MIN_REAL) / WIDTH;
            double imaginary = MIN_IMAGINARY + py * (MAX_IMAGINARY - MIN_IMAGINARY) / HEIGHT;
            double x = 0.0;
            double y = 0.0;
            int iterations = 0;
            while (x*x + y*y <= 4.0 && iterations < MAX_ITER) {
                double xTemp = x*x - y*y + real;
                y = 2.0*x*y + imaginary;
                x = xTemp;
                ++iterations;
            }

            unsigned char r, g, b;
            getColorFromIterations(iterations, r, g, b);
            int index = (px + py * WIDTH) * 3;
            pixelBuffer[index] = r;
            pixelBuffer[index + 1] = g;
            pixelBuffer[index + 2] = b;
        }
    }

    glDrawPixels(WIDTH, HEIGHT, GL_RGB, GL_UNSIGNED_BYTE, pixelBuffer.data());
    glFlush();
}

// OpenGL initialization
void initGL() {
    glClearColor(1.0, 1.0, 1.0, 1.0); // Set background color to white
    glColor3f(0.0, 0.0, 0.0);         // Set drawing color to black
    glMatrixMode(GL_PROJECTION);      // Set up the projection matrix
    gluOrtho2D(0.0, WIDTH, 0.0, HEIGHT); // Set the orthographic projection
}

// Main function
int main(int argc, char **argv) {
    glutInit(&argc, argv);
    glutInitDisplayMode(GLUT_SINGLE | GLUT_RGB);
    glutInitWindowSize(WIDTH, HEIGHT);
    glutInitWindowPosition(100, 100);
    glutCreateWindow("Mandelbrot Set");
    initGL();
    glutDisplayFunc(renderMandelbrot);
    glutMainLoop();
    return 0;
}