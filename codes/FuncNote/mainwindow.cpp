#include "mainwindow.h"
#include "ui_mainwindow.h"
#include "version.h"
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <Windows.h>

#include <iostream>
#include <shellapi.h>
#include <QRegExp>
#include <QDir>
#include <QFile>
#include <QFileInfo>
#include <QFileInfoList>

using namespace std;


bool FindFile(QString& path);

MainWindow::MainWindow(QWidget *parent) :
    QMainWindow(parent),
    ui(new Ui::MainWindow)
{
    QTextCodec::setCodecForLocale(QTextCodec::codecForName("GBK"));
    QTextCodec::setCodecForCStrings(QTextCodec::codecForName("GBK"));
    QTextCodec::setCodecForTr(QTextCodec::codecForName("GBK"));


    ui->setupUi(this);
    //关闭按钮
    connect(this->ui->closepushBtn,SIGNAL(clicked()),qApp,SLOT(closeAllWindows()));
    connect(this->ui->closepushBtn,SIGNAL(released()),qApp,SLOT(closeAllWindows()));

    connect(this->ui->aboutpushBtn,SIGNAL(clicked()),this,SLOT(aboutversion()));//程序版本

    connect(ui->broserpushBtn,SIGNAL(clicked()),this,SLOT(openfile()));

    connect(ui->calcpushBtn,SIGNAL(clicked()),this,SLOT(calc()));

    connect(ui->broserdirpushBtn,SIGNAL(clicked()),this,SLOT(opendirectoryAndScan()));

}
void MainWindow::aboutversion()
{
    char buf[64];

    sprintf(buf,"%s<font color='red'>%s</font>",prefixnoteversion,noteversion);
    //    snprintf(buf,sizeof(buf),"<font color='red'>%s</font>",noteversion);
    QMessageBox::about(NULL, "NoteVer", buf);
}
void MainWindow::openfile()
{
    beforeconvertInfo();
    QString file=QFileDialog::getOpenFileName(this,"打开源程序目录或文件"," ","file(*.c *.cpp)");
    qDebug()<<"file name is:"<<file<<endl;

    if(!file.isEmpty()){
        PathLabShowText(file);
    }else{
        return;
    }
    DealSingleFile(file);
    convertinfores();

}
void MainWindow::make_dir(QString createdir)
{
    QDir *temp = new QDir;
    bool exist = temp->exists(createdir);
    if(exist){
        //QMessageBox::warning(this,tr("创建文件夹"),tr("文件夹已经存在！"));
    }
    else
    {
        bool ok = temp->mkdir(createdir);
        //      if( ok )
        //        QMessageBox::warning(this,tr("创建文件夹"),tr("文件夹创建成功！"));
    }
}
void MainWindow::setMkdirDefaultName()
{
   createdir="./Annotation";
}
QString MainWindow::getMkdirDefaultName()
{
   return createdir;
}
void MainWindow::DealSingleFile(const QString& file)
{
    qDebug()<<"begin to deal with==>"<<file<<endl;
    if(file.endsWith(".cpp")||file.endsWith(".c"))
    {
        qDebug()<<"good files"<<endl;
    }else{
        qDebug()<<"bad files"<<endl;
        return;
    }

    filecon=readFile(file);
    FileConShowText(filecon);
    QString convertfile=getFilename(file);

    setMkdirDefaultName();
    make_dir(createdir);
//    bool exist = temp->exists(createdir);
//    if(exist){
//        //QMessageBox::warning(this,tr("创建文件夹"),tr("文件夹已经存在！"));
//    }
//    else
//    {
//        bool ok = temp->mkdir(createdir);
//        //      if( ok )
//        //        QMessageBox::warning(this,tr("创建文件夹"),tr("文件夹创建成功！"));
//    }
    QString lastFile=createdir+'/'+convertfile;

    analysisfile_byLine(file,lastFile);
}

void MainWindow::opendirectoryAndScan()
{
    beforeconvertInfo();
    QString dirname=opendirectory();
    qDebug()<<"==>>>dirname::"<<endl;
    if(dirname.isEmpty()){
        NotChooseDirInfo();
        return;
    }
    FindFile(dirname);
    convertinfores();

}
int MainWindow::getFilesize(const QString& path)
{
    QFile file(path);
    if (!file.open(QIODevice::ReadOnly)) return -1;
    qDebug() << file.size();
    file.close();
    return file.size();
}

