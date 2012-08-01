#include "intelliplugin.h"
#include "uesave.h"
#include <QDebug>
#include <QWebView>

IntelliPlugin::IntelliPlugin(QWidget *parent) :
    QWebPluginFactory(parent)
{
        qDebug()<<"IntelliPlugin::IntelliPlugin()"<<endl;
        MimeType mime;
        mime.name = "application/save-plugin";
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
                        if (mimeType == "application/save-plugin") {
                                qDebug() << "create save "<<endl;
                                UeSave * uesave = new UeSave();
                                qDebug() << "finish save"<<endl;
                                return uesave;
                        }
                }
        }
        return NULL;
}

QList<IntelliPlugin::Plugin> IntelliPlugin::plugins() const
{
        Plugin plugin;
        plugin.name = "application/save-plugin";
        plugin.description = "Just for save call test";
        plugin.mimeTypes.append(m_mimeType);

        QList<IntelliPlugin::Plugin> plugList;
        plugList.append(plugin);
        return plugList;
}
