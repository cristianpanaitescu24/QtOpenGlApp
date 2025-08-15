#include "ControlsWidget.h"
#include <QPushButton>
#include <QSlider>
#include <QVBoxLayout>
#include <QLabel>

ControlsWidget::ControlsWidget(QWidget* parent)
    : QWidget(parent)
{
    b1 = new QPushButton("Button 1", this);
    b2 = new QPushButton("Button 2", this);
    b3 = new QPushButton("Button 3", this);

    slider1 = new QSlider(Qt::Horizontal, this);
    slider2 = new QSlider(Qt::Horizontal, this);

    for (QSlider* slider : {slider1, slider2}) {
        slider->setRange(0, 100);  // internal int range
        slider->setValue(50);      // start at 0.5
    }

    QVBoxLayout* layout = new QVBoxLayout(this);
    layout->addWidget(b1);
    layout->addWidget(b2);
    layout->addWidget(b3);
    layout->addWidget(new QLabel("Slider 1"));
    layout->addWidget(slider1);
    layout->addWidget(new QLabel("Slider 2"));
    layout->addWidget(slider2);
    setLayout(layout);

    connect(slider1, &QSlider::valueChanged, this, [this](int v) {
        emit slider1Changed(v / 100.0f);
    });
    connect(slider2, &QSlider::valueChanged, this, [this](int v) {
        emit slider2Changed(v / 100.0f);
    });
    connect(b1, &QPushButton::clicked, this, &ControlsWidget::button1Pressed);
    connect(b2, &QPushButton::clicked, this, &ControlsWidget::button2Pressed);
    connect(b3, &QPushButton::released, this, &ControlsWidget::button3Pressed);
}
