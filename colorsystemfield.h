#pragma once

#include <QWidget>
#include <QSlider>
#include <QLineEdit>

class colorSystemField : public QLineEdit
{
    Q_OBJECT
public:
    explicit colorSystemField(QWidget *parent = nullptr, QSlider *control_slider = nullptr);
    virtual ~colorSystemField();
signals:

private:
    QSlider *slider;
};

