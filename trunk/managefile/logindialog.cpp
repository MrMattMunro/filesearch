#include <QFileDialog>
#include <QMessageBox>

#include <QtDebug>
#include <QDir>
#include <QUuid>
#include <QStandardItemModel>
#include <QDateTime>

#include "logindialog.h"
#include "preferences.h"
#include "utils.h"
#include "db/docdao.h"
#include "db/dirdao.h"

// µ«¬ºΩÁ√Ê
LoginDialog::LoginDialog(QWidget * parent)
        : QDialog(parent),
          update(false)
{
	setupUi(this);

        connect(loginBtn, SIGNAL(clicked()), this, SLOT(loginBtn_clicked()));
        connect(registerBtn, SIGNAL(clicked()), this, SLOT(registerBtn_clicked()));
        connect(resetBtn, SIGNAL(clicked()), this, SLOT(resetBtn_clicked()));

        this->setWindowIcon(Utils::getIcon("file_manager.png"));
        this->setWindowTitle(tr("Slfile"));
        tabWidget->setCurrentIndex(0);

}

// µ«¬º
void LoginDialog::loginBtn_clicked()
{

    update = true;
    this->close();
}

// ◊¢≤·
void LoginDialog::registerBtn_clicked()
{

    update = true;
    this->close();
}

// ÷ÿ÷√
void LoginDialog::resetBtn_clicked(){


}


