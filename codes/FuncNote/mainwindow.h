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
//  bool scanDir(QString& path);//ɨ���ļ���

protected:
    void PathLabShowText(QString &filepath);
    QString readFile(const QString& fpath);//��ȡ�ļ�
    void analysisfile();//�����ļ�
    void analysisfile_byReg();//ͨ��������ʽ��ȡ
    void analysisfile_byLine(const QString& fpath, const QString &fwname);
    void GenFileNotExist(const QString& head_note_file,const QString&  Annotation_Head,QString &Annotation_Head_Nor);//�ļ������ھ�����һ��
    void FileConShowText(QString &fileContent);//��ʾ������ʾ�ı�
    QString getFileConText();//
    QString getFilename(const QString &file);//��ȡ�ļ�����
    bool FindFile(const QString &path);
    void DealSingleFile(const QString& file);//�������ļ�
    void setMkdirDefaultName();//���ô���Ĭ���ļ����ļ�
    QString getMkdirDefaultName();//��ȡĬ���ļ�������
    void make_dir(QString createdir);//create dir
    void convertinfores();//ת�������ʾ
    void beforeconvertInfo();
    void NotChooseDirInfo();
    int getFilesize(const QString& path);//��ȡ�ļ���С
    QString getDate(void);//��ȡʱ��


    //////////////////////////////////////////////////
    QString createdir;//����Ŀ¼����
private slots:
    void aboutversion();//��ȡ�汾
    QString opendirectory();//��Ŀ¼
    void opendirectoryAndScan();


    void openfile();
    void calc();//���ü�����
private:
    QString filecon;//�ļ�����
    Ui::MainWindow *ui;
};

#endif // MAINWINDOW_H
