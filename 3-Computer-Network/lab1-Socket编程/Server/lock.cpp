#include "lock.h"
#include<QFile>
#include <QMessageBox>
#include <QTextCodec>
lock::lock()
{

}

QString lock::encryption(const QString &st){
    QByteArray ba = st.toUtf8().toBase64();
    QString DataAsString = QTextCodec::codecForMib(106)->toUnicode(ba);
    return DataAsString;
}

QString lock::Deciphering(const QString &ds){
    QByteArray tt;
    tt.append(ds);
    QByteArray sb = QByteArray::fromBase64(tt);
    QString DataAsString = QTextCodec::codecForMib(106)->toUnicode(sb);
    return DataAsString;
}
