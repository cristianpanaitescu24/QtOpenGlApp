#include "GLTexture.h"


GLTexture::GLTexture(const QString &filePath)
    : mImage(nullptr)
{
    initializeOpenGLFunctions();

    QImage image(filePath);
    if (!image.isNull())
    {
        glGenTextures(1, &mTextureId);
        glBindTexture(GL_TEXTURE_2D, mTextureId);

        glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_S, GL_REPEAT);
        glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_T, GL_REPEAT);

        glTexParameterf(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_LINEAR);
        glTexParameterf(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_LINEAR);

        // auto mysize = image.width() * image.height() * 4;
        // uint8_t *mydata = (uint8_t *)malloc(mysize);
        // memset(mydata, 128, mysize);

        glTexImage2D(
            GL_TEXTURE_2D,
            0,
            GL_BGRA,
            image.width(),
            image.height(),
            0,
            GL_BGRA,
            GL_UNSIGNED_BYTE,
            image.bits());

        glBindTexture(GL_TEXTURE_2D, 0);

        // free(mydata);
    }
}


GLTexture::~GLTexture()
{
    glDeleteTextures(1, &mTextureId);
}

