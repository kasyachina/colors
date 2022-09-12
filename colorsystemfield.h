#pragma once

#include <QWidget>
#include <QSlider>
#include <QLineEdit>
#include <QValidator>
#include <QMessageBox>

class colorSystemField;

class colorSystemSlider : public QSlider
{
    Q_OBJECT
public:
    explicit colorSystemSlider(QWidget *parent = nullptr);
    void ChangeActiveField(colorSystemField *new_field);
    void ClearActiveField();
    colorSystemField* GetActiveField() const;
    virtual ~colorSystemSlider(){}
public slots:
    void ActiveFieldValueChanged();
private:
    colorSystemField *activeField = nullptr;
};

class colorSystemField : public QLineEdit
{
    Q_OBJECT
public:
    explicit colorSystemField(QWidget *parent = nullptr, colorSystemSlider *control_slider = nullptr, int _left = 0, int _right = 100, int _id = 0);
    int getValue() const;
    virtual ~colorSystemField(){}
public slots:
    void EnterPressed();
    void ChangeValue(int newValue);
    void ChangeValueText(const QString& newValue);
signals:
    void valueChanged(int newValue, int fieldId);
private:
    int id;
    int leftThreshold, rightThreshold;
    void setActive();
    int value;
    colorSystemSlider *slider;
    void mousePressEvent(QMouseEvent *) override;
};

