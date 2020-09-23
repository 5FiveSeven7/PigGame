#include "widget.h"
#include "ui_widget.h"

Widget::Widget(QWidget *parent)
    : QWidget(parent)
    , ui(new Ui::Widget)
{
    ui->setupUi(this);


    ui->stackedWidget->resize(1500,1000);
    //设置begin页面
        //将当前页设置为begin,并为begin设置背景图
        ui->stackedWidget->setCurrentWidget(ui->Begin);
        ui->Begin->setObjectName("background_begin");
        ui->Begin->setStyleSheet("QWidget#background_begin{border-image:url(:/image/Begin_backg.jpg)}");

        //为begin页面的cancel按钮实现功能
        connect(ui->Cancel,&QPushButton::clicked,this,&QWidget::close);

        //为begin页面的start按钮实现功能 跳转到work页面
        connect(ui->Start,&QPushButton::clicked,this,&Widget::getdata);
    //设置work页面

        //为work设置背景图
        ui->Work->setObjectName("background_work");
        ui->Work->setStyleSheet("QWidget#background_work{border-image:url(:/image/work_backg.jpg)}");
        //为work的时间继续按钮实现功能
        connect(ui->time_begin,&QPushButton::clicked,
                [=]()
        {
            timeid = startTimer(1000);
        });
        //为work的时间暂停按钮实现功能
        connect(ui->time_pause,&QPushButton::clicked,
                [=]()
        {
            killTimer(timeid);
        });


        //实现猪圈查询按钮功能
        connect(ui->pigpen_SeeB,&QPushButton::clicked,
                [=]()
        {
            ui->stackedWidget->setCurrentWidget(ui->pigpen_see);
            //查询时暂停时间
            killTimer(timeid);
        });



    //设置pigpen_see页面
        //实现返回按钮
        connect(ui->see_reuturn,&QPushButton::clicked,
                [=]()
        {
            ui->stackedWidget->setCurrentWidget(ui->Work);
        });



        //实现具体猪圈按钮
        connect(ui->pushButton_01,&Mypushbotton::clicked1,this,&Widget::jumping1);
        connect(ui->pushButton_02,&Mypushbotton::clicked1,this,&Widget::jumping1);
        connect(ui->pushButton_03,&Mypushbotton::clicked1,this,&Widget::jumping1);
        connect(ui->pushButton_04,&Mypushbotton::clicked1,this,&Widget::jumping1);
        connect(ui->pushButton_05,&Mypushbotton::clicked1,this,&Widget::jumping1);
        connect(ui->pushButton_06,&Mypushbotton::clicked1,this,&Widget::jumping1);
        connect(ui->pushButton_07,&Mypushbotton::clicked1,this,&Widget::jumping1);
        connect(ui->pushButton_08,&Mypushbotton::clicked1,this,&Widget::jumping1);
        connect(ui->pushButton_09,&Mypushbotton::clicked1,this,&Widget::jumping1);
        connect(ui->pushButton_10,&Mypushbotton::clicked1,this,&Widget::jumping1);
        connect(ui->pushButton_11,&Mypushbotton::clicked1,this,&Widget::jumping1);
        connect(ui->pushButton_12,&Mypushbotton::clicked1,this,&Widget::jumping1);
        connect(ui->pushButton_13,&Mypushbotton::clicked1,this,&Widget::jumping1);
        connect(ui->pushButton_14,&Mypushbotton::clicked1,this,&Widget::jumping1);
        connect(ui->pushButton_15,&Mypushbotton::clicked1,this,&Widget::jumping1);
        connect(ui->pushButton_16,&Mypushbotton::clicked1,this,&Widget::jumping1);
        connect(ui->pushButton_17,&Mypushbotton::clicked1,this,&Widget::jumping1);
        connect(ui->pushButton_18,&Mypushbotton::clicked1,this,&Widget::jumping1);
        connect(ui->pushButton_19,&Mypushbotton::clicked1,this,&Widget::jumping1);
        connect(ui->pushButton_20,&Mypushbotton::clicked1,this,&Widget::jumping1);
        connect(ui->pushButton_21,&Mypushbotton::clicked1,this,&Widget::jumping1);
        connect(ui->pushButton_22,&Mypushbotton::clicked1,this,&Widget::jumping1);
        connect(ui->pushButton_23,&Mypushbotton::clicked1,this,&Widget::jumping1);
        connect(ui->pushButton_24,&Mypushbotton::clicked1,this,&Widget::jumping1);
        connect(ui->pushButton_25,&Mypushbotton::clicked1,this,&Widget::jumping1);
        connect(ui->pushButton_26,&Mypushbotton::clicked1,this,&Widget::jumping1);
        connect(ui->pushButton_27,&Mypushbotton::clicked1,this,&Widget::jumping1);
        connect(ui->pushButton_28,&Mypushbotton::clicked1,this,&Widget::jumping1);
        connect(ui->pushButton_29,&Mypushbotton::clicked1,this,&Widget::jumping1);
        connect(ui->pushButton_30,&Mypushbotton::clicked1,this,&Widget::jumping1);
        connect(ui->pushButton_31,&Mypushbotton::clicked1,this,&Widget::jumping1);
        connect(ui->pushButton_32,&Mypushbotton::clicked1,this,&Widget::jumping1);
        connect(ui->pushButton_33,&Mypushbotton::clicked1,this,&Widget::jumping1);
        connect(ui->pushButton_34,&Mypushbotton::clicked1,this,&Widget::jumping1);
        connect(ui->pushButton_35,&Mypushbotton::clicked1,this,&Widget::jumping1);
        connect(ui->pushButton_36,&Mypushbotton::clicked1,this,&Widget::jumping1);
        connect(ui->pushButton_37,&Mypushbotton::clicked1,this,&Widget::jumping1);
        connect(ui->pushButton_38,&Mypushbotton::clicked1,this,&Widget::jumping1);
        connect(ui->pushButton_39,&Mypushbotton::clicked1,this,&Widget::jumping1);
        connect(ui->pushButton_40,&Mypushbotton::clicked1,this,&Widget::jumping1);
        connect(ui->pushButton_41,&Mypushbotton::clicked1,this,&Widget::jumping1);
        connect(ui->pushButton_42,&Mypushbotton::clicked1,this,&Widget::jumping1);
        connect(ui->pushButton_43,&Mypushbotton::clicked1,this,&Widget::jumping1);
        connect(ui->pushButton_44,&Mypushbotton::clicked1,this,&Widget::jumping1);
        connect(ui->pushButton_45,&Mypushbotton::clicked1,this,&Widget::jumping1);
        connect(ui->pushButton_46,&Mypushbotton::clicked1,this,&Widget::jumping1);
        connect(ui->pushButton_47,&Mypushbotton::clicked1,this,&Widget::jumping1);
        connect(ui->pushButton_48,&Mypushbotton::clicked1,this,&Widget::jumping1);
        connect(ui->pushButton_49,&Mypushbotton::clicked1,this,&Widget::jumping1);
        connect(ui->pushButton_50,&Mypushbotton::clicked1,this,&Widget::jumping1);
        connect(ui->pushButton_51,&Mypushbotton::clicked1,this,&Widget::jumping1);
        connect(ui->pushButton_52,&Mypushbotton::clicked1,this,&Widget::jumping1);
        connect(ui->pushButton_53,&Mypushbotton::clicked1,this,&Widget::jumping1);
        connect(ui->pushButton_54,&Mypushbotton::clicked1,this,&Widget::jumping1);
        connect(ui->pushButton_55,&Mypushbotton::clicked1,this,&Widget::jumping1);
        connect(ui->pushButton_56,&Mypushbotton::clicked1,this,&Widget::jumping1);
        connect(ui->pushButton_57,&Mypushbotton::clicked1,this,&Widget::jumping1);
        connect(ui->pushButton_58,&Mypushbotton::clicked1,this,&Widget::jumping1);
        connect(ui->pushButton_59,&Mypushbotton::clicked1,this,&Widget::jumping1);
        connect(ui->pushButton_60,&Mypushbotton::clicked1,this,&Widget::jumping1);
        connect(ui->pushButton_61,&Mypushbotton::clicked1,this,&Widget::jumping1);
        connect(ui->pushButton_62,&Mypushbotton::clicked1,this,&Widget::jumping1);
        connect(ui->pushButton_63,&Mypushbotton::clicked1,this,&Widget::jumping1);
        connect(ui->pushButton_64,&Mypushbotton::clicked1,this,&Widget::jumping1);
        connect(ui->pushButton_65,&Mypushbotton::clicked1,this,&Widget::jumping1);
        connect(ui->pushButton_66,&Mypushbotton::clicked1,this,&Widget::jumping1);
        connect(ui->pushButton_67,&Mypushbotton::clicked1,this,&Widget::jumping1);
        connect(ui->pushButton_68,&Mypushbotton::clicked1,this,&Widget::jumping1);
        connect(ui->pushButton_69,&Mypushbotton::clicked1,this,&Widget::jumping1);
        connect(ui->pushButton_70,&Mypushbotton::clicked1,this,&Widget::jumping1);
        connect(ui->pushButton_71,&Mypushbotton::clicked1,this,&Widget::jumping1);
        connect(ui->pushButton_72,&Mypushbotton::clicked1,this,&Widget::jumping1);
        connect(ui->pushButton_73,&Mypushbotton::clicked1,this,&Widget::jumping1);
        connect(ui->pushButton_74,&Mypushbotton::clicked1,this,&Widget::jumping1);
        connect(ui->pushButton_75,&Mypushbotton::clicked1,this,&Widget::jumping1);
        connect(ui->pushButton_76,&Mypushbotton::clicked1,this,&Widget::jumping1);
        connect(ui->pushButton_77,&Mypushbotton::clicked1,this,&Widget::jumping1);
        connect(ui->pushButton_78,&Mypushbotton::clicked1,this,&Widget::jumping1);
        connect(ui->pushButton_79,&Mypushbotton::clicked1,this,&Widget::jumping1);
        connect(ui->pushButton_80,&Mypushbotton::clicked1,this,&Widget::jumping1);
        connect(ui->pushButton_81,&Mypushbotton::clicked1,this,&Widget::jumping1);
        connect(ui->pushButton_82,&Mypushbotton::clicked1,this,&Widget::jumping1);
        connect(ui->pushButton_83,&Mypushbotton::clicked1,this,&Widget::jumping1);
        connect(ui->pushButton_84,&Mypushbotton::clicked1,this,&Widget::jumping1);
        connect(ui->pushButton_85,&Mypushbotton::clicked1,this,&Widget::jumping1);
        connect(ui->pushButton_86,&Mypushbotton::clicked1,this,&Widget::jumping1);
        connect(ui->pushButton_87,&Mypushbotton::clicked1,this,&Widget::jumping1);
        connect(ui->pushButton_88,&Mypushbotton::clicked1,this,&Widget::jumping1);
        connect(ui->pushButton_89,&Mypushbotton::clicked1,this,&Widget::jumping1);
        connect(ui->pushButton_90,&Mypushbotton::clicked1,this,&Widget::jumping1);
        connect(ui->pushButton_91,&Mypushbotton::clicked1,this,&Widget::jumping1);
        connect(ui->pushButton_92,&Mypushbotton::clicked1,this,&Widget::jumping1);
        connect(ui->pushButton_93,&Mypushbotton::clicked1,this,&Widget::jumping1);
        connect(ui->pushButton_94,&Mypushbotton::clicked1,this,&Widget::jumping1);
        connect(ui->pushButton_95,&Mypushbotton::clicked1,this,&Widget::jumping1);
        connect(ui->pushButton_96,&Mypushbotton::clicked1,this,&Widget::jumping1);
        connect(ui->pushButton_97,&Mypushbotton::clicked1,this,&Widget::jumping1);
        connect(ui->pushButton_98,&Mypushbotton::clicked1,this,&Widget::jumping1);
        connect(ui->pushButton_99,&Mypushbotton::clicked1,this,&Widget::jumping1);
        connect(ui->pushButton_100,&Mypushbotton::clicked1,this,&Widget::jumping1);






    //设置certain_see
        //实现返回按钮
        connect(ui->certainSee_return,&QPushButton::clicked,
        [=]()
        {
            ui->stackedWidget->setCurrentWidget(ui->pigpen_see);
        });

}

