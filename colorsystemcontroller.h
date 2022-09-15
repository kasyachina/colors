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
    std::vector<int> fromXYZtoRGB(const std::vector<qreal>& xyzValues);
    std::vector<qreal> fromLABtoXYZ(const std::vector<int>& labValues);
    QColor mainColor;
    QWidget *colorDisplayWidget;
    QVBoxLayout *vLayout = nullptr;
    colorSystem *systems[3];
    QPalette *selectedColorPalette;
};

