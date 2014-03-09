#include <QFileDialog>
#include <QMessageBox>

#include <QtDebug>
#include <QDir>
#include <QUuid>
#include <QStandardItemModel>
#include <QDateTime>

#include "importdocdialog.h"
#include "preferences.h"
#include "utils.h"
#include "db/docdao.h"
#include "db/dirdao.h"

ImportDocDialog::ImportDocDialog(QWidget * parent, const QString & baseUuid, const QString & basedir)
	: QDialog(parent),
	  m_parent(parent),
          m_baseUuid(baseUuid),
          m_baseDir(basedir), update(false)
{
        setupUi(this);
        inclueSubDirCheck->setChecked(true);
        createSubDirCheck->setChecked(false);

        // fileTypeCmb
        fileTypeCmb->clear();
        fileTypeCmb->insertItems(0, QStringList()
         << QApplication::translate("ImportDocDialog", "All supported files", 0)
         << QApplication::translate("ImportDocDialog", "Office files(*.doc,*.docx,*.xls,*.xlsx,*.ppt,*.pptx)", 0)
         << QApplication::translate("ImportDocDialog", "Pdf files(*.pdf)", 0)
         << QApplication::translate("ImportDocDialog", "Html files(*.html,*.htm)", 0)
         << QApplication::translate("ImportDocDialog", "Picture file(*.jpeg,*.jpg,*.png,*.bmp,*.gif)", 0)
         << QApplication::translate("ImportDocDialog", "Flash files(*.flv,*.swf)", 0)
         << QApplication::translate("ImportDocDialog", "Source files(*.cpp,*.h,*.hpp,*.c,*.java,*.js,*.cs,*.vbs,*.sql,*.rb,*.py,*.asp,*.aspx,*.jsp,*.php,*.xml)", 0)
         << QApplication::translate("ImportDocDialog", "Txt files(*.txt,*.ini,*.bar,*.inf)", 0)
         << QApplication::translate("ImportDocDialog", "Movie fies(*.rm,*.rmvb,*.avi,*.mpg,*.mlv,*.mpe,*.mpeg,*.m2v)", 0)
        );


        Preferences* p = Preferences::instance();
        fileTypeCmb->insertItems(10, p->allsupported());

        // Set UI
        // 设置目标目录
        destDir->setText(m_baseDir);

        // 列表
        model = new QStandardItemModel();
        // 新建Model
        model->setColumnCount(1);

        this->setWindowIcon(Utils::getIcon("document-import.png"));
        this->setWindowTitle(tr("Document Import"));

        progressBar->hide();
        pgfilename->hide();
        cancelled = false;

        previewView->horizontalHeader()->setVisible(false);

        connect(fileSelBtn, SIGNAL(clicked()), this, SLOT(fileSelBtn_clicked()));
        connect(previewBtn, SIGNAL(clicked()), this, SLOT(previewBtn_clicked()));
        connect(delBtn, SIGNAL(clicked()), this, SLOT(delBtn_clicked()));

        connect(buttonBox, SIGNAL(accepted()), this, SLOT(confirmBtn_clicked()));
        connect(buttonBox,SIGNAL(rejected()),this,SLOT(cancelBtn_clicked()));

}

// 选择路径
void ImportDocDialog::fileSelBtn_clicked()
{
  QString path = QFileDialog::getExistingDirectory(this, tr("Select existing doc directory"),
                                                   tr("Choose a directory"), QFileDialog::ShowDirsOnly);
   if (path.isEmpty()){
        return;
   }
   path = QDir::toNativeSeparators(path);
   // 设定路径
   fileSelDir->setText(path);
   m_importDir = path;
}

