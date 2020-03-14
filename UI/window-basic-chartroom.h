#ifndef OBSBASICCHARTROOM_H
#define OBSBASICCHARTROOM_H

#include <QMainWindow>

QT_BEGIN_NAMESPACE
namespace Ui { class OBSBasicChartRoom; }
QT_END_NAMESPACE

class OBSBasicChartRoom : public QMainWindow
{
    Q_OBJECT

public:
    OBSBasicChartRoom(QWidget *parent = nullptr);
    ~OBSBasicChartRoom();
    void SetUseInfo(const std::string &account, const std::string &strToken,
		    int userId, int userType);

    int InitLoadMessage();

    private:
    Ui::OBSBasicChartRoom *ui;

    std::string m_account;
    std::string m_strToken;
    int m_usertype;
    int m_userId;
    int m_messageId;
};
#endif // OBSBASICCHARTROOM_H
