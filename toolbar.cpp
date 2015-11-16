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

    moveTimer = new QTimer(this);
    connect(moveTimer, SIGNAL(timeout()), this, SLOT(onMouseTimerTimeout()));
    moveTimer->start(1000);
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
    appearing = true;
    show();
}

void Toolbar::disappear()
{
    appearing = false;
    hide();
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
    {
        win->showFullScreen();
    }
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
