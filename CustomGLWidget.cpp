#include "CustomGlWidget.h"
#include <QWidget.h>
#include <QTimer>
#include <cmath>

CustomGlWidget::CustomGlWidget(QWidget* parent)
    : QOpenGLWidget(parent)
{
    QTimer* timer = new QTimer(this);
    connect(timer, &QTimer::timeout, this, QOverload<>::of(&CustomGlWidget::update));
    timer->start(16); // 60fps
}

void CustomGlWidget::initializeGL()
{
    initializeOpenGLFunctions();
    renderer.Init();

    glClearColor(0.7f, 0.2f, 0.3f, 1.0f); // random red color
}

void CustomGlWidget::resizeGL(int w, int h)
{

    glViewport(0, 0, w, h);
}

void CustomGlWidget::paintGL()

{
    glClearColor(slider1Value, slider2Value, 0.0f, 1.0f);
    glClear(GL_COLOR_BUFFER_BIT);

    renderer.Draw();
}

// CODE FOR SLOTS
void CustomGlWidget::setSlider1Value(float v) {
    slider1Value = v;
    update();
}

void CustomGlWidget::setSlider2Value(float v) {
    slider2Value = v;
    update();
}

void CustomGlWidget::doAction1() {
    qDebug() << "button 1: TODO Make this cicle between different shapes";
}

void CustomGlWidget::doAction2() {
    qDebug() << "button 2: TODO Make this change position of shape with new random one";
}
