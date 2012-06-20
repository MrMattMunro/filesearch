#include <QDir>
#include <QTextStream>
#include <QDebug>
#include <QFile>
#include <QDir>
#include <QDesktopServices>
#include <QUrl>
#include <preferences.h>
#include <QAxObject>
#include <QAxWidget>

#include "fileutils.h"

// 目标Copy
bool FileUtils::copyDirectoryFiles(const QDir &fromDir, const QDir &toDir, bool coverFileIfExist)
{
    QDir sourceDir = fromDir;
    QDir targetDir = toDir;
    if(!targetDir.exists()){    /**< 如果目标目录不存在，则进行创建 */
        if(!targetDir.mkdir(toDir.absolutePath()))
            return false;
    }

    QFileInfoList fileInfoList = sourceDir.entryInfoList();
    foreach(QFileInfo fileInfo, fileInfoList){
        if(fileInfo.fileName() == "." || fileInfo.fileName() == "..")
            continue;

        if(fileInfo.isDir()){    /**< 当为目录时，递归的进行copy */
            if(!copyDirectoryFiles(fileInfo.filePath(),
                                   targetDir.filePath(fileInfo.fileName()),
                                   coverFileIfExist))
                return false;
        }else{            /**< 当允许覆盖操作时，将旧文件进行删除操作 */
            if(coverFileIfExist && targetDir.exists(fileInfo.fileName())){
                targetDir.remove(fileInfo.fileName());
            }

            /// 进行文件copy
            if(!QFile::copy(fileInfo.filePath(), targetDir.filePath(fileInfo.fileName()))){
                return false;
            }
        }
    }
    return true;
}

// 把目标文件copy到目标目录
bool FileUtils::copyFileToDir(QString sfromFile, QString toDir, bool coverFileIfExist)
{
    QDir *targetDir = new QDir (toDir);
    QFileInfo *fileInfo = new QFileInfo(sfromFile);
    /** 如果目标目录不存在，则进行创建 */
    if(!targetDir->exists()){
        if(!targetDir->mkpath(targetDir->absolutePath()))
            return false;
    }

     /**< 当允许覆盖操作时，将旧文件进行删除操作 */
    if(coverFileIfExist && targetDir->exists(fileInfo->fileName())){
        targetDir->remove(fileInfo->fileName());
    }

    /// 进行文件copy
    if(!QFile::copy(fileInfo->absoluteFilePath(), toDir.append(QDir::separator()).append(fileInfo->fileName()))){
        return false;
    }

    return true;
}

// 目标Copy目录结构
bool FileUtils::copyDirectory(const QDir &fromDir, const QDir &toDir)
{
    QDir sourceDir = fromDir;
    QDir targetDir = toDir;
    /**< 如果目标目录不存在，则进行创建 */
    if(!targetDir.exists()){
        if(!targetDir.mkdir(toDir.absolutePath())){
          return false;
        }
    }

    QFileInfoList fileInfoList = sourceDir.entryInfoList();
    foreach(QFileInfo fileInfo, fileInfoList){
        if(fileInfo.fileName() == "." || fileInfo.fileName() == ".."){
             continue;
        }
         /**< 当为目录时，递归的进行copy */
        if(fileInfo.isDir()){
            if(!copyDirectory(fileInfo.filePath(), targetDir.filePath(fileInfo.fileName()))){
                 return false;
            }
        }
    }
    return true;
}

// 删除空目录
bool FileUtils::delDirectory(const QDir &fromDir)
{
    QDir sourceDir = fromDir;
    /** 如果目标目录不存在，则进行创建 */
    if(!fromDir.exists()){
        return true;
    }
    QFileInfoList fileInfoList = sourceDir.entryInfoList(QDir::Dirs | QDir::Files | QDir::NoDotAndDotDot);
    if(fileInfoList.size() == 0){
        sourceDir.rmpath(fromDir.absolutePath());
    }
    foreach(QFileInfo fileInfo, fileInfoList){
        if(fileInfo.fileName() == "." || fileInfo.fileName() == ".."){
             continue;
        }
         /** 当为目录时，递归的进行copy */
        if(fileInfo.isDir()){
            if(!delDirectory(fileInfo.filePath())){
                 return false;
            }
        }
    }
    return true;
}

// 写入文件
bool FileUtils::writeFile(QString filepath, QStringList lines)
{

    QFile file(filepath);
    if (!file.open( QIODevice::Append | QIODevice::Text )) {
        return false;
    }

     QTextStream stream( &file );
     for ( QStringList::Iterator it = lines.begin(); it != lines.end(); ++it ){
       stream << *it << "\n";
     }
     file.close();
     return true;
}

// 读取文件
QStringList FileUtils::readFile(QString filepath)
{
      QStringList lines;
      QFile file(filepath);
      if (!file.open( QIODevice::ReadOnly | QIODevice::Text )) {
            return lines;
      }

      QTextStream stream( &file );
      QString line;
      while ( !stream.atEnd() ) {
          line = stream.readLine(); // 不包括“\n”的一行文本
          lines << line;
      }
      file.close();
      return lines;

}

