#include <iostream>
#include "mainwindow.h"
#include "ui_mainwindow.h"


#include <QMainWindow>
#include <QNetworkAccessManager>
#include <QNetworkRequest>
#include <QNetworkReply>
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
    // QList<QNetworkCookie>  cookies = manager->cookieJar()->cookiesForUrl(qurl);
    //qDebug() <<	cookies;
    if(reply->error()==QNetworkReply::NoError){
        //qDebug() <<"success" << reply->readAll();
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
    connect(manager, SIGNAL(finished(QNetworkReply *)), this, SLOT(fin(QNetworkReply *)));

    QNetworkRequest req;
    qurl=QUrl("http://www.mutuke.com");
    req.setUrl(qurl);
    req.setHeader(QNetworkRequest::ContentTypeHeader, "application/x-www-form-urlencoded");
    QByteArray postData;
    postData.append("param1=string&");
    postData.append("param2=string");
    manager->post(req,postData);
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


