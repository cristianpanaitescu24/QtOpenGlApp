#pragma once
#include <QMainWindow>
#include "CustomGlWidget.h"

class MyGLWidget;

class MainWindow : public QMainWindow {
    Q_OBJECT
public:
    MainWindow(QWidget *parent = nullptr);
private:
    CustomGlWidget* glWidget;
};
