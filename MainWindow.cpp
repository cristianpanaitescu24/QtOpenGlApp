#include "MainWindow.h"
#include "ControlsWidget.h"
#include "CustomGlWidget.h"
#include <QHBoxLayout>

MainWindow::MainWindow(QWidget *parent)
    : QMainWindow(parent) {
    glWidget = new CustomGlWidget(this);
    setCentralWidget(glWidget);
    resize(800, 600);

    QWidget* central = new QWidget(this);
    QHBoxLayout* hLayout = new QHBoxLayout(central);

    CustomGlWidget* glWidget = new CustomGlWidget(central);
    ControlsWidget* controls = new ControlsWidget(central);

    hLayout->addWidget(glWidget, 4);
    hLayout->addWidget(controls, 1);

    central->setLayout(hLayout);
    setCentralWidget(central);

    // Connect controls to GL widget
    connect(controls, &ControlsWidget::slider1Changed, glWidget, &CustomGlWidget::setSlider1Value);
    connect(controls, &ControlsWidget::slider2Changed, glWidget, &CustomGlWidget::setSlider2Value);
    connect(controls, &ControlsWidget::button1Pressed, glWidget, &CustomGlWidget::doAction1);
    connect(controls, &ControlsWidget::button2Pressed, glWidget, &CustomGlWidget::doAction2);
    connect(controls, &ControlsWidget::button3Pressed, glWidget, &CustomGlWidget::nnnn);
}
