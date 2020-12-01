#ifndef WIDGET_H
#define WIDGET_H

#include <QWidget>
#include "game.h"
#include "field.h"

QT_BEGIN_NAMESPACE
namespace Ui { class Widget; }
QT_END_NAMESPACE

class Widget : public QWidget
{
    Q_OBJECT

public:
    Widget(QWidget *parent = nullptr);
    ~Widget();


private slots:
void load_clicked();

private:
    Ui::Widget *ui;
    field *Field_;

};
#endif // WIDGET_H