// 选择路径
void ImportDocDialog::previewBtn_clicked()
{
    // 如果没有选择导入目录
    if(m_importDir.isEmpty()){
        QMessageBox::warning(this, tr("Warning"), tr("Please Select the Path to Import Into.."), QMessageBox::Yes);
        return;
    }

   // 取得fliter
   int curIndex = fileTypeCmb->currentIndex();
   QDir *dir=new QDir(m_importDir);
   // dir.setFilter(QDir::Dirs|QDir::Files|QDir::NoDotAndDotDot);
   // 取到所有的文件和文件名，但是去掉.和..的文件夹（这是QT默认有的）
   //dir.setFilter(QDir::Dirs|QDir::Files|QDir::NoDotAndDotDot);

   Preferences* p = Preferences::instance();

   QStringList filter;
   // all supported files
   if(curIndex == 0){
       filter = p->allsupported();
   }
   // officedoc
   if(curIndex == 1){
       filter = p->officedoc();
   }
   // officedoc
   if(curIndex == 2){
       filter = p->pdf();
   }
   // htmls files
   if(curIndex == 3){
       filter = p->htmls();
   }
   // pics files
   if(curIndex == 4){
       filter = p->pics();
   }
   // swfs files
   if(curIndex == 5){
       filter = p->swfs();
   }
   // sources files
   if(curIndex == 6){
       filter = p->sources();
   }
   // txts files
   if(curIndex == 7){
       filter = p->txts();
   }
   // movies files
   if(curIndex == 8){
       filter = p->movies();
   }

   // 单独文件类型
   if(curIndex > 8){
      filter << fileTypeCmb->currentText();
   }

   // 自定义文件类型
   QString scustomFileType = customFileType->text();
   if(!scustomFileType.isEmpty()){
       QStringList customList = scustomFileType.split(",");
       filter.append(customList);
   }

   // 自定义排除文件类型
   QString sexcludefileType = excludefileType->text();
   if(!sexcludefileType.isEmpty()){
       QStringList customexList = sexcludefileType.split(",");
       for (int var = 0; var < customexList.size(); ++var) {
            QString temp = customexList.at(var);
            filter.removeAll(temp);
       }
   }

   // model
   model->clear();

   // 是否包含子目录
   if(inclueSubDirCheck->isChecked()){
       loadFiles(m_importDir, filter, model);
   }else{
       // 不包含子目录
       dir->setNameFilters(filter);
       QList<QFileInfo> *fileInfos=new QList<QFileInfo>(dir->entryInfoList(filter));
       QFileInfo fileinfo;
       // 列出子目录文件
       for (int var = 0; var < fileInfos->size(); ++var) {
                fileinfo = fileInfos->at(var);
                if(fileinfo.isFile()){
                    QString filepath = fileinfo.absoluteFilePath();
                    filepath = QDir::toNativeSeparators(filepath);
                    QList<QStandardItem*> items;
                    QStandardItem* item = new QStandardItem(filepath);
                    items << item;
                    model->appendRow(items);
                }
       }
   }

   previewView->setModel(model);
   // 设置第一列的宽度
   int tablewidth = this->previewView->width();
   this->previewView->setColumnWidth(0, tablewidth * 1);
}

//// 根据文件父目录取得递归得到子目录树结构
int ImportDocDialog::loadFiles(QString parentPath, QStringList filter, QStandardItemModel *model){
    //目录
    QDir dir(parentPath);
    if (!dir.exists()) {
        return -1;
    }
    // 取到所有的文件和文件名，但是去掉.和..的文件夹（这是QT默认有的）
    dir.setFilter(QDir::Dirs | QDir::Files | QDir::NoDotAndDotDot);

    //转化成一个list
    QFileInfoList list = dir.entryInfoList();

    for(int i = 0; i< list.size(); i++){
        QFileInfo fileInfo = list.at(i);
        QString filepath = fileInfo.filePath();
        //如果是文件夹
        bool bisDir = fileInfo.isDir();
        if(bisDir) {
            loadFiles(filepath, filter, model);
        }else{
            filepath = QDir::toNativeSeparators(filepath);
            int dotpos = filepath.lastIndexOf(".");
            QString suffix = filepath.right(filepath.length() - dotpos);
            suffix = "*" + suffix;
            if(filter.contains(suffix)){
                QStandardItem* item = new QStandardItem(filepath);
                QList<QStandardItem*> items;
                items << item;
                model->appendRow(items);

            }
        }
    }
    return 0;
}

