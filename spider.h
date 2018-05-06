#ifndef SPIDER_H
#define SPIDER_H

#include<QRegExp>
#include <QString>
#include <QtCore>
#include<QNetworkAccessManager>
#include<QNetworkRequest>
#include<QNetworkReply>

class spider{

public:

    void _spider(QString,QString &);
    void post_header(QString,QString,QString &);
    void RegExp_All(QString,QString,QString &);
    void segmentation(QString,QString,QStringList &);
    void unite(QStringList,QString,QString &);

};

#endif // SPIDER_H
