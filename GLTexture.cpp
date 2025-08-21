#include "GLTexture.h"


GLTexture::GLTexture(const QString &filePath)
    : m_texture(nullptr)
{
    initializeOpenGLFunctions();

    QImage image(filePath);
    if (!image.isNull())
    {
        m_texture = new QOpenGLTexture(image);
        m_texture->setMinificationFilter(QOpenGLTexture::LinearMipMapLinear);
        m_texture->setMagnificationFilter(QOpenGLTexture::Linear);
        m_texture->setWrapMode(QOpenGLTexture::Repeat);
    }
}


GLTexture::~GLTexture()
{
    delete m_texture;
}

void GLTexture::Bind()
{
    if (m_texture)
        m_texture->bind(GL_TEXTURE0);

}
