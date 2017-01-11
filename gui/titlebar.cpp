#include "titlebar.h"
#include "ui_titlebar.h"
#include <QFile>
#include <QDebug>
#include <QHoverEvent>
#include "resizablewindow.h"
#include <QPropertyAnimation>
#include <QSystemTrayIcon>

TitleBar::TitleBar(QWidget *parent) :
    QWidget(parent),
    ui(new Ui::TitleBar)
{
    ui->setupUi(this);

    setAttribute(Qt::WA_Hover);

    ui->maximiseButton->installEventFilter(this);
}

TitleBar::~TitleBar()
{
    delete ui;
}

bool TitleBar::eventFilter(QObject *watched, QEvent *event)
{
    if(watched == ui->maximiseButton)
    {
        switch (event->type()) {
        case QEvent::HoverEnter:
            ui->maximiseButton->setStyleSheet("background-color: #8F92BD");
            break;
        case QEvent::HoverLeave:
            ui->maximiseButton->setStyleSheet("background-color: #54566F");
            break;
        }

    }
    return QWidget::eventFilter(watched, event);
}

void TitleBar::mouseMoveEvent(QMouseEvent *event)
{
    return QWidget::mouseMoveEvent(event);
}

void TitleBar::on_closeButton_clicked()
{
    ((ResizableWindow*)parentWidget())->animateWindowClosing(true);
}

void TitleBar::on_maximiseButton_clicked()
{
    ((ResizableWindow*)parentWidget())->maximiseWindow();
    ui->maximiseButton->setStyleSheet("background-color: #54566F");
}

void TitleBar::on_minimiseButton_clicked()
{
    ((ResizableWindow*)parentWidget())->animateWindowClosing(false);
}