Widget::~Widget()
{
    delete ui;
}

void Widget::keyPressEvent(QKeyEvent *event)
{
    //当在开始界面时，实现 按下esc可以关闭窗口 的功能
    if(ui->stackedWidget->currentIndex() == 0 && event->key() == Qt::Key_Escape)
    {
        emit ui->Cancel->clicked();
    }
    //当在开始界面时，实现 按下enter可以开始程序 的功能
    else if(ui->stackedWidget->currentIndex() == 0 && event->key() == Qt::Key_Enter)
    {
        emit ui->Start->clicked();
    }
}


void Widget::getdata()
{
    //提示玩家是否选择自行录入相关数据，若no则随机录入相关数据
    int ret1 = QMessageBox::question(this,"温馨提示","请问是否手动录入猪的数量及品种？");
    if(ret1 == QMessageBox::Yes)
    {
        ui->stackedWidget->setCurrentWidget(ui->Cin_data);

        //限制LineEditor只能输入整数
        ui->lineEdit0->setValidator(new QIntValidator(0,999,this));
        ui->lineEdit1->setValidator(new QIntValidator(0,999,this));
        ui->lineEdit2->setValidator(new QIntValidator(0,999,this));

        //获取数据
        connect(ui->Confirm_Cin,&QPushButton::clicked,this,&Widget::initialize);

    }
    else
    {

        //为新进各种类猪的数量取随机值,规定各种类猪的随机引进数量不得超过100只
        qsrand(QTime(0,0,0).secsTo(QTime::currentTime()));
        num0 = qrand()%100;
        qsrand(QTime(1,20,2).secsTo(QTime::currentTime()));
        num1 = qrand()%100;
        qsrand(QTime(1,2,30).secsTo(QTime::currentTime()));
        num2 = qrand()%100;

        allpig += num0 + num1 + num2;

        //将新加入猪的数据输出
        ui->information_display->append(QString("加入大黑猪的数量： %1 。").arg(num0));
        ui->information_display->append(QString("加入小花猪的数量： %1 。").arg(num1));
        ui->information_display->append(QString("加入大花白猪的数量： %1 。").arg(num2));
        ui->information_display->append(QString("目前所有猪数量： %1 。").arg(allpig));
        ui->information_display->append(QString("\n"));


        //进入 修改猪圈中的小猪链表 函数
        linelist();
        num0 =num1 =num2 = 0;
    }
}


