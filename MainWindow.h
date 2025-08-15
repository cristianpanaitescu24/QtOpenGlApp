#pragma once
#include <QMainWindow>
#include "CustomGlWidget.h"


class MainWindow : public QMainWindow {
    Q_OBJECT
public:
    MainWindow(QWidget *parent = nullptr);
private:
    CustomGlWidget* glWidget;
};
