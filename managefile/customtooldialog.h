#include <QProgressDialog>
#include "ui_customtooldialog.h"

#include <QStandardItemModel>
#include <QToolBar>
#include <QToolButton>

class ToolButton : public QToolButton
{
        Q_OBJECT
public:
        ToolButton(QWidget *parent) : QToolButton(parent)
        {
                connect(this, SIGNAL(pressed()), this, SLOT(startDrag()));
        }
        public slots:
                void startDrag()
                {
                        QDrag *dr = new QDrag(this);
                        // The data to be transferred by the drag and drop operation is contained in a QMimeData object
                        QMimeData *mimeData = new QMimeData;
                        QByteArray ba = text().toLatin1().data();
                        QString theText = "bla/x-something";
                        mimeData->setData(theText, ba);
                        // Assign ownership of the QMimeData object to the QDrag object.
                        dr->setMimeData(mimeData);
                        // Start the drag and drop operation
                        if (dr->start(Qt::MoveAction))
                                deleteLater();
                }
};

class ToolBar : public QToolBar
{
        public:
                ToolBar(QWidget *parent) : QToolBar(parent)
                {
                        setAcceptDrops(true);
                }

                void dragEnterEvent(QDragEnterEvent *event)
                {
                        if (event->mimeData()->hasFormat("bla/x-something"))
                                event->acceptProposedAction();
                }

                void dropEvent(QDropEvent *event)
                {
                        if (event->mimeData()->hasFormat("bla/x-something")) {
                                event->accept();
                                event->setDropAction(Qt::MoveAction);
                                QByteArray pieceData = event->mimeData()->data("bla/x-something");
                                QDataStream dataStream(&pieceData, QIODevice::ReadOnly);
                                ToolButton *button = new ToolButton(this);
                                button->setText(pieceData);
                                addWidget(button);
                                } else {
                                    event->ignore();
                                }
                }
};

class CustomToolDialog : public QDialog, public Ui::CustomToolDialog
{
	Q_OBJECT

	public:
                CustomToolDialog(QWidget * parent = 0);
                bool update;
                QString m_tagUuId;
                QString m_tagname;
                QString m_desp;

	private:
                QObject * m_parent;

	private slots:
                void confirmBtn_clicked();

        signals:

};
