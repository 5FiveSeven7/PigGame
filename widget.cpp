#include "widget.h"
#include "ui_widget.h"

Widget::Widget(QWidget *parent)
    : QWidget(parent)
    , ui(new Ui::Widget)
{
    ui->setupUi(this);
    //播放背景音乐
    QMediaPlaylist *playerlist = new QMediaPlaylist;
    playerlist->addMedia(QUrl("E:/QT project/PigGame/Pig/bgm.m4a"));
    playerlist->setCurrentIndex(1);
    playerlist->setPlaybackMode(QMediaPlaylist::CurrentItemInLoop);
    QMediaPlayer *player = new QMediaPlayer;
    player->setPlaylist(playerlist);
    player->setVolume(50);
    player->play();


    ui->stackedWidget->resize(1500,1000);
    //设置begin页面
        //将当前页设置为begin,并为begin设置背景图
        ui->stackedWidget->setCurrentWidget(ui->Begin);
        ui->Begin->setObjectName("background_begin");
        ui->Begin->setStyleSheet("QWidget#background_begin{border-image:url(:/image/Begin_backg.jpg)}");

        //为begin页面的cancel按钮实现功能
        connect(ui->Cancel,&QPushButton::clicked,this,&QWidget::close);

        //为begin页面的start按钮实现功能 跳转到work页面
        connect(ui->Start,&QPushButton::clicked,
                [=]()
        {
            file.setFileName("E:/QT project/PigGame/Pig/Buy and Sell.txt");
            file.open(QFile::WriteOnly|QFile::Truncate);
            file.close();
            file1.setFileName("E:/QT project/PigGame/Pig/Information.txt");
            file1.open(QFile::WriteOnly|QFile::Truncate);
            file1.close();
            Widget::getdata();
        });

        //为begin页面的continue按钮实现功能
        connect(ui->continue_begin,&QPushButton::clicked,
                [=]()
        {
            file1.setFileName("E:/QT project/PigGame/Pig/Information.txt");
            file1.open(QIODevice::ReadOnly);
            QString str = file1.readLine();
            //记录str的相对位置
            int kong = 0;
            int dayt;
            float summoney;

            //记录上个空格的位置
            int tkong = -1;

            //读取文档中记录的天数以及金钱数
            for(int i =0 ;i <str.length();i++)
            {

                if(str[i] == ' ')
                {
                    QString tstr = str.mid(tkong+1,i-tkong-1);

                    tkong = i;
                    if(kong == 0)
                    {
                        dayt = tstr.toInt();
                        kong ++;
                        tstr.clear();

                    }
                    else if(kong == 1)
                    {
                        summoney = tstr.toFloat();
                        kong --;
                        tstr.clear();
                    }
                }
            }

            now_time = dayt;
            sum_sell = summoney;

            //读取文档中的小猪的具体信息
            for(int i=0;i<100;i++)
            {
                for(int j=0;j<10;j++)
                {
                    kong = 0;
                    tkong = -1;
                    QString str = file1.readLine();
                    if(str[0] == '#')
                    {
                        continue;
                    }
                    else
                    {
                        addpig(i,0);
                        allpig++;
                        for(int n =0;n<str.length();n++)
                        {
                            if(str[n] == ' ')
                            {
                                QString tstr = str.mid(tkong+1,n-tkong-1);
                                tkong = n;
                                if(kong == 0)
                                {
                                    int ts = tstr.toInt();
                                    pigpen[i].pigpen_pig[j]->species = ts;
                                                qDebug() << ts;
                                    if(ts == 0)
                                    {
                                        pigpen[i].judge_black = true;
                                    }
                                    kong++;
                                    tstr.clear();
                                }
                                else if(kong == 1)
                                {
                                    float tw = tstr.toFloat();
                                    pigpen[i].pigpen_pig[j]->weight = tw;
                                    kong++;
                                    tstr.clear();
                                }
                                else if(kong == 2)
                                {
                                    int td = tstr.toInt();
                                    pigpen[i].pigpen_pig[j]->days = td;
                                    kong++;
                                    tstr.clear();
                                }
                                else if(kong == 3)
                                {
                                    bool tf = tstr.toInt();
                                    pigpen[i].pigpen_pig[j]->flu = tf;
                                    kong++;
                                    tstr.clear();
                                }
                                else if(kong == 4)
                                {
                                    bool tpf = tstr.toInt();
                                    pigpen[i].pigpen_pig[j]->pre_flu = tpf;
                                    kong = 0;
                                    tstr.clear();
                                }
                            }
                        }
                    }
                }
            }
            ui->stackedWidget->setCurrentWidget(ui->Work);
            timeid = startTimer(1000);

        });




    //为cin_data实现功能
        //限制LineEditor只能输入整数
        ui->lineEdit0->setValidator(new QIntValidator(0,999,this));
        ui->lineEdit1->setValidator(new QIntValidator(0,999,this));
        ui->lineEdit2->setValidator(new QIntValidator(0,999,this));

        //获取数据
        connect(ui->Confirm_Cin,&QPushButton::clicked,this,&Widget::initialize);






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

        //实现各查询各种类猪的按钮功能
        connect(ui->species_SeeBlack,&QPushButton::clicked,
                [=]()
        {
            seeSpecies(0);
        }) ;
        connect(ui->species_SeeLittle,&QPushButton::clicked,
                [=]()
        {
            seeSpecies(1);
        });
        connect(ui->species_SeeBig,&QPushButton::clicked,
                [=]()
        {
            seeSpecies(2);
        });

        //实现检查猪瘟按钮
        connect(ui->flu_check,&QPushButton::clicked,
                [=]()
        {

            int flu_sum = 0;
            for(int i =0 ;i < 100 ;i++)
            {
                for (int j =0 ;j <pigpen[i].sum;j++)
                {
                    if(pigpen[i].pigpen_pig[j]->flu == true) flu_sum++;
                }
            }
            ui->information_display->append(QString("现在已经有 %1 只猪患猪瘟").arg(flu_sum));
            ui->information_display->append(QString("现在还有 %2 元 \n").arg(sum_sell));
        });


        //实现隔离猪瘟按钮，隔离猪瘟后猪仍会死亡，但是政府会补偿部分损失,隔离猪瘟要1万元
        connect(ui->flu_deal,&QPushButton::clicked,
                [=]()
        {
            if(sum_sell < 10000.0)
            {
                QMessageBox::warning(this,"警告","你的钱不够隔离猪瘟!");
                return;
            }
            sum_sell -= 10000.0;

            //相关补偿款
            float plait0 = 0;
            float plait1 = 0;
            float plait2 = 0;
            for(int i =0;i<100;i++)
            {
                for(int j=0;j<pigpen[i].sum;j++)
                {
                    if(pigpen[i].pigpen_pig[j]->flu == true)
                    {
                        if(pigpen[i].pigpen_pig[j]->species == 0)  plait0 += 300.0;
                        else if(pigpen[i].pigpen_pig[j]->species == 1) plait1 += 140.0;
                        else if(pigpen[i].pigpen_pig[j]->species == 2) plait2 += 120.0;
                        moveflu(i,j);
                        if(pigpen[i].pigpen_pig[j]!=NULL)
                        {
                            j--;
                        }
                    }
                }
            }
            sum_sell += plait0 +plait1 + plait2;
            ui->information_display->append(QString("已将所有病猪隔离,"
                                                    "政府补贴黑猪共 %1 元"
                                                    "补贴小花猪共 %2 元"
                                                    "补贴大花白猪共 %3 元"
                                                    "现有 %4 元 \n")
                                            .arg(plait0)
                                            .arg(plait1)
                                            .arg(plait2)
                                            .arg(sum_sell));
        }
        );


        //将信息显示板透明
        ui->information_display->setStyleSheet("background-color:transparent;");


    //设置pigpen_see页面
        //设置背景
        ui->pigpen_see->setObjectName("background_see");
        ui->pigpen_see->setStyleSheet("QWidget#background_see{border-image:url(:/image/zhujuan.jpg)}");


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
        //设置背景图
        ui->certain_see->setObjectName("background_cer");
        ui->certain_see->setStyleSheet("QWidget#background_cer{border-image:url(:/image/kuiang.jpg)}");



        //实现查看具体猪信息的按钮的功能
        connect(ui->seepig_1,&QPushButton::clicked,
                [=]()
        {
            if(pigpen[ii].pigpen_pig[0] != NULL)
            {
                QMessageBox::information(this,"信息",QString("该猪的种类: %1 （0为黑猪，1为小花猪，2为大花白猪）\n"
                                                           "该猪的所在猪圈: %2 \n"
                                                           "该猪的重量: %3 kg \n"
                                                           "该猪的饲养天数: %4 \n"
                                                           "该猪是否有猪瘟: %5")
                        .arg(pigpen[ii].pigpen_pig[0]->species)
                        .arg(pigpen[ii].pigpen_pig[0]->pigpen+1)
                        .arg(pigpen[ii].pigpen_pig[0]->weight)
                        .arg(pigpen[ii].pigpen_pig[0]->days)
                        .arg(pigpen[ii].pigpen_pig[0]->flu));
            }
            else
            {
                QMessageBox::warning(this,"警告","找不到该猪信息");
            }
        });
        connect(ui->seepig_2,&QPushButton::clicked,
                [=]()
        {
            if(pigpen[ii].pigpen_pig[1] != NULL)
            {
                QMessageBox::information(this,"信息",QString("该猪的种类: %1 （0为黑猪，1为小花猪，2为大花白猪）\n"
                                                           "该猪的所在猪圈: %2 \n"
                                                           "该猪的重量: %3 kg \n"
                                                           "该猪的饲养天数: %4 \n"
                                                           "该猪是否有猪瘟: %5")
                        .arg(pigpen[ii].pigpen_pig[1]->species)
                        .arg(pigpen[ii].pigpen_pig[1]->pigpen+1)
                        .arg(pigpen[ii].pigpen_pig[1]->weight)
                        .arg(pigpen[ii].pigpen_pig[1]->days)
                        .arg(pigpen[ii].pigpen_pig[1]->flu));
            }
            else
            {
                QMessageBox::warning(this,"警告","找不到该猪信息");
            }
        });
        connect(ui->seepig_3,&QPushButton::clicked,
                [=]()
        {
            if(pigpen[ii].pigpen_pig[2] != NULL)
            {
                QMessageBox::information(this,"信息",QString("该猪的种类: %1 （0为黑猪，1为小花猪，2为大花白猪）\n"
                                                           "该猪的所在猪圈: %2 \n"
                                                           "该猪的重量: %3 kg \n"
                                                           "该猪的饲养天数: %4 \n"
                                                           "该猪是否有猪瘟: %5")
                        .arg(pigpen[ii].pigpen_pig[2]->species)
                        .arg(pigpen[ii].pigpen_pig[2]->pigpen+1)
                        .arg(pigpen[ii].pigpen_pig[2]->weight)
                        .arg(pigpen[ii].pigpen_pig[2]->days)
                        .arg(pigpen[ii].pigpen_pig[2]->flu));
            }
            else
            {
                QMessageBox::warning(this,"警告","找不到该猪信息");
            }
        });
        connect(ui->seepig_4,&QPushButton::clicked,
                [=]()
        {
            if(pigpen[ii].pigpen_pig[3] != NULL)
            {
                QMessageBox::information(this,"信息",QString("该猪的种类: %1 （0为黑猪，1为小花猪，2为大花白猪）\n"
                                                           "该猪的所在猪圈: %2 \n"
                                                           "该猪的重量: %3 kg \n"
                                                           "该猪的饲养天数: %4 \n"
                                                           "该猪是否有猪瘟: %5")
                        .arg(pigpen[ii].pigpen_pig[3]->species)
                        .arg(pigpen[ii].pigpen_pig[3]->pigpen+1)
                        .arg(pigpen[ii].pigpen_pig[3]->weight)
                        .arg(pigpen[ii].pigpen_pig[3]->days)
                        .arg(pigpen[ii].pigpen_pig[3]->flu));
            }
            else
            {
                QMessageBox::warning(this,"警告","找不到该猪信息");
            }
        });
        connect(ui->seepig_5,&QPushButton::clicked,
                [=]()
        {
            if(pigpen[ii].pigpen_pig[4] != NULL)
            {
                QMessageBox::information(this,"信息",QString("该猪的种类: %1 （0为黑猪，1为小花猪，2为大花白猪）\n"
                                                           "该猪的所在猪圈: %2 \n"
                                                           "该猪的重量: %3 kg \n"
                                                           "该猪的饲养天数: %4 \n"
                                                           "该猪是否有猪瘟: %5")
                        .arg(pigpen[ii].pigpen_pig[4]->species)
                        .arg(pigpen[ii].pigpen_pig[4]->pigpen+1)
                        .arg(pigpen[ii].pigpen_pig[4]->weight)
                        .arg(pigpen[ii].pigpen_pig[4]->days)
                        .arg(pigpen[ii].pigpen_pig[4]->flu));
            }
            else
            {
                QMessageBox::warning(this,"警告","找不到该猪信息");
            }
        });
        connect(ui->seepig_6,&QPushButton::clicked,
                [=]()
        {
            if(pigpen[ii].pigpen_pig[5] != NULL)
            {
                QMessageBox::information(this,"信息",QString("该猪的种类: %1 （0为黑猪，1为小花猪，2为大花白猪）\n"
                                                           "该猪的所在猪圈: %2 \n"
                                                           "该猪的重量: %3 kg \n"
                                                           "该猪的饲养天数: %4 \n"
                                                           "该猪是否有猪瘟: %5")
                        .arg(pigpen[ii].pigpen_pig[5]->species)
                        .arg(pigpen[ii].pigpen_pig[5]->pigpen+1)
                        .arg(pigpen[ii].pigpen_pig[5]->weight)
                        .arg(pigpen[ii].pigpen_pig[5]->days)
                        .arg(pigpen[ii].pigpen_pig[5]->flu));
            }
            else
            {
                QMessageBox::warning(this,"警告","找不到该猪信息");
            }
        });
        connect(ui->seepig_7,&QPushButton::clicked,
                [=]()
        {
            if(pigpen[ii].pigpen_pig[6] != NULL)
            {
                QMessageBox::information(this,"信息",QString("该猪的种类: %1 （0为黑猪，1为小花猪，2为大花白猪）\n"
                                                           "该猪的所在猪圈: %2 \n"
                                                           "该猪的重量: %3 kg \n"
                                                           "该猪的饲养天数: %4 \n"
                                                           "该猪是否有猪瘟: %5")
                        .arg(pigpen[ii].pigpen_pig[6]->species)
                        .arg(pigpen[ii].pigpen_pig[6]->pigpen+1)
                        .arg(pigpen[ii].pigpen_pig[6]->weight)
                        .arg(pigpen[ii].pigpen_pig[6]->days)
                        .arg(pigpen[ii].pigpen_pig[6]->flu));
            }
            else
            {
                QMessageBox::warning(this,"警告","找不到该猪信息");
            }
        });
        connect(ui->seepig_8,&QPushButton::clicked,
                [=]()
        {
            if(pigpen[ii].pigpen_pig[7] != NULL)
            {
                QMessageBox::information(this,"信息",QString("该猪的种类: %1 （0为黑猪，1为小花猪，2为大花白猪）\n"
                                                           "该猪的所在猪圈: %2 \n"
                                                           "该猪的重量: %3 kg \n"
                                                           "该猪的饲养天数: %4 \n"
                                                           "该猪是否有猪瘟: %5")
                        .arg(pigpen[ii].pigpen_pig[7]->species)
                        .arg(pigpen[ii].pigpen_pig[7]->pigpen+1)
                        .arg(pigpen[ii].pigpen_pig[7]->weight)
                        .arg(pigpen[ii].pigpen_pig[7]->days)
                        .arg(pigpen[ii].pigpen_pig[7]->flu));
            }
            else
            {
                QMessageBox::warning(this,"警告","找不到该猪信息");
            }
        });
        connect(ui->seepig_9,&QPushButton::clicked,
                [=]()
        {
            if(pigpen[ii].pigpen_pig[8] != NULL)
            {
                QMessageBox::information(this,"信息",QString("该猪的种类: %1 （0为黑猪，1为小花猪，2为大花白猪）\n"
                                                           "该猪的所在猪圈: %2 \n"
                                                           "该猪的重量: %3 kg \n"
                                                           "该猪的饲养天数: %4 \n"
                                                           "该猪是否有猪瘟: %5")
                        .arg(pigpen[ii].pigpen_pig[8]->species)
                        .arg(pigpen[ii].pigpen_pig[8]->pigpen+1)
                        .arg(pigpen[ii].pigpen_pig[8]->weight)
                        .arg(pigpen[ii].pigpen_pig[8]->days)
                        .arg(pigpen[ii].pigpen_pig[8]->flu));
            }
            else
            {
                QMessageBox::warning(this,"警告","找不到该猪信息");
            }
        });
        connect(ui->seepig_10,&QPushButton::clicked,
                [=]()
        {
            if(pigpen[ii].pigpen_pig[9] != NULL)
            {
                QMessageBox::information(this,"信息",QString("该猪的种类: %1 （0为黑猪，1为小花猪，2为大花白猪）\n"
                                                           "该猪的所在猪圈: %2 \n"
                                                           "该猪的重量: %3 kg \n"
                                                           "该猪的饲养天数: %4 \n"
                                                           "该猪是否有猪瘟: %5")
                        .arg(pigpen[ii].pigpen_pig[9]->species)
                        .arg(pigpen[ii].pigpen_pig[9]->pigpen+1)
                        .arg(pigpen[ii].pigpen_pig[9]->weight)
                        .arg(pigpen[ii].pigpen_pig[9]->days)
                        .arg(pigpen[ii].pigpen_pig[9]->flu));
            }
            else
            {
                QMessageBox::warning(this,"警告","找不到该猪信息");
            }
        });


        //实现返回按钮
        connect(ui->certainSee_return,&QPushButton::clicked,
        [=]()
        {
            ui->stackedWidget->setCurrentWidget(ui->pigpen_see);
            return;
        });




    //为chart页面
        //为返回按钮设置功能
        connect(ui->chart_return,&QPushButton::clicked,
                [=]()
        {
            ui->stackedWidget->setCurrentWidget(ui->Work);
        });




}

