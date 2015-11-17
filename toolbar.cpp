#include "toolbar.h"
#include "ui_toolbar.h"
#include "options.h"

#include <QString>
#include <QFileDialog>
#include <VLCQtCore/Enums.h>
#include <VLCQtCore/Media.h>
#include <VLCQtCore/Video.h>
#include <VLCQtCore/Audio.h>

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

    updateTimer = new QTimer(this);
    connect(updateTimer, SIGNAL(timeout()), this, SLOT(onUpdateTimerTimeout()));
    updateTimer->start(250);

    connect(ui->toggle, &QPushButton::clicked, this, &Toolbar::onToggleBtnClicked);
    connect(ui->fullscreen, &QPushButton::clicked, this, &Toolbar::onFullscreenBtnClicked);
    connect(ui->open, &QPushButton::clicked, this, &Toolbar::onOpenBtnClicked);
    connect(ui->sub, &QPushButton::clicked, this, &Toolbar::onSubBtnClicked);
    connect(ui->options, &QPushButton::clicked, this, &Toolbar::onOptionsBtnClicked);
    connect(ui->minimize, &QPushButton::clicked, this, &Toolbar::onMinimizeBtnClicked);
    connect(ui->VolumeSlider, SIGNAL(valueChanged(int)), this, SLOT(onVSliderChanged(int)));
    connect(ui->TrackSlider, SIGNAL(sliderReleased()), this, SLOT(onHSliderChanged()));
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
    win->setCursor(Qt::BlankCursor);
}

void Toolbar::onToggleBtnClicked()
{
    win->m_player->togglePause();
    if (win->m_player->state() == Vlc::Playing)
    {
        ui->toggle->setIcon(QIcon(":/images/assets/images/appbar.control.play.png"));
    }
    else
    {
        ui->toggle->setIcon(QIcon(":/images/assets/images/appbar.control.pause.png"));
    }
}

void Toolbar::maximize()
{
    win->showMaximized();
    appear();
}
void Toolbar::fullscreen()
{
    win->showFullScreen();
    appear();
}
void Toolbar::onFullscreenBtnClicked()
{
    hide();
    if (win->windowState().testFlag(Qt::WindowFullScreen))
        QTimer::singleShot(0, this, SLOT(maximize()));
    else
        QTimer::singleShot(0, this, SLOT(fullscreen()));
}

void Toolbar::onOpenBtnClicked()
{
    QString file = QFileDialog::getOpenFileName(this, "Open file", QString(), "Multimedia files(*)");
    if (file.isEmpty())
        return;
    VlcMedia* _media = new VlcMedia(file, true, win->m_inst);
    win->m_player->open(_media);
    ui->toggle->setIcon(QIcon(":/images/assets/images/appbar.control.pause.png"));

    ui->toggle->setEnabled(true);
    ui->VolumeSlider->setEnabled(true);
    ui->TrackSlider->setEnabled(true);
    win->m_opt->setEnabled(true);

    QTimer::singleShot(3000, win->m_opt, SLOT(updateVideo()));
    QTimer::singleShot(3000, win->m_opt, SLOT(updateAudio()));
    QTimer::singleShot(3000, win->m_opt, SLOT(updateSubtitles()));
}

void Toolbar::onSubBtnClicked()
{
    QString file = QFileDialog::getOpenFileName(this, "Open file", QString(), "Subtitle files(*)");
    if (file.isEmpty())
        return;
    win->m_player->video()->setSubtitleFile(file);
    QTimer::singleShot(3000, win->m_opt, SLOT(updateSubtitles()));
}

void Toolbar::onOptionsBtnClicked()
{
    if (win->m_opt->isHidden())
        win->m_opt->show();
    else
        win->m_opt->hide();
}

void Toolbar::minimize()
{
    win->showMinimized();
    appear();
}
void Toolbar::onMinimizeBtnClicked()
{
    hide();
    QTimer::singleShot(0, this, SLOT(minimize()));
}

void Toolbar::onVSliderChanged(int value)
{
    win->m_player->audio()->setVolume(value);
}

void Toolbar::onHSliderChanged()
{
    win->m_player->setPosition(ui->TrackSlider->value() / (float)ui->TrackSlider->maximum());
}

void Toolbar::onMouseMove()
{
    moveTimer->start(moveTimer->interval());
    if (!appearing)
        appear();
    win->setCursor(Qt::ArrowCursor);
}

void Toolbar::onMouseTimerTimeout()
{
    if (appearing)
        disappear();
}

void Toolbar::onUpdateTimerTimeout()
{
    if (!ui->TrackSlider->isSliderDown())
        ui->TrackSlider->setValue(win->m_player->position() * ui->TrackSlider->maximum());
}
