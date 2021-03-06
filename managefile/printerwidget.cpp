#include "printerwidget.h"

#include <QPrinter>
#include <QPrintDialog>
#include <QPainter>
#include <QDialog>
#include <QDebug>
#include <windows.h>
#include <winspool.h>
#include <QMessageBox>
#include <QTextDocument>
#include <QFile>

#define BUF_LEN 1024

BOOL RawDataToPrinter(QString szPrinterName, QString lpData, DWORD dwCount);
bool RawDataToPrinter(QString printerName,QStringList *barcode);

// ( QString szPrinterName, QString lpData, DWORD dwCount)

PrinterWidget::PrinterWidget(QWidget * parent): QDialog(parent),
      m_parent(parent)
{
   setupUi(this);
}

void PrinterWidget::printer()
{
    QPrinter printer(QPrinter::PrinterResolution);
    QPrintDialog *dlg = new QPrintDialog(&printer, this);

    if (dlg->exec() == QDialog::Accepted)
    {
        QPainter p(&printer);
        //p.drawText(0,0,"${^XA^FO10,100^BY3^BCN,100,Y,N,N^FDDC123456^FS^XZ}$");
        //p.drawText(0,0,"${^XA^FO10,100^BY3^BCN,100,Y,N,N^FDCD123456^FS^XZ}$");

        QString printerName = printer.printerName();
        QString lpData = tr("^XA^FO10,100^BY3^BCN,100,Y,N,N^FDDD123456^FS^XZ");
//        long dwCount = lpData.length();

        QStringList sl;
//        sl.append(tr("^XA^FO10,100^BY3^BCN,100,Y,N,N^FDAB123456^FS^XZ"));
//        sl.append(tr("^XA^FO10,100^BY3^BCN,100,Y,N,N^FDCD123456^FS^XZ"));
//        sl.append(tr("^XA^FO10,100^BY3^BCN,100,Y,N,N^FDEF123456^FS^XZ"));

        sl.append(tr("rfgggggg"));
        sl.append(tr("sdffffffffff"));
        sl.append(tr("sdfffffffffffffffffff"));

        QFile file("D:\\aaa.doc");
        file.open(QIODevice::ReadOnly);
        QDataStream ds(&file);
        ds.setVersion(QDataStream::Qt_4_6);

        ds.setByteOrder(QDataStream::LittleEndian);// QDataStream::BigEndian


        QByteArray rawdata;
        int dwCount = 0;

        char* buff=new char [BUF_LEN];

        //文件不为空
        while (!ds.atEnd())
        {
            int nReadBytes = ds.readRawData(buff, BUF_LEN);
            rawdata.append(buff, nReadBytes);
            dwCount = dwCount + nReadBytes;
        }

        file.close();

        qDebug() << "dwCount::" + dwCount;
        qDebug() << "rawdata::" + rawdata;

        QString dd(rawdata);

        if(RawDataToPrinter(printerName, dd, (DWORD)dwCount))
        {
            qDebug() << "OK";
        }else
        {
            qDebug() << "NO";
        }

//        if(RawDataToPrinter(printerName, &sl)==true)
//        {
//            qDebug() << "OK";
//        }else
//        {
//            qDebug() << "NO";
//        }

        /*if(RawDataToPrinter((char*)printerName.toLocal8Bit().data(),(unsigned char*)lpData.toLocal8Bit().data(),dwCount) == true)
        {
            qDebug() << "OK";
        }else
        {
            qDebug() << "NO";
        }*/
    }
    delete dlg;
}

BOOL RawDataToPrinter(QString szPrinterName, QString lpData, DWORD dwCount)
{
    HANDLE     hPrinter;
    DOC_INFO_1A DocInfo;
    DWORD      dwJob;
    DWORD      dwBytesWritten;

// Need a handle to the printer.
    //获取打印机的handle
    bool ok;
    ok = OpenPrinterW((LPWSTR)szPrinterName.utf16(),(LPHANDLE)&hPrinter,0);
    if(!ok){
        ok = OpenPrinterA((LPSTR)szPrinterName.toLatin1().data(), (LPHANDLE)&hPrinter, 0);
    }
    if(!ok){
       qDebug() << "QWin32PrintEngine::initialize: OpenPrinter failed";
    }


// Fill in the structure with info about this "document."
    DocInfo.pDocName = "BarCode";
    DocInfo.pOutputFile = NULL;
    DocInfo.pDatatype = "RAW";

// Inform the spooler the document is beginning.
    if((dwJob = StartDocPrinterA(hPrinter,1,(PBYTE)&DocInfo)) == 0)
    {
        ClosePrinter(hPrinter);
        return FALSE;
    }

// Start a page.
    if(!StartPagePrinter(hPrinter))
    {
        EndDocPrinter(hPrinter);
        ClosePrinter(hPrinter);
        return FALSE;
    }

// Send the data to the printer.
    if(!WritePrinter(hPrinter, (unsigned char *)lpData.toLocal8Bit().data(), dwCount, &dwBytesWritten))
    {
        EndPagePrinter(hPrinter);
        EndDocPrinter(hPrinter);
        ClosePrinter(hPrinter);
        return FALSE;
    }

//    if(!WritePrinter(hPrinter, (unsigned char *)lpData.toLocal8Bit().data(), dwCount, &dwBytesWritten))
//    {
//        EndPagePrinter(hPrinter);
//        EndDocPrinter(hPrinter);
//        ClosePrinter(hPrinter);
//        return FALSE;
//    }

// End the page.
    if(!EndPagePrinter(hPrinter))
    {
        EndDocPrinter(hPrinter);
        ClosePrinter(hPrinter);
        return FALSE;
    }

// Inform the spooler that the document is ending.
    if(!EndDocPrinter(hPrinter))
    {
        ClosePrinter(hPrinter);
        return FALSE;
    }

// Tidy up the printer handle.
    ClosePrinter(hPrinter);

//// Check to see if correct number of bytes were written.
//    if(dwBytesWritten != dwCount)
//    {
//        QMessageBox::warning(0,QObject::tr("打印"),QObject::tr("打印输出数据与输入数据大小不相符"),QObject::tr("确定(&E)"));
//        return FALSE;
//    }else
//    {
//        return TRUE;
//    }
    return true;
}

