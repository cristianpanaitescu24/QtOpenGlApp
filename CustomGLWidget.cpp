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
    glClearColor(0.2f, 0.2f, 0.2f, 1.0f);
    glClear(GL_COLOR_BUFFER_BIT);

    renderer.Draw();
}

// CODE FOR SLOTS
void CustomGlWidget::setSlider1Value(float v) {
    renderer.SetShapeX(v * 2 - 1.f);
    update();
}

void CustomGlWidget::setSlider2Value(float v) {
    renderer.SetShapeY(v * 2 - 1.f);
    update();
}

void CustomGlWidget::doAction1() {
    if(renderer.currentShape == ShapeType::Triangle)
    {
        qDebug("updating shape to Square");
        renderer.SetShape(ShapeType::Square);
    }
    else if(renderer.currentShape == ShapeType::Square)
    {
        qDebug("updating shape to Circle");
        renderer.SetShape(ShapeType::Circle);
    }
    else if(renderer.currentShape == ShapeType::Circle)
    {
        qDebug("updating shape to Triangle");
        renderer.SetShape(ShapeType::Triangle);
    }
}

void CustomGlWidget::doAction2()
{
    qDebug("Randomizing shape color.");
    renderer.SetShapeColorToRandom();
}


void CustomGlWidget::nnnn()
{
    qDebug("Randomizing shape color. BUTTON 3 pressed");
    renderer.SetShapeX(renderer.GetShapeX() + 0.05f);
}
