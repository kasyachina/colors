#include "colorsystemfield.h"
#include "QDebug"

colorSystemField::colorSystemField(QWidget *parent, colorSystemSlider *control_slider, int _left, int _right, int _id) :
    QLineEdit(parent), id(_id), leftThreshold(_left), rightThreshold(_right), slider(control_slider)
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
    if (newValue > rightThreshold)
    {
        newValue = rightThreshold;
    }
    if (newValue < leftThreshold)
    {
        newValue = leftThreshold;
    }
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
    bool ok;
    int parsedInt = newValue.toInt(&ok);
    if (ok)
    {
        ChangeValue(parsedInt);
    }
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
    ChangeValue(value);
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