QString MainWindow::opendirectory()
{

#if 1
    //  选择文件夹

    QFileDialog* openFilePath = new QFileDialog( this, " 请选择文件夹", "file");     //打开一个目录选择对话框
    openFilePath->setFileMode(QFileDialog::DirectoryOnly);
#if 0
    if ( openFilePath->exec() == QDialog::Accepted )
    {
        //code here！
        qDebug()<<"==>>dir path::"<<openFilePath->selectedFiles()<<endl;
        qDebug()<<"==>>dir path::"<<openFilePath->selectedFilter()<<endl;
        qDebug()<<"==>>dir path::"<<openFilePath->selectedNameFilter()<<endl;
        qDebug()<<"==>>dir path::"<<openFilePath->getExistingDirectory(this)<<endl;
    }
#else
    setMkdirDefaultName();
    QString dirname=openFilePath->getExistingDirectory(this);
//    make_dir(getMkdirDefaultName()+"_"+dirname);
    qDebug()<<"==>>dir path::"<<dirname;
    if(dirname.isEmpty()||dirname == ""){
        delete openFilePath;
        return NULL;
    }
#endif
    delete openFilePath;

    return dirname;


#else
    //此为撕开目录
    //  QString path=QDir::currentPath();
    //  path.replace("/","\\");
    //  QProcess::startDetached("explorer "+path);
#endif

}
bool MainWindow::FindFile(const QString& path)
{
    QDir dir(path);

    if (!dir.exists())
        return false;

    dir.setFilter(QDir::Dirs|QDir::Files);//除了目录或文件，其他的过滤掉

    dir.setSorting(QDir::DirsFirst);//优先显示目录

    QFileInfoList list = dir.entryInfoList();//获取文件信息列表

    int i = 0;

    bool bIsDir;
    unsigned int nFiles=0;
    do{

        QFileInfo fileInfo = list.at(i);

        if(fileInfo.fileName()=="."|fileInfo.fileName()=="..")

        {

            i++;

            continue;

        }

        bIsDir = fileInfo.isDir();

        if (bIsDir)

        {

            nFiles++;                //对文件属性进行处理

            //fileInfo.size(),fileInfo.fileName(),fileInfo.path()

            FindFile(fileInfo.filePath());

        }

        else

        {
            //此为文件
            qDebug()<<"==>>file::"<<fileInfo.fileName();
            qDebug()<<"==>>file path::"<<fileInfo.absoluteFilePath();
            DealSingleFile(fileInfo.absoluteFilePath());

            nFiles++;

        }

        i++;

    }

    while(i<list.size());
    qDebug()<<"Find "<<nFiles<<"files";


}

QString MainWindow::getFilename(const QString& file)
{
    char bufname[1024];
    strncpy(bufname,file.toLocal8Bit(),sizeof(bufname));
    qDebug()<<"==>>bufname::"<<bufname;
    char *p=strrchr(bufname,'/');
    if(p){
        p++;
    }else{
        p=bufname;
    }
    qDebug()<<"==>>lastname:"<<p;
    QString normaliStr=QString(p)+".txt";
    //  normaliStr.replace(".cpp",".txt");
    //  normaliStr.replace(".c",".txt");
    //  normaliStr.replace(".h",".txt");
    //  normaliStr.replace(".","_Note.");

    return normaliStr;
}

void MainWindow::FileConShowText(QString &fileContent)
{
    this->ui->fileContextBrowser->setText(fileContent);
}
QString MainWindow::getFileConText()
{
    return filecon;
}

void MainWindow::analysisfile()
{

    if(getFileConText().isEmpty())
        return;
    char buf[102400];
    char tmpbuf[102400];
    strcpy(buf,filecon.toLocal8Bit().data());
    qDebug()<<"filecon:=====================================\n"<<buf;
    int filelen=strlen(buf);
    int funcnums=0;
    for(int i=0,k=0;i<filelen+1;i++)
    {

        if(buf[i]==')'&&buf[i+1]=='\n'&&buf[i+2]=='{'){
            qDebug()<<":::::::::::::got one func\n";
            tmpbuf[k]=buf[i];k++;


            funcnums++;
            continue;

        }
        tmpbuf[k]=buf[i];
    }
    qDebug()<<"funcnums:"<<funcnums<<endl;
    filecon.replace(")\n{",")\n/*我的注释是*/\n{");
    FileConShowText(filecon);

}

void MainWindow::analysisfile_byReg()
{
#if 1

    //  QString pattern("\"([\:\/\\\.a-zA-Z0-9]+\.html)\"");
    //  QString pattern("\w.*\)\n{");//用来提取函数定义一行

    //\w.*\)\n

    //  QString pattern("(.*)=(.*)");
    //  QString pattern("[^\w+)\n\{]");//用来提取函数定义一行
    QString pattern("\w.*\)$");//用来提取函数定义一行
    QRegExp rx(pattern);

    //  QString str("a=100");
    //  qDebug()<<filecon<<endl;
    //  QString str=filecon;
    QString str="void MainWindow::aboutversion()";
    int pos = str.indexOf(rx);              // 0, position of the first match.
    // Returns -1 if str is not found.
    // You can also use rx.indexIn(str);
    qDebug() <<"qgrex==========::"<<pos;
    if ( pos >= 0 )
    {
        qDebug() << rx.matchedLength();     // 5, length of the last matched string
        // or -1 if there was no match
        qDebug() << rx.capturedTexts();     // QStringList("a=100", "a", "100"),
        //   0: text matching pattern
        //   1: text captured by the 1st ()
        //   2: text captured by the 2nd ()

        qDebug() << rx.cap(0);              // a=100, text matching pattern
        qDebug() << rx.cap(1);              // a, text captured by the nth ()
        qDebug() << rx.cap(2);              // 100,

        qDebug() << rx.pos(0);              // 0, position of the nth captured text
        qDebug() << rx.pos(1);              // 0
        qDebug() << rx.pos(2);              // 2
    }
#else
    QString pattern("(.*)=(.*)");
    QRegExp rx(pattern);

    QString str("a=100");
    int pos = str.indexOf(rx);              // 0, position of the first match.
    // Returns -1 if str is not found.
    // You can also use rx.indexIn(str);
    qDebug() << pos;
    if ( pos >= 0 )
    {
        qDebug() << rx.matchedLength();     // 5, length of the last matched string
        // or -1 if there was no match
        qDebug() << rx.capturedTexts();     // QStringList("a=100", "a", "100"),
        //   0: text matching pattern
        //   1: text captured by the 1st ()
        //   2: text captured by the 2nd ()

        qDebug() << rx.cap(0);              // a=100, text matching pattern
        qDebug() << rx.cap(1);              // a, text captured by the nth ()
        qDebug() << rx.cap(2);              // 100,

        qDebug() << rx.pos(0);              // 0, position of the nth captured text
        qDebug() << rx.pos(1);              // 0
        qDebug() << rx.pos(2);              // 2
    }

#endif


}
void MainWindow::GenFileNotExist(const QString& head_note_file,const QString&  Annotation_Head,QString& Annotation_Head_Nor)
{
    QFile filehead_note(head_note_file);
    //如果注释头文件不存在，则生成一个默认的
    if(filehead_note.exists()){
        qDebug()<<head_note_file<<" exist!!"<<endl;
        Annotation_Head_Nor=readFile(head_note_file);//这里就可以修改文件来改变相关的内容了。
    }else{
        if(!filehead_note.open(QIODevice::WriteOnly|QIODevice::Text))
        {
            qDebug()<<"Open file failure!";
            return;
        }else{
            filehead_note.write(Annotation_Head.toLocal8Bit());//
            Annotation_Head_Nor=Annotation_Head;
            filehead_note.close();
        }
    }
    filehead_note.close();

}
QString MainWindow::getDate(void)
{
    QDateTime dt;
    QTime time;
    QDate date;
    dt.setTime(time.currentTime());
    dt.setDate(date.currentDate());
    return dt.toString("yyyy/MM/dd hh:mm:ss");
}