Widget::~Widget()
{


    //关闭时调用析构函数来保存当前猪场信息到Information文件
    file1.setFileName("E:/QT project/PigGame/Pig/Information.txt");
    bool isok = file1.open(QIODevice::WriteOnly);
    if(isok)
    {
        QTextStream stream(&file1);
        stream.setCodec(QTextCodec::codecForName("utf-8"));
        stream << now_time << ' ' << sum_sell << ' ' << '\n';
        for(int i =0 ;i<100;i++)
        {
            for(int j =0 ;j< 10;j++)
            {
                if(pigpen[i].pigpen_pig[j] == NULL)
                {
                    stream << "# \n";
                }
                else
                {
                    stream << pigpen[i].pigpen_pig[j]->species << ' ';
                    stream << pigpen[i].pigpen_pig[j]->weight << ' ';
                    stream << pigpen[i].pigpen_pig[j]->days << ' ';
                    stream << pigpen[i].pigpen_pig[j]->flu << ' ';
                    stream << pigpen[i].pigpen_pig[j]->pre_flu << ' ';
                    stream << '\n';
                }
            }
        }
    }
    file1.close();


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
    //判断当前金钱是否小于等于零
    if(sum_sell <= 0)
    {
        QMessageBox::warning(this,"警告","你没钱买猪了！");
        return;
    }


    //提示玩家是否选择自行录入相关数据，若no则随机录入相关数据
    int ret1 = QMessageBox::question(this,"温馨提示","请问是否手动录入所要购买猪的数量及品种？");
    if(ret1 == QMessageBox::Yes)
    {
        ui->stackedWidget->setCurrentWidget(ui->Cin_data);
    }
    else
    {
        int t_sum_sell = -1;
        //为新进各种类猪的数量取随机值,规定各种类猪的随机引进数量不得超过100只,且保证不会超额购买
        while(t_sum_sell < 0)
        {
            t_sum_sell = sum_sell;
            qsrand(QTime(0,0,0).secsTo(QTime::currentTime()));
            num0 = qrand()%100;
            qsrand(QTime(1,20,2).secsTo(QTime::currentTime()));
            num1 = qrand()%100;
            qsrand(QTime(1,2,30).secsTo(QTime::currentTime()));
            num2 = qrand()%100;
            t_sum_sell = t_sum_sell- num0*600.0 - num1*280.0 - num2*240.0;
        }

        allpig += num0 + num1 + num2;
        sum_sell = sum_sell- num0*600.0 - num1*280.0 - num2*240.0;



        //将新加入猪的数据输出
        ui->information_display->append(QString("加入大黑猪的数量： %1 。").arg(num0));
        ui->information_display->append(QString("加入小花猪的数量： %1 。").arg(num1));
        ui->information_display->append(QString("加入大花白猪的数量： %1 。").arg(num2));
        ui->information_display->append(QString("目前所有猪数量： %1 。").arg(allpig));
        ui->information_display->append(QString("目前所有的钱： %1 。\n").arg(sum_sell));


        //写入购入信息到文件中]
        file.setFileName("E:/QT project/PigGame/Pig/Buy and Sell.txt");
        bool isok = file.open(QIODevice::WriteOnly|QIODevice::Append);
        if( isok )
        {
            QTextStream stream(&file);
            stream.setCodec(QTextCodec::codecForName("utf-8"));
            QString str = QString("第 %1 天： \n "
                                  "购入大黑猪 %2 只,"
                                  "购入小花猪 %3 只,"
                                  "购入大花白猪 %4 只,"
                                  "共购入 %5 只,"
                                  "还有 %6 元。 \n")
                    .arg(now_time).arg(num0).arg(num1).arg(num2).arg(num0+num1+num2).arg(sum_sell);
            stream << str.toUtf8();
        }
        file.close();


        //进入 修改猪圈中的小猪链表 函数
        linelist();
        num0 =num1 =num2 = 0;
    }
    return;
}


