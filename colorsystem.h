#pragma once

#include <QWidget>
#include <QLineEdit>
#include <QLayout>
#include <colorsystemfield.h>
#include <QLabel>
#include <vector>
#include <utility>

class colorSystem : public QWidget
{
    Q_OBJECT
public:
    explicit colorSystem(QWidget *parent = nullptr, int number_of_fields = 3, std::vector<std::pair<qreal, qreal>> ranges = {});
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

