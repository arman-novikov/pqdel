#include "connectiondial.h"

ConnectionDial::ConnectionDial(QWidget *parent,
                               QString &dbnameS,
                               QString &usernameS,
                               QString &passwordS)
    : QDialog(parent)
{
    initWidgets(dbnameS, usernameS, passwordS);

    dbnamelbl->setText("database");
    usernamelbl->setText("username");
    passworsdlbl->setText("password");

    dbnamelbl->setFixedWidth(lblsFixedWidth);
    usernamelbl->setFixedWidth(lblsFixedWidth);
    passworsdlbl->setFixedWidth(lblsFixedWidth);

    connectButton->setText("connect");
    cancelButton->setText("cancel");

    dbnamelay->addWidget(dbnamelbl);
    dbnamelay->addWidget(dbname);

    usernamelay->addWidget(usernamelbl);
    usernamelay->addWidget(username);

    passwordlay->addWidget(passworsdlbl);
    passwordlay->addWidget(password);

    buttonslay->addWidget(cancelButton);
    buttonslay->addWidget(connectButton);

    mainlay->addLayout(dbnamelay);
    mainlay->addLayout(usernamelay);
    mainlay->addLayout(passwordlay);
    mainlay->addLayout(buttonslay);

    setLayout(mainlay);
    setWindowTitle("new coonection");

    setFixedSize(dialWindowWidth, dialWindowHeigth);

    totalConnect();
}

void ConnectionDial::initWidgets(QString &dbnameS,
                                 QString &usernameS,
                                 QString &passwordS)
{
    dbname = new QLineEdit(dbnameS);
    username = new QLineEdit(usernameS);
    password = new QLineEdit(passwordS);
    password->setEchoMode(QLineEdit::Password);

    dbnamelbl = new QLabel();
    usernamelbl = new QLabel();
    passworsdlbl = new QLabel();

    connectButton = new QPushButton();
    cancelButton = new QPushButton();

    dbnamelay = new QHBoxLayout();
    usernamelay = new QHBoxLayout();
    passwordlay = new QHBoxLayout();
    buttonslay = new QHBoxLayout();

    mainlay = new QVBoxLayout(this);
}

void ConnectionDial::totalConnect()
{
    connect(cancelButton, SIGNAL(clicked(bool)), this, SLOT(close()));
    connect(connectButton, SIGNAL(clicked(bool)), this, SLOT(connectClicked()));
}

void ConnectionDial::connectClicked()
{
    emit dbConnectionRequest(dbname->text(), username->text(), password->text());
    close();
}

ConnectionDial::~ConnectionDial()
{

}