void Widget::initialize()
{

    //获取Cin_data中的数据

    num0 = ui->lineEdit0->text().toInt();
    num1 = ui->lineEdit1->text().toInt();
    num2 = ui->lineEdit2->text().toInt();

    allpig += num0 + num1 + num2;

    //将新加入猪的数据输出
    ui->information_display->append(QString("加入大黑猪的数量： %1 。").arg(num0));
    ui->information_display->append(QString("加入小花猪的数量： %1 。").arg(num1));
    ui->information_display->append(QString("加入大花白猪的数量： %1 。").arg(num2));
    ui->information_display->append(QString("目前所有猪数量： %1 。").arg(allpig));
    ui->information_display->append(QString("\n"));


    //进入 修改猪圈中的小猪链表 函数
    linelist();
    num0 =num1 =num2 = 0;
}


void Widget::linelist()
{
    addflowerpig();
    addblackpig();


    ui->stackedWidget->setCurrentWidget(ui->Work);
    //跳转至work便时间开始
    timeid = startTimer(1000);

}


void Widget::timerEvent(QTimerEvent *)
{

    now_time++;
    //为work的LCD窗口实现功能
    ui->time_display->display(now_time);
    //为work的进度条实现功能
    ui->progressBar->setMinimum(0);
    ui->progressBar->setMaximum(1000);
    ui->progressBar->setValue(allpig);

    //为pigpen_see的lcd天数实现功能
    ui->LCD_DAY->display(now_time);

    //每过一天为猪圈内的猪增重
    for(int i=0;i<100;i++)
    {
        for(int j=0;j < pigpen[i].sum;j++ )
        {
            pigpen[i].pigpen_pig[j]->days += 1;
            pigpen[i].pigpen_pig[j]->weight += generateRand(0.0,1.2);

        }
    }

    //每过三个月（默认一个月三十天,一年360天），对猪圈中的猪进行检查，并贩卖相关猪，引进新猪

    if(now_time % 90 == 0)
    {
        killTimer(timeid);
        //卖猪
        float sum1 = 0;
        float sum2 = 0;
        float sum3 = 0;
        int sell_0 = 0;
        int sell_1 = 0;
        int sell_2 = 0;
        for(int i = 0;i< 100 ; i++)
        {
            for(int n = 0 ; n < pigpen[i].sum ;n++)
            {
                if(pigpen[i].pigpen_pig[n]->days > 360 || pigpen[i].pigpen_pig[n]->weight > 75.0)
                {
                    if(pigpen[i].pigpen_pig[n] == pigpen[i].start)
                    {
                        pigpen[i].start = pigpen[i].pigpen_pig[n]->next;
                        Pig *p1 = pigpen[i].pigpen_pig[n];
                        for(int k = n;k < pigpen[i].sum-1;k++)
                        {
                            pigpen[i].pigpen_pig[k] = pigpen[i].pigpen_pig[k+1];
                        }
                        pigpen[i].pigpen_pig[pigpen[i].sum-1] = NULL;
                        pigpen[i].sum--;
                        allpig--;
                        if(pigpen[i].sum == 0) pigpen[i].judge_black =false;
                       p1->next = NULL;
                       if(p1->species == 0)
                       {
                           sum1 += p1->weight*30.0;
                           sum_sell += p1->weight*30.0;
                           sell_0++;
                       }
                       else if(p1->species == 1)
                       {
                           sum2 += p1->weight*14.0;
                           sum_sell +=p1->weight*14.0;
                           sell_1++;
                       }
                       else if(p1->species == 2)
                       {
                           sum3 += p1->weight*12.0;
                           sum_sell += p1->weight*12.0;
                           sell_2++;
                       }



                       //回收卖出的猪占用的内存空间
                       delete p1;
                       n--;
                    }
                    else if(pigpen[i].end == pigpen[i].pigpen_pig[n]&&pigpen[i].start!=pigpen[i].pigpen_pig[n])
                    {
                        pigpen[i].end = pigpen[i].pigpen_pig[n-1];
                        pigpen[i].end->next = NULL;
                        Pig *p1 = pigpen[i].pigpen_pig[n];
                        pigpen[i].pigpen_pig[n] = NULL;
                        pigpen[i].sum--;
                        allpig--;
                        if(p1->species == 0)
                        {
                            sum1 += p1->weight*30.0;
                            sum_sell += p1->weight*30.0;
                            sell_0++;
                        }
                        else if(p1->species == 1)
                        {
                            sum2 += p1->weight*14.0;
                            sum_sell +=p1->weight*14.0;
                            sell_1++;
                        }
                        else if(p1->species == 2)
                        {
                            sum3 += p1->weight*12.0;
                            sum_sell += p1->weight*12.0;
                            sell_2++;
                        }


                        delete p1;
                    }
                    else
                    {
                        pigpen[i].pigpen_pig[n-1]->next = pigpen[i].pigpen_pig[n]->next;
                        Pig *p1 = pigpen[i].pigpen_pig[n];
                        for(int k = n;k < pigpen[i].sum - 1 ; k++)
                        {
                            pigpen[i].pigpen_pig[k] =pigpen[i].pigpen_pig[k+1];
                        }
                        pigpen[i].pigpen_pig[pigpen[i].sum-1] = NULL;
                        pigpen[i].sum--;
                        allpig--;
                        if(p1->species == 0)
                        {
                            sum1 += p1->weight*30.0;
                            sum_sell += p1->weight*30.0;
                            sell_0++;
                        }
                        else if(p1->species == 1)
                        {
                            sum2 += p1->weight*14.0;
                            sum_sell +=p1->weight*14.0;
                            sell_1++;
                        }
                        else if(p1->species == 2)
                        {
                            sum3 += p1->weight*12.0;
                            sum_sell += p1->weight*12.0;
                            sell_2++;
                        }



                        delete p1;
                        n--;
                    }
                }
            }
        }
        float sum0 = sum1 + sum2 +sum3;
        ui->information_display->append(QString("卖出了大黑猪 %1 只。").arg(sell_0));
        ui->information_display->append(QString("卖出了小花猪 %1 只。").arg(sell_1));
        ui->information_display->append(QString("卖出了大花白猪 %1 只。").arg(sell_2));
        ui->information_display->append(QString("现存猪 %1 只。").arg(allpig));
        ui->information_display->append(QString("本次卖出 %1 元。").arg(sum0));
        ui->information_display->append(QString("迄今为止已获利 %1 元。").arg(sum_sell));
        ui->information_display->append(QString("\n"));


        //买猪

        getdata();




    }

}

