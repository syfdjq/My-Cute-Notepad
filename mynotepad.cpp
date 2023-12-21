#include "mynotepad.h"
#include "ui_mynotepad.h"
#include <QFile>
#include <QFileDialog>
#include <QTextStream>
#include <QMessageBox>
#include <QFont>
#include <QFontDialog>
#include <QAction>
#include <QDebug>
#include <QPixmap>
#include <QPalette>
#include <QPainter>

Mynotepad::Mynotepad(QWidget *parent)
    : QMainWindow(parent)
    , ui(new Ui::Mynotepad)
{
    ui->setupUi(this);
    connect(ui->actionnew,&QAction::triggered,this,&Mynotepad::New);
    connect(ui->actionopen,&QAction::triggered,this,&Mynotepad::open);
    connect(ui->actionsave,&QAction::triggered,this,&Mynotepad::save);
    connect(ui->actionsave_as,&QAction::triggered,this,&Mynotepad::saveAs);
#if QT_CONFIG(clipboard)
    connect(ui->textEdit, &QTextEdit::copyAvailable, ui->actionCopy, &QAction::setEnabled);
    connect(ui->actionCopy, &QAction::triggered, ui->textEdit, &QTextEdit::copy);
    connect(ui->actionCut, &QAction::triggered, ui->textEdit, &QTextEdit::cut);
    connect(ui->actionPaste, &QAction::triggered, ui->textEdit, &QTextEdit::paste);
    connect(ui->textEdit, &QTextEdit::copyAvailable, ui->actionCopy_2, &QAction::setEnabled);
    connect(ui->actionCopy_2, &QAction::triggered, ui->textEdit, &QTextEdit::copy);
    connect(ui->actionCut_2, &QAction::triggered, ui->textEdit, &QTextEdit::cut);
    connect(ui->actionPaste_2, &QAction::triggered, ui->textEdit, &QTextEdit::paste);
#endif
    connect(ui->textEdit, &QTextEdit::undoAvailable, ui->actionUndo, &QAction::setEnabled);
    connect(ui->actionUndo, &QAction::triggered, ui->textEdit, &QTextEdit::undo);
    connect(ui->textEdit, &QTextEdit::redoAvailable, ui->actionRedo, &QAction::setEnabled);
    connect(ui->actionRedo, &QAction::triggered, ui->textEdit, &QTextEdit::redo);

    connect(ui->actionFont, &QAction::triggered, this, &Mynotepad::selectFont);
    connect(ui->actionBold, &QAction::triggered, this, &Mynotepad::setFontBold);
    connect(ui->actionUnderline, &QAction::triggered, this, &Mynotepad::setFontUnderline);
    connect(ui->actionItalic, &QAction::triggered, this, &Mynotepad::setFontItalic);
    connect(ui->actionAbout, &QAction::triggered, this, &Mynotepad::about);

    connect(ui->actionBold_2, &QAction::triggered, this, &Mynotepad::setFontBold);
    connect(ui->actionUnderline_2, &QAction::triggered, this, &Mynotepad::setFontUnderline);
    connect(ui->actionItalic_2, &QAction::triggered, this, &Mynotepad::setFontItalic);
    connect(ui->actionnew_2,&QAction::triggered,this,&Mynotepad::New);
    connect(ui->actionopen_2,&QAction::triggered,this,&Mynotepad::open);
    connect(ui->actionsave_2,&QAction::triggered,this,&Mynotepad::save);
    connect(ui->actionsave_as_2,&QAction::triggered,this,&Mynotepad::saveAs);

    connect(ui->textEdit, &QTextEdit::undoAvailable, ui->actionUndo_2, &QAction::setEnabled);
    connect(ui->actionUndo_2, &QAction::triggered, ui->textEdit, &QTextEdit::undo);
    connect(ui->textEdit, &QTextEdit::redoAvailable, ui->actionRedo_2, &QAction::setEnabled);
    connect(ui->actionRedo_2, &QAction::triggered, ui->textEdit, &QTextEdit::redo);

    connect(ui->actiongreen_eye,&QAction::triggered,this,&Mynotepad::Night_Light_mode);
    //connect(ui->actionsettingBackGround,&QAction::triggered,this,&Mynotepad::settingBackGround);


    ui->textEdit->setStyleSheet("background-color: rgba(255, 255, 255,0);\n"
                                "background-attachment:fixed;\n"
                                "background-repeat:none;\n"
                                "background-position:center");


    connect(ui->actionsettingBackGround,&QAction::triggered,[&](){


    });

}

