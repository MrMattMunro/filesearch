#include "intelliplugin.h"
#include "shineprint.h"
#include <QDebug>
#include <QWebView>

IntelliPlugin::IntelliPlugin(QWidget *parent) :
    QWebPluginFactory(parent)
{
        qDebug()<<"IntelliPlugin::IntelliPlugin()"<<endl;
        MimeType mime;
        mime.name = "application/print-plugin";
        m_mimeType.append(mime);
}

IntelliPlugin::~IntelliPlugin()
{
}

QObject* IntelliPlugin::create(const QString &mimeType, const QUrl &, const QStringList &argumentNames, const QStringList &argumentValues) const
{
        qDebug() << " IntelliPlugin::create()"<<endl;
        foreach (MimeType mime, this->m_mimeType) {
                if (!mime.name.isEmpty() && mime.name==mimeType) {
                        if (mimeType == "application/print-plugin") {
                                qDebug() << "create shine print"<<endl;
                               ShinePrint * pShinePrint = new ShinePrint();
                                qDebug() << "finish create shine print."<<endl;
                               return pShinePrint;
                        }
                }
        }
        return NULL;
}

QList<IntelliPlugin::Plugin> IntelliPlugin::plugins() const
{
        Plugin plugin;
        plugin.name = "application/print-plugin";
        plugin.description = "Just for PrintMessage call test";
        plugin.mimeTypes.append(m_mimeType);

        QList<IntelliPlugin::Plugin> plugList;
        plugList.append(plugin);
        return plugList;
}
