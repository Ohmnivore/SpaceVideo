#include "options.h"
#include "ui_options.h"

#include <QDebug>

#include <VLCQtCore/Audio.h>
#include <VLCQtCore/Video.h>

Options::Options(MainWindow* parent) :
    QWidget(parent),
    ui(new Ui::Options)
{
    ui->setupUi(this);
    win = parent;

    connect(ui->videoBox, SIGNAL(activated(int)), this, SLOT(videoSet(int)));
    connect(ui->audioBox, SIGNAL(activated(int)), this, SLOT(audioSet(int)));
    connect(ui->subtitleBox, SIGNAL(activated(int)), this, SLOT(subtitleSet(int)));
}

Options::~Options()
{
    delete ui;
}

void Options::updateVideo()
{
    ui->videoBox->clear();
    if (win->m_player->video()->track() > 0)
    {
        qDebug() << win->m_player->video()->trackDescription();
        qDebug() << win->m_player->video()->trackIds();
        qDebug() << win->m_player->video()->track();

        QStringList descr = win->m_player->video()->trackDescription();
        QList<int> id = win->m_player->video()->trackIds();
        for (int i = 0; i < descr.size(); ++i)
            ui->videoBox->addItem(descr.at(i), id.at(i));
        ui->videoBox->setCurrentIndex(id.indexOf(win->m_player->video()->track()));
    }
}

void Options::updateAudio()
{
    ui->audioBox->clear();
    if (win->m_player->audio()->track() > 0)
    {
        qDebug() << win->m_player->audio()->trackDescription();
        qDebug() << win->m_player->audio()->trackIds();
        qDebug() << win->m_player->audio()->track();

        QStringList descr = win->m_player->audio()->trackDescription();
        QList<int> id = win->m_player->audio()->trackIds();
        for (int i = 0; i < descr.size(); ++i)
            ui->audioBox->addItem(descr.at(i), id.at(i));
        ui->audioBox->setCurrentIndex(id.indexOf(win->m_player->audio()->track()));
    }
}

void Options::updateSubtitles()
{
    ui->subtitleBox->clear();
    if (win->m_player->video()->subtitle() > 0)
    {
        qDebug() << win->m_player->video()->subtitleDescription();
        qDebug() << win->m_player->video()->subtitleIds();
        qDebug() << win->m_player->video()->subtitle();

        QStringList descr = win->m_player->video()->subtitleDescription();
        QList<int> id = win->m_player->video()->subtitleIds();
        for (int i = 0; i < descr.size(); ++i)
            ui->subtitleBox->addItem(descr.at(i), id.at(i));
        ui->subtitleBox->setCurrentIndex(id.indexOf(win->m_player->video()->subtitle()));
    }
}

void Options::videoSet(int id)
{
    int track = ui->videoBox->itemData(id).toInt();
    win->m_player->video()->setTrack(track);
}

void Options::audioSet(int id)
{
    int track = ui->audioBox->itemData(id).toInt();
    win->m_player->audio()->setTrack(track);
}

void Options::subtitleSet(int id)
{
    int track = ui->subtitleBox->itemData(id).toInt();
    win->m_player->video()->setSubtitle(track);
}
