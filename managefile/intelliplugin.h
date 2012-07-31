#ifndef INTELLIPLUGIN_H
#define INTELLIPLUGIN_H

#include <QWebPluginFactory>

class IntelliPlugin : public QWebPluginFactory
{
    Q_OBJECT
public:
    explicit IntelliPlugin(QWidget *parent = 0);
    virtual ~IntelliPlugin();

    virtual QObject* create(const QString &mimeType, const QUrl &, const QStringList &argumentNames, const QStringList &argumentValues) const;
    virtual QList<IntelliPlugin::Plugin> plugins() const;

signals:

public slots:

private:
    QList<MimeType> m_mimeType;
};

#endif // INTELLIPLUGIN_H
