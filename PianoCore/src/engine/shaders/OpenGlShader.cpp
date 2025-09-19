#include "OpenGlShader.h"

#include <GLES3/gl32.h>
#include <GLFW/glfw3.h>

#include <fstream>
#include <iostream>
#include <string>

#include "simple_fragment.h"
#include "simple_vertex.h"

namespace Shaders {

unsigned int OpenGlShader::loadShader() {
    std::cout << "Compiling Vertex Shaders\n" << std::endl;
    auto vertexShader = OpenGlShader::compileVertexShaders();
    std::cout << "Compiling Fragment Shaders\n" << std::endl;
    auto fragmentShader = OpenGlShader::compileFragmentShaders();
    std::cout << "Linking Shaders...\n" << std::endl;
    auto shaderProgram = OpenGlShader::LinkShader(vertexShader, fragmentShader);
    return shaderProgram;
}

OpenGlShader::OpenGlShader(const char* vertexPath, const char* fragmentPath) {
    this->ID = loadShader();
}

void OpenGlShader::use() {
    glUseProgram(ID);
}

void OpenGlShader::setFloat(const std::string& name, float value) const {
    glUniform1f(glGetUniformLocation(ID, name.c_str()), value);
}

std::string LoadShaderAsString(const std::string& filename) {
    std::string result = "";

    std::string line = "";
    std::ifstream myFile(filename.c_str());

    if (myFile.is_open()) {
        while (std::getline(myFile, line)) {
            result += line + '\n';
        }
        myFile.close();
    } else {
        std::cout << "Unable to open file at " << filename << std::endl;
    }
    std::cout << "Result " << result.c_str() << std::endl;
    return result;
}

unsigned int OpenGlShader::compileVertexShaders() {
    unsigned int vertexShader = glCreateShader(GL_VERTEX_SHADER);

    const std::string vertShaderSources[] = {
        LoadShaderAsString("./shaders/base.vert")};
    return OpenGlShader::CompileShader(GL_VERTEX_SHADER, vertShaderSources[0]);
}

GLuint OpenGlShader::CompileShader(GLuint type, const std::string& source) {
    GLuint shaderObject;

    if (type == GL_VERTEX_SHADER) {
        shaderObject = glCreateShader(GL_VERTEX_SHADER);
    } else if (type == GL_FRAGMENT_SHADER) {
        shaderObject = glCreateShader(GL_FRAGMENT_SHADER);
    } else {
        std::cout << "ERROR::SHADER::COMPILATION_FAILED\n"
                  << "UNDETERMINED SHADER TYPE: " << type << std::endl;
    }

    const char* src = source.c_str();
    glShaderSource(shaderObject, 1, &src, nullptr);
    glCompileShader(shaderObject);

    // check for shader compile errors
    int success;
    char infoLog[512];
    glGetShaderiv(shaderObject, GL_COMPILE_STATUS, &success);
    if (!success) {
        glGetShaderInfoLog(shaderObject, 512, NULL, infoLog);
        std::cout << "ERROR::SHADER::COMPILATION_FAILED\n"
                  << infoLog << std::endl;
    }
    return shaderObject;
}

unsigned int OpenGlShader::compileFragmentShaders() {
    unsigned int fragmentShader = glCreateShader(GL_FRAGMENT_SHADER);

    const std::string fragShaderSources[] = {
        LoadShaderAsString("./shaders/base.frag")};
    return OpenGlShader::CompileShader(GL_FRAGMENT_SHADER,
                                       fragShaderSources[0]);
}

unsigned int OpenGlShader::LinkShader(unsigned int vertexShader,
                                      unsigned int fragmentShader) {
    unsigned int shaderProgram = glCreateProgram();
    glAttachShader(shaderProgram, vertexShader);
    glAttachShader(shaderProgram, fragmentShader);
    glLinkProgram(shaderProgram);
    // check for linking errors
    int success;
    char infoLog[512];
    glGetProgramiv(shaderProgram, GL_LINK_STATUS, &success);
    if (!success) {
        glGetProgramInfoLog(shaderProgram, 512, NULL, infoLog);
        std::cout << "ERROR::SHADER::PROGRAM::LINKING_FAILED\n"
                  << infoLog << std::endl;
    }
    glDeleteShader(vertexShader);
    glDeleteShader(fragmentShader);
    return shaderProgram;
}

}  // namespace Shaders