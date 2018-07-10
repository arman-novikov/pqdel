#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include <QMainWindow>
#include <QMenu>
#include <QAction>
#include <QSqlDatabase>

#include "connectiondial.h"

const int mainWindowWidth  = 400;
const int mainWindowHeigth = 300;

class MainWindow : public QDialog
{
    Q_OBJECT

public:
    MainWindow(QWidget *parent = 0);
    ~MainWindow();

private:
    void createMenuBar();
    void totalConnect();

    bool isConnected, wasConnectionTrial;
    QSqlDatabase db;
    qStringsVector openConnectionParams;

    ConnectionDial *dbDial;

    QHBoxLayout *hLayout, *mainLayout;
    QVBoxLayout *left, *right;

    QPushButton *dbConnectionButton;
    QLabel *dbConnectionLabel;

    QMessageBox *msgBox;

private slots:
    void dbConnectionDialogue();
    //void tryConnect(QString _dbname, QString _username, QString _password);
    void tryConnect();
};

#endif // MAINWINDOW_H