//// 删除文件按钮
void ImportDocDialog::delBtn_clicked(){

    QItemSelectionModel *selections = previewView->selectionModel();
    QModelIndexList selected = selections->selectedIndexes();
    QMap<int, int> rowMap;
    foreach (QModelIndex index, selected)
    {
        rowMap.insert(index.row(), 0);
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

// 设置进度条点
bool ImportDocDialog::setProgress(int p)
{
        if (cancelled){
            return false;
        }
        progressBar->setValue(p);
        return true;
}

// 确定按钮
void ImportDocDialog::confirmBtn_clicked(){

    int row = model->rowCount();
    // 如果没有选择导入目录
    if(row == 0 ){
       QMessageBox::warning(this, tr("Warning"), tr("No Import file. Please Confirm"), QMessageBox::Yes);
       return;
    }
    // 设置button disable
    buttonBox->setDisabled(true);
    fileSelBtn->setDisabled(true);
    previewBtn->setDisabled(true);
    delBtn->setDisabled(true);

    // 存储每一层文件夹名 <1, dirList>
    QMap<int, QStringList> writeMap;
    // 存储每一层文件夹名 <1, uuidList>
    QMap<QString, QString> uuidMap;

    pgfilename->show();
    progressBar->show();

    progressBar->setWindowModality(Qt::WindowModal);
    progressBar->setRange(0, row);

    QString parentUuId = m_baseUuid;

    bool isCreateSubDir = createSubDirCheck->isChecked();
    m_importDir = m_importDir.append(QDir::separator());

    if(isCreateSubDir){
        // 创建子文件夹
        for (int var = 0; var < row; ++ var) {

            QStandardItem* temp = model->item(var);
            QString path = temp->text();

            QString filepath = path.left(path.lastIndexOf(QDir::separator()));
            filepath = filepath.replace("\"","");

            // 设置目标目录
            QString destDir = filepath.remove(0, m_importDir.length());

            QStringList dirs = destDir.split(QDir::separator());
            // 建立目录
            for (int i = 0; i < dirs.length(); i++) {
                QString tmpDir = dirs.at(i);
                if(tmpDir.isEmpty()){
                  continue;
                }
                // 第一层文件夹
                if(i == 0){
                   parentUuId = m_baseUuid;
                }

                QStringList exitedDirs = writeMap[i];
                if(exitedDirs.contains(tmpDir)){
                    // 存在的状态下
                    parentUuId = uuidMap[tmpDir];
                    continue;
                } else {
                      QUuid uuid = QUuid::createUuid();
                      Dir dir;
                      dir.DIR_GUID = uuid.toString();
                      dir.DIR_NAME = tmpDir;
                      dir.DIR_PARENT_UUID = parentUuId;
                      dir.DIR_ICON = "folder.ico";
                      dir.DIR_ORDER = 0;
                      dir.DELETE_FLAG = '0';
                      dir.MF_VERSION = 0;
                      DirDao::insertDir(dir);

                      exitedDirs.append(tmpDir);
                      writeMap.insert(i, exitedDirs);
                      uuidMap.insert(tmpDir, uuid.toString());

                      if(i == dirs.length() - 1){
                          uuidMap.insert(destDir, uuid.toString());
                      }else{
                          parentUuId = uuid.toString();
                      }
               }
            }
        }

        // 写入文档信息
        for (int var = 0; var < row; ++ var) {

                QStandardItem* temp = model->item(var);
                QString path = temp->text();
                pgfilename->setText(path);

                QString filepath = path.left(path.lastIndexOf(QDir::separator()));
                filepath = filepath.replace("\"","");

                // 设置目标目录
                QString destDir = filepath.remove(0, m_importDir.length());
                QUuid docUuid = QUuid::createUuid();
                QFileInfo fileinfo(path);
                Doc doc;
                doc.DOCUMENT_GUID = docUuid.toString();
                doc.DOCUMENT_TITLE = fileinfo.fileName();

                QString parentUUid = uuidMap[destDir];
                if(parentUUid.isEmpty()){
                   parentUUid = m_baseUuid;
                }
                doc.DIR_GUID = parentUUid;
                doc.DOCUMENT_LOCATION = path;
                doc.DOCUMENT_NAME = fileinfo.fileName();
                doc.DOCUMENT_SEO = "";
                doc.DOCUMENT_URL = "";
                doc.DOCUMENT_AUTHOR = fileinfo.owner();
                doc.DOCUMENT_KEYWORDS = "";
                doc.DOCUMENT_TYPE = "";
                doc.DOCUMENT_OWNER = fileinfo.owner();
                doc.DT_CREATED = fileinfo.created().toString("yyyy-MM-dd hh:mm:ss");
                doc.DT_MODIFIED = fileinfo.lastModified().toString("yyyy-MM-dd hh:mm:ss");
                doc.DT_ACCESSED = fileinfo.lastRead().toString("yyyy-MM-dd hh:mm:ss");
                doc.DOCUMENT_ICON_INDEX = 0;
                doc.DOCUMENT_SYNC = 0;
                doc.DOCUMENT_PROTECT = "0";
                doc.DOCUMENT_ENCODE= "0";
                doc.DOCUMENT_READ_COUNT = 0;
                doc.DOCUMENT_RELATE_COUNT = 0;
                doc.DOCUMENT_INDEXFLG = "0";
                doc.DOCUMENT_OPERFLG = "";
                doc.DELETE_FLAG = "0";
                doc.MF_VERSION = 0;

                DocDao::insertDoc(doc);
                setProgress(var);
        }
    } else{
            // 不建立子文件夹
          for (int var = 0; var < row; ++var) {

                QStandardItem* temp = model->item(var);
                QString path = temp->text();
                pgfilename->setText(path);

                QUuid docUuid = QUuid::createUuid();
                QFileInfo fileinfo(path);
                Doc doc;
                doc.DOCUMENT_GUID = docUuid.toString();
                doc.DOCUMENT_TITLE = fileinfo.fileName();

                doc.DIR_GUID = parentUuId;
                doc.DOCUMENT_LOCATION = path;
                doc.DOCUMENT_NAME = fileinfo.fileName();
                doc.DOCUMENT_SEO = "";
                doc.DOCUMENT_URL = "";
                doc.DOCUMENT_AUTHOR = fileinfo.owner();
                doc.DOCUMENT_KEYWORDS = "";
                doc.DOCUMENT_TYPE = "";
                doc.DOCUMENT_OWNER = fileinfo.owner();
                doc.DT_CREATED = fileinfo.created().toString("yyyy-MM-dd hh:mm:ss");
                doc.DT_MODIFIED = fileinfo.lastModified().toString("yyyy-MM-dd hh:mm:ss");
                doc.DT_ACCESSED = fileinfo.lastRead().toString("yyyy-MM-dd hh:mm:ss");
                doc.DOCUMENT_ICON_INDEX = 0;
                doc.DOCUMENT_SYNC = 0;
                doc.DOCUMENT_PROTECT = "0";
                doc.DOCUMENT_ENCODE= "0";
                doc.DOCUMENT_READ_COUNT = 0;
                doc.DOCUMENT_RELATE_COUNT = 0;
                doc.DOCUMENT_INDEXFLG = "0";
                doc.DOCUMENT_OPERFLG = "0";
                doc.DELETE_FLAG = "0";
                doc.MF_VERSION = 0;

                DocDao::insertDoc(doc);
                setProgress(var);
            }
    }

    update = true;
    this->close();

}

// 取消按钮
void ImportDocDialog::cancelBtn_clicked(){
    cancelled = true;
    update = false;
    this->close();
}



