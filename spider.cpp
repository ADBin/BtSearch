#include"spider.h"

void spider::_spider(QString url_all,QString &code)
{
    qDebug("1111111111111");
    QUrl url(url_all);
    QNetworkAccessManager manager;
    QEventLoop loop;
    qDebug() << "Reading code form " << url;
    //发出请求
    QNetworkReply *reply;
    QNetworkRequest test;
    test.setHeader(QNetworkRequest::UserAgentHeader, "Mozilla/5.0 (Windows NT 6.1; Win64; x64) AppleWebKit/537.36 (KHTML, like Gecko) Chrome/65.0.3325.181 Safari/537.36");
    test.setUrl(url);
    reply= manager.get(test);

    //请求结束并下载完成后，退出子事件循环
    QObject::connect(reply, SIGNAL(finished()), &loop, SLOT(quit()));
    //开启子事件循环
    loop.exec();

    //将读到的信息写入文件

    QTextCodec *codec = QTextCodec::codecForName("utf-8");
        //使用utf8编码, 这样可以显示中文
    code = codec->toUnicode(reply->readAll());
}

//筛选
void spider::RegExp_All(QString all,QString regexp,QString &value)
{
    QRegExp rx(regexp);
    int pos(0);
   // QString value;

    while ((pos = rx.indexIn(all, pos)) != -1)
    {
       value.push_back(rx.capturedTexts().at(0));
       pos += rx.matchedLength();
    }
}

void spider::post_header(QString url_,QString post,QString &code)
{
    QUrl url(url_);
    QNetworkAccessManager manager;
    QEventLoop loop;
    qDebug() << "Reading code form " << url;
    //发出请求
    QNetworkReply *reply;
    QNetworkRequest *test;
    test=new QNetworkRequest();
    test->setUrl(url);
    test->setRawHeader("User-Agent", "Mozilla/5.0 (Windows NT 6.1; Win64; x64) AppleWebKit/537.36 (KHTML, like Gecko) Chrome/65.0.3325.181 Safari/537.36");
    //test->setRawHeader("Upgrade-Insecure-Requests","1");
    test->setRawHeader("Referer","http://cnbtkitty.org/");

    QByteArray post_data;
    post_data.append(post);

    reply= manager.post(*test,post_data);

    //请求结束并下载完成后，退出子事件循环
    QObject::connect(reply, SIGNAL(finished()), &loop, SLOT(quit()));
    //开启子事件循环
    loop.exec();

    //qDebug()<<reply->readAll();

    code = reply->rawHeader("Location");
    //qDebug()<<reply->rawHeaderList();

}



//分割
void spider::segmentation(QString all,QString change,QStringList &value)
{
    value=all.split(change);
}

//合并
void spider::unite(QStringList all,QString a,QString &id_end)
{
   id_end=all.join(a);
}
