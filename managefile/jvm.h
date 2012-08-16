#pragma once

#ifndef JVM_H
#define JVM_H

#endif // JVM_H

#include "windows.h"
#include "jni.h"
#include <string>
#include <iostream>
#include <QString>
#include <QList>
#include <QObject>
#include <QMap>
#include <db/docdao.h>

using namespace std;

/*! \brief A model for extensions dipslay.
Extensions are stored as a files with full path in m_values.
\author Petr Vanek <petr@scribus.info>
*/
class Jvm : public QObject
{
        Q_OBJECT

        public:
               // Jvm(QObject * parent = 0);
                ~Jvm();
                bool invokeMethod(QString clz, QString method, QString methodSign, QMap<QString, QString> parms);
                static bool BeginJVM();
                static bool EndJVM();
        private:

             //输出java异常信息
             static JNIEnv* env;
             static JavaVM* jvm;
             string JStringToCString (JNIEnv *env, jstring str); // (jstring str, LPTSTR desc, int desc_len);
             jstring NewJString(JNIEnv *env, char *str);
};

