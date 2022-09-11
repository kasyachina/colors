#include "colorsystemfield.h"
#include <qDebug>

colorSystemField::colorSystemField(QWidget *parent, colorSystemSlider *control_slider, int _left, int _right) :
    QLineEdit(parent), leftThreshold(_left), rightThreshold(_right), slider(control_slider)
{
    slider -> setVisible(false);
    connect(this, &QLineEdit::returnPressed, this, &colorSystemField::EnterPressed);
    ChangeValue(_left);
}
void colorSystemField::EnterPressed()
{
    slider -> setVisible(false);
    slider -> ClearActiveField();
    clearFocus();
}
void colorSystemField::ChangeValue(int newValue)
{
    value = newValue;
    setText(QString::number(value));
    emit valueChanged(newValue);
}
void colorSystemField::mousePressEvent(QMouseEvent *)
{
    if (slider -> GetActiveField())
    {
        disconnect(slider, &QSlider::valueChanged, slider -> GetActiveField(), &colorSystemField::ChangeValue);
        disconnect(this, &QLineEdit::textChanged, slider, &colorSystemSlider::ActiveFieldValueChanged);
    }
    slider -> ChangeActiveField(this);
    slider -> setVisible(true);
    slider -> setRange(leftThreshold, rightThreshold);
    slider -> ActiveFieldValueChanged();
    connect(this, &QLineEdit::textChanged, slider, &colorSystemSlider::ActiveFieldValueChanged);
    connect(slider, &QSlider::sliderReleased, this, [this](){ this -> setFocus(); });
    connect(slider, &QSlider::valueChanged, this, &colorSystemField::ChangeValue);
}
colorSystemSlider::colorSystemSlider(QWidget *parent) : QSlider(Qt::Horizontal, parent)
{
    setTracking(true);
}
void colorSystemSlider::ClearActiveField()
{
    activeField = nullptr;
}
colorSystemField* colorSystemSlider::GetActiveField() const
{
    return activeField;
}
void colorSystemSlider::ChangeActiveField(colorSystemField *new_field)
{
    activeField = new_field;
}
void colorSystemSlider::ActiveFieldValueChanged()
{
    setValue(activeField->text().toInt());
}
