#ifndef DIGITALFILTERS_H
#define DIGITALFILTERS_H

#include <QWidget>

namespace Ui {
class DigitalFilters;
}

class DigitalFilters : public QWidget
{
    Q_OBJECT

public:
    explicit DigitalFilters(QWidget *parent = 0);
    ~DigitalFilters();

private:
    Ui::DigitalFilters *ui;
};

#endif // DIGITALFILTERS_H
