#include "titlebar.h"
#include "ui_titlebar.h"
#include <QFile>
#include <QDebug>
#include <QHoverEvent>
#include "resizablewindow.h"
#include <QPropertyAnimation>

TitleBar::TitleBar(QWidget *parent) :
    QWidget(parent),
    ui(new Ui::TitleBar)
{
    ui->setupUi(this);
    ui->closeButton->resize(ui->closeButton->width(), ui->closeButton->width());
    QImage imageClose(":/images/close.png");
    ui->closeButton->setIcon(QPixmap::fromImage(imageClose));

    ui->minimiseButton->resize(ui->minimiseButton->width(), ui->minimiseButton->width());
    QImage imageMinimise(":/images/minimise.png");
    ui->minimiseButton->setIcon(QPixmap::fromImage(imageMinimise));

    ui->maximiseButton->resize(ui->maximiseButton->width(), ui->maximiseButton->width());
    QImage imageMaximise(":/images/maximise.png");
    ui->maximiseButton->setIcon(QPixmap::fromImage(imageMaximise));


    setAttribute(Qt::WA_Hover);
    ui->maximiseButton->installEventFilter(this);
}

TitleBar::~TitleBar()
{
    delete ui;
}

bool TitleBar::eventFilter(QObject *watched, QEvent *event)
{
    switch (event->type()) {
    case QHoverEvent::HoverMove:
        if (watched == ui->maximiseButton)
        {
            qInfo() << "Heloo Button";
        }
        break;
    default:
        break;
    }
    return QWidget::eventFilter(watched, event);
}

void TitleBar::on_closeButton_clicked()
{
    QCoreApplication::exit(0);
}

void TitleBar::on_maximiseButton_clicked()
{
    if(m_currentWindowState == MAXIMIZED)
    {
        parentWidget()->setWindowState(Qt::WindowNoState);
        m_currentWindowState = NORMAL;
    }
    else
    {
        parentWidget()->setWindowState(Qt::WindowMaximized);
        m_currentWindowState = MAXIMIZED;
    }
}

void TitleBar::on_minimiseButton_clicked()
{
    parentWidget()->setWindowState(Qt::WindowMinimized);
}
