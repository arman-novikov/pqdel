#include "mainwindow.h"

MainWindow::MainWindow(QWidget *parent)
    : QDialog(parent)
{
    isConnected = false;
    wasConnectionTrial = false;
    db = QSqlDatabase::addDatabase("QPSQL", "mydb");

    openConnectionParams =  qStringsVector(
                                {QString(""), QString(""), QString("")});

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

void MainWindow::tryConnect()
{
    db.setHostName("127.0.0.1");
    db.setDatabaseName(openConnectionParams.at(DBNAME_POSITION));
    db.setUserName(openConnectionParams.at(USERNAME_POSITION));
    db.setPassword(openConnectionParams.at(PASSWORD_POSITION));

    isConnected = db.open();
    wasConnectionTrial = true;
}

void MainWindow::dbConnectionDialogue()
{
    if(!isConnected){
        ConnectionDial *dbDial  = new ConnectionDial(this, &openConnectionParams);
        QMessageBox    *msg     = new QMessageBox(this);

        dbDial->setAttribute(Qt::WA_DeleteOnClose);
        msg->setAttribute(Qt::WA_DeleteOnClose);

        connect(dbDial, SIGNAL(dbConnectionRequest()),
                this,   SLOT(tryConnect()));
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
