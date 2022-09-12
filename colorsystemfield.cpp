#include "colorsystemfield.h"

colorSystemField::colorSystemField(QWidget *parent, colorSystemSlider *control_slider, int _left, int _right, int _id) :
    QLineEdit(parent), leftThreshold(_left), rightThreshold(_right), id(_id), slider(control_slider)
{
    slider -> setVisible(false);
    connect(this, &QLineEdit::returnPressed, this, &colorSystemField::EnterPressed);
    connect(this, &QLineEdit::textChanged, this, &colorSystemField::ChangeValueText);
    QString warningMessage = "This field must be integer in range [" + QString::number(leftThreshold) + "," + QString::number(rightThreshold) + "]";
    connect(this, &QLineEdit::inputRejected, this, [this, warningMessage](){QMessageBox::warning(this, "Error", warningMessage);});
    QIntValidator *val = new QIntValidator(leftThreshold, rightThreshold, this);
    setValidator(val);
    ChangeValue(_left);
}
void colorSystemField::EnterPressed()
{
    slider -> setVisible(false);
    clearFocus();
}
int colorSystemField::getValue() const
{
    return value;
}
void colorSystemField::ChangeValue(int newValue)
{
    value = newValue;
    if (text() != QString::number(value))
    {
        setText(QString::number(value));
    }
    if (slider -> GetActiveField() == this && slider -> value() != value)
    {
        slider -> setValue(value);
    }
    emit valueChanged(newValue, id);
}
void colorSystemField::ChangeValueText(const QString& newValue)
{
    ChangeValue(newValue.toInt());
}
void colorSystemField::mousePressEvent(QMouseEvent *)
{
    if (slider -> GetActiveField())
    {
        disconnect(slider, &QSlider::sliderReleased, this, &colorSystemField::setActive);
        disconnect(slider, &QSlider::valueChanged, slider -> GetActiveField(), &colorSystemField::ChangeValue);

    }
    slider -> ChangeActiveField(this);
    slider -> setVisible(true);
    slider -> setRange(leftThreshold, rightThreshold);
    slider -> ActiveFieldValueChanged();
    connect(slider, &QSlider::sliderReleased, this, &colorSystemField::setActive);
    connect(slider, &QSlider::valueChanged, this, &colorSystemField::ChangeValue);
}
colorSystemSlider::colorSystemSlider(QWidget *parent) : QSlider(Qt::Horizontal, parent)
{
    setTracking(true);
}
void colorSystemField::setActive()
{
    setFocus();
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