void Widget::initialize()
{

    //获取Cin_data中的数据

    num0 = ui->lineEdit0->text().toInt();
    num1 = ui->lineEdit1->text().toInt();
    num2 = ui->lineEdit2->text().toInt();
    sum_sell = sum_sell - num0*600.0 -num1*280.0 -num2*240.0;
    if(sum_sell < 0)
    {
        QMessageBox::warning(this,"警告","你钱不够啊!");
        sum_sell += num0*600.0 +num1*280.0 +num2*240.0;
        return;
    }

    allpig += num0 + num1 + num2;

    //将新加入猪的数据输出
    ui->information_display->append(QString("加入大黑猪的数量： %1 。").arg(num0));
    ui->information_display->append(QString("加入小花猪的数量： %1 。").arg(num1));
    ui->information_display->append(QString("加入大花白猪的数量： %1 。").arg(num2));
    ui->information_display->append(QString("目前所有猪数量： %1 。").arg(allpig));
    ui->information_display->append(QString("目前所有的钱： %1 。\n").arg(sum_sell));

    //写入购入信息到文件中]
    file.setFileName("E:/QT project/PigGame/Pig/Buy and Sell.txt");
    bool isok = file.open(QIODevice::WriteOnly|QIODevice::Append);
    if( isok )
    {
        QTextStream stream(&file);
        stream.setCodec(QTextCodec::codecForName("utf-8"));
        QString str = QString("第 %1 天： \n "
                              "购入大黑猪 %2 只,"
                              "购入小花猪 %3 只,"
                              "购入大花白猪 %4 只,"
                              "共购入 %5 只,"
                              "还有 %6 元。\n")
                .arg(now_time).arg(num0).arg(num1).arg(num2).arg(num0+num1+num2).arg(sum_sell);
        stream << str.toUtf8() ;
    }
    file.close();




    //进入 修改猪圈中的小猪链表 函数
    linelist();
    num0 =num1 =num2 = 0;
    return;
}


