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
}

TitleBar::~TitleBar()
{
    delete ui;
}

bool TitleBar::eventFilter(QObject *watched, QEvent *event)
{
    return QWidget::eventFilter(watched, event);
}

void TitleBar::on_closeButton_clicked()
{
    ((ResizableWindow*)parentWidget())->animateWindowClosing(true);
}

void TitleBar::on_maximiseButton_clicked()
{
    ((ResizableWindow*)parentWidget())->maximiseWindow();
}

void TitleBar::on_minimiseButton_clicked()
{
    ((ResizableWindow*)parentWidget())->animateWindowClosing(false);
}

