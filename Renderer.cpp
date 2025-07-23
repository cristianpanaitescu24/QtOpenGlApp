#include "Renderer.h"
#include <QFile>
#include <QDebug>

GlRenderer::GlRenderer()
    : vbo(QOpenGLBuffer::VertexBuffer)
{
}

GlRenderer::~GlRenderer()
{
    if (shaderProgram) {
        delete shaderProgram;
        shaderProgram = nullptr;
    }

    if (vbo.isCreated()) vbo.destroy();
    if (vao.isCreated()) vao.destroy();
}

bool GlRenderer::Init()
{
    initializeOpenGLFunctions();

    if (!LoadShader(VERTEX_SHADER_FILE, FRAGMENT_SHADER_FILE)) {
        return false;
    }

    return SetAttributes(currentShape);
}

bool GlRenderer::LoadShader(const QString& vertexPath, const QString& fragmentPath)
{
    QFile vFile(vertexPath), fFile(fragmentPath);

    if (!vFile.open(QIODevice::ReadOnly) || !fFile.open(QIODevice::ReadOnly)) {
        qWarning() << "Shader file not found!";
        return false;
    }

    QByteArray vSource = vFile.readAll();
    QByteArray fSource = fFile.readAll();

    shaderProgram = new QOpenGLShaderProgram();

    if (!shaderProgram->addShaderFromSourceCode(QOpenGLShader::Vertex, vSource)) {
        qWarning() << "Vertex shader error:" << shaderProgram->log();
        return false;
    }

    if (!shaderProgram->addShaderFromSourceCode(QOpenGLShader::Fragment, fSource)) {
        qWarning() << "Fragment shader error:" << shaderProgram->log();
        return false;
    }

    if (!shaderProgram->link()) {
        qWarning() << "Shader link error:" << shaderProgram->log();
        return false;
    }

    return true;
}

bool GlRenderer::SetAttributes(ShapeType shape)
{
    // Define vertices
    float vertices[6] = { 0 };

    if (shape == ShapeType::Triangle) {
        float tri[] = {
            0.0f,  0.5f,
            -0.5f, -0.5f,
            0.5f, -0.5f
        };
        memcpy(vertices, tri, sizeof(tri));
    } else {
        qWarning() << "Only Triangle shape implemented.";
        return false;
    }

    // Create VAO
    if (!vao.isCreated()) vao.create();
    vao.bind();

    // Create VBO
    if (!vbo.isCreated()) vbo.create();
    vbo.bind();
    vbo.allocate(vertices, sizeof(vertices));

    // Configure attribute
    shaderProgram->bind();
    shaderProgram->enableAttributeArray(0);
    shaderProgram->setAttributeBuffer(0, GL_FLOAT, 0, 2, 2 * sizeof(float));
    shaderProgram->release();

    vao.release();
    vbo.release();

    return true;
}

bool GlRenderer::SetUniforms()
{
    if (!shaderProgram) return false;

    shaderProgram->bind();
    shaderProgram->setUniformValue("u_size", u_size);
    shaderProgram->setUniformValue("u_color", QVector3D(1.0f, 0.0f, 0.0f));

    return true;
}

void GlRenderer::Draw()
{
    if (!shaderProgram || !vao.isCreated()) return;

    shaderProgram->bind();
    SetUniforms();

    vao.bind();
    glDrawArrays(GL_TRIANGLES, 0, 3);
    vao.release();

    shaderProgram->release();
}