void Widget::linelist()
{
    addflowerpig();
    addblackpig();


    ui->stackedWidget->setCurrentWidget(ui->Work);
    //跳转至work便时间开始
    timeid = startTimer(1000);
    return;

}


void Widget::timerEvent(QTimerEvent *)
{

    now_time++;
    //为work的LCD窗口实现功能
    ui->time_display->display(now_time);
    //为work的总猪数实现功能
    ui->lcdNumber->display(allpig);
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

    //判断是否全部感染flu
    int judge_all = 0;
    for(int i=0;i<100;i++)
    {
        for(int j=0;j<pigpen[i].sum;j++)
        {
            if(pigpen[i].pigpen_pig[j]->flu == true)
            {
                judge_all++;
            }
        }
    }
    if(judge_all == allpig &&judge_all != 0)
    {
        QMessageBox::warning(this,"注意","所有猪都已感染猪瘟！你失败了");
        this->close();

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
                       if(p1->species == 0&& p1->flu ==false)
                       {
                           sum1 += p1->weight*30.0;
                           sum_sell += p1->weight*30.0;
                           sell_0++;
                       }
                       else if(p1->species == 1&& p1->flu ==false)
                       {
                           sum2 += p1->weight*14.0;
                           sum_sell +=p1->weight*14.0;
                           sell_1++;
                       }
                       else if(p1->species == 2&& p1->flu ==false)
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
                        if(p1->species == 0&& p1->flu ==false)
                        {
                            sum1 += p1->weight*30.0;
                            sum_sell += p1->weight*30.0;
                            sell_0++;
                        }
                        else if(p1->species == 1&& p1->flu ==false)
                        {
                            sum2 += p1->weight*14.0;
                            sum_sell +=p1->weight*14.0;
                            sell_1++;
                        }
                        else if(p1->species == 2&& p1->flu ==false)
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
                        if(p1->species == 0 && p1->flu ==false)
                        {
                            sum1 += p1->weight*30.0;
                            sum_sell += p1->weight*30.0;
                            sell_0++;
                        }
                        else if(p1->species == 1&& p1->flu ==false)
                        {
                            sum2 += p1->weight*14.0;
                            sum_sell +=p1->weight*14.0;
                            sell_1++;
                        }
                        else if(p1->species == 2&& p1->flu ==false)
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
        ui->information_display->append("若有猪瘟则无法获得相应金钱");
        ui->information_display->append(QString("现存猪 %1 只。").arg(allpig));
        ui->information_display->append(QString("本次卖出 %1 元。").arg(sum0));
        ui->information_display->append(QString("现有 %1 元。\n").arg(sum_sell));


        //写入出售信息到文件中]
        file.setFileName("E:/QT project/PigGame/Pig/Buy and Sell.txt");
        bool isok = file.open(QIODevice::WriteOnly|QIODevice::Append);
        if( isok )
        {
            QTextStream stream(&file);
            stream.setCodec(QTextCodec::codecForName("utf-8"));
            QString str = QString("第 %1 天： \n"
                                  "售出了大黑猪 %2 只，"
                                  "售出了小花猪 %3 只，"
                                  "售出了大花白猪 %4 只，"
                                  "共售出了 %5 只，"
                                  "现在有 %6 元。\n")
                    .arg(now_time).arg(sell_0).arg(sell_1).arg(sell_2).arg(sell_0+sell_1+sell_2).arg(sum_sell);
            stream << str.toUtf8();
        }
        file.close();

        if(sum_sell >=2000000.0)
        {
            QMessageBox::information(this,"提示","恭喜你！成功赚到了两百万元!");
            this->close();
        }



        //买猪

        getdata();




    }



    //！！！！猪瘟相关实现
        //当饲养的猪超过三十天后，会有感染猪瘟的风险
        if(now_time >= 30)
        {
            if(now_time == 30) ui->information_display->append("小心！从现在起猪圈内的小猪可能会感染猪瘟！"
                                                               "并且隔离病猪需要花费10000元\n ");


            //每天有三十十分之一的可能性凭空产生一只病猪
            qsrand(QTime(0,0,0).secsTo(QTime::currentTime()));
            int virus = qrand()%30;
            if(virus == 1)
            {
                //创建随机猪圈中随机猪感染病毒
                int virus_pigpen;
                int virus_pig;

                //随机有猪的猪圈
                qsrand(QTime(0,0,42).secsTo(QTime::currentTime()));
                while(pigpen[virus_pigpen = qrand()%100].sum == 0);
                //该猪圈中的随机一只猪
                qsrand(QTime(7,10,0).secsTo(QTime::currentTime()));
                while(pigpen[virus_pigpen].pigpen_pig[virus_pig = qrand()%10] == NULL);

                pigpen[virus_pigpen].pigpen_pig[virus_pig]->flu = true;

                ui->information_display->append("祸从天降，有一只猪由于某种原因感染了猪瘟！");

            }
            //预感染的猪全部发病
            for(int i =0;i<100;i++)
            {
                for(int j=0;j<pigpen[i].sum;j++)
                {
                    if(pigpen[i].pigpen_pig[j]->pre_flu == true) pigpen[i].pigpen_pig[j]->flu = true;
                }
            }


            //出现病猪后的传染
            for(int i =0;i< 100 ;i++)
            {
                bool flupig = 0;
                for(int j=0;j<pigpen[i].sum;j++)
                {
                    if(pigpen[i].pigpen_pig[j]->flu == true)
                    {
                        flupig = true;
                        break;
                    }
                }
                if(flupig == false) continue;
                else
                {
                    //本猪圈的传染
                    for(int j=0;j<pigpen[i].sum;j++)
                    {
                        qsrand(QTime(0,j,6).secsTo(QTime::currentTime()));
                        int virus1 = qrand()%2;
                        if(virus1 == 0)
                        {
                            pigpen[i].pigpen_pig[j]->pre_flu = true;
                        }
                    }
                    //周围猪圈的感染
                    if(i-1 >= 0)
                    {
                        for(int j=0;j<pigpen[i-1].sum;j++)
                        {
                            qsrand(QTime(0,j,32).secsTo(QTime::currentTime()));
                            int virus1 = qrand()%20;
                            if(virus1 == 0||virus1 == 1 || virus1 ==6)
                            {
                                pigpen[i-1].pigpen_pig[j]->pre_flu = true;
                            }
                        }
                    }
                    if(i+1 <= 99)
                    {
                        for(int j=0;j<pigpen[i+1].sum;j++)
                        {
                            qsrand(QTime(0,j,51).secsTo(QTime::currentTime()));
                            int virus1 = qrand()%20;
                            if(virus1 == 0 || virus1 ==9 || virus1 ==14)
                            {
                                pigpen[i+1].pigpen_pig[j]->pre_flu = true;
                            }
                        }
                    }
                }
            }


        }

    return;

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
    return;

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
    return;
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

    return;
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
    return;
}

