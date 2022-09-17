#include "colorsystem.h"
#include <QDebug>

colorSystem::colorSystem(QWidget *parent, int numberOfFields, std::vector<std::pair<qreal, qreal>> ranges, QString name, int _id) :
    QWidget(parent), size(numberOfFields), systemId(_id)
{
    blockSignals(true);
    slider = new colorSystemSlider(this);
    QHBoxLayout *h = new QHBoxLayout;
    for (int i = 0; i < size; i++)
    {
        fields[i] = new colorSystemField(this, slider, ranges[i].first, ranges[i].second, i);
        connect(fields[i], &colorSystemField::valueChanged, this, &colorSystem::ChangeFieldValue);
        connect(fields[i], &colorSystemField::sliderActivated, this, &colorSystem::SliderActivated);
        if (i > 0)
        {
            h -> addStretch(30);
        }
        h -> addWidget(fields[i]);
    }
    QVBoxLayout *v = new QVBoxLayout(this);
    nameLabel = new QLabel;
    nameLabel -> setText(name);
    v -> addWidget(nameLabel);
    v -> addLayout(h);
    v -> addWidget(slider);
    blockSignals(false);
}
void colorSystem::SliderActivated()
{
    emit systemSliderActivated(systemId);
}
void colorSystem::DisableSlider()
{
    if (slider -> isVisible() && slider -> GetActiveField())
    {
        disconnect(slider, &QSlider::sliderReleased, slider -> GetActiveField(), &colorSystemField::setActive);
        disconnect(slider, &QSlider::valueChanged, slider -> GetActiveField(), &colorSystemField::ChangeValue);
        slider -> setVisible(false);
    }
}
void colorSystem::BlockAllSignals(bool block)
{
    blockSignals(block);
    for (int i = 0; i < size; i++)
    {
        fields[i]->blockSignals(block);
    }
}
void colorSystem::ChangeFieldValue(int newValue, int fieldId)
{
    values[fieldId] = newValue;
    if (fields[fieldId]->getValue() != newValue)
    {
        fields[fieldId]->ChangeValue(newValue);
    }
    //qDebug() << '{' << systemId << '}';
    std::vector<int> newValues;
    for (int i = 0; i < size; i++)
    {
        newValues.push_back(values[i]);
        //qDebug() << '[' << values[i];
    }
    //qDebug() << ']';
    emit systemValueChanged(newValues, systemId);
}
colorSystem::~colorSystem()
{
    for (int i = 0; i < size; i++)
    {
        delete fields[i];
    }
    delete slider;
    delete nameLabel;
}
RGBSystem::RGBSystem(QWidget *parent, int id):colorSystem(parent, 3, {{0, 255}, {0, 255}, {0, 255}}, "RGB", id)
{}
ColorSystem RGBSystem::getSystemType() const
{
    return ColorSystem::RGB;
}
CMYKSystem::CMYKSystem(QWidget *parent, int id):colorSystem(parent, 4, {{0, 255}, {0, 255}, {0, 255}, {0, 255}}, "CMYK", id)
{}
ColorSystem CMYKSystem::getSystemType() const
{
    return ColorSystem::CMYK;
}
HSVSystem::HSVSystem(QWidget *parent, int id):colorSystem(parent, 3, {{0, 360}, {0, 255}, {0, 255}}, "HSV", id)
{}
ColorSystem HSVSystem::getSystemType() const
{
    return ColorSystem::HSV;
}
HSLSystem::HSLSystem(QWidget *parent, int id):colorSystem(parent, 3, {{0, 360}, {0, 255}, {0, 255}}, "HSL", id)
{}
ColorSystem HSLSystem::getSystemType() const
{
    return ColorSystem::HSL;
}
XYZSystem::XYZSystem(QWidget *parent, int id):colorSystem(parent, 3, {{0, 95}, {0, 100}, {0, 109}}, "XYZ", id)
{}
ColorSystem XYZSystem::getSystemType() const
{
    return ColorSystem::XYZ;
}
LABSystem::LABSystem(QWidget *parent, int id):colorSystem(parent, 3, {{0, 100}, {-128, 127}, {-128, 127}}, "LAB", id)
{}
ColorSystem LABSystem::getSystemType() const
{
    return ColorSystem::LAB;
}
