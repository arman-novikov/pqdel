#ifndef CONNECTIONDIAL_H
#define CONNECTIONDIAL_H

#include <QDialog>
#include <QLineEdit>
#include <QPushButton>
#include <QLabel>
#include <QHBoxLayout>
#include <QVBoxLayout>

const int lblsFixedWidth   = 75;
const int dialWindowWidth  = 300;
const int dialWindowHeigth = 150;

class ConnectionDial: public QDialog
{
    Q_OBJECT

public:
    ConnectionDial(QWidget *parent,
                   QString &dbname,
                   QString &username,
                   QString &password);
    ~ConnectionDial();

signals:
    void dbConnectionRequest(QString dbname, QString username, QString password);

private:
    void initWidgets(QString &dbname, QString &username, QString &password);
    void totalConnect();
    QLineEdit *dbname, *username, *password;
    QLabel *dbnamelbl, *usernamelbl, *passworsdlbl;
    QPushButton *connectButton, *cancelButton;
    QHBoxLayout *dbnamelay, *usernamelay, *passwordlay, *buttonslay;
    QVBoxLayout *mainlay;

private slots:
    void connectClicked();
};

#endif // CONNECTIONDIAL_H

