#include "colorsystemcontroller.h"
#include <QDebug>

colorSystemController::colorSystemController(QWidget *parent, const std::vector<ColorSystem>& data, QWidget *displayWidget):
    QWidget(parent), colorDisplayWidget(displayWidget)
{
    selectedColorPalette = new QPalette;
    setMainColor(Qt::white);
    vLayout = nullptr;
    for (int i = 0; i < 3; i++)
    {
        systems[i] = nullptr;
    }
    ChangeSystems(data);
    OnChangeSystemValues({0, 0, 0}, 0);
}
void colorSystemController::ChangeSystems(const std::vector<ColorSystem>& data)
{
    if (vLayout)
        delete vLayout;
    vLayout = new QVBoxLayout(this);
    for (int i = 0; i < 3; i++)
    {
        if (systems[i])
        {
            delete systems[i];
            disconnect(systems[i], &colorSystem::systemValueChanged, this, &colorSystemController::OnChangeSystemValues);
        }
        switch (data[i])
        {
            case ColorSystem::RGB:
                systems[i] = new RGBSystem(this, i);
            break;
            case ColorSystem::CMYK:
                systems[i] = new CMYKSystem(this, i);
            break;
            case ColorSystem::HSV:
                systems[i] = new HSVSystem(this, i);
            break;
            case ColorSystem::HLS:
                systems[i] = new HLSSystem(this, i);
            break;
            case ColorSystem::XYZ:
                systems[i] = new XYZSystem(this, i);
            break;
            case ColorSystem::LAB:
                systems[i] = new LABSystem(this, i);
        }
        vLayout->addWidget(systems[i]);
        connect(systems[i], &colorSystem::systemValueChanged, this, &colorSystemController::OnChangeSystemValues);
    }
}
QColor colorSystemController::getMainColor() const
{
    return mainColor;
}
void colorSystemController::OnChangeSystemValues(const std::vector<int>& newValues, int systemId)
{
    QColor newColor;
    switch (systems[systemId]->getSystemType())
    {
    case ColorSystem::RGB:
        newColor.setRgb(newValues[0], newValues[1], newValues[2]);
        break;
    case ColorSystem::CMYK:
        newColor.setCmyk(newValues[0], newValues[1], newValues[2], newValues[3]);
        break;
    case ColorSystem::HLS:
        newColor.setHsl(newValues[0], newValues[1], newValues[2]);
        break;
    case ColorSystem::HSV:
        newColor.setHsv(newValues[0], newValues[1], newValues[2]);
        break;
    case ColorSystem::XYZ:
        //fromXYZtoRGB func
        break;
    case ColorSystem::LAB:
        //fromLABtoXYZ func + fromXYZtoRGB func
        break;
    }
    for (int i = 0; i < 3; i++)
    {
        if (i != systemId)
        {
            colorSystem *currentSystem = systems[i];
            currentSystem->BlockAllSignals(true);
            switch (currentSystem->getSystemType())
            {
            case ColorSystem::RGB:
                currentSystem -> ChangeFieldValue(newColor.red(), 0);
                currentSystem -> ChangeFieldValue(newColor.green(), 1);
                currentSystem -> ChangeFieldValue(newColor.blue(), 2);
                break;
            case ColorSystem::CMYK:
                currentSystem -> ChangeFieldValue(newColor.cyan(), 0);
                currentSystem -> ChangeFieldValue(newColor.magenta(), 1);
                currentSystem -> ChangeFieldValue(newColor.yellow(), 2);
                currentSystem -> ChangeFieldValue(newColor.black(), 3);
                break;
            case ColorSystem::HLS:
                currentSystem -> ChangeFieldValue(newColor.hslHue(), 0);
                currentSystem -> ChangeFieldValue(newColor.lightness(), 1);
                currentSystem -> ChangeFieldValue(newColor.hslSaturation(), 2);
                break;
            case ColorSystem::HSV:
                currentSystem -> ChangeFieldValue(newColor.hue(), 0);
                currentSystem -> ChangeFieldValue(newColor.saturation(), 1);
                currentSystem -> ChangeFieldValue(newColor.value(), 2);
                break;
            case ColorSystem::XYZ:
                //fromRGBtoXYZ func
                break;
            case ColorSystem::LAB:
                //fromRGBtoXYZ func + fromXYZtoLAB func
                break;
            }
            currentSystem->BlockAllSignals(false);
        }
    }
    setMainColor(newColor);
}
void colorSystemController::setMainColor(const QColor &newColor)
{
    mainColor = newColor;
    selectedColorPalette -> setColor(QPalette::Window, mainColor);
    colorDisplayWidget -> setPalette(*selectedColorPalette);
}
colorSystemController::~colorSystemController()
{
    delete vLayout;
    for (int i = 0; i < 3; i++)
    {
        delete systems[i];
    }
    delete selectedColorPalette;
}
