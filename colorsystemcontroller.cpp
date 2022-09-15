#include "colorsystemcontroller.h"
#include <QDebug>
#include <QtMath>

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
            disconnect(systems[i], &colorSystem::systemSliderActivated, this, &colorSystemController::OnSystemSliderActivated);
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
        connect(systems[i], &colorSystem::systemSliderActivated, this, &colorSystemController::OnSystemSliderActivated);
    }
    OnChangeSystemValues({255, 255, 255}, -1);
}
QColor colorSystemController::getMainColor() const
{
    return mainColor;
}
void colorSystemController::OnSystemSliderActivated(int systemId)
{
    for(int i = 0; i < 3; i++)
    {
        if (i != systemId)
        {
            systems[i] -> DisableSlider();
        }
    }
}
std::vector<qreal> colorSystemController::fromRGBtoXYZ(const std::vector<int> &rgbValues)
{
    qreal R = rgbValues[0], G = rgbValues[1], B = rgbValues[2];
    auto F = [](qreal x)
    {
      if (x > 0.04045)
      {
          return qPow((x + 0.055) / 1.055, 2.4);
      }
      else return x / 12.92;
    };
    qreal Rn = F(R / 255) * 100, Gn = F(G / 255) * 100, Bn = F(B / 255) * 100;
    qreal X, Y, Z;
    X = 0.412453 * Rn + 0.357580 * Gn + 0.180423 * Bn;
    Y = 0.212671 * Rn + 0.715160 * Gn + 0.072169 * Bn;
    Z = 0.019334 * Rn + 0.119193 * Gn + 0.950227 * Bn;
    return {X, Y, Z};
}
std::vector<int> colorSystemController::fromXYZtoRGB(const std::vector<qreal> &xyzValues)
{
    qreal X = xyzValues[0] / 100, Y = xyzValues[1] / 100, Z = xyzValues[2] / 100;
    auto F = [](qreal x)
    {
      if (x > 0.0031308)
      {
          return qPow(x, 1 / 2.4) * 1.055 - 0.055;
      }
      else return x * 12.92;
    };
    qreal Rn = 3.2406 * X - 1.5372 * Y - 0.4986 * Z;
    qreal Gn = -0.9689 * X + 1.8758 * Y + 0.0415 * Z;
    qreal Bn = 0.0557 * X - 0.2040 * Y + 1.0570 * Z;
    qreal R = F(Rn) * 255, G = F(Gn) * 255, B = F(Bn) * 255;
    return {(int)R, (int)G, (int)B};
}
std::vector<qreal> colorSystemController::fromLABtoXYZ(const std::vector<int>& labValues)
{
    qreal L = labValues[0], A = labValues[1], B = labValues[2];
    auto F = [](qreal x)
    {
        if (x * x * x >= 0.008856)
        {
            return x * x * x;
        }
        else
        {
            return (x - 16.0 / 116) / 7.787;
        }
    };
    qreal Xw = 95.047, Yw = 100, Zw = 108.883;
    qreal X, Y, Z;
    X = F(A / 500 + (L + 16) / 116) * Yw;
    Y = F((L + 16) / 116) * Xw;
    Z = F((L + 16) / 116 - B / 200) * Zw;
    return {X, Y, Z};
}
std::vector<int> colorSystemController::fromXYZtoLAB(const std::vector<qreal>& xyzValues)
{
    qreal X = xyzValues[0], Y = xyzValues[1], Z = xyzValues[2];
    auto F = [](qreal x)
    {
        if (qPow(x, 1.0 / 3) >= 0.008856)
        {
            return qPow(x, 1.0 / 3);
        }
        else
        {
            return 7.787 * x + 16.0 / 116;
        }
    };
    qreal Xw = 95.047, Yw = 100, Zw = 108.883;
    qreal L, A, B;
    L = 116 * F(Y / Yw) - 16;
    A = 500 * (F(X / Xw) - F(Y / Yw));
    B = 200 * (F(Y / Yw) - F(Z / Zw));
    return {(int)L, (int)A, (int)B};
}
void colorSystemController::OnChangeSystemValues(const std::vector<int>& newValues, int systemId)
{
    QColor newColor;
    if (systemId != -1)
    {
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
        {
            auto rgbValues = fromXYZtoRGB({(qreal)newValues[0], (qreal)newValues[1], (qreal)newValues[2]});
            newColor.setRgb(rgbValues[0], rgbValues[1], rgbValues[2]);
            break;
        }
        case ColorSystem::LAB:
        {
            auto xyzValues = fromLABtoXYZ(newValues);
            auto rgbValues = fromXYZtoRGB(xyzValues);
            newColor.setRgb(rgbValues[0], rgbValues[1], rgbValues[2]);
            break;
        }
        }
    }
    else
    {
        newColor.setRgb(newValues[0], newValues[1], newValues[2]);
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
            {
                auto rgbValues = {newColor.red(), newColor.green(), newColor.blue()};
                auto xyzValues = fromRGBtoXYZ(rgbValues);
                currentSystem -> ChangeFieldValue((int)xyzValues[0], 0);
                currentSystem -> ChangeFieldValue((int)xyzValues[1], 1);
                currentSystem -> ChangeFieldValue((int)xyzValues[2], 2);
                //fromRGBtoXyz func
                break;
            }
            case ColorSystem::LAB:
            {
                auto rgbValues = {newColor.red(), newColor.green(), newColor.blue()};
                auto xyzValues = fromRGBtoXYZ(rgbValues);
                auto labValues = fromXYZtoLAB(xyzValues);
                currentSystem -> ChangeFieldValue((int)labValues[0], 0);
                currentSystem -> ChangeFieldValue((int)labValues[1], 1);
                currentSystem -> ChangeFieldValue((int)labValues[2], 2);
                //fromRGBtoXYZ func + fromXYZtoLAB func
                break;
            }
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
