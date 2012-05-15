#include <QFileDialog>
#include <QMessageBox>

#include <QtDebug>
#include <QDir>
#include <QMenu>
#include <QStandardItemModel>
#include <QDesktopServices>

#include "relatedocdialog.h"
#include "preferences.h"
#include "utils.h"
#include "fileutils.h"
#include "db/docdao.h"
#include "db/relatedocdao.h"

RelateDocDialog::RelateDocDialog(QWidget * parent): QDialog(parent),  update(false)
{
	setupUi(this);
        // 列表
        model = new QStandardItemModel();
        // 新建Model
        model->setColumnCount(4);
        model->setHeaderData(0,Qt::Horizontal,tr("Author"));
        model->setHeaderData(1,Qt::Horizontal,tr("FileName"));
        model->setHeaderData(2,Qt::Horizontal,tr("Date"));
        model->setHeaderData(3,Qt::Horizontal,tr("relateDocUid"));

        initDocs();

        // 传递选择的docUuid
        Preferences* p = Preferences::instance();
        m_docUuid = p->getSelDocUid();

        if(! m_docUuid.isEmpty()){
            Doc doc = DocDao::selectDoc(m_docUuid);
            m_docPath = doc.DOCUMENT_LOCATION;
            this->setWindowTitle(doc.DOCUMENT_NAME);
        }

        this->setWindowIcon(Utils::getIcon("doc.png"));

        setContextMenuPolicy(Qt::CustomContextMenu);
        connect(this, SIGNAL(customContextMenuRequested(QPoint)), this, SLOT(contextMenuRequested(QPoint)));

}

// 打开菜单
void RelateDocDialog::contextMenuRequested(const QPoint &pos)
{
    QMenu menu;
    selIndex = docsView->indexAt(pos);

    menu.addAction(tr("Open this Doc"), this, SLOT(openRelateDoc()));
    menu.addAction(tr("Delete this Doc"), this, SLOT(deleteRelateDoc()));
    menu.addAction(tr("Delete All Docs"), this, SLOT(deleteAllRelateDoc()));

    menu.exec(QCursor::pos());
}

// 打开菜单
void RelateDocDialog::openRelateDoc()
{
    QItemSelectionModel *selections = docsView->selectionModel();
    QModelIndexList selected = selections->selectedIndexes();

    // 选择第一个
    QModelIndex index = selected.at(0);
    QStandardItem* item = model->item(index.row(), 3);
    QString docUuid = qvariant_cast<QString>(item->data(Qt::DisplayRole));

    Doc doc = DocDao::selectDoc(docUuid);
    QString filepath = doc.DOCUMENT_LOCATION;
    QFileInfo fileInfo(filepath);
    if(!fileInfo.exists()){
        QMessageBox::warning(this, tr("Warning"), tr("Please Confirm The original file  has Deleted Or Moved. "), QMessageBox::Yes);
        return;
    }
    QDesktopServices::openUrl ( QUrl::fromLocalFile(filepath) );
}


// 删除关联文档
void RelateDocDialog::deleteRelateDoc()
{

    int ret = QMessageBox::question(this, "", tr("Are you sure that delete the related Doc ?"),
                                    QMessageBox::Yes, QMessageBox::No);
    if(ret == QMessageBox::Yes){

        QItemSelectionModel *selections = docsView->selectionModel();
        QModelIndexList selected = selections->selectedIndexes();
        QMap<int, int> rowMap;

        foreach (QModelIndex index, selected)
        {
            rowMap.insert(index.row(), 0);

            QStandardItem* item = model->item(index.row(), 3);
            QString relateDocUuid = qvariant_cast<QString>(item->data(Qt::DisplayRole));
            RelateDoc relateDoc;
            relateDoc.DOCUMENT_GUID = m_docUuid;
            relateDoc.DOCUMENT_GUID = relateDocUuid;
            RelateDocDao::deleteRelateDoc(relateDoc);
        }

        int rowToDel;
        QMapIterator<int, int> rowMapIterator(rowMap);
        rowMapIterator.toBack();
        while (rowMapIterator.hasPrevious())
        {
            rowMapIterator.previous();
            rowToDel = rowMapIterator.key();
            model->removeRow(rowToDel);
        }
    }

    if(ret == QMessageBox::No){
       return;
    }
}

// 删除所有关联文档
void RelateDocDialog::deleteAllRelateDoc()
{
    int ret = QMessageBox::question(this, "", tr("Are you sure that delete All the related docs ?"),
                                    QMessageBox::Yes, QMessageBox::No);
    if(ret == QMessageBox::Yes){
        if(!m_docUuid.isEmpty()){
            RelateDoc relateDoc;
            relateDoc.DOCUMENT_GUID = m_docUuid;
            RelateDocDao::deleteRelateDoc(relateDoc);
            model->clear();
        }
    }

    if(ret == QMessageBox::No){
       return;
    }

}

// 确定按钮
void RelateDocDialog::initDocs(){

    Preferences* p = Preferences::instance();
    m_docUuid = p->getSelDocUid();

    QList<RelateDoc> relateDocs = RelateDocDao::selectRelateDocs(m_docUuid);
    // 列出子目录文件
    for (int var = 0; var < relateDocs.length(); ++var) {
             RelateDoc relateDoc = relateDocs.at(var);

             Doc doc = DocDao::selectDoc(relateDoc.RELATED_DOCUMENT_GUID);
             QStandardItem* author = new QStandardItem(doc.DOCUMENT_AUTHOR);
             QStandardItem* filename = new QStandardItem(doc.DOCUMENT_NAME);
             QStandardItem* accdate = new QStandardItem(doc.DT_ACCESSED);
             QStandardItem* relateDocUuId = new QStandardItem(relateDoc.RELATED_DOCUMENT_GUID);

             QList<QStandardItem*> items;
             items << author ;
             items << filename;
             items << accdate;
             items << relateDocUuId;

             model->appendRow(items);
    }

    docsView->setModel(model);
    docsView->setSelectionBehavior(QAbstractItemView::SelectRows);
    docsView->hideColumn(3);
    docsView->resizeColumnsToContents();
}
