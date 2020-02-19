#ifndef OBSBASICWEBVIEW_H
#define OBSBASICWEBVIEW_H

#include <QMainWindow>
#include <QtWebEngineWidgets/QWebEngineView>

QT_BEGIN_NAMESPACE
namespace Ui { class OBSBasicWebView; }
QT_END_NAMESPACE

class OBSBasicWebView : public QMainWindow
{
    Q_OBJECT

public:
    OBSBasicWebView(QWidget *parent = nullptr);
    ~OBSBasicWebView();

    void OBSInit();

   private:
    Ui::OBSBasicWebView *ui;
    QWebEngineView * m_webview;
};
#endif // OBSBASICWEBVIEW_H