void Widget::addflowerpig()
{
    mixflower_index = 0;
    while(num1)
    {
        for(int i =0 ;i<100;i++)
        {
            if(pigpen[i].judge_black == false)
            {
                mixflower_index = i;
                break;
            }
        }
        for(int i = 0;i < 100 ;i ++)
        {
            if(pigpen[i].judge_black == false && pigpen[i].sum < pigpen[mixflower_index].sum)
            {
                mixflower_index = i;
            }
        }

            addpig(mixflower_index,1);
            num1--;

        mixflower_index = 0;
    }
    while(num2)
    {
        for(int i =0 ;i<100;i++)
        {
            if(pigpen[i].judge_black == false)
            {
                mixflower_index = i;
                break;
            }
        }
        for(int i = 0;i < 100 ; i++)
        {
            if(pigpen[i].judge_black == false && pigpen[i].sum < pigpen[mixflower_index].sum)
            {
                mixflower_index = i;
            }
        }

            addpig(mixflower_index,2);
            num2--;

        mixflower_index = 0;
    }

}
void Widget::addblackpig()
{
    mixblack_index = 0;
    while(num0)
    {
        //判断是否有空的黑猪圈
        bool temp_judge = 0;
        for(int i =0 ;i<100;i++)
        {
            if(pigpen[i].judge_black == true && pigpen[i].sum < 10)
            {
                mixblack_index = i;
                temp_judge = true;
                break;
            }
        }
        if(temp_judge == true)
        {
            for(int i = 0;i < 100; i++)
            {
                if(pigpen[i].judge_black == true && pigpen[i].sum < pigpen[mixblack_index].sum)
                {
                    mixblack_index = i;
                }
            }
            addpig(mixblack_index,0);
            num0--;
        }
        else
        {
            for(int i =0 ;i<100;i++)
            {
                if(pigpen[i].judge_black == false )
                {
                    mixflower_index = i;
                    break;
                }
            }
            for(int i = 0;i < 100 ; i++)
            {
                if(pigpen[i].judge_black == false && pigpen[i].sum < pigpen[mixflower_index].sum)
                {
                    mixflower_index = i;
                }
            }
            if(pigpen[mixflower_index].start != NULL) movepig(mixflower_index);
            pigpen[mixflower_index].judge_black = true;
            addpig(mixflower_index,0);
            num0--;
        }
        mixblack_index = 0;
        mixflower_index = 0;
    }
}

