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

#include "exportdocdialog.h"
#include "preferences.h"
#include "utils.h"
#include "fileutils.h"

ExportDocDialog::ExportDocDialog(QWidget * parent, const QString & basedir,const QString & dir)
	: QDialog(parent),
	  m_parent(parent),
          m_baseDir(basedir),
          m_dir(dir),update(false)
{
	setupUi(this);
        inclueSubDirChk->setChecked(true);
        createSubDirChk->setChecked(true);

        // Set UI
        // 设置目标目录
        QString tdestDir = m_dir;
        tdestDir = tdestDir.remove(0, m_baseDir.length());
        destDir->setText(dir);

        // 列表
        model = new QStandardItemModel();
        // 新建Model
        model->setColumnCount(1);

        this->setWindowIcon(Utils::getIcon("document-import.png"));
        this->setWindowTitle(tr("Doc Export"));

        progressBar->hide();
        pgfilename->hide();
        cancelled = false;

        connect(fileSelBtn, SIGNAL(clicked()), this, SLOT(fileSelBtn_clicked()));
        connect(previewBtn, SIGNAL(clicked()), this, SLOT(previewBtn_clicked()));
        connect(delBtn, SIGNAL(clicked()), this, SLOT(delBtn_clicked()));

        connect(buttonBox, SIGNAL(accepted()), this, SLOT(confirmBtn_clicked()));
        connect(buttonBox,SIGNAL(rejected()),this,SLOT(cancelBtn_clicked()));
}

// 选择导出路径
void ExportDocDialog::fileSelBtn_clicked()
{
  QString path = QFileDialog::getExistingDirectory(this, tr("Select existing Export directory"),
                                                   tr("Choose a directory"), QFileDialog::ShowDirsOnly);
   if (path.isEmpty()){
        return;
   }
   path = QDir::toNativeSeparators(path);
   // 设定导出路径
   fileSelDir->setText(path);
   m_exportDir = path;
}

// 预览文件列表
void ExportDocDialog::previewBtn_clicked()
{

   // 自定义排除文件类型
   QString sexcludefileType = excludefileType->text();
   QStringList customexList;
   if(!sexcludefileType.isEmpty()){
       customexList = sexcludefileType.split(",");
   }

   // model
   model->clear();

   // 是否包含子目录
   if(inclueSubDirChk->isChecked()){
       loadFiles(m_dir, customexList, model);
   } else {
       // 是files.dat文件
       QString path = m_dir;
       path.append(QDir::separator()).append("files.dat");
       QFile datfile(path);
       if (datfile.exists()){
           path = QDir::toNativeSeparators(path);
           // 读取dat文件
           QStringList files = FileUtils::readFile(path);
           for (int var = 0; var < files.length(); ++var) {
               QString file = files.at(var);
               if(!file.isEmpty()){
                   QStringList arr = file.split(",");
                   QString filepath = arr[1];
                   int dotpos = filepath.lastIndexOf(".");
                   QString suffix = filepath.right(filepath.length() - dotpos);
                   suffix = "*" + suffix;
                   // 排除手动除去文件类型
                   if(!customexList.contains(suffix)){
                      // 取得文件名
                       QString filename = arr[1].right(arr[1].length() - arr[1].lastIndexOf(QDir::separator()));

                       // 取得BaseDir
                       QString tdestDir = m_dir;
                       tdestDir = tdestDir.remove(0, m_baseDir.length());

                       QStandardItem* item = new QStandardItem(tdestDir + filename);
                       item->setData(arr[1], Qt::ToolTip);
                       QList<QStandardItem*> items;
                       items << item;
                       model->appendRow(items);

                   }
               }
           }
       }
   }

   previewView->setModel(model);
   // 设置第一列的宽度
   int tablewidth = this->previewView->width();
   this->previewView->setColumnWidth(0, tablewidth * 1);
}

