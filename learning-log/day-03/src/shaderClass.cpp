#include"shaderClass.h"

std::string get_file_contents(const char* filename){
    std::ifstream in(filename, std::ios::binary);
    if(in){
        std::string contents;
        in.seekg(0, std::ios::end);
        contents.resize(in.tellg());
        in.seekg(0, std::ios::beg);
        in.read(&contents[0], contents.size());
        in.close();
        return(contents);
    }
    throw(errno);
}

Shader::Shader(const char* vertexFile, const char* fragmentFile){
    std::string vertexCode = get_file_contents(vertexFile);
    std::string fragmentCode = get_file_contents(fragmentFile);

    const char* vertexSource = vertexCode.c_str();
    const char* fragmentSource = fragmentCode.c_str();

    //Create vertex shader object and get it's reference
    GLuint vertexShader = glCreateShader(GL_VERTEX_SHADER);
    //Attach vertex shader source to the fragment shader object
    glShaderSource(vertexShader, 1, &vertexSource, NULL);
    //Compile the Vertex shader into machine code
    glCompileShader(vertexShader);

    //Create fragment shader object and get it's reference
    GLuint fragmentShader = glCreateShader(GL_FRAGMENT_SHADER);
    //Attach fragment shader source to the fragment shader object
    glShaderSource(fragmentShader, 1, &fragmentSource, NULL);
    //Compile the Fragment shader into machine code
    glCompileShader(fragmentShader);

    //Create shader projgram and get it's reference
    ID = glCreateProgram();

    //Attach the vertex and fragment shaders together to the shader program
    glAttachShader(ID, vertexShader);
    glAttachShader(ID, fragmentShader);

    //Link all the shaders together
    glLinkProgram(ID);

    //Delete the vertex and fragment shader objects
    glDeleteShader(vertexShader);
    glDeleteShader(fragmentShader);
}

void Shader::Activate(){
    glUseProgram(ID);
}

void Shader::Delete(){
    glUseProgram(ID);
}