#ifndef MYNOTEPAD_H
#define MYNOTEPAD_H

#include <QMainWindow>

QT_BEGIN_NAMESPACE
namespace Ui { class Mynotepad; }
QT_END_NAMESPACE

class Mynotepad : public QMainWindow
{
    Q_OBJECT

public:
    Mynotepad(QWidget *parent = nullptr);
    ~Mynotepad();
    void New(); //新建
    void open();    //打开
    void save();    //保存
    void saveAs();  //另存为
    void selectFont(); //选择字体
    void setFontBold(bool bold); //选择加粗
    void setFontUnderline(bool underline);  //选择下划线
    void setFontItalic(bool italic);  //选择斜体
    void about(); //关于
    void Night_Light_mode(); //护眼模式
    void settingBackGround(); //设置背景图片

    void paintEvent(QPaintEvent *event); //重写paintEvent事件

private slots:

private:

    Ui::Mynotepad *ui;
    QString currentFile;
};
#endif // MYNOTEPAD_H
