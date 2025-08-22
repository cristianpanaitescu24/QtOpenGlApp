

#include <QOpenGLFunctions>
#include <QImage>
#include <QString>

#pragma once

class GLTexture : protected QOpenGLFunctions
{
public:
    GLTexture(const QString &filePath);
    GLTexture(uint32_t format);

    virtual ~GLTexture();

    // getter function
    GLuint GetTextureID() {return mTextureId;}

protected:
private:

    GLuint      mTextureId;
    QImage     *mImage;

};