bool RawDataToPrinter(QString printerName, QStringList *barcode)
{
    HANDLE hPrinter;
    DOC_INFO_1A DocInfo;
    DWORD dwJob;
    DWORD dwBytesWritten;
    long dwCount;

    if(!(barcode->length() >0))
    {
        return false;
    }

    //获取打印机的handle
    bool ok;
    ok = OpenPrinterW((LPWSTR)printerName.utf16(),(LPHANDLE)&hPrinter,0);
    if(!ok){
        ok = OpenPrinterA((LPSTR)printerName.toLatin1().data(), (LPHANDLE)&hPrinter, 0);
    }
    if(!ok){
       qDebug() << "QWin32PrintEngine::initialize: OpenPrinter failed";
    }

    //填充打印文档的DOC_INFO_1A
    DocInfo.pDocName = "BarCode";
    DocInfo.pOutputFile = NULL;
    DocInfo.pDatatype = "RAW";

    //通知打印服务，准备开始打印文档
    if((dwJob = StartDocPrinterA(hPrinter,1,(PBYTE)&DocInfo)) == 0)
    {
        ClosePrinter(hPrinter);
        return false;
    }

    //开始一页的打印
    if(!StartPagePrinter(hPrinter))
    {
        EndDocPrinter(hPrinter);
        ClosePrinter(hPrinter);
        return false;
    }

    foreach(QString str,*barcode)
    {
        //发送数据到打印机
        dwCount = str.toLocal8Bit().length();
        if(!WritePrinter(hPrinter,(unsigned char *)str.toLocal8Bit().data(), dwCount,&dwBytesWritten))
        {
            EndPagePrinter(hPrinter);
            EndDocPrinter(hPrinter);
            ClosePrinter(hPrinter);
            return false;
        }
        //检查实际写入数据是否与原始数据大小相符
        if(dwBytesWritten != dwCount)
        {
            QMessageBox::warning(0,QObject::tr("打印"),QObject::tr("打印输出数据与输入数据大小不相符"),QObject::tr("确定(&E)"));
            EndPagePrinter(hPrinter);
            EndDocPrinter(hPrinter);
            ClosePrinter(hPrinter);
            return false;
        }
    }

    //结束一页的打印
    if(!EndPagePrinter(hPrinter))
    {
        EndDocPrinter(hPrinter);
        ClosePrinter(hPrinter);
        return FALSE;
    }

    //通知打印服务，文档打印结束
    if(!EndDocPrinter(hPrinter))
    {
        ClosePrinter(hPrinter);
        return FALSE;
    }

    //收回handle
    ClosePrinter(hPrinter);
    return true;
}

//void printHtml(QString htmlPath)
//{
//    QFile file(htmlPath);
//    if (!file.open(QIODevice::ReadOnly | QIODevice::Text)){
//        return;
//    }

//    QString htmlContent;
//    QTextStream in(&file);
//    in >> htmlContent;

//    QTextDocument *document = new QTextDocument();
//    document->setHtml(htmlContent);

//    QPrinter printer;
//    QPrintDialog *dialog = new QPrintDialog(&printer, this);
//    if (dialog->exec() != QDialog::Accepted){
//        return;
//    }

//    document->print(&printer);
//    delete document;
//}

//void printTxt(QString txtFilePath)
//{
//    QFile txtFileOut(txtFilePath);

//    txtFileOut.open(QFile::ReadOnly | QFile::Text);
//    QTextStream txtFileIn(&txtFileOut);
//    QString txtFileToQString(txtFileIn.readAll());
//    QTextDocument *document = new QTextDocument(txtFileToQString);

//    QPrinter printer;

//    QPrintDialog *dlg = new QPrintDialog(&printer, this);
//    if (dlg->exec() != QDialog::Accepted){
//        return;
//    }
//    document->print(&printer);
//    delete document;
//}
