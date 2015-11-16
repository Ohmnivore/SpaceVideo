#include "toolbar.h"
#include "ui_toolbar.h"

#include <QString>
#include <QFileDialog>
#include <QGraphicsEffect>
#include <QPropertyAnimation>

Toolbar::Toolbar(MainWindow *parent) :
    QWidget(parent),
    ui(new Ui::Toolbar)
{
    ui->setupUi(this);
    win = parent;

    opacity = new QGraphicsOpacityEffect(this);
    opacity->setOpacity(0);
    setGraphicsEffect(opacity);
    animation = new QPropertyAnimation(opacity, "opacity");
    animation->setEasingCurve(QEasingCurve::InCubic);
    moveTimer = new QTimer(this);
    connect(moveTimer, SIGNAL(timeout()), this, SLOT(onMouseTimerTimeout()));
    moveTimer->start(2000);
    appear();

    connect(ui->toggle, &QPushButton::clicked, this, &Toolbar::onToggleBtnClicked);
    connect(ui->fullscreen, &QPushButton::clicked, this, &Toolbar::onFullscreenBtnClicked);
    connect(ui->open, &QPushButton::clicked, this, &Toolbar::onOpenBtnClicked);
    connect(ui->sub, &QPushButton::clicked, this, &Toolbar::onSubBtnClicked);
    connect(ui->minimize, &QPushButton::clicked, this, &Toolbar::onMinimizeBtnClicked);
}

Toolbar::~Toolbar()
{
    delete ui;
}

void Toolbar::appear()
{
    animation->stop();
    animation->setDuration(1000);
    animation->setStartValue(opacity->opacity());
    animation->setEndValue(1.0);
    animation->start();
    appearing = true;
}

void Toolbar::disappear()
{
    animation->stop();
    animation->setDuration(1000);
    animation->setStartValue(opacity->opacity());
    animation->setEndValue(0.0);
    animation->start();
    appearing = false;
}

void Toolbar::onToggleBtnClicked()
{
    if (!win->m_player->isPlaying())
    {
        win->m_player->play();
        ui->toggle->setIcon(QIcon(":/images/assets/images/appbar.control.pause.png"));
    }
    else
    {
        win->m_player->pause(!win->m_player->isPaused());
        if (win->m_player->isPaused())
            ui->toggle->setIcon(QIcon(":/images/assets/images/appbar.control.play.png"));
        else
            ui->toggle->setIcon(QIcon(":/images/assets/images/appbar.control.pause.png"));
    }
}

void Toolbar::onFullscreenBtnClicked()
{
    if (win->windowState().testFlag(Qt::WindowFullScreen))
        win->showMaximized();
    else
        win->showFullScreen();
}

void Toolbar::onOpenBtnClicked()
{
    QString file = QFileDialog::getOpenFileName(0, "Open a media file");
    if (!file.isEmpty())
        win->m_player->play(file);
}

void Toolbar::onSubBtnClicked()
{
    QString file = QFileDialog::getOpenFileName(0, "Open a media file");
    if (!file.isEmpty())
        win->m_sub->setFile(file);
}

void Toolbar::onMinimizeBtnClicked()
{
    win->showMinimized();
}

void Toolbar::onMouseMove()
{
    moveTimer->start(moveTimer->interval());
    if (!appearing)
        appear();
}

void Toolbar::onMouseTimerTimeout()
{
    if (appearing)
        disappear();
}
