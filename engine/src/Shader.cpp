#include "Shader.h"

#include <stdio.h>
#include "Utils.h"

// Memory Management

Shader::Shader() {
    id = 0;
}

Shader::~Shader() {
    if (id != 0) {
        glDeleteProgram(id);
    }
}

void Shader::init(const char *vertPathName, 
                                        const char *fragPathName, 
                                        const char *geomPathName, 
                                        GLenum gsInput, 
                                        GLenum gsOutput) {
    id = compileProgram(vertPathName,
                                            fragPathName,
                                            geomPathName,
                                            gsInput,
                                            gsOutput);
}

void Shader::tearDown(unsigned int vertShader, unsigned int fragShader, unsigned int geomShader) {
    // Clean up program (generally on error)
    if (vertShader) {
        glDeleteShader(vertShader);
    }
    if (fragShader) {
        glDeleteShader(fragShader);
    }
    if (geomShader) {
        glDeleteShader(geomShader);
    }
    if (id) {
        glDeleteProgram(id);
    }
}

// mark Getters & Setters

unsigned int Shader::programId() {
    return id;
}

void Shader::enable() {
    glUseProgram(id); 
}

void Shader::disable() {
    glUseProgram(0);
}

void Shader::setUniform1f(const char *name, float value) {
    // register var
    int loc = glGetUniformLocation(id, name);
    if (loc >= 0) {
        // 
        glUniform1f(loc, value);
    }
}

void Shader::setUniform2f(const char *name, float x, float y) {
    // register var
    int loc = glGetUniformLocation(id, name);
    if (loc >= 0) {
        // 
        glUniform2f(loc, x, y);
    }
}
void Shader::setUniform3f(const char *name, float x, float y, float z) {
    // register var
    int loc = glGetUniformLocation(id, name);
    if (loc >= 0) {
        // 
        glUniform3f(loc, x, y, z);
    }
}

void Shader::setUniform4f(const char *name, float x, float y, float z, float w) {
    // register var
    int loc = glGetUniformLocation(id, name);
    if (loc >= 0) {
        // 
        glUniform4f(loc, x, y, z, w);
    }
}

void Shader::setUniformfv(const char *name, float *v, int elementSize, int count) {
    // register var
    int loc = glGetUniformLocation(id, name);
    if (loc >= 0) {
        switch (elementSize) {
            case 1:
                glUniform1fv(loc, count, v);
                break;
            case 2:
                glUniform2fv(loc, count, v);
                break;
            case 3:
                glUniform3fv(loc, count, v);
                break;
            case 4:
                glUniform4fv(loc, count, v);
                break;
        }
    } else {
        printf("error %s\n", name);
    }
}

void Shader::setUniformMatrix4fv(const char *name, float *m, bool transpose) {
    // register var
    int loc = glGetUniformLocation(id, name);
    if (loc >= 0) {
        // 
        glUniformMatrix4fv(loc, 1, transpose, m);
    }
}

void Shader::bindTexture(const char *name, unsigned int tex, GLenum target, int unit) {
    // register var
    int loc = glGetUniformLocation(id, name);
    if (loc >= 0) {
        glActiveTexture(GL_TEXTURE0 + unit);
        glBindTexture(target, tex);
        glUseProgram(id);
        glUniform1i(loc, unit);
        glActiveTexture(GL_TEXTURE0);
    }
}

// Compile Methods

bool Shader::checkCompileStatus(unsigned int shader) {
    int status;
    glGetShaderiv(shader, GL_COMPILE_STATUS, &status);
    if (!status){
            char log[2048];
            int len;
            glGetShaderInfoLog(shader, 2048, (GLsizei *)&len, log);
            printf("Error: shader(%04d), Info log: %s\n", (int)shader, log);
            glDeleteShader(shader);
            return false;
    }
    return true;
}

bool Shader::compileShader(const char *vertPathName, GLenum shaderType, unsigned int &shader) {
    char *source = callocStringWithContentsOfFile(vertPathName);
    if (!source) {
        printf("Failed to load shader");
    }

    // Immputable reference
    const char *shaderSource = source;
    shader = glCreateShader(shaderType);
    glShaderSource(shader, 1, &shaderSource, 0);
    glCompileShader(shader);

    if (!checkCompileStatus(shader)) {
        printf("<compileProgram compilation error with vertexShader>:\n");
        printf("%s\n", source);
        return false;
    }

    free(source);
    return true;
}

unsigned int Shader::compileProgram(const char *vertPathName, 
                                                                            const char *fragPathName, 
                                                                            const char *geomPathName,
                                                                            GLenum gsInput, 
                                                                            GLenum gsOutput) {
    
    unsigned int vertShader, fragShader, geomShader;
    vertShader = fragShader = geomShader = 0;

        printf("Compiling %s\n", vertPathName);
    // Create and compile vertex shader
    if (!compileShader(vertPathName, GL_VERTEX_SHADER, vertShader)) {
        tearDown(vertShader, fragShader, geomShader);
        return 0;
    }
        printf("Compiling %s\n", fragPathName);
    // Create and compile fragment shader
    if (!compileShader(fragPathName, GL_FRAGMENT_SHADER, fragShader)) {
        tearDown(vertShader, fragShader, geomShader);
        return 0;
    }

    // Create shader program
    unsigned int program = glCreateProgram();

    // Attach vertex and fragment shaders to program
    glAttachShader(program, vertShader);
    glAttachShader(program, fragShader);

    // Create, compile and attach fragment shader, if any
    if (geomPathName) {
        if (!compileShader(geomPathName, GL_GEOMETRY_SHADER_EXT, geomShader)) {
            tearDown(vertShader, fragShader, geomShader);
            return 0;
        }
        glAttachShader(program, geomShader);

        // Set up geometry params before linking
        glProgramParameteriEXT(program, GL_GEOMETRY_INPUT_TYPE_EXT, gsInput);
        glProgramParameteriEXT(program, GL_GEOMETRY_OUTPUT_TYPE_EXT, gsOutput);
        glProgramParameteriEXT(program, GL_GEOMETRY_VERTICES_OUT_EXT, 4);
    } else {
        geomShader = 0;
    }

    glLinkProgram(program);

    // Check if program linked
    GLint success = 0;
    glGetProgramiv(program, GL_LINK_STATUS, &success);
    if (!success) {
            char temp[1024];
            glGetProgramInfoLog(program, 1024, 0, temp);
            printf("Failed to link program:\n%s\n", temp);

            tearDown(vertShader, fragShader, geomShader);
            return 0;
    }

    // Release shaders
    if (vertShader) {
        glDetachShader(program, vertShader);
        glDeleteShader(vertShader);
    }
    if (fragShader) {
        glDetachShader(program, fragShader);
        glDeleteShader(fragShader);
    }
    if (geomShader) {
        glDetachShader(program, geomShader);
        glDeleteShader(geomShader);
    }

    return program;
}
