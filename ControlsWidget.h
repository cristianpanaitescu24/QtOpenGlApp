#pragma once


#include <QWidget>

class QPushButton;
class QSlider;


class ControlsWidget : public QWidget {
    Q_OBJECT
public:
    explicit ControlsWidget(QWidget* parent = nullptr);

signals:
    void slider1Changed(float value);  // normalized 0.0 - 1.0
    void slider2Changed(float value);
    void button1Pressed();
    void button2Pressed();
    void button3Pressed();

private:
    QPushButton* b1;
    QPushButton* b2;
    QPushButton* b3;

    QSlider* slider1;
    QSlider* slider2;

};

