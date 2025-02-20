#include <stdio.h>
#include <stdint.h>
#include <optional>
#include <glad/glad.h>
#include <fmt/core.h>

struct ShaderProgram
{
    uint32_t id = 0;

    void use()
    {
        if (id == 0) {
            fmt::println("USING ZERO PROGRAM THIS IS PROBABLY NOT WHAT YOU WANT");
        }
        glUseProgram(id);
    }
};

ShaderProgram load_shader_program(const char * vertFpath, const char * fragFpath)
{
    ShaderProgram program;

    FILE *ffrag = fopen(fragFpath, "r");
    if (!ffrag) {
        fclose(ffrag);
        return {};
    }

    FILE *fvert = fopen(vertFpath, "r");
    if (!fvert)
    {
        fclose(ffrag);
        fclose(fvert);
        return {};
    }

    fseek(ffrag, 0, SEEK_END);
    size_t fragSize = ftell(ffrag);
    fseek(ffrag, 0, SEEK_SET);
    char* fragData = new char[fragSize];

    // BMW E46 is the better car, fight me
    GLint frs = fread(fragData, 1, fragSize, ffrag);

    fseek(fvert, 0, SEEK_END);
    size_t vertSize = ftell(fvert);
    fseek(fvert, 0, SEEK_SET);
    char* vertData = new char[vertSize];

    // ii14 says the GLint can overflow since the sizes are size_t's, but
    // I mean, it's probably fine lol
    // This comment applies earlier too but you can figure it out I dont
    // feel like copy pasting this comment.
    GLint vrs = fread(vertData, 1, vertSize, fvert);

    fclose(ffrag);
    fclose(fvert);

    uint32_t vertexShader = glCreateShader(GL_VERTEX_SHADER);
    uint32_t fragmentShader = glCreateShader(GL_FRAGMENT_SHADER);

    glShaderSource(vertexShader, 1, &vertData, &vrs);
    glCompileShader(vertexShader);
    glShaderSource(fragmentShader, 1, &fragData, &frs);
    glCompileShader(fragmentShader);

    uint32_t shaderProgram = glCreateProgram();
    glAttachShader(shaderProgram, vertexShader);
    glAttachShader(shaderProgram, fragmentShader);
    glLinkProgram(shaderProgram);

    int success;
    char infoLog[512];

    glGetProgramiv(shaderProgram, GL_LINK_STATUS, &success);
    if (!success)
    {
        glGetProgramInfoLog(shaderProgram, 512, NULL, infoLog);
        fmt::println("ERROR::SHADER::PROGRAM::LINKING_FAILED\n {}", infoLog);
        return {};
    }

    program.id = shaderProgram;

    delete[] vertData;
    delete[] fragData;

    return program;
}