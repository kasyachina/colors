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
    CMYK
};

class colorSystem : public QWidget
{
    Q_OBJECT
public:
    explicit colorSystem(QWidget *parent = nullptr, int number_of_fields = 3, std::vector<std::pair<qreal, qreal>> ranges = {}, QString name = "Sample color system");
    virtual ColorSystem getSystemId() const = 0;
    virtual ~colorSystem();
public slots:
    void ChangeFieldValue(int newValue, int id);
signals:
    void systemValueChanged(std::vector<int> new_values);

private:
    colorSystemField *fields[4];
    int values[4];
    colorSystemField *activeBox;
    QLabel *nameLabel;
    int size;
    colorSystemSlider *controlSlider;
};

class RGBSystem : public colorSystem
{
public:
    explicit RGBSystem(QWidget *parent);
    ColorSystem getSystemId() const override;
};
class CMYKSystem : public colorSystem
{
public:
    explicit CMYKSystem(QWidget *parent);
    ColorSystem getSystemId() const override;
};

