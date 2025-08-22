#include "Renderer.h"
#include <QFile>
#include <QDebug>
#include <QRandomGenerator>

#define PATH_TO_IMAGE "C:\\Users\\crist\\Downloads\\zlotea.jpg"

GlRenderer::GlRenderer()
    : vbo(QOpenGLBuffer::VertexBuffer)
{
    verticesCount = 0;

    shapePositionX = 0;
    shapePositionY = 0;
}

GlRenderer::~GlRenderer()
{
    delete myTexture;

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

    bool res = SetAttributes(currentShape);

    if(res == true)
    {
        myTexture = new GLTexture(PATH_TO_IMAGE);
    }

    return res;
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
    float *vertices = new float[1000]; // heap memory. very big memory. needs allocation and manangement


    if (shape == ShapeType::Triangle) {
        float tri[] = {
            0.0f,  0.5f,
            -0.5f, -0.5f,
            0.5f, -0.5f
        };
        memcpy(vertices, tri, sizeof(tri));

        verticesCount = 3;
    }
    else if(shape == ShapeType::Square)
    {
        float sq[] = {  // stack memory. smaller. dosnt  neeed allocation and destruction.
            // first triangle
            -0.5f, -0.5f, //  left bottom
            -0.5f,  0.5f, //  left top
             0.5f, -0.5f, //  right bottm

            // second triangle
             0.5f, -0.5f, //  right bottm
            -0.5f,  0.5f, //  left top
             0.5f,  0.5   //  right top
        };

        memcpy(vertices, sq, sizeof(sq));

        verticesCount = 6;
    }
    else
    {
        qWarning() << "Only Triangle and Squares shape implemented.";
        return false;
    }

    float texcoords[] {
        0.0f, 1.0f,  // bottom left
        0.0f, 0.0f,  // bottom right
        1.0f, 1.0f,  // top left

        // Triangle 2
        1.0f, 1.0f,  // bottom right
        0.0f, 0.0f,  // top right
        1.0f, 0.0f   // top left
    };

    // Create VAO
    if (!vao.isCreated()) vao.create();
    vao.bind();
    // Configure attribute
    shaderProgram->bind();

    // Create VBO
    if (!vbo.isCreated())
        vbo.create();
    vbo.bind();
    vbo.allocate(vertices, verticesCount * sizeof(float) * 2);

    // my vertex position
    shaderProgram->enableAttributeArray(0);
    shaderProgram->setAttributeBuffer(0, GL_FLOAT, 0, 2, 2 * sizeof(float));

    if (!vboTexcoords.isCreated())
        vboTexcoords.create();
    vboTexcoords.bind();
    vboTexcoords.allocate(texcoords, verticesCount * sizeof(float) * 2);

    // my vertex color
    shaderProgram->enableAttributeArray(1);
    shaderProgram->setAttributeBuffer(1, GL_FLOAT, 0, 2, 2 * sizeof(float));

    shaderProgram->release();


    vao.release();
    vbo.release();
    vboTexcoords.release();

    delete[] vertices;

    return true;
}

bool GlRenderer::SetUniforms()
{
    if (!shaderProgram) return false;

    shaderProgram->bind();
    shaderProgram->setUniformValue("u_positionOffset", QVector2D(shapePositionX, shapePositionY));
    shaderProgram->setUniformValue("u_color", QVector3D(r, g, b));
    int err = 0;

    err = glGetError();
    qDebug("error %d", err);

    int textureLocation = glGetUniformLocation(shaderProgram->programId(), "u_texture");
    glActiveTexture(GL_TEXTURE0);

    err = glGetError();
    qDebug("error before glBindTexture%d", err);
    auto texid = myTexture->GetTextureID();
    glBindTexture(GL_TEXTURE_2D, texid);

    err = glGetError();
    qDebug("error after glBindTexture %d", err);
    glUniform1i(textureLocation, 0);

    err = glGetError();
    qDebug("error %d", err);

    return true;
}

void GlRenderer::Draw()
{
    if (!shaderProgram || !vao.isCreated()) return;

    shaderProgram->bind();
    SetUniforms();

    vao.bind();
    glDrawArrays(GL_TRIANGLES, 0, verticesCount);
    vao.release();

    shaderProgram->release();

}

void GlRenderer::SetShape(ShapeType shape)
{
    currentShape = shape;

    SetAttributes(shape);
}


void GlRenderer::SetShapeColorToRandom()
{
    uint value = 0;
    value = QRandomGenerator::global()->generate() % 101;
    r = value / 100.f;

    value = QRandomGenerator::global()->generate() % 101;
    g = value / 100.f;

    value = QRandomGenerator::global()->generate() % 101;
    b = value / 100.f;
}
