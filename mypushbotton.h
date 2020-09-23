#ifndef MYPUSHBOTTON_H
#define MYPUSHBOTTON_H

#include <QObject>
#include <QWidget>
#include <QPushButton>
#include <QMouseEvent>

class Mypushbotton : public QPushButton
{
    Q_OBJECT
public:
    explicit Mypushbotton(QWidget *parent = nullptr);

    void emit_signal();

signals:
    void clicked1(QString str);

};

#endif // MYPUSHBOTTON_H
