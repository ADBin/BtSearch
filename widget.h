#ifndef WIDGET_H
#define WIDGET_H

#include <QWidget>
#include "spider.h"

namespace Ui {
class Widget;
}

class Widget : public QWidget
{
    Q_OBJECT

public:
    explicit Widget(QWidget *parent = 0);
    ~Widget();

    spider a;

    void btkitty(QString);
    void btkittyBt(QString);
    void alicili(QString);
    void aliciliBt(QString);

private slots:
    void btSearch();

private:
    Ui::Widget *ui;
};

#endif // WIDGET_H
