#pragma once
#include <QWidget>
#include <QtOpenGLWidgets/QOpenGLWidget>
#include <QtOpenGL/QOpenGLFunctions_3_3_Core>
#include "Renderer.h"

// This is our window that draws using pure OpenGl
class CustomGlWidget : public QOpenGLWidget, protected QOpenGLFunctions_3_3_Core
{
    Q_OBJECT
public:
    // constructor
    CustomGlWidget(QWidget* parent = nullptr);

public slots:
    void setSlider1Value(float v);
    void setSlider2Value(float v);
    void doAction1();
    void doAction2();
    void nnnn();

protected:
    void initializeGL() override;
    void resizeGL(int w, int h) override;
    void paintGL() override;

    GlRenderer renderer;
};