// 读取目录下所有的文件
QStringList FileUtils::readAllDatFile(QString filepath, QStringList lines)
{
      QDir dir(filepath);
      if(!dir.exists()){
          return QStringList();
      }

      QFileInfoList fileInfoList = dir.entryInfoList(QDir::Dirs | QDir::Files | QDir::NoDotAndDotDot);

      foreach(QFileInfo fileInfo, fileInfoList){
          if(fileInfo.isDir()){
              QString dir = fileInfo.filePath();
              lines.append(readAllDatFile(dir, lines));
          } else if(fileInfo.isFile()){
              QString dir = fileInfo.filePath();
              lines.append(readFile(dir));
          }
      }
      return lines;
}

// 删除文件夹
bool FileUtils::removeDirectory(QString dirName)
{
    QDir dir(dirName);
    QString tmpdir = "";
    if(!dir.exists()){
        return false;
    }

    QFileInfoList fileInfoList = dir.entryInfoList();
    foreach(QFileInfo fileInfo, fileInfoList){
        if(fileInfo.fileName() == "." || fileInfo.fileName() == "..")
            continue;

        if(fileInfo.isDir()){
            tmpdir = dirName + ("/") + fileInfo.fileName();
            removeDirectory(tmpdir);
            dir.rmdir(fileInfo.fileName()); /**< 移除子目录 */
        } else if(fileInfo.isFile()){
            QFile tmpFile(fileInfo.fileName());
            dir.remove(tmpFile.fileName()); /**< 删除临时文件 */
        }
    }

    /**< 返回上级目录，因为只有返回上级目录，才可以删除这个目录 */
    dir.cdUp();
    if(dir.exists(dirName)){
        if(!dir.rmdir(dirName))
            return false;
    }
    return true;
}

// 删除文件夹内所有文件
void FileUtils::deleteDirectory(QFileInfo fileList){

    if(fileList.isDir()){
        int childCount =0;
        QString dir = fileList.filePath();
        QDir thisDir(dir);
        childCount = thisDir.entryInfoList().count();
        QFileInfoList newFileList = thisDir.entryInfoList();
        if(childCount >2 ){
            for(int i=0; i < childCount; i++){
                if(newFileList.at(i).fileName().operator ==(".")|newFileList.at(i).fileName().operator ==("..")){
                    continue;
                }
                deleteDirectory(newFileList.at(i));
            }
        }
        fileList.absoluteDir().rmdir(fileList.fileName());
    } else if(fileList.isFile()){
        fileList.absoluteDir().remove(fileList.fileName());
    }
}

// 取得文件夹里的所有文件
int FileUtils::loadAllFile(QDir dir, QList<QString> fileList){
    //目录
    if (!dir.exists()) {
        return -1;
    }

    // 取到所有的文件和文件名，但是去掉.和..的文件夹（这是QT默认有的）
    dir.setFilter(QDir::Dirs|QDir::Files|QDir::NoDotAndDotDot);

    //文件夹优先
    dir.setSorting(QDir::DirsFirst);

    //转化成一个list
    QFileInfoList list = dir.entryInfoList();
    if(list.size()< 1 ) {
        return -1;
    }

    int i=0;
    //递归算法的核心部分
    do{
        QFileInfo fileInfo = list.at(i);
        //如果是文件夹，递归
        bool bisDir = fileInfo.isDir();
        if(bisDir) {
            loadAllFile(QDir(fileInfo.filePath()), fileList);
        } else{
            fileList.append(fileInfo.filePath());
        }//end else
        i++;
    } while(i < list.size());
}

// 打开文件
int FileUtils::openFile(const QString &filepath){
    // 打开文件
    QDir file(filepath);
    if (filepath.isEmpty() || !file.exists()) {
        return -1;
    }

    // QDesktopServices::openUrl(QUrl("file:////Users/Biao/Desktop/1.mp4"));
    QDesktopServices::openUrl(QUrl::fromLocalFile(filepath));

}



//// 打开Office文档
//QAxWidget FileUtils::openOfficeFileInTab(const QString &filepath){
//      // 文件不存在
//      QAxWidget wordActive("Word.Application");
//      QAxObject* word = wordActive.querySubObject("ActiveDocument");

//      // 读取preferences
//      Preferences* p = Preferences::instance();
//      QStringList wordtypes = p->word();
//      QString suffixname =  suffix(filepath);
//      if(wordtypes.contains(suffixname)){
//         word->dynamicCall("SetVisible(bool)", true );
//         word->querySubObject("Open(const QString&)", QString(filepath));
//         return wordActive;
//      }
//}

// 取得文件后缀名
QString FileUtils::suffix(const QString &filepath){
    // 文件不存在
    int dotpos = filepath.lastIndexOf(".");
    QString dotsuffix = filepath.right(filepath.length() - dotpos);
    return "*" + dotsuffix;
}








