#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include <QMainWindow>
#include <QDateTime>
#include <QDebug>
#include <QFile>
#include <QFileDialog>

namespace Ui {
class MainWindow;
}

class MainWindow : public QMainWindow
{
    Q_OBJECT

public:
    explicit MainWindow(QWidget *parent = nullptr);
    ~MainWindow();

private slots:
    void on_logFilePB_clicked();
    void on_readFilePB_clicked();
private:
    void init();
    void createLogFileWithDateTime();
private:
    Ui::MainWindow *ui;
    struct aCmd{
        int msgId;
        int word0;
        int word1;
    }sACmd;
};

#endif // MAINWINDOW_H
