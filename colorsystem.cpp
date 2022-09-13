#include "colorsystem.h"
#include <QDebug>

colorSystem::colorSystem(QWidget *parent, int numberOfFields, std::vector<std::pair<qreal, qreal>> ranges, QString name) : QWidget(parent), size(numberOfFields)
{
    controlSlider = new colorSystemSlider(this);
    QHBoxLayout *h = new QHBoxLayout;
    for (int i = 0; i < size; i++)
    {
        fields[i] = new colorSystemField(this, controlSlider, ranges[i].first, ranges[i].second, i);
        values[i] = ranges[i].first;
        connect(fields[i], &colorSystemField::valueChanged, this, &colorSystem::ChangeFieldValue);
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
    v -> addWidget(controlSlider);
}
void colorSystem::ChangeFieldValue(int newValue, int id)
{
    values[id] = newValue;
    if (fields[id]->getValue() != newValue)
    {
        fields[id]->ChangeValue(newValue);
    }

    std::vector<int> newValues;
    for (int i = 0; i < size; i++)
    {
        newValues.push_back(values[i]);
        //qDebug() << '[' << values[i];
    }
    //qDebug() << ']';
    emit systemValueChanged(newValues);
}
colorSystem::~colorSystem()
{
    for (int i = 0; i < size; i++)
    {
        delete fields[i];
    }
    delete controlSlider;
    delete nameLabel;
}
RGBSystem::RGBSystem(QWidget *parent):colorSystem(parent, 3, {{0, 255}, {0, 255}, {0, 255}}, "RGB")
{}
ColorSystem RGBSystem::getSystemId() const
{
    return ColorSystem::RGB;
}
CMYKSystem::CMYKSystem(QWidget *parent):colorSystem(parent, 4, {{0, 255}, {0, 255}, {0, 255}, {0, 255}}, "CMYK")
{}
ColorSystem CMYKSystem::getSystemId() const
{
    return ColorSystem::CMYK;
}
HSVSystem::HSVSystem(QWidget *parent):colorSystem(parent, 3, {{0, 360}, {0, 100}, {0, 100}}, "HSV")
{}
ColorSystem HSVSystem::getSystemId() const
{
    return ColorSystem::HSV;
}
HLSSystem::HLSSystem(QWidget *parent):colorSystem(parent, 3, {{0, 360}, {0, 100}, {0, 100}}, "HLS")
{}
ColorSystem HLSSystem::getSystemId() const
{
    return ColorSystem::HLS;
}
XYZSystem::XYZSystem(QWidget *parent):colorSystem(parent, 3, {{0, 95}, {0, 100}, {0, 109}}, "XYZ")
{}
ColorSystem XYZSystem::getSystemId() const
{
    return ColorSystem::XYZ;
}
LABSystem::LABSystem(QWidget *parent):colorSystem(parent, 3, {{0, 100}, {-128, 127}, {-128, 127}}, "LAB")
{}
ColorSystem LABSystem::getSystemId() const
{
    return ColorSystem::LAB;
}