Mynotepad::~Mynotepad()
{
    delete ui;
}

void Mynotepad::New()
{
    currentFile.clear();
    ui->textEdit->setText(QString());
}
void Mynotepad::open()
{
    QString fileName = QFileDialog::getOpenFileName(this, "打开文件","","(*.txt)");
    if (fileName.isEmpty())
        return;
    QFile file(fileName);
    currentFile = fileName;
    if (!file.open(QIODevice::ReadOnly | QFile::Text)) {
        QMessageBox::warning(this, "错误", "不能打开文件: " + file.errorString());
        return;
    }
    setWindowTitle(fileName);
    QTextStream in(&file);
    QString text = in.readAll();
    ui->textEdit->setText(text);
    file.close();
}

void Mynotepad::save()
{
    QString fileName;
    if (currentFile.isEmpty()) {
        fileName = QFileDialog::getSaveFileName(this, "保存","","(*.txt)");
        if (fileName.isEmpty())
            return;
        currentFile = fileName;
    }
    else {
        fileName = currentFile;
    }
    QFile file(fileName);
    if (!file.open(QIODevice::WriteOnly | QFile::Text)) {
        QMessageBox::warning(this, "错误", "不能保存文件: " + file.errorString());
        return;
    }
    setWindowTitle(fileName);
    QTextStream out(&file);
    QString text = ui->textEdit->toPlainText();
    out << text;
    file.close();
}

void Mynotepad::saveAs()
{
    QString fileName = QFileDialog::getSaveFileName(this, "另存为","","(*.txt)");
    if (fileName.isEmpty())
        return;
    QFile file(fileName);

    if (!file.open(QFile::WriteOnly | QFile::Text)) {
        QMessageBox::warning(this, "Warning", "Cannot save file: " + file.errorString());
        return;
    }
    currentFile = fileName;
    setWindowTitle(fileName);
    QTextStream out(&file);
    QString text = ui->textEdit->toPlainText();
    out << text;
    file.close();
}

void Mynotepad::selectFont()
{
    bool fontSelected;
    QFont font = QFontDialog::getFont(&fontSelected, this);
    if (fontSelected)
        ui->textEdit->setFont(font);
}

void Mynotepad::setFontUnderline(bool underline)
{
    ui->textEdit->setFontUnderline(underline);
}

void Mynotepad::setFontItalic(bool italic)
{
    ui->textEdit->setFontItalic(italic);
}

void Mynotepad::setFontBold(bool bold)
{
    bold ? ui->textEdit->setFontWeight(QFont::Bold) :
        ui->textEdit->setFontWeight(QFont::Normal);
}

void Mynotepad::about()
{
    QMessageBox::about(this, tr("关于"),
                       tr("这个记事本是<b>成都理工大学22级计算机8班税健芝</b> 所做       "
                          "有疑问请联系 QQ:970112025"
                          "版本号:1.0"
                          "更新日期:2023.12.21"));
}

void Mynotepad::Night_Light_mode()
{
    if(ui->actiongreen_eye->isChecked()==true)
    {

        this->setStyleSheet("QMainWindow {background-color:rgb(110, 123, 108)}");
        ui->textEdit->setStyleSheet("QTextEdit {background-color:rgb(199, 237, 204)}");
    }
    else
    {
        this->setStyleSheet("");
        ui->textEdit->setStyleSheet("");
    }

}

void Mynotepad::settingBackGround()
{

//    QString image = QFileDialog::getOpenFileName(this, "打开文件");
//    Q_UNUSED(event);
//    QPainter painter(this);
//    painter.setOpacity(0.2);
//    painter.drawPixmap(rect(),QPixmap(image), QRect());

}


void Mynotepad::paintEvent(QPaintEvent *event)
{


        Q_UNUSED(event);
        QPainter painter(this);
        painter.setOpacity(0.2);
        painter.drawPixmap(rect(),QPixmap(":/notepad_rec/bkg.jpg"), QRect());


}



