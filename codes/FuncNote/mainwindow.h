#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include <QMainWindow>
#include <QtGui>
#include <QTextCodec>

namespace Ui {
class MainWindow;
}

class MainWindow : public QMainWindow
{
    Q_OBJECT
    
public:
  explicit MainWindow(QWidget *parent = 0);
  ~MainWindow();
//  bool scanDir(QString& path);//扫描文件夹

protected:
    void PathLabShowText(QString &filepath);
    QString readFile(const QString& fpath);//读取文件
    void analysisfile();//分析文件
    void analysisfile_byReg();//通过正则表达式提取
    void analysisfile_byLine(const QString& fpath, const QString &fwname);
    void GenFileNotExist(const QString& head_note_file,const QString&  Annotation_Head,QString &Annotation_Head_Nor);//文件不存在就生成一个
    void FileConShowText(QString &fileContent);//显示区域显示文本
    QString getFileConText();//
    QString getFilename(const QString &file);//获取文件名称
    bool FindFile(const QString &path);
    void DealSingleFile(const QString& file);//处理单个文件
    void setMkdirDefaultName();//设置创建默认文件夹文件
    QString getMkdirDefaultName();//获取默认文件夹名称
    void make_dir(QString createdir);//create dir
    void convertinfores();//转换结果显示
    void beforeconvertInfo();
    void NotChooseDirInfo();
    int getFilesize(const QString& path);//获取文件大小
    QString getDate(void);//获取时间


    //////////////////////////////////////////////////
    QString createdir;//创建目录名称
private slots:
    void aboutversion();//获取版本
    QString opendirectory();//打开目录
    void opendirectoryAndScan();


    void openfile();
    void calc();//调用计算器
private:
    QString filecon;//文件内容
    Ui::MainWindow *ui;
};

#endif // MAINWINDOW_H
