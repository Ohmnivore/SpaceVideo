#ifndef TOOLBAR_H
#define TOOLBAR_H

#include "mainwindow.h"
#include <QWidget>
#include <QPropertyAnimation>

namespace Ui {
class Toolbar;
}

class Toolbar : public QWidget
{
    Q_OBJECT

public:
    MainWindow* win;
    QPropertyAnimation* animation;
    bool appearing;

    explicit Toolbar(MainWindow* parent);
    ~Toolbar();
    void appear();
    void disappear();
    void onMouseMove();

public slots:
    void onToggleBtnClicked();
    void onFullscreenBtnClicked();
    void onOpenBtnClicked();
    void onSubBtnClicked();
    void onMinimizeBtnClicked();

private:
    Ui::Toolbar* ui;
};

#endif // TOOLBAR_H