void Widget::movepig(int i)
{
    while(1)
    {
        int temp_mixflower;
        for(int j =0 ;j<100;j++)
        {
            if(j == i) continue;
            if(pigpen[j].judge_black == false )
            {
                temp_mixflower = j;
                break;
            }
        }
        for(int j = 0;j < 100 ; j++)
        {
            if(j == i) continue;
            if(pigpen[j].judge_black == false && pigpen[j].sum < pigpen[temp_mixflower].sum)
            {
                temp_mixflower = j;
            }
        }
        if(pigpen[i].start == pigpen[i].end)
        {
            Pig *p1 = pigpen[i].start;
            pigpen[i].start = NULL;
            pigpen[i].end = NULL;
            pigpen[i].sum = 0;
            for(int l = 0;l < 10 ;l++)
            {
                pigpen[i].pigpen_pig[l] = NULL;
            }
            pigpen[temp_mixflower].end->next = p1;
            pigpen[temp_mixflower].end = p1;
            p1->next = NULL;
            pigpen[temp_mixflower].pigpen_pig[pigpen[temp_mixflower].sum] = p1;
            pigpen[temp_mixflower].sum++;
            p1->pigpen = temp_mixflower;
            break;

        }
        else
        {
            Pig *p1 = pigpen[i].start;
            pigpen[i].start = p1->next;
            p1->next = NULL;
            pigpen[i].sum--;
            pigpen[temp_mixflower].end->next = p1;
            pigpen[temp_mixflower].end = p1;
            pigpen[temp_mixflower].pigpen_pig[pigpen[temp_mixflower].sum] = p1;
            pigpen[temp_mixflower].sum++;
            p1->pigpen = temp_mixflower;
        }
    }

}

