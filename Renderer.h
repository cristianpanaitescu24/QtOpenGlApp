#pragma once

#include <QOpenGLFunctions_3_3_Core>
#include <QOpenGLBuffer>
#include <QOpenGLVertexArrayObject>
#include <QOpenGLShaderProgram>
#include "GLTexture.h"

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

    void SetShape(ShapeType shape);

    ShapeType currentShape = ShapeType::Triangle;

    void SetShapeX(float x) {
        qDebug("Chaging positon to %d", x);
        shapePositionX = x;
    }
    void SetShapeY(float y) { shapePositionY = y; }

    float GetShapeX() {return shapePositionX; }
    float GetShapeY() {return shapePositionY; }

    void SetShapeColorToRandom();
private:
    bool LoadShader(const QString& vertexPath, const QString& fragmentPath);
    bool SetAttributes(ShapeType shape);
    bool SetUniforms();

    QOpenGLShaderProgram* shaderProgram = nullptr;

    QOpenGLBuffer               vbo;
    QOpenGLBuffer               vboTexcoords;


    QOpenGLVertexArrayObject    vao;

    // Uniform values
    float                       shapePositionX;
    float                       shapePositionY;

    float   r = 0.f, g = 0.f,  b = 0.f;

    int                         verticesCount;

    // Texture
    GLTexture *                 myTexture;

};
