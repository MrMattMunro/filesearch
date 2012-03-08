//QTreeView的扩展类

#ifndef _MY_TREELIST_H_
#define _MY_TREELIST_H_

#include <QApplication>
#include <QTreeView>
#include <QList>
#include <QWidget>
#include <QStandardItem>
#include <QMouseEvent>

class myTreeList : public QTreeView
{
Q_OBJECT
public:
        myTreeList(QString title = NULL, QWidget *parent = 0);
	~myTreeList();
	void         setTreeTitle(QString title); //设置tree的名称
	void         setSubTreeTitle(int subTree,QString title);
        void         addItem(int subTree, QString itemName, QString path, QString icon); //增加item
        void         addItemByParentItem(QStandardItem *parenItem, QString itemName,  QString path, QString icon); //增加item
	void         addItems(int subTree, QList<QString> nameList);
	void         delelteItem(int subTree, QString itemName);
        bool         delSubItems(QStandardItem *parenItem);
	void         clearTree(int subTree, QString itemName);//清空所有的item
	void         enableMouse(bool yesOrNo);  //设置鼠标相应
	bool         getMouseStatus();   //查看是可以使用鼠标
	QString      getCurTitle();  //获取当前鼠标双击的title
        QString      getCurPath();   //获取当前鼠标双击的路径
	QModelIndex  getCurIndex();
        QStandardItem* getCurItem(); // 获取当前双击节点
        QPoint       getCurPoint();  // 获取当前点击位置
        void         loadDirByLay(QString parentPath, int lay, QStandardItem *curItem);
        void         delSubTree();   // 删除当前树
        void         setCurItemByPath(QString path);
private slots:
        void         showChildTree();
signals:
	//鼠标双击
	void         LBtnDbClk();
        //鼠标单击
        void         LBtnClk();
        //选中某个Item
        void         RBtnClk();
protected:
	void         mouseDoubleClickEvent(QMouseEvent *event);
        // void         mousePressEvent(QMouseEvent *event);
        void         mouseReleaseEvent(QMouseEvent *event);
        //void         mouseDoubleClickEvent(QMouseEvent *event);
        //void         mouseMoveEvent(QMouseEvent *event);
        //void         keyPressEvent(QKeyEvent *event);
    //#ifndef QT_NO_DRAGANDDROP
        //void dragMoveEvent(QDragMoveEvent *event);
    //#endif
private:
	int                   numSubTree;
	bool                  mouseStatus;
	QString               treeTitle;
	QString               curTitle; //当前鼠标双击选的名称
        QString               curPath;  //当前鼠标双击的路径
	QModelIndex           curIndex;
        QStandardItem*        curItem;
        QStandardItemModel    *model;
        QPoint                curPoint;

};

#endif