void Widget::addpig(int i,int s)
{
    if(pigpen[i].start == NULL)
    {
        Pig *p1 = new Pig;
        pigpen[i].start = p1;
        pigpen[i].end = p1;
        p1->next = NULL;
        p1->weight = generateRand(20.0,50.0);
        p1->pigpen = i;
        p1->species = s;
        pigpen[i].pigpen_pig[pigpen[i].sum] = p1;
        pigpen[i].sum++;
    }
    else
    {
        Pig *p1 = new Pig;
        pigpen[i].end->next = p1;
        pigpen[i].end = p1;
        p1->next = NULL;
        p1->weight = generateRand(20.0,50.0);
        p1->pigpen = i;
        p1->species = s;
        pigpen[i].pigpen_pig[pigpen[i].sum] = p1;
        pigpen[i].sum++;
    }
}

void Widget::jumping1(QString str)
{
    //编辑信息
    ui->stackedWidget->setCurrentWidget(ui->certain_see);
    ui->pigpen_num->setText(str);
    int i = str.toInt() - 1;
    ui->LCD_SUM->display(pigpen[i].sum);
    //计算各种类猪的数量
    int tnum0 = 0;
    int tnum1 = 0;
    int tnum2 = 0;
    for(int n = 0; n< pigpen[i].sum ;n++)
    {
        if(pigpen[i].pigpen_pig[n]->species == 0) tnum0++;
        else if(pigpen[i].pigpen_pig[n]->species == 1 ) tnum1++;
        else if(pigpen[i].pigpen_pig[n]->species == 2 ) tnum2++;
    }
    ui->LCD_BLACK->display(tnum0);
    ui->LCD_LITTLE->display(tnum1);
    ui->LCD_BIG->display(tnum2);

}


float Widget::generateRand(float min, float max)
{
    static bool seedStatus;
    if (!seedStatus)
    {
        qsrand(QTime(0, 0, 0).secsTo(QTime::currentTime()));
        seedStatus = true;
    }
    if(min>max)
    {
        float temp=min;
        min=max;
        max=temp;
    }
    double diff = fabs(max-min);
    double m1=(double)(qrand()%100)/100;
    double retval=min+m1*diff;
    return retval;
}


