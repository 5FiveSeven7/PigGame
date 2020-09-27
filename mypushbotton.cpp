#include "mypushbotton.h"

Mypushbotton::Mypushbotton(QWidget *parent) : QPushButton(parent)
{

    connect(this,&QPushButton::clicked,this,&Mypushbotton::emit_signal);

}
void Mypushbotton::emit_signal()
{
    emit clicked1(this->text());
}