void MainWindow::analysisfile_byLine(const QString& fpath,const QString &fwname)
{
    if(fpath.isEmpty())
        return ;

    QFile file(fpath);
    QFile filew(fwname);
    if(!file.open(QIODevice::ReadOnly|QIODevice::Text))
    {
        qDebug()<<"Open file failure!";
        return;
    }
    if(!filew.open(QIODevice::WriteOnly|QIODevice::Text)){
        qDebug()<<"Open file failure!";
        return;
    }
    QString  Annotation_Head=\
            "/*****************************************************************************\n"
            "*author:\n"
            "*time  :\n"
            "*****************************************************************************/\n";
    QString Annotation_Head_Nor;
    Annotation_Head_Nor.clear();
    QString  Annotation_Fun="/*****************************************************************************\n"
            "*FUNC:\n"
            "*IN:\n"
            "*OUT:\n"
            "*****************************************************************************/\n";
    QString Annotation_Fun_Nor;
    Annotation_Fun_Nor.clear();
    //注释文件头内容
    QString head_note_file="./head_Annotation.txt";
    QString fun_note_file="./fun_Annotation.txt";

    GenFileNotExist(head_note_file,Annotation_Head,Annotation_Head_Nor);
    GenFileNotExist(fun_note_file,Annotation_Fun,Annotation_Fun_Nor);

    QString FunList;
    FunList.clear();
    FunList+="//"+getDate()+"\n";
    FunList+=Annotation_Head_Nor;
    QTextStream fs(&file);

    int firsttime=0;
    QString line;
    QString secline;
    QString thirdline;
    QString fourthline;
    QString fifthline;
    QString sixthline;
    char *pstr=NULL;
    int LineFlag=1;//标记读几行，默认为1行

#define IFINVALIDCONTINUE(A) \
    do{\
    if(line.contains(A)){\
    printf("%s sign make continue\n",A);\
    LineFlag=2;\
    continue;\
}\
}while(0)
#define CLEARSTR(LINE) LINE.clear()
#define GETFSLINE(LINE) LINE=fs.readLine()

    while(!fs.atEnd()){
        if(0==firsttime){
            line=fs.readLine();//读第一行
            secline=fs.readLine();//读第二行
            thirdline=fs.readLine();//读第三行
            fourthline=fs.readLine();//读第4行
            fifthline=fs.readLine();//读第5行
            sixthline=fs.readLine();//读第6行
            firsttime++;
        }else if(1==LineFlag){

        }else if(2==LineFlag){//依次将变量替换即可
            CLEARSTR(line);
            line=secline;
            CLEARSTR(secline);
            secline=thirdline;
            CLEARSTR(thirdline);
            thirdline=fourthline;
            CLEARSTR(fourthline);
            fourthline=fifthline;
            CLEARSTR(fifthline);
            fifthline=sixthline;
            CLEARSTR(sixthline);
            sixthline=fs.readLine();

        }else if(3==LineFlag){//需要多读两行，即略去表达式的两行
            CLEARSTR(line);
            line=fourthline;
            CLEARSTR(secline);
            secline=fifthline;
            CLEARSTR(thirdline);
            thirdline=sixthline;
            CLEARSTR(fourthline);
            fourthline=fs.readLine();
            CLEARSTR(fifthline);
            fifthline=fs.readLine();
            CLEARSTR(sixthline);
            sixthline=fs.readLine();
        }else if(4==LineFlag){//需要多读三行,即略去表达式的三行
            CLEARSTR(line);
            line=fifthline;
            CLEARSTR(secline);
            secline=sixthline;
            CLEARSTR(thirdline);
            thirdline=fs.readLine();
            CLEARSTR(fourthline);
            fourthline=fs.readLine();
            CLEARSTR(fifthline);
            fifthline=fs.readLine();
            CLEARSTR(sixthline);
            sixthline=fs.readLine();
        }else if(5==LineFlag){
            CLEARSTR(line);
            line=sixthline;
            CLEARSTR(secline);
            secline=fs.readLine();
            CLEARSTR(thirdline);
            thirdline=fs.readLine();
            CLEARSTR(fourthline);
            fourthline=fs.readLine();
            CLEARSTR(fifthline);
            fifthline=fs.readLine();
        }else if(6==LineFlag){
            CLEARSTR(line);
            line=fs.readLine();
            CLEARSTR(secline);
            secline=fs.readLine();
            CLEARSTR(thirdline);
            thirdline=fs.readLine();
            CLEARSTR(fourthline);
            fourthline=fs.readLine();
            CLEARSTR(fifthline);
            fifthline=fs.readLine();
            sixthline.clear();
            sixthline=fs.readLine();

        }
        cout<<"line :"<<line.toLocal8Bit().data()<<endl;
        //此处的行数为表达式的行数，不包含｛所在的行数，
//处理函数表达式有分五行显示的特殊情况，【逗号+一个空格】
        if((line.endsWith(",")||line.endsWith(", "))
                &&(secline.endsWith(",")||secline.endsWith(", "))
                &&(thirdline.endsWith(",")||thirdline.endsWith(", "))
                &&(fourthline.endsWith(",")||fourthline.endsWith(", "))
                &&fifthline.endsWith(")")
                &&sixthline=="{")
            goto SIXLINELAB;
        if((line.endsWith(",")||line.endsWith(", "))
                &&(secline.endsWith(",")||secline.endsWith(", "))
                &&fifthline.endsWith(")")
                &&sixthline=="{")
            goto SIXLINELAB;



        //处理函数表达式有分四行显示的特殊情况，【逗号+一个空格】
//        if(line.endsWith(",")&&secline.endsWith(",")&&thirdline.endsWith(",")
//                &&fourthline.endsWith(")")&&fifthline=="{")
//            goto FIVELINELAB;
        if((line.endsWith(",")||line.endsWith(", "))
                &&(secline.endsWith(",")||secline.endsWith(", "))
                &&(thirdline.endsWith(",")||thirdline.endsWith(", "))
                &&fourthline.endsWith(")")
                &&fifthline=="{")
            goto FIVELINELAB;
        if((line.endsWith(",")||line.endsWith(", "))
                &&(secline.endsWith(",")||secline.endsWith(", "))
                &&fourthline.endsWith(")")
                &&fifthline=="{")
            goto FIVELINELAB;
        //v1.2.4添加对特殊情况的处理，比如第四行末尾const QWidget *widget) const
        if((line.endsWith(",")||line.endsWith(", "))
                &&(secline.endsWith(",")||secline.endsWith(", "))
                &&(thirdline.endsWith(",")||thirdline.endsWith(", "))
                &&fourthline.contains(")")
                &&fifthline=="{")
            goto FIVELINELAB;

        //v1.2.4添加对特殊情况的处理，
/*
GR_CURSOR_ID
GrNewCursor(GR_SIZE width, GR_SIZE height, GR_COORD hotx, GR_COORD hoty,
    GR_COLOR foreground, GR_COLOR background,
    GR_BITMAP *fgbitmap, GR_BITMAP *bgbitmap)
{
*/
        if((line.length()>2||line.contains(" "))
                &&(secline.endsWith(",")||secline.endsWith(", "))
                &&(thirdline.endsWith(",")||thirdline.endsWith(", "))
                &&fourthline.contains(")")
                &&fifthline=="{")
            goto FIVELINELAB;
        //v1.2.4添加对特殊情况的处理，
        /*
u_int32_t checksum (buf, nbytes, sum)
    unsigned char *buf;
    unsigned nbytes;
    u_int32_t sum;
{
*/
        if((line.length()>2&&line.endsWith(")"))
                &&(secline.endsWith(";")||secline.endsWith("; "))
                &&(thirdline.endsWith(";")||thirdline.endsWith("; "))
                &&(fourthline.contains(";")||fourthline.contains("; "))
                &&fifthline=="{")
            goto FIVELINELAB;




        //处理有三行的特殊情况：
        if((line.endsWith(",")||line.endsWith(", "))
                &&thirdline.endsWith(")")
                &&fourthline=="{")
            goto FOURTHLINELAB;
        if(line.endsWith(",")&&secline.endsWith(",")&&thirdline.endsWith(")")&&fourthline=="{")
            goto FOURTHLINELAB;
        if(line.endsWith("(")//这里比较特殊，一般是没有的，以此添加
                &&secline.endsWith(",")
                &&thirdline.endsWith(")")
                &&fourthline=="{")
            goto FOURTHLINELAB;
        //v1.2.4添加对特殊情况的处理，比如第三行末尾QStyleHintReturn *returnData) const
        if((line.endsWith(",")||line.endsWith(", "))
                &&(secline.endsWith(",")||secline.endsWith(", "))
                &&thirdline.contains(")")
                &&fourthline=="{")
            goto FOURTHLINELAB;


 //v1.2.4添加对特殊情况的处理
        /*
static GR_BOOL
GetTypedEventCallback(GR_WINDOW_ID wid, GR_EVENT_MASK mask, GR_UPDATE_TYPE update,
    GR_EVENT *ep, void *arg)
{*/
        if((line.length()>2||line.contains(" "))
                &&!line.contains("/*")
                &&!line.contains("*/")
                &&!line.contains(";")
                &&!line.contains("#")
                &&(secline.endsWith(",")||secline.endsWith(", "))
                &&thirdline.contains(")")
                &&fourthline=="{")
            goto FOURTHLINELAB;

        //v1.2.4添加对特殊情况的处理，
        /*
u_int32_t checksum (buf, nbytes)
    unsigned char *buf;
    unsigned nbytes;
{
*/
        if((line.length()>2&&line.endsWith(")"))
                &&(secline.endsWith(";")||secline.endsWith("; "))
                &&(thirdline.endsWith(";")||thirdline.endsWith("; "))
                &&fourthline=="{")
            goto FOURTHLINELAB;






        //处理函数表达式有分两行显示的特殊情况
        if(line.endsWith(",")&&secline.endsWith(")")&&thirdline=="{")
            goto THIRDLINELAB;
        //处理函数表达式有分两行显示的特殊情况，【逗号+一个空格】
        if(line.endsWith(", ")&&secline.endsWith(")")&&thirdline=="{")
            goto THIRDLINELAB;
        //v1.2.4添加对特殊情况的处理，比如第二行末尾为const
        if((line.endsWith(", ")||line.endsWith(","))&&thirdline=="{")
            goto THIRDLINELAB;
        //v1.2.4添加对特殊情况的处理，比如第二行末尾为: QTableWidget(parent)
        if((line.endsWith(")")||line.endsWith(") "))
                &&line.contains("::")
                &&secline.contains(":")
                &&thirdline=="{")
            goto THIRDLINELAB;
        //v1.2.4添加对特殊情况的处理，比如第二行末尾
        /*
        ataInGasPumpXmlFormat(//firstline
                const QString &fileName)//secondline
        */
        if((line.endsWith("(")||line.endsWith("( "))
                &&secline.contains(")")
                &&thirdline=="{")
            goto THIRDLINELAB;
        //v1.2.4添加对特殊情况的处理，比如第一行末尾
        /*
void
GrClose(void)
{
*/
        if((line.contains(" ")||line.endsWith("static ")
            ||line.endsWith("int")
            ||line.endsWith("void"))
                &&!line.contains("/*")
                &&!line.contains("*/")
                &&!line.contains(";")
                &&!line.contains("#")
                &&secline.contains(")")
                &&thirdline=="{")
            goto THIRDLINELAB;
        //v1.2.4添加对特殊情况的处理，比如第一行末尾
        /*GR_COLOR
          GrGetSysColor(int index)
        */
        if(line.length()>2
                &&!line.contains("/*")
                &&!line.contains("*/")
                &&!line.contains(";")
                &&!line.contains("#")
                &&secline.contains(")")
                &&secline.contains("(")
                &&thirdline=="{")
            goto THIRDLINELAB;

        //v1.2.4添加对特殊情况的处理，
        /*
u_int32_t checksum (buf)
    unsigned char *buf;
{
*/
        if((line.length()>2&&line.endsWith(")"))
                &&(secline.endsWith(";")||secline.endsWith("; "))
                &&thirdline=="{")
            goto THIRDLINELAB;






        if(line.isEmpty()){
            LineFlag=2;
            continue;
        }
        if(line.length()<4){
            LineFlag=2;
            continue;
        }
        //        if(!line.endsWith(")"))continue;
        IFINVALIDCONTINUE("\/\/");
        IFINVALIDCONTINUE("if(");
        IFINVALIDCONTINUE("while(");
        IFINVALIDCONTINUE("==");
        IFINVALIDCONTINUE("=");
        IFINVALIDCONTINUE(":");
        IFINVALIDCONTINUE("<");
        IFINVALIDCONTINUE(">");
        IFINVALIDCONTINUE("&&");
        IFINVALIDCONTINUE("!=");
        IFINVALIDCONTINUE("++");
        IFINVALIDCONTINUE("+");
        IFINVALIDCONTINUE("||");
        IFINVALIDCONTINUE(";");
        IFINVALIDCONTINUE("-");
        IFINVALIDCONTINUE("\/");
        IFINVALIDCONTINUE("?");
        IFINVALIDCONTINUE("!");
        IFINVALIDCONTINUE(".");
        IFINVALIDCONTINUE("^");
        IFINVALIDCONTINUE("\"");
        IFINVALIDCONTINUE("'");
        IFINVALIDCONTINUE("))");


        //        if(line.endsWith(")")&&secline.endsWith("{"));
        //        if(!line.endsWith(")")&&secline.endsWith("{"));
        //        if(!secline.endsWith("{"))continue;
        if(secline!="{"||line.contains("=")||line.contains("typedef ")){
            LineFlag=2;
            continue;
        }
        //        if(secline.s)
        pstr=line.toLocal8Bit().data();
        if('*'==pstr[0]){
            LineFlag=2;
            continue;
        }
        //      qDebug()<<"=>:"<<line;
        FunList += Annotation_Fun_Nor+line+";\n";
//        qDebug()<<"LineFlag:"<<LineFlag<<",FunIs:"<<FunList<<endl;
//        qDebug()<<"LineFlag:"<<LineFlag<<endl;
        LineFlag=2;
        qDebug()<<"LineFlag:"<<LineFlag<<endl;
        continue;


THIRDLINELAB:
        FunList += Annotation_Fun_Nor+line+"\n"+secline+";\n";
        LineFlag=3;
        qDebug()<<"LineFlag:"<<LineFlag<<endl;
        continue;

FOURTHLINELAB:
        FunList += Annotation_Fun_Nor+line+"\n"+secline+"\n"+thirdline
                +";\n";
        //这儿就需要至少三两行了

        LineFlag=4;
        qDebug()<<"LineFlag:"<<LineFlag<<endl;
        continue;


FIVELINELAB:
        FunList += Annotation_Fun_Nor+line+"\n"+secline+"\n"+thirdline
                +"\n"+fourthline+";\n";
        //这儿就需要至少读四行了
        LineFlag=5;
        qDebug()<<"LineFlag:"<<LineFlag<<endl;

        continue;

SIXLINELAB:
        FunList += Annotation_Fun_Nor
                +line+"\n"
                +secline+"\n"
                +thirdline+"\n"
                +fourthline+"\n"
                +fifthline
                +";\n";
        //这儿就需要至少读五行了
        LineFlag=6;
        qDebug()<<"LineFlag:"<<LineFlag<<endl;

        continue;
    }
#if 1

    if(!FunList.compare(Annotation_Head_Nor)){//如果文件中没有函数，则不写入文件了,效果不太好用啊

    }else{
        filew.write("//"+fpath.toLocal8Bit()+"\n");
        filew.write(FunList.toLocal8Bit());
    }
#else
    filew.write(FunList.toLocal8Bit());
#endif
    filew.close();

    if(getFilesize(fwname)<=0)
    {
        remove(fwname.toLocal8Bit().data());
        unlink(fwname.toLocal8Bit().data());
    }

    ui->edittextEdit->setText(FunList);
    file.close();

}

QString MainWindow::readFile(const QString& fpath)
{
    if(fpath.isEmpty())
        return "";

    QFile file(fpath);

    if(!file.open(QIODevice::ReadOnly|QIODevice::Text))
    {
        qDebug()<<"Open file failure!";
        return "";
    }
    QTextStream fs(&file);
    QString fileContent (fs.readAll());

    //    qDebug()<<"The content of file is \n"<<fileContent;
    file.close();
    return fileContent;
}
void MainWindow::PathLabShowText(QString &filepath)
{
    this->ui->pathlab->setText(filepath);
}

void MainWindow::calc()
{
    //调用记事本
    ShellExecuteA(NULL,"open","NOTEPAD.EXE",NULL,NULL,SW_SHOWNORMAL);
    //调用计算器
    ShellExecuteA(NULL,"open","calc.exe",NULL,NULL,SW_SHOWNORMAL);

}

void MainWindow::convertinfores()
{
    ui->resultLabel->setText(tr("Done"));
}
void MainWindow::beforeconvertInfo()
{
    ui->resultLabel->setText(tr(""));
}
void MainWindow::NotChooseDirInfo()
{
    ui->resultLabel->setText(tr("no choose dir"));
}
MainWindow::~MainWindow()
{
    delete ui;
}
