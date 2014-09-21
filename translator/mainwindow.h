#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include <QMainWindow>
#include <QNetworkAccessManager>
#include <QNetworkRequest>
#include <QUrl>

namespace Ui {
class MainWindow;
}

class MainWindow : public QMainWindow
{
    Q_OBJECT

public:
    explicit MainWindow(QWidget *parent = 0);
    ~MainWindow();
    void parse(QByteArray data);

private slots:
    void on_translate_clicked();
    void fin(QNetworkReply *);

private:
    Ui::MainWindow *ui;
    QNetworkAccessManager *manager;
    QUrl qurl;
    QVariant keepCookie;
};

#endif // MAINWINDOW_H
