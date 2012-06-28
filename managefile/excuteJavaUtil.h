#include "windows.h"
#include "jni.h"
#include <string>
#include <iostream>
#include <QString>
#include <QList>

using namespace std;

#ifndef EXCUTEJAVAUTIL_H
#define EXCUTEJAVAUTIL_H

namespace ExcuteJavaUtil {

bool indexFiles(QString indexpath, QList<QString> files);
string JStringToCString (JNIEnv *env, jstring str); // (jstring str, LPTSTR desc, int desc_len);
jstring NewJString(JNIEnv *env, char *str);

};

#endif
