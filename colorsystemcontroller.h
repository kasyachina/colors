#pragma once
#include "colorsystem.h"
#include <QBoxLayout>

class colorSystemController : public QWidget
{
    Q_OBJECT
public:
    colorSystemController(QWidget *parent, const std::vector<ColorSystem>& data);
    void ChangeSystems(const std::vector<ColorSystem>& data);
    ~colorSystemController();
signals:

private:
    QVBoxLayout *vLayout = nullptr;
    colorSystem *systems[3];
};

