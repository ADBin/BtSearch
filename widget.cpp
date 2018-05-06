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
    ui->go->setShortcut(Qt::Key_Return);
    connect(ui->go,SIGNAL(clicked()),this,SLOT(btSearch()));
    
}

Widget::~Widget()
{
    delete ui;
}

void Widget::btSearch()
{
    QString key = ui->search_key->text();

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
    QString url;// = "https://btkitty.xyz/search/"+search+"/time_1.html";
    //QString url = "https://btkitty.xyz/search/游戏人生/time_1.html";
    ui->status->setText("正在获取源btkitty...");
    QString data = "keyword="+search+"&hidden=true";
    a.post_header("http://cnbtkitty.org/",data,url);

    qDebug()<<url;
    a._spider(url,code);
    qDebug()<<code;
    if (code=="")
    {
        ui->status->setText("获取失败，404");
        return;
    }
    qDebug()<<code;
    qDebug("22222222222");

    //a.RegExp_All(code,"<a href=\"/torrent/(\\w+).html\"",get_bt);
    a.RegExp_All(code,"<a href=\"http://cnbtkitty.org/item/(\\w+)-?(\\w+)-?(\\w+).html\"",get_bt);
//    QString test="<a href=\"/torrent/(\\w+).html\"";
//    QRegExp rx(test);
//    code.indexOf(rx);
////    qDebug()<<rx.length;
//    qDebug()<<rx.cap(3);
    if (get_bt=="")
    {
        ui->status->setText("获取失败，404");
        return;
    }
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
        //btkittyBt("https://btkitty.xyz"+url_2[i]);
        btkittyBt(url_2[i]);
    }

}

void Widget::btkittyBt(QString url)
{
    QString code,get_bt;
    //------------------------
    a._spider(url,code);
    //qDebug()<<code;

   // a.RegExp_All(code,"<h2>.+</h2>",get_name);

    QString test="<h2>(.+)</h2>";
    QRegExp rx(test);
    code.indexOf(rx);
    qDebug()<<rx.cap(1);
    //------------------------
    //qDebug()<<rx.cap(0);
   // qDebug()<<get_name;
    //a.RegExp_All(code,">magnet:(.+)<",get_bt);
    //code = "<dt class='t1'><span>磁力链接：</span></dt><dd class='magnet'><a href='magnet:?xt=urn:btih:58f193105ac32bd55f8fb78325c0043240168482&amp;dn=NO%20GAME%20NO%20LIFE%20%E6%B8%B8%E6%88%8F%E4%BA%BA%E7%94%9F'>magnet:?xt=urn:btih:58f193105ac32bd55f8fb78325c0043240168482&dn=NO GAME NO LIFE 游戏人生</a></dd>";
    a.RegExp_All(code,"<a href='magnet:(.+)'>",get_bt);
    qDebug("......");
    qDebug()<<get_bt;
    qDebug("......");
    code="";
    QStringList url_1,url_2;
    a.segmentation(get_bt,"<a href='",url_1);
    a.unite(url_1,"",code);
    a.segmentation(code,"'",url_2);
    qDebug()<<url_2[0];
//    ui->textBrowser->insertPlainText(rx.cap(1)+"\n"+url_2[0]+"\n\n");

}

//alicili
void Widget::alicili(QString search)
{
    QString code;
    QString url = "http://alicili.pw/list/"+search+"/1-0-0/";
//    QString url = "http://alicili.pw/list/游戏人生/1-0-0/";
    ui->status->setText("正在获取源alicili数据...");
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
    if (all=="")
    {
        ui->status->setText("获取失败，404");
        return;
    }
    QString name_url;
    a.RegExp_All(all,"<a href='http://alicili.pw/cili/(\\w+)/' target='_blank'>",name_url);
    if (name_url=="")
    {
        ui->status->setText("获取失败，404");
        return;
    }
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
    if (get_bt=="")
    {
        ui->status->setText("获取失败，404");
        return;
    }

    qDebug()<<get_bt;
    code="";
    QStringList url_1,url_2;
    a.segmentation(get_bt,"<a href='",url_1);
    a.unite(url_1,"",code);
    a.segmentation(code,"'>magnet",url_2);
    ui->textBrowser->insertPlainText(rx.cap(1)+"\n"+url_2[0]+"\n\n");
}
