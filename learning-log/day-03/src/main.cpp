#include<iostream>
#include<cmath>
#include<glad/glad.h>
#include<GLFW/glfw3.h>

int main(){
    //Initializing the GLFW
    glfwInit();

    //Give GLFW the current OpenGL version(4.6)
    glfwWindowHint(GLFW_CONTEXT_VERSION_MAJOR, 3);
    glfwWindowHint(GLFW_CONTEXT_VERSION_MINOR, 3);

    //We are using core in order to avoid outdated functions
    glfwWindowHint(GLFW_OPENGL_PROFILE, GLFW_OPENGL_CORE_PROFILE);

    //Verticies coordintates
    GLfloat verts[] = {
        -0.5f, -0.5f * float(sqrt(3)) / 3, 0.0f,
        0.5f, -0.5f * float(sqrt(3)) / 3, 0.0f,
        0.0f, 0.5f * float(sqrt(3)) * 2 / 3, 0.0f,
        -0.5f / 2, 0.5f * float(sqrt(3)) / 6, 0.0f,
        0.5f / 2, 0.5f * float(sqrt(3)) / 6, 0.0f,
        0.0f, -0.5f * float(sqrt(3)) / 3, 0.0f
    };

    GLuint indices[]{
        0, 3, 5, // Lower Left Triangle
        3, 2, 4, // Lowe Right Triangle 
        5, 4, 1  // Top Triagnle
    };

    //Create a window 800x800
    GLFWwindow* window = glfwCreateWindow(800, 800, "OpenGL Test", NULL, NULL);

    //If the instance of the window is Null then terminate GLFW
    if(window == NULL){
        std::cout << "Failed to generate GLFW window" << std::endl;
        glfwTerminate();
        return -1;
    }

    //Tell glfw that we are currently using the window
    glfwMakeContextCurrent(window);

    //Load GLAD so it configures OpenGL
    gladLoadGL();

    //Specify viewport
    glViewport(0, 0, 800, 800);  

    //Create reference containers for the vertex array object and the vertex buffer object
    GLuint VAO, VBO, EBO;
    
    //Generate the vertex array object and the vertex buffer object
    glGenVertexArrays(1, &VAO);
    glGenBuffers(1, &EBO);

    //Make the VAO the current vertex array object by binding it
    glBindVertexArray(VAO);

    glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, EBO);
    glBufferData(GL_ELEMENT_ARRAY_BUFFER, sizeof(indices), indices, GL_STATIC_DRAW);

    //Configure the Vertex attribute so that OpenGL knows how to reaad the VBO
    glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, 
                          3 * sizeof(float), (void*)0);
    //Enable the Vertex attribute so that OpenGL knows to use it
    glEnableVertexAttribArray(0);

    //Bind both the VBO and VAO to 0 so that we don't accidentally modify the VAO and VBO we created
    glBindBuffer(GL_ARRAY_BUFFER, 0);
    glBindVertexArray(0);
    glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, 0);


    //main while loop
    while(!glfwWindowShouldClose(window)){
        //Color of background
        glClearColor(0.07f, 0.13f, 0.17f, 1.0f);
        //clean the back buffer and assign the new color to it
        glClear(GL_COLOR_BUFFER_BIT);
        //Tell opengl which shader program we want to use
        glUseProgram(shaderProgram);
        // Bind the VAO so OpenGL knows to use it
        glBindVertexArray(VAO);
        //Draw the triangle using the GL_TRIANGLES primitive
        glDrawElements(GL_TRIANGLES, 9, GL_UNSIGNED_INT, 0);
        //Swap the back buffer with the front buffer
        glfwSwapBuffers(window);

        //Take care of all GLFW events
        glfwPollEvents();
    }

    //Delete all the objects we've created
    glDeleteVertexArrays(1, &VAO);
    glDeleteBuffers(1, &EBO);
    glDeleteProgram(shaderProgram);

    //Delete window
    glfwDestroyWindow(window);
    //Terminate GLFW
    glfwTerminate();
    return 0;
}