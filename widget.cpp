#include "widget.h"
#include "ui_widget.h"


Widget::Widget(QWidget *parent) :
    QWidget(parent),
    ui(new Ui::Widget)
{
    ui->setupUi(this);
//    alicili("key");
    //btkitty("key");
    //btkittyBt("https://btkitty.xyz/torrent/087deead494db1d9bd307d85420fbf2a9e67287a.html");
    connect(ui->go,SIGNAL(clicked()),this,SLOT(btSearch()));

}

Widget::~Widget()
{
    delete ui;
}

void Widget::btSearch()
{
    QString key = ui->search_key->text();
//    QString test;
//    a._spider(key,test);
//    ui->textBrowser->insertPlainText(test);
    ui->textBrowser->setPlainText("");
    if (key == "")
        return;
    btkitty(key);
    ui->textBrowser->insertPlainText("==============================\n==============================\n");
    alicili(key);
    ui->status->setText("完成");
}


//btkitty
void Widget::btkitty(QString search)
{
    QString code,get_bt;
    QString url = "https://btkitty.xyz/search/"+search+"/time_1.html";
    //QString url = "https://btkitty.xyz/search/游戏人生/time_1.html";
    ui->status->setText("获取源一数据...");

    a._spider(url,code);
    if (code=="")
    {
        ui->status->setText("获取失败，404");
        return;
    }
    qDebug()<<code;
    qDebug("22222222222");

    a.RegExp_All(code,"<a href=\"/torrent/(\\w+).html\"",get_bt);


    qDebug()<<get_bt;
    code="";
    QStringList url_1,url_2;
    a.segmentation(get_bt,"<a href=\"",url_1);
    a.unite(url_1,"",code);
    a.segmentation(code,"\"",url_2);
    //btkittyBt("https://btkitty.xyz"+url_2[0]);
    for(int i=0;i<url_2.length()-1;i++)
    {
        qDebug()<<url_2[i];
        btkittyBt("https://btkitty.xyz"+url_2[i]);
    }

}

void Widget::btkittyBt(QString url)
{
    QString code,get_bt;
    a._spider(url,code);
    //qDebug()<<code;

   // a.RegExp_All(code,"<h2>.+</h2>",get_name);
    QString test="<h2>(.+)</h2>";
    QRegExp rx(test);
    code.indexOf(rx);
    qDebug()<<rx.cap(1);
    //qDebug()<<rx.cap(0);
   // qDebug()<<get_name;
    a.RegExp_All(code,">magnet:(.+)<",get_bt);
    //qDebug()<<get_bt;
    code="";
    QStringList url_1,url_2;
    a.segmentation(get_bt,">",url_1);
    a.unite(url_1,"",code);
    a.segmentation(code,"<",url_2);
    qDebug()<<url_2[0];
    ui->textBrowser->insertPlainText(rx.cap(1)+"\n"+url_2[0]+"\n\n");

}

//alicili
void Widget::alicili(QString search)
{
    QString code;
    QString url = "http://alicili.pw/list/"+search+"/1-0-0/";
//    QString url = "http://alicili.pw/list/游戏人生/1-0-0/";
    ui->status->setText("获取源二数据...");
    a._spider(url,code);
    if (code=="")
    {
        ui->status->setText("获取失败，404");
        return;
    }
    QString all;
   // qDebug()<<code;
    a.RegExp_All(code,"<dl class='item'>.*<div class=\"pages\">",all);
   // qDebug()<<all;
    code="";
    QString name_url;
    a.RegExp_All(all,"<a href='http://alicili.pw/cili/(\\w+)/' target='_blank'>",name_url);
    qDebug()<<name_url;
    QStringList url_1,url_2;
    a.segmentation(name_url,"<a href='",url_1);
    a.unite(url_1,"",code);
    a.segmentation(code,"' target='_blank'>",url_2);
    for(int i=0;i<url_2.length()-1;i++)
    {
        qDebug()<<url_2[i];
        aliciliBt(url_2[i]);
    }
    //aliciliBt(url_2[0]);
}
void Widget::aliciliBt(QString url)
{
    QString code,get_bt;
    a._spider(url,code);
    qDebug()<<code;

    QString test="<h2>(.+)</h2>";
    QRegExp rx(test);
    code.indexOf(rx);
    qDebug()<<rx.cap(1);
    a.RegExp_All(code,"<a href='magnet.*'>magnet",get_bt);
    qDebug()<<get_bt;
    code="";
    QStringList url_1,url_2;
    a.segmentation(get_bt,"<a href='",url_1);
    a.unite(url_1,"",code);
    a.segmentation(code,"'>magnet",url_2);
    ui->textBrowser->insertPlainText(rx.cap(1)+"\n"+url_2[0]+"\n\n");
}
