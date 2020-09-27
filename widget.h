#ifndef WIDGET_H
#define WIDGET_H

#include "touwenjian.h"


QT_BEGIN_NAMESPACE
namespace Ui { class Widget; }
QT_CHARTS_USE_NAMESPACE
QT_END_NAMESPACE
//创建猪的结构体
struct Pig
{
    //指向下一个对象的指针
    Pig *next;
    //具体对象的花色：黑猪为0，小花猪为1，大花白猪为2.
    int species;
    //所在的猪圈编号：0-99。
    int pigpen;
    //猪的体重
    float weight;
    //猪的饲养天数
    int days = 0;
    //是否有猪瘟
    bool flu = 0;
    //第一天感染第二天才会表现出感染性
    bool pre_flu = 0;


};

//创建一个猪圈的结构体
struct Pigpen
{
    //该猪圈的猪的数量
    int sum = 0;
    //该猪圈是否圈养黑猪
    bool judge_black = 0;
    //指向猪圈猪链表头和表尾和表中的指针
    Pig *start = NULL;
    Pig *end = NULL;

    //指向猪圈内某头猪的指针
    Pig *pigpen_pig[10] = {NULL,NULL,NULL,NULL,NULL,NULL,NULL,NULL,NULL,NULL};

};

class Widget : public QWidget
{
    Q_OBJECT

    //创建100个猪圈对象，编号从0-99
    Pigpen pigpen[100];

    int num0 = 0;
    int num1 = 0;
    int num2 = 0;

    int allpig = 0;
    int timeid;

    int now_time = 0;

    //现有的价钱
    //添加购进小猪要花钱的功能，黑猪一只150，小花猪一只70，大花白猪一只60
    float sum_sell = 60000.0 +28000.0 +24000.0;

    int mixflower_index = 0;
    int mixblack_index = 0;
    //查询时当时所在猪圈
    int ii;

    Dialog *dialog;
    QFile file;
    QFile file1;
public:
    Widget(QWidget *parent = nullptr);
    ~Widget();
    //写一个初始化函数用于读取Cin_data页面数据
    void initialize();
    //用来修改小猪链表的函数
    void linelist();
    //为cin_data服务的函数
    void getdata();

    float generateRand(float min, float max);

    //添加花猪函数
    void addflowerpig();
    //添加黑猪函数
    void addblackpig();

    //加猪函数
    void addpig(int i,int speceies);

    //移猪函数
    void movepig(int i);

    //查看具体猪圈跳转槽函数
    void jumping1(QString str);

    //查询具体种类猪函数
    void seeSpecies(int i);

    //移除病猪函数
    void moveflu(int i,int n);




private:
    Ui::Widget *ui;

protected:
    //void paintEvent(QPaintEvent *event) override;
    void keyPressEvent(QKeyEvent *event) override;
    void timerEvent(QTimerEvent *event) override;


private slots:
    void on_check_information_clicked();
};
#endif // WIDGET_H
