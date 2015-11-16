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

    QGraphicsOpacityEffect* effect = new QGraphicsOpacityEffect(this);
    effect->setProperty("opacity", 0.0);
    this->setGraphicsEffect(effect);
    animation = new QPropertyAnimation(graphicsEffect(), "opacity");
    animation->setEasingCurve(QEasingCurve::InCubic);
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
    animation->setDuration(2000);
    animation->setStartValue(graphicsEffect()->property("opacity"));
    animation->setEndValue(1.0);
    animation->start();
    appearing = true;
}

void Toolbar::disappear()
{
    animation->stop();
    animation->setDuration(2000);
    animation->setStartValue(graphicsEffect()->property("opacity"));
    animation->setEndValue(0.0);
    animation->start();
}

void Toolbar::onToggleBtnClicked()
{
    if (!win->m_player->isPlaying())
        win->m_player->play();
    else
        win->m_player->pause(!win->m_player->isPaused());
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
    if (!appearing)
        appear();
}
