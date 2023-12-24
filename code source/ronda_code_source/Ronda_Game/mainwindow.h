#ifndef MAINWINDOW_H
#define MAINWINDOW_H
#include "playwindow.h"
#include <QMainWindow>
#include "qmediaplayer.h"
#include <QMediaPlayer>//lib msc
#include <QtMultimedia>//lib msc
#include <QSoundEffect>//sound
QT_BEGIN_NAMESPACE
namespace Ui { class MainWindow; }
QT_END_NAMESPACE

class MainWindow : public QMainWindow
{
    Q_OBJECT

public:
    MainWindow(QWidget *parent = nullptr);
    ~MainWindow();

public slots:
    void on_exit_clicked();

private slots:
    void on_start_clicked();
    void on_pushButton_fullscreen_clicked();
    void on_pushButton_sound_clicked();

    void on_comboBox_currentIndexChanged(int index);


private:
    PlayWindow *playwindow;
    Ui::MainWindow *ui;
    QMediaPlayer musicPlayer;
    int lvl;
    bool soundOn;
};
#endif // MAINWINDOW_H
