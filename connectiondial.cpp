#include "connectiondial.h"

ConnectionDial::ConnectionDial(QWidget *parent, qStringsVector *connectionParams)
    : QDialog(parent)
{
    initWidgets(connectionParams);
    params = connectionParams;

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

void ConnectionDial::initWidgets(qStringsVector *connectionParams)
{
    dbname = new QLineEdit(connectionParams->at(DBNAME_POSITION));
    username = new QLineEdit(connectionParams->at(USERNAME_POSITION));
    password = new QLineEdit(connectionParams->at(PASSWORD_POSITION));
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
    if (dbname->text().isEmpty()   ||
        username->text().isEmpty() ||
        password->text().isEmpty()) {

        QMessageBox *msg = new QMessageBox(this);
        msg->setAttribute(Qt::WA_DeleteOnClose);
        msg->setText("fill data fields");
        msg->exec();
        return;
    }

    params->replace(DBNAME_POSITION, dbname->text());
    params->replace(USERNAME_POSITION, username->text());
    params->replace(PASSWORD_POSITION, password->text());
    emit dbConnectionRequest();
    close();
}

ConnectionDial::~ConnectionDial()
{

}
