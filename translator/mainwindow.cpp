#include <iostream>
#include "mainwindow.h"
#include "ui_mainwindow.h"


#include <QMainWindow>
#include <QNetworkAccessManager>
#include <QNetworkRequest>
#include <QNetworkReply>
#include <QNetworkCookie>
#include <QNetworkCookieJar>
#include <QUrl>

#include <QByteArray>
#include <QJsonParseError>
#include <QJsonDocument>
#include <QJsonObject>
#include <QNetworkCookieJar>


using namespace std;
MainWindow::MainWindow(QWidget *parent) :
    QMainWindow(parent),
    ui(new Ui::MainWindow)
{
    ui->setupUi(this);
}

MainWindow::~MainWindow()
{
    delete ui;
}

void MainWindow::fin(QNetworkReply *reply){
    QList<QNetworkCookie>  cookies = manager->cookieJar()->cookiesForUrl(qurl);
    keepCookie.setValue(cookies);
    qDebug()<<keepCookie;
    if(reply->error()==QNetworkReply::NoError){
        qDebug() <<"success" << reply->readAll();
        MainWindow::parse(reply->readAll());
    }else{
        qDebug() << "fail" << reply->errorString();
        delete reply;
    }
}

void MainWindow::on_translate_clicked()
{
    string str=ui->lineEdit->text().toUtf8().constData();
    cout << str << endl;

    QEventLoop loop;
    manager = new QNetworkAccessManager(this);
    manager->setCookieJar(new QNetworkCookieJar(this));
    qDebug()<<"heheheh";
    connect(manager, SIGNAL(finished(QNetworkReply *)), this, SLOT(fin(QNetworkReply *)));

    QNetworkRequest req;
    //qurl=QUrl("http://www.mutuke.com");
    qurl=QUrl("http://localhost:3220/letdoit");
    req.setUrl(qurl);
    //req.setHeader(QNetworkRequest::ContentTypeHeader, "application/x-www-form-urlencoded");
    req.setHeader(QNetworkRequest::ContentTypeHeader, "text/html");
    req.setHeader(QNetworkRequest::CookieHeader,keepCookie);
    req.setRawHeader("cache-control","max-age=0");
    req.setRawHeader("accept-language", "zh-CN,zh;q=0.8,en;q=0.6");
  //  req.setRawHeader("cookie","connect.sid=s%3A0vKTJz_Jdl51g3kg116_h1LSpJKMOmoD.s5ooDUi8o%2B1prbvqlofO8gqAfF6n8jeBjzihKAaRgfc");
    req.setRawHeader("accept","text/html,application/xhtml+xml,application/xml;q=0.9,image/webp,*/*;q=0.8");
    req.setRawHeader("accept-encoding","gzip,deflate,sdch");
    QByteArray postData;
    postData.append("param1=string&");
    postData.append("param2=string");
    //manager->post(req,postData);
    manager->get(req);

    /*
    loop.exec();
    if(reply->error()==QNetworkReply::NoError){
        //qDebug() <<"success" << reply->readAll();
        MainWindow::parse(reply->readAll());
    }else{
        qDebug() << "fail" << reply->errorString();
        delete reply;
    }
    */
}

void MainWindow::parse(QByteArray data){
    QJsonParseError jsonError;//Qt5新类
            QJsonDocument json = QJsonDocument::fromJson(data, &jsonError);//Qt5新类
            qDebug() <<"what" << data;
            if(jsonError.error == QJsonParseError::NoError)//Qt5新类
            {
                if(json.isObject())
                {
                    QJsonObject obj = json.object();//Qt5新类
                     qDebug() << obj["abc"].toString();
                    if(obj.contains("weatherinfo"))
                    {
                        if(obj["weatherinfo"].isObject())
                        {
                            QJsonObject weatherObj = obj["weatherinfo"].toObject();
                            //weatherMap = weatherObj.toVariantMap();
                            //qDebug() << weatherMap;
                            //showWeather();
                            return;
                        }
                    }
                }
            }
}


