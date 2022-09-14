#include "colorsystemcontroller.h"

colorSystemController::colorSystemController(QWidget *parent, const std::vector<ColorSystem>& data): QWidget(parent)
{
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
            delete systems[i];
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
    }
}
colorSystemController::~colorSystemController()
{
    delete vLayout;
    for (int i = 0; i < 3; i++)
    {
        delete systems[i];
    }
}
