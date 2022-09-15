#include "widget.h"
#include "ui_widget.h"
#include <QPalette>
#include <QColorDialog>
#include <QDebug>

Widget::Widget(QWidget *parent)
    : QWidget(parent)
    , ui(new Ui::Widget)
{
    ui->setupUi(this);

    ui -> colorShowcase -> setAutoFillBackground(true);

    QHBoxLayout *h = new QHBoxLayout(this);
    QVBoxLayout *vr = new QVBoxLayout;

    controller = new colorSystemController(this, {ColorSystem::RGB, ColorSystem::LAB, ColorSystem::CMYK}, ui -> colorShowcase);
    normalSize = QSize(570, 270);
    ui -> selectModel -> setCurrentIndex(0);
    vr -> addWidget(ui -> selectModel);
    vr -> addWidget(ui -> colorShowcase);
    vr -> addWidget(ui -> chooseColorButton);
    h -> addWidget(controller);
    h -> addLayout(vr);
    setWindowTitle("Color systems");
    resize(normalSize);
}

Widget::~Widget()
{
    delete ui;
    delete controller;
}

void Widget::on_chooseColorButton_clicked()
{
    QColor color = QColorDialog::getColor(controller -> getMainColor());
    if (color.isValid())
    {
        controller -> setMainColor(color);
    }
}

void Widget::on_selectModel_currentTextChanged(const QString &arg1)
{
    auto parts = arg1.split(" <-> ");
    std::vector<ColorSystem> v;
    for (const auto& x : parts)
    {
        if (x == "RGB")
        {
            v.push_back(ColorSystem::RGB);
        }
        if (x == "CMYK")
        {
            v.push_back(ColorSystem::CMYK);
        }
        if (x == "HLS")
        {
            v.push_back(ColorSystem::HLS);
        }
        if (x == "HSV")
        {
            v.push_back(ColorSystem::HSV);
        }
        if (x == "LAB")
        {
            v.push_back(ColorSystem::LAB);
        }
        if (x == "XYZ")
        {
            v.push_back(ColorSystem::XYZ);
        }
    }
    controller->ChangeSystems(v);
    resize(normalSize);
}
