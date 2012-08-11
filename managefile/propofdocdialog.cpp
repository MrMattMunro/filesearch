#include "propofdocdialog.h"

#include <QDir>
#include <QMessageBox>
#include "db/docdao.h"
#include "db/dirdao.h"
#include "db/relatedocdao.h"

PropOfDocDialog::PropOfDocDialog (QWidget *parent, const QString & curUuid)
    : QDialog(parent), m_curUuid(curUuid),update(false)
{
    setupUi(this);

    // 取得当前文档
    Doc doc = DocDao::selectDoc(m_curUuid);
    this->setWindowTitle(doc.DOCUMENT_NAME +" - " +tr ("Property Editor","Window caption"));


    // 设置基本信息
    title->setText(doc.DOCUMENT_NAME);
    url->setText(doc.DOCUMENT_URL);
    uuid->setText(doc.DOCUMENT_GUID);
    keywords->setText(doc.DOCUMENT_KEYWORDS);

    QList<Dir> dirList;
    DirDao::selectAllParentDirbyDir(dirList, doc.DIR_GUID);

    QString sopplocation;
    sopplocation.append(QDir::separator());
    for (int var = dirList.length() - 1; var >= 0 ; --var) {
        Dir dir = dirList.at(var);
        sopplocation.append(dir.DIR_NAME);
        sopplocation.append(QDir::separator());
    }

    opplocation->setText(sopplocation);
    location->setText(doc.DOCUMENT_LOCATION);

    // 设置时间
    QString dtCreated = doc.DT_CREATED;
    QString dtModified = doc.DT_MODIFIED;
    QString dtAccessd = doc.DT_ACCESSED;
    // 2012-02-06 11:18:48
    QDateTime created = QDateTime::fromString(dtCreated,"yyyy-MM-dd hh:mm:ss");
    QDateTime modified = QDateTime::fromString(dtModified,"yyyy-MM-dd hh:mm:ss");
    QDateTime accessd = QDateTime::fromString(dtAccessd,"yyyy-MM-dd hh:mm:ss");

    createday->setDate(created.date());
    createtime->setTime(created.time());

    modifyday->setDate(modified.date());
    modifytime->setTime(modified.time());

    accessday->setDate(accessd.date());
    accesstime->setTime(accessd.time());

    // 列表
    model = new QStandardItemModel();
    // 新建Model
    model->setColumnCount(4);
    model->setHeaderData(0,Qt::Horizontal,tr("Author"));
    model->setHeaderData(1,Qt::Horizontal,tr("FileName"));
    model->setHeaderData(2,Qt::Horizontal,tr("Date"));
    model->setHeaderData(3,Qt::Horizontal,tr("relateDocUid"));

    // 设置被其他关联的文档
    QList<RelateDoc> relateDocs = RelateDocDao::selectRelatedDocsByRel(doc.DOCUMENT_GUID);
    for (int var = 0; var < relateDocs.length() ; var ++ ) {
        RelateDoc relatedoc = relateDocs.at(var);
        Doc doc = DocDao::selectDoc(relatedoc.DOCUMENT_GUID);

        QStandardItem* author = new QStandardItem(doc.DOCUMENT_AUTHOR);
        QStandardItem* filename = new QStandardItem(doc.DOCUMENT_NAME);
        QStandardItem* accdate = new QStandardItem(doc.DT_ACCESSED);
        QStandardItem* docUuId = new QStandardItem(doc.DOCUMENT_GUID);

        QList<QStandardItem*> items;
        items << author ;
        items << filename;
        items << accdate;
        items << docUuId;

        model->appendRow(items);
    }
    relatedDocs->setModel(model);
    relatedDocs->setSelectionBehavior(QAbstractItemView::SelectRows);
    relatedDocs->hideColumn(3);
    relatedDocs->resizeColumnsToContents();

    // 设置其他
    author->setText(doc.DOCUMENT_AUTHOR);
    owner->setText(doc.DOCUMENT_OWNER);
    readcount->setText(QString::number(doc.DOCUMENT_READ_COUNT));
    relatedcount->setText(QString::number(relateDocs.size()));
    version->setText(QString::number(doc.MF_VERSION));

    // 设置不可更改项
    url->setReadOnly(true);
    uuid->setReadOnly(true);
    opplocation->setReadOnly(true);
    location->setReadOnly(true);
    readcount->setReadOnly(true);
    relatedcount->setReadOnly(true);
    version->setReadOnly(true);
    title->setReadOnly(true);

    connect(closeBtn,SIGNAL(clicked()),this, SLOT(closeBtn_clicked()));
    connect(applyBtn,SIGNAL(clicked()),this, SLOT(applyBtn_clicked()));

    // 默认选中第一个tab
    tabWidget->setCurrentIndex(0);

}
// 更新数据项
void PropOfDocDialog::applyBtn_clicked()
{
    Doc doc = DocDao::selectDoc(m_curUuid);
    // 更新数据项
    // keyWords
    doc.DOCUMENT_KEYWORDS = keywords->text();

    // 设置时间
    doc.DT_CREATED = createday->text() + " " + createtime->text();
    doc.DT_MODIFIED = modifyday->text() + " " + modifytime->text();
    doc.DT_ACCESSED = accessday->text() + " " + accesstime->text();

    // author
    doc.DOCUMENT_AUTHOR = author->text();
    // owner
    doc.DOCUMENT_OWNER = owner->text();
    // version
    doc.MF_VERSION = doc.MF_VERSION + 1;
    DocDao::updateDoc(doc);

    update = true;
    this->close();
}


void PropOfDocDialog::closeBtn_clicked()
{
    update = true;
    this->close();
}

