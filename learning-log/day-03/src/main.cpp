#include<iostream>
#include<cmath>
#include<glad/glad.h>
#include<GLFW/glfw3.h>

//Vertex Shader
const char* vertexShaderSource = "#version 330 core\n"
"layout (location = 0) in vec3 aPos;\n"
"void main()\n"
"{\n"
"   gl_Position = vec4(aPos.x, aPos.y, aPos.z, 1.0);\n"
"}\0";
//Fragment Shader
const char* fragmentShaderSource = "#version 330 core\n"
"out vec4 FragColor;\n"
"void main()\n"
"{"
"   FragColor = vec4(1.0f, 1.0f, 0.0f, 1.0f);\n"
"}\n\0";

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
        0.0f, 0.5f * float(sqrt(3)) * 2 / 3, 0.0f
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

    //Create vertex shader object and get it's reference
    GLuint vertexShader = glCreateShader(GL_VERTEX_SHADER);
    //Attach vertex shader source to the fragment shader object
    glShaderSource(vertexShader, 1, &vertexShaderSource, NULL);
    //Compile the Vertex shader into machine code
    glCompileShader(vertexShader);

    //Create fragment shader object and get it's reference
    GLuint fragmentShader = glCreateShader(GL_FRAGMENT_SHADER);
    //Attach fragment shader source to the fragment shader object
    glShaderSource(fragmentShader, 1, &fragmentShaderSource, NULL);
    //Compile the Fragment shader into machine code
    glCompileShader(fragmentShader);

    //Create shader projgram and get it's reference
    GLuint shaderProgram = glCreateProgram();

    //Attach the vertex and fragment shaders together to the shader program
    glAttachShader(shaderProgram, vertexShader);
    glAttachShader(shaderProgram, fragmentShader);

    //Link all the shaders together
    glLinkProgram(shaderProgram);

    //Delete the vertex and fragment shader objects
    glDeleteShader(vertexShader);
    glDeleteShader(fragmentShader);

    //Create reference containers for the vertex array object and the vertex buffer object
    GLuint VAO, VBO;
    
    //Generate the vertex array object and the vertex buffer object
    glGenVertexArrays(1, &VAO);
    glGenBuffers(1, &VBO);

    //Make the VAO the current vertex array object by binding it
    glBindVertexArray(VAO);

    //Bind the VBO specifying it's a GL_ARRAY_BUFFER
    glBindBuffer(GL_ARRAY_BUFFER, VBO);
    //Introduce the verticies into the VBO
    glBufferData(GL_ARRAY_BUFFER, sizeof(verts), verts, GL_STATIC_DRAW);

    //Configure the Vertex attribute so that OpenGL knows how to reaad the VBO
    glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, 
                          3 * sizeof(float), (void*)0);
    //Enable the Vertex attribute so that OpenGL knows to use it
    glEnableVertexAttribArray(0);

    //Bind both the VBO and VAO to 0 so that we don't accidentally modify the VAO and VBO we created
    glBindBuffer(GL_ARRAY_BUFFER, 0);
    glBindVertexArray(0);

    //BG color
    glClearColor(0.07f, 0.13f, 0.17f, 1.0f);
    //Clean back buffer assign new color
    glClear(GL_COLOR_BUFFER_BIT);
    //Swap back with front buffer
    glfwSwapBuffers(window);

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
        glDrawArrays(GL_TRIANGLES, 0, 3);
        //Swap the back buffer with the front buffer
        glfwSwapBuffers(window);

        //Take care of all GLFW events
        glfwPollEvents();
    }

    //Delete all the objects we've created
    glDeleteVertexArrays(1, &VAO);
    glDeleteBuffers(1, &VBO);
    glDeleteProgram(shaderProgram);

    //Delete window
    glfwDestroyWindow(window);
    //Terminate GLFW
    glfwTerminate();
    return 0;
}