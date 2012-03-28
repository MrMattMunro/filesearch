/*
For general Sqliteman copyright and licensing information please refer
to the COPYING file provided with the program. Following this notice may exist
a copyright and/or license notice that predates the release of Sqliteman
for which a new license (GPL+exception) is in place.
*/
#include <QFileDialog>
#include <QMessageBox>

#include <QtDebug>
#include <QDir>
#include <QStandardItemModel>
#include <QDesktopServices>
#include <QUrl>
#include <QUuid>
#include "propoftagdialog.h"
#include "utils.h"
#include "fileutils.h"
#include "db/tagdao.h"

PropOfTagDialog::PropOfTagDialog(QWidget * parent, const QString & uuid, const QString & tagname,
           const QString & sdesp):QDialog(parent),
          m_tagUuId(uuid),
          m_tagname(tagname),
          m_desp(sdesp),
          update(false)
{
	setupUi(this);
        // Set UI
        this->setWindowIcon(Utils::getIcon("tag.ico"));
        this->setWindowTitle(tr("Properties Of Tag"));


        tagName->setText(m_tagname);
        desp->setPlainText(m_desp);


        connect(buttonBox, SIGNAL(accepted()), this, SLOT(confirmBtn_clicked()));
        connect(buttonBox,SIGNAL(rejected()),this,SLOT(cancelBtn_clicked()));
}

// 更新
void PropOfTagDialog::confirmBtn_clicked(){
    // 插入数据库
    Tag tag;
    tag.TAG_GUID = m_tagUuId;
    tag.TAG_NAME = tagName->text();
    m_tagname = tag.TAG_NAME;
    tag.TAG_DESCRIPTION = desp->toPlainText();
    m_desp = tag.TAG_NAME;
    tag.MF_VERSION = 1;

    bool success  = TagDao::updateTag(tag);
    if(success){
        update = true;
        this->close();
    }
}

// 取消按钮
void PropOfTagDialog::cancelBtn_clicked(){
     update = false;
     this->close();
}