//// 根据文件父目录取得递归得到子目录树结构
int ExportDocDialog::loadFiles(QString parentPath, QStringList excludeTypeList, QStandardItemModel *model){
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
        QString datfilepath = fileInfo.filePath();
        //如果是文件夹
        bool bisDir = fileInfo.isDir();
        if(bisDir) {
            loadFiles(datfilepath, excludeTypeList, model);
        }else{
            // 是files.dat文件
            if (datfilepath.indexOf("files.dat") != -1 ){
                datfilepath = QDir::toNativeSeparators(datfilepath);
                // 读取dat文件
                QStringList files = FileUtils::readFile(datfilepath);
                for (int var = 0; var < files.length(); ++var) {
                    QString file = files.at(var);
                    if(!file.isEmpty()){
                        QStringList arr = file.split(",");
                        QString filepath = arr[1];
                        int dotpos = filepath.lastIndexOf(".");
                        QString suffix = filepath.right(filepath.length() - dotpos);
                        suffix = "*" + suffix;
                        // 排除手动除去文件类型
                        if(!excludeTypeList.contains(suffix)){
                           // 取得文件名
                            QString filename = arr[1].right(arr[1].length() - arr[1].lastIndexOf(QDir::separator()) - 1);

                            // 取得BaseDir
                            QString tdestDir = datfilepath;
                            tdestDir = tdestDir.remove("files.dat");
                            tdestDir = tdestDir.mid(m_baseDir.length() + 1, tdestDir.length());

                            QStandardItem* item = new QStandardItem(tdestDir + filename);
                            item->setData(arr[1], Qt::ToolTip);
                            QList<QStandardItem*> items;
                            items << item;
                            model->appendRow(items);

                        }
                    }
                }
            }
        }
    }
}

// 删除文件按钮
void ExportDocDialog::delBtn_clicked(){

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

//// 确定按钮 复制文件本省到写入到导出目录，可能文件很大，需要有进度条。
void ExportDocDialog::confirmBtn_clicked(){
    // 如果没有选择导入目录
    if(m_exportDir.isEmpty()){
        QMessageBox::warning(this, tr("Warning"), tr("Please Select the Path to Export Into.."), QMessageBox::Yes);
        return;
    }

    // 是否创建子文件夹
    bool isCreateSubDir = createSubDirChk->isChecked();

    // 设置界面元素不可用
    this->setEnabled(false);

    pgfilename->show();
    progressBar->show();

    // 目录排序
    model->sort(0, Qt::DescendingOrder);
    // 拷贝文件
    int row= model->rowCount();
    progressBar->setWindowModality(Qt::WindowModal);
    progressBar->setRange(0, row);
     // 取得导出的文件列表
    for (int var = 0; var < row; ++var) {
         QStandardItem* temp = model->item(var);
         QString filepath = qvariant_cast<QString>(temp->data(Qt::ToolTip));
         QString displayfilepath = qvariant_cast<QString>(temp->data(Qt::DisplayRole));
         pgfilename->setText(displayfilepath);
         // 是否创建子文件夹
         if(isCreateSubDir){
            QString destDir = m_exportDir + displayfilepath.left(displayfilepath.lastIndexOf(QDir::separator()));
            // 创建子目录
            FileUtils::copyFileToDir(filepath, destDir, true);
         }else{
            FileUtils::copyFileToDir(filepath, m_exportDir, true);
         }
         setProgress(var);
     }
     update = true;
     // 提示导出完成
     int com = QMessageBox::information(this, tr("Message"), tr("Documents Exported Success!"), QMessageBox::Yes);
     if (com == QMessageBox::Yes)
     {
            this->close();
            QDesktopServices::openUrl(QUrl("file:///" + m_exportDir));
            return;
     }
}

// 设置进度条点
bool ExportDocDialog::setProgress(int p)
{
        if (cancelled){
            return false;
        }
        progressBar->setValue(p);
        return true;
}

// 取消按钮
void ExportDocDialog::cancelBtn_clicked(){
     cancelled = true;
     update = false;
     this->close();
}



