#ifndef CONNECTIONDIAL_H
#define CONNECTIONDIAL_H

#include <QDialog>
#include <QLineEdit>
#include <QPushButton>
#include <QLabel>
#include <QHBoxLayout>
#include <QVBoxLayout>
#include <QVector>
#include <QMessageBox>

#include <QDebug>
#include <QScopedPointer>

typedef QVector<QString> qStringsVector;

const int OPEN_CONNECTION_PARAMS_NUM = 3;
const int DBNAME_POSITION   = 0;
const int USERNAME_POSITION = 1;
const int PASSWORD_POSITION = 2;

const int lblsFixedWidth   = 75;
const int dialWindowWidth  = 300;
const int dialWindowHeigth = 150;

class ConnectionDial: public QDialog
{
    Q_OBJECT

public:
    ConnectionDial(QWidget *parent, qStringsVector *connectionParams);
    ~ConnectionDial();

signals:
    void dbConnectionRequest();

private:
    void initWidgets(qStringsVector *connectionParams);
    void totalConnect();

    QLineEdit *dbname, *username, *password;
    qStringsVector *params;
    QLabel *dbnamelbl, *usernamelbl, *passworsdlbl;
    QPushButton *connectButton, *cancelButton;
    QHBoxLayout *dbnamelay, *usernamelay, *passwordlay, *buttonslay;
    QVBoxLayout *mainlay;

private slots:
    void connectClicked();
};

#endif // CONNECTIONDIAL_H

