#include <iostream>
#include <math.h>
#include <string.h>
#include <GLFW/glfw3.h>

int main(int argc, char *argv[])
{
    GLFWwindow* window;

    int vertices = 21;
    if (argv[1]) {
        vertices = atoi(argv[1]);
    }
    int dir = 0;
    if (argv[2] && strcmp(argv[2], "true") == 0) {
        dir = 1;
    }
    float centerX = -0.4f;
    float centerY = -0.4f;
    if (dir == 0) {
        centerX = 0.0f;
        centerY = 0.0f;
    }
    float radius = 0.59f;
    float angleIncrement = (M_PI*2)/(double) vertices;
    float pointsX[vertices];
    float pointsY[vertices];

    // Print args
    std::cout << "argc: " + std::to_string(argc) << std::endl;
    for (int i = 0; i < argc; i++) {
        std::cout << argv[i] << std::endl;
    }


    /* Initialize the library */
    if (!glfwInit())
        return -1;

    /* Create a windowed mode window and its OpenGL context */
    window = glfwCreateWindow(640, 480, "Rosette", NULL, NULL);
    if (!window)
    {
        glfwTerminate();
        return -1;
    }

    /* Make the window's context current */
    glfwMakeContextCurrent(window);

    /* Loop until the user closes the window */
    while (!glfwWindowShouldClose(window))
    {
        if(dir > 0) {
            if (centerY >= 0.4f && centerX < 0.4) {
                dir = 2;
            }
            if (centerX >= 0.4f && centerY > -0.4) {
                dir = 3;
            }
            if (centerY <= -0.4f && centerX > -0.4) {
                dir = 4;
            }
            if (centerX <= -0.4f && centerY < 0.4) {
                dir = 1;
            }

            switch (dir) {
                case 1:
                    centerY += 0.01;
                    break;
                case 2:
                    centerX += 0.01;
                    break;
                case 3:
                    centerY -= 0.01;
                    break;
                case 4:
                    centerX -= 0.01;
                    break;
            }
        }

        // Gen Points
        for (int i = 0; i < vertices; i++) { // Generate points. Added 0.5pi to rotate it -90
            pointsX[i] = (centerX + (radius * cos((angleIncrement * i)+(M_PI/2))));
            pointsY[i] = (centerY + (radius * sin((angleIncrement * i)+(M_PI/2))));
        }

        /* Render here */
        glClear(GL_COLOR_BUFFER_BIT);

        // Rosette?
        for (int i = 0; i < vertices; i++) {
            for (int j = 1; j < vertices; j++) {
                glBegin(GL_LINES);
                glVertex2f(pointsX[i], pointsY[i]);
                glVertex2f(pointsX[j], pointsY[j]);
                glEnd();
            }
        }


        /* Swap front and back buffers */
        glfwSwapBuffers(window);

        /* Poll for and process events */
        glfwPollEvents();
    }

    glfwTerminate();
    return 0;
}
