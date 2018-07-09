#include "mainwindow.h"

MainWindow::MainWindow(QWidget *parent)
    : QDialog(parent)
{
    isConnected = false;
    wasConnectionTrial = false;
    db = QSqlDatabase::addDatabase("QPSQL", "mydb");

    dbConnectionButton  = new QPushButton("new connection");
    dbConnectionLabel   = new QLabel("not connected");

    hLayout = new QHBoxLayout();
    hLayout->addWidget(dbConnectionLabel);
    hLayout->addWidget(dbConnectionButton);

    left = new QVBoxLayout();
    left->addLayout(hLayout);

    mainLayout = new QHBoxLayout(this);
    mainLayout->addLayout(left);

    this->totalConnect();
    this->setLayout(mainLayout);
    this->setWindowTitle("PSQL deleter");
    this->setFixedSize(mainWindowWidth, mainWindowHeigth);
}

void MainWindow::totalConnect()
{
    connect(this->dbConnectionButton, SIGNAL(clicked(bool)),
            this,                     SLOT(dbConnectionDialogue()));
}

void MainWindow::tryConnect(QString _dbname, QString _username, QString _password)
{
    dbname = QString(_dbname);
    username = QString(_username);
    password = QString(_password);

    db.setHostName("127.0.0.1");
    db.setDatabaseName(dbname);
    db.setUserName(username);
    db.setPassword(password);

    isConnected = db.open();
    wasConnectionTrial = true;
}

void MainWindow::dbConnectionDialogue()
{
    if(!isConnected){
        ConnectionDial *dbDial  = new ConnectionDial(this, dbname, username, password);
        QMessageBox    *msg     = new QMessageBox(this);

        connect(dbDial, SIGNAL(dbConnectionRequest(QString, QString, QString)),
                this,   SLOT(tryConnect(QString, QString, QString)));

        dbDial->exec();

        if (isConnected) {
            msg->setText("connection successful");
            msg->exec();
            dbConnectionLabel->setText("connected");
            dbConnectionButton->setText("disconnect");
        } else if (wasConnectionTrial) {
            msg->setText("connection failed");
            msg->exec();
        }

    } else {
        db.close();
        isConnected = false;
        dbConnectionLabel->setText("not connected");
        dbConnectionButton->setText("new connection");
    }

    wasConnectionTrial = false; //restore default settings
}

MainWindow::~MainWindow()
{
    db.close();
}