void Widget::jumping1(QString str)
{
    //编辑信息
    ui->stackedWidget->setCurrentWidget(ui->certain_see);
    ui->pigpen_num->setText(str);
    ii = str.toInt() - 1;
    ui->LCD_SUM->display(pigpen[ii].sum);
    //计算各种类猪的数量
    int tnum0 = 0;
    int tnum1 = 0;
    int tnum2 = 0;
    for(int n = 0; n< pigpen[ii].sum ;n++)
    {
        if(pigpen[ii].pigpen_pig[n]->species == 0) tnum0++;
        else if(pigpen[ii].pigpen_pig[n]->species == 1 ) tnum1++;
        else if(pigpen[ii].pigpen_pig[n]->species == 2 ) tnum2++;
    }
    ui->LCD_BLACK->display(tnum0);
    ui->LCD_LITTLE->display(tnum1);
    ui->LCD_BIG->display(tnum2);





}


void Widget::moveflu(int i, int n)
{
    if(pigpen[i].pigpen_pig[n]->flu == false) return;
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

       delete p1;
    }
    else if(pigpen[i].end == pigpen[i].pigpen_pig[n]&&pigpen[i].start!=pigpen[i].pigpen_pig[n])
    {
        pigpen[i].end = pigpen[i].pigpen_pig[n-1];
        pigpen[i].end->next = NULL;
        Pig *p1 = pigpen[i].pigpen_pig[n];
        pigpen[i].pigpen_pig[n] = NULL;
        pigpen[i].sum--;
        allpig--;

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


        delete p1;
     }

}


