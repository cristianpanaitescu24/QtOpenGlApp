#pragma once

#include <QOpenGLFunctions_3_3_Core>
#include <QOpenGLBuffer>
#include <QOpenGLVertexArrayObject>
#include <QOpenGLShaderProgram>

enum class ShapeType {
    Triangle,
    Square,
    Circle
};

#define VERTEX_SHADER_FILE "./shaders/simple_shader.vsh"
#define FRAGMENT_SHADER_FILE "./shaders/simple_shader.fsh"

// Hardcoded uniform valuesW
#define DEFAULT_SIZE 0.8f

class GlRenderer : public QOpenGLFunctions_3_3_Core {
public:
    GlRenderer();
    ~GlRenderer();

    bool Init();
    void Draw();

    void SetShape(ShapeType shape) { currentShape = shape; SetAttributes(shape); }

private:
    bool LoadShader(const QString& vertexPath, const QString& fragmentPath);
    bool SetAttributes(ShapeType shape);
    bool SetUniforms();

    QOpenGLShaderProgram* shaderProgram = nullptr;
    QOpenGLBuffer vbo;
    QOpenGLVertexArrayObject vao;

    ShapeType currentShape = ShapeType::Triangle;

    // Uniform values
    float u_size = DEFAULT_SIZE;
};
