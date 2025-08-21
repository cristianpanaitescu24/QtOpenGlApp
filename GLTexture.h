// Texture.h
#pragma once

#include <QOpenGLFunctions>
#include <QOpenGLTexture>
#include <QImage>
#include <QString>

class GLTexture : protected QOpenGLFunctions
{
public:
    GLTexture(const QString &filePath);

    ~GLTexture();

    void Bind();

private:
    QOpenGLTexture *m_texture;
};