void Widget::seeSpecies(int n)
{
    ui->stackedWidget->setCurrentWidget(ui->chart);
    killTimer(timeid);
    //准备时间-数量表格
    //分为0-30 30-60 60-90 90-120 120-150 150-180 180-210 210-240 240-270 270-300 300-330 330-360十二个时间段
    int sum_days[12] = {0};
    for(int i = 0;i<100;i++)
    {
        for(int j=0;j<pigpen[i].sum;j++)
        {
            if(pigpen[i].pigpen_pig[j]->days >=0 && pigpen[i].pigpen_pig[j]->days <30&&pigpen[i].pigpen_pig[j]->species == n)
            {
                sum_days[0]++;
            }
            else if(pigpen[i].pigpen_pig[j]->days >=30 && pigpen[i].pigpen_pig[j]->days <60&&pigpen[i].pigpen_pig[j]->species == n)
            {
                sum_days[1]++;
            }
            else if(pigpen[i].pigpen_pig[j]->days >=60 && pigpen[i].pigpen_pig[j]->days <90&&pigpen[i].pigpen_pig[j]->species == n)
            {
                sum_days[2]++;
            }
            else if(pigpen[i].pigpen_pig[j]->days >=90&&pigpen[i].pigpen_pig[j]->days<120&&pigpen[i].pigpen_pig[j]->species == n)
            {
                sum_days[3]++;
            }
            else if(pigpen[i].pigpen_pig[j]->days >=120&&pigpen[i].pigpen_pig[j]->days<150&&pigpen[i].pigpen_pig[j]->species == n)
            {
                sum_days[4]++;
            }
            else if(pigpen[i].pigpen_pig[j]->days>=150&&pigpen[i].pigpen_pig[j]->days<180&&pigpen[i].pigpen_pig[j]->species == n)
            {
                sum_days[5]++;
            }
            else if(pigpen[i].pigpen_pig[j]->days>=180&&pigpen[i].pigpen_pig[j]->days<210&&pigpen[i].pigpen_pig[j]->species == n)
            {
                sum_days[6]++;
            }
            else if(pigpen[i].pigpen_pig[j]->days>=210&&pigpen[i].pigpen_pig[j]->days<240&&pigpen[i].pigpen_pig[j]->species == n)
            {
                sum_days[7]++;
            }
            else if(pigpen[i].pigpen_pig[j]->days>=240&&pigpen[i].pigpen_pig[j]->days<270&&pigpen[i].pigpen_pig[j]->species == n)
            {
                sum_days[8]++;
            }
            else if(pigpen[i].pigpen_pig[j]->days>=270&&pigpen[i].pigpen_pig[j]->days<300&&pigpen[i].pigpen_pig[j]->species == n)
            {
                sum_days[9]++;
            }
            else if(pigpen[i].pigpen_pig[j]->days>=300&&pigpen[i].pigpen_pig[j]->days<330&&pigpen[i].pigpen_pig[j]->species == n)
            {
                sum_days[10]++;
            }
            else if(pigpen[i].pigpen_pig[j]->days>=330&&pigpen[i].pigpen_pig[j]->days<360&&pigpen[i].pigpen_pig[j]->species == n)
            {
                sum_days[11]++;
            }
        }
    }

    QSplineSeries *series_days = new QSplineSeries();
    series_days->setName("days");
    series_days->append(1,sum_days[0]);
    series_days->append(2,sum_days[1]);
    series_days->append(3,sum_days[2]);
    series_days->append(4,sum_days[3]);
    series_days->append(5,sum_days[4]);
    series_days->append(6,sum_days[5]);
    series_days->append(7,sum_days[6]);
    series_days->append(8,sum_days[7]);
    series_days->append(9,sum_days[8]);
    series_days->append(10,sum_days[9]);
    series_days->append(11,sum_days[10]);
    series_days->append(12,sum_days[11]);
    QChart *chart_days = new QChart();
    chart_days->legend()->hide();
    chart_days->addSeries(series_days);
    chart_days->setTitle("该猪种数量与天数的图像（横坐标代表30天区间的倍数）");
    chart_days->createDefaultAxes();
    chart_days->axisY()->setRange(0, 360);
    ui->widget_days->setChart(chart_days);

    //准备数量-重量表格
    //分为20-30 30-40 40-50 50-60 60-75 五个阶段
    int sum_weight[5] = {0};
    for(int i=0;i<100;i++)
    {
        for(int j=0;j<pigpen[i].sum;j++)
        {
            if(pigpen[i].pigpen_pig[j]->weight>=20.0&&pigpen[i].pigpen_pig[j]->weight<30.0&&pigpen[i].pigpen_pig[j]->species == n)
            {
                sum_weight[0]++;
            }
            else if(pigpen[i].pigpen_pig[j]->weight>=30.0&&pigpen[i].pigpen_pig[j]->weight<40&&pigpen[i].pigpen_pig[j]->species == n)
            {
                sum_weight[1]++;
            }
            else if(pigpen[i].pigpen_pig[j]->weight>=40.0&&pigpen[i].pigpen_pig[j]->weight<50.0&&pigpen[i].pigpen_pig[j]->species == n)
            {
                sum_weight[2]++;
            }
            else if(pigpen[i].pigpen_pig[j]->weight >=50.0&&pigpen[i].pigpen_pig[j]->weight<60.0&&pigpen[i].pigpen_pig[j]->species == n)
            {
                sum_weight[3]++;
            }
            else if(pigpen[i].pigpen_pig[j]->weight >=60.0&&pigpen[i].pigpen_pig[j]->weight<75.0&&pigpen[i].pigpen_pig[j]->species == n)
            {
                sum_weight[4]++;
            }
        }
    }
    QSplineSeries *series_weight = new QSplineSeries();
    series_weight->setName("weight");
    series_weight->append(1,sum_weight[0]);
    series_weight->append(2,sum_weight[1]);
    series_weight->append(3,sum_weight[2]);
    series_weight->append(4,sum_weight[3]);
    series_weight->append(5,sum_weight[4]);
    QChart *chart_weight = new QChart();
    chart_weight->legend()->hide();
    chart_weight->addSeries(series_weight);
    chart_weight->setTitle("该猪种数量与重量的图像（横坐标代表10kg的倍数）");
    chart_weight->createDefaultAxes();
    chart_weight->axisY()->setRange(0, 360);
    ui->widget_weight->setChart(chart_weight);

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


//读取购入与售出信息文件
void Widget::on_check_information_clicked()
{
    file.setFileName("E:/QT project/PigGame/Pig/Buy and Sell.txt");
    file.open(QIODevice::ReadOnly);
    QByteArray array = file.readAll();
    dialog = new Dialog;
    dialog->ui->textEdit->setText(array);
    file.close();
    dialog->show();

}
