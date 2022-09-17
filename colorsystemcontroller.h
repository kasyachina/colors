#pragma once
#include "colorsystem.h"
#include <QBoxLayout>

class colorSystemController : public QWidget
{
    Q_OBJECT
public:
    colorSystemController(QWidget *parent, const std::vector<ColorSystem>& data, QWidget *displayWidget);
    QColor getMainColor() const;
    void setMainColor(const QColor& newColor);
    void ChangeSystems(const std::vector<ColorSystem>& data);
    ~colorSystemController();
public slots:
    void OnChangeSystemValues(const std::vector<int>& newValues, int systemId);
    void OnSystemSliderActivated(int systemId);
private:
    std::vector<qreal> fromXYZtoRGB(const std::vector<qreal>& xyzValues);
    std::vector<qreal> fromRGBtoXYZ(const std::vector<qreal>& rgbValues);
    std::vector<qreal> fromLABtoXYZ(const std::vector<qreal>& labValues);
    std::vector<qreal> fromXYZtoLAB(const std::vector<qreal>& xyzValues);
    QColor mainColor;
    QWidget *colorDisplayWidget;
    QVBoxLayout *vLayout = nullptr;
    colorSystem *systems[3];
    QPalette *selectedColorPalette;
};

