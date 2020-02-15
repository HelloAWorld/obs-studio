#include "window-basic-webview.h"
#include "./ui_OBSBasicWebView.h"
#include <QUrl>>

OBSBasicWebView::OBSBasicWebView(QWidget *parent)
    : QMainWindow(parent)
    , ui(new Ui::OBSBasicWebView)
{
    ui->setupUi(this);

    m_webview = new QWebEngineView(this);
    m_webview->load(QUrl("http://www.baidu.com"));
    m_webview->resize(this->width(), this->height());
    m_webview->showMaximized();
}

OBSBasicWebView::~OBSBasicWebView()
{
    delete ui;
}

