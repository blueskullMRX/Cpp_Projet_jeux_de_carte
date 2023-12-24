#include "mainwindow.h"
#include "ui_mainwindow.h"
#include "playwindow.h"

MainWindow::MainWindow(QWidget *parent)
    : QMainWindow(parent)
    , ui(new Ui::MainWindow)
{
    ui->setupUi(this);
    setWindowTitle("Ronda Beta V0.4"); //set title
    //music bloc
    musicPlayer.setSource(QUrl("qrc:/audio/audio/AITA_2.0.mp3"));
    QAudioOutput* audioOutput = new QAudioOutput(this);
    audioOutput->setVolume(0.3);
    musicPlayer.setAudioOutput(audioOutput);
    musicPlayer.play();
    soundOn=true;
    lvl=0;
}

MainWindow::~MainWindow()
{
    delete ui;
}


void MainWindow::on_exit_clicked()
{
    QApplication::quit();
}


void MainWindow::on_start_clicked()
{   musicPlayer.stop();
    playwindow = new PlayWindow;
    playwindow->difficulty = lvl;
    playwindow->show();//show the game window
    playwindow->startgame();//call the game to start
}
void MainWindow::on_pushButton_fullscreen_clicked()
{if (isFullScreen()) {
        showNormal();


    } else {
        showFullScreen();
    }
    QPixmap bkgnd(":/backgrounds/imgs/best_psd_1.png");
    bkgnd = bkgnd.scaled(this->size(), Qt::IgnoreAspectRatio);

    QPalette palette;
    palette.setBrush(QPalette::Window, bkgnd);

    this->setPalette(palette);
}
void MainWindow::on_pushButton_sound_clicked()
{
    soundOn = !soundOn; // Toggle the state

    if (soundOn)
    {
        musicPlayer.play();
        ui->pushButton_sound->setStyleSheet("background-color: none;");
        ui->pushButton_sound->setIcon(QIcon(":/backgrounds/imgs/btns/volume-up.png"));

    }
    else
    {
        musicPlayer.pause();
        ui->pushButton_sound->setStyleSheet("background-color: gold;");
        ui->pushButton_sound->setIcon(QIcon(":/backgrounds/imgs/btns/mute.png"));

    }
}

void MainWindow::on_comboBox_currentIndexChanged(int index)
{
    lvl=index;

}

