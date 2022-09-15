#pragma once

#include <QWidget>
#include <QLineEdit>
#include <QLayout>
#include <colorsystemfield.h>
#include <QLabel>
#include <vector>
#include <utility>

enum class ColorSystem
{
    RGB,
    CMYK,
    HSV,
    HLS,
    XYZ,
    LAB
};

class colorSystem : public QWidget
{
    Q_OBJECT
public:
    explicit colorSystem(QWidget *parent = nullptr, int number_of_fields = 3, std::vector<std::pair<qreal, qreal>> ranges = {}, QString name = "Sample color system", int id = 0);
    void BlockAllSignals(bool block);
    virtual ColorSystem getSystemType() const = 0;
    virtual ~colorSystem();
public slots:
    void ChangeFieldValue(int newValue, int fieldId);
signals:
    void systemValueChanged(std::vector<int> new_values, int systemId);

private:
    colorSystemField *fields[4];
    int values[4];
    colorSystemField *activeBox;
    QLabel *nameLabel;
    int size;
    int systemId;
    colorSystemSlider *controlSlider;
};

class RGBSystem : public colorSystem
{
public:
    explicit RGBSystem(QWidget *parent, int id);
    ColorSystem getSystemType() const override;
};
class CMYKSystem : public colorSystem
{
public:
    explicit CMYKSystem(QWidget *parent, int id);
    ColorSystem getSystemType() const override;
};
class HSVSystem : public colorSystem
{
public:
    explicit HSVSystem(QWidget *parent, int id);
    ColorSystem getSystemType() const override;
};
class HLSSystem : public colorSystem
{
public:
    explicit HLSSystem(QWidget *parent, int id);
    ColorSystem getSystemType() const override;
};
class XYZSystem : public colorSystem
{
public:
    explicit XYZSystem(QWidget *parent, int id);
    ColorSystem getSystemType() const override;
};
class LABSystem : public colorSystem
{
public:
    explicit LABSystem(QWidget *parent, int id);
    ColorSystem getSystemType() const override;
};

