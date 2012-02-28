//默认的树结构只有一列两个子树
#include <QStandardItem>
#include <QMessageBox>
#include <QModelIndex>


#include "myTreeList.h"
#include "utils.h"

myTreeList::myTreeList(QString title, QWidget *parent) : treeTitle("tree"), QTreeView(parent), numSubTree(2),
    mouseStatus(true), curTitle("title")
{
	//默认两个子树的树形结构
        model = new QStandardItemModel(1,1);
        model->setHeaderData(0, Qt::Horizontal, title);
        QStandardItem  *allDocItem = new QStandardItem(tr("AllDocs"));
        allDocItem->setIcon(Utils::getIcon("expander_normal.png"));
        allDocItem->setData("alldocs", Qt::UserRole + 1);

        QStandardItem  *allTagItem = new QStandardItem(tr("AllTags"));
        allTagItem->setIcon(Utils::getIcon("expander_normal.png"));
        allTagItem->setData("alltags", Qt::UserRole + 1);

        model->setItem(0, allDocItem);
        model->setItem(1, allTagItem);

	this->setModel(model);
	this->setAnimated(true);
}

myTreeList::~myTreeList()
{
        delete model;
}

void myTreeList::setTreeTitle(QString title)
{
	model->setHeaderData(0, Qt::Horizontal, title);
}

void myTreeList::setSubTreeTitle(int subTree, QString title)
{
	model->item(subTree)->setText(title);
}

void myTreeList::addItem(int subTree, QString itemName, QString path, QString icon)
{
	QStandardItem  *parenItem = model->item(subTree);
	QStandardItem  *childItem =  new QStandardItem(itemName);
        childItem->setData(path, Qt::UserRole + 1);

        childItem->setIcon(Utils::getIcon(icon));
	parenItem->appendRow(childItem);
}

void myTreeList::addItem(QStandardItem *parenItem, QString itemName, QString path, QString icon)
{
        QStandardItem  *childItem =  new QStandardItem(itemName);
        childItem->setData(path, Qt::UserRole + 1);
        childItem->setIcon(Utils::getIcon(icon));
        parenItem->appendRow(childItem);
}

void myTreeList::addItems(int subTree, QList<QString> nameList)
{
	QStandardItem  *parenItem = model->item(subTree);
	QList<QStandardItem*> childItems;
	QStandardItem  *tmpItem = NULL;
	int   i = 0;
	
	for(i = 0; i < nameList.size(); i++)
	{
		if(tmpItem != NULL)
		{
			tmpItem = NULL;
		}
		tmpItem = new QStandardItem(nameList.at(i));
		childItems.push_back(tmpItem);
	}
	
	parenItem->appendRows(childItems);
}

void myTreeList::delelteItem(int subTree, QString itemName)
{
	QStandardItem  *parenItem = model->item(subTree);
	int  i = 0;
	
	//找出名字为itemName的子项，并将其删除
	for(i = 0; i < parenItem->rowCount(); i++)
	{	
		if(itemName == parenItem->child(i)->text())
		{
			parenItem->removeRow (i);
			break;
		}
	}
}

void myTreeList::clearTree(int subTree, QString itemName)
{
	QStandardItem  *parenItem = model->item(subTree);
	int   i = 0;
	for(i = parenItem->rowCount() - 1; i >= 0; i--)
	{
		parenItem->removeRow(i);
	}
	
}

void myTreeList::enableMouse(bool yesOrNo)
{
	mouseStatus = yesOrNo;
}

bool myTreeList::getMouseStatus()
{
	return mouseStatus;
}

QString myTreeList::getCurTitle()
{
	return curTitle;
}

QModelIndex myTreeList::getCurIndex()
{
	return curIndex;
}
QStandardItem* myTreeList::getCurItem()
{
       return curItem;
}
QString myTreeList::getCurPath()
{
        return curPath;
}

QPoint myTreeList::getCurPoint(){
      return curPoint;
}
// 左键双击
void myTreeList::mouseDoubleClickEvent(QMouseEvent *event)
{

        if(true == mouseStatus && Qt::LeftButton == event->button())
	{
                QModelIndex  index = this->currentIndex();
                curItem = model->itemFromIndex(index);

                curPath = qvariant_cast<QString>(curItem->data());

		curIndex = index;
		curTitle = index.data().toString();

		emit LBtnDbClk();
	}
}
//// 右键单击
//void myTreeList::mousePressEvent(QMouseEvent *event)
//{

//        // 左键退出
//        if( Qt::LeftButton == event->button()){
//          return;
//        }

//        if(true == mouseStatus )
//        {
//                QModelIndex  index = this->currentIndex();
//                curItem = model->itemFromIndex(index);
//                curPath = qvariant_cast<QString>(curItem->data());

//                curIndex = index;
//                curTitle = index.data().toString();
//                curPoint = event->pos();
//                emit RBtnClk();
//        }
//}

// 单击
void myTreeList::mouseReleaseEvent(QMouseEvent *event)
{
    // 设置当前目录
    QModelIndex  index = this->currentIndex();
    curItem = model->itemFromIndex(index);
    curPath = qvariant_cast<QString>(curItem->data());

    // 左键退出
    if( Qt::LeftButton == event->button()){
        emit LBtnClk();
        return;
    }

    if(true == mouseStatus && Qt::RightButton == event->button())
    {
            curIndex = index;
            curTitle = index.data().toString();
            curPoint = event->pos();
            emit RBtnClk();
    }
}


