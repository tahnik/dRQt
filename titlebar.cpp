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
    animateWindowClosing(true);
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
    animateWindowClosing(false);
}

void TitleBar::animateWindowClosing(bool exit)
{
    m_currentWindow = parentWidget()->geometry();
    m_newWindow = parentWidget()->geometry();
    m_newWindow.setLeft(m_currentWindow.left() + animationOffset);
    m_newWindow.setTop(m_currentWindow.top() + animationOffset);
    m_newWindow.setRight(m_currentWindow.right() - animationOffset);
    m_newWindow.setBottom(m_currentWindow.bottom() - animationOffset);

    opacityAnimation = new QPropertyAnimation(parentWidget(), "windowOpacity");
    opacityAnimation->setDuration(150);
    opacityAnimation->setStartValue(1);
    opacityAnimation->setEndValue(0);
    opacityAnimation->start();

    geometryAnimation = new QPropertyAnimation(parentWidget(), "geometry");
    geometryAnimation->setDuration(150);
    geometryAnimation->setStartValue(m_currentWindow);
    geometryAnimation->setEndValue(m_newWindow);
    geometryAnimation->start();

    if(exit)
    {
        connect(geometryAnimation, SIGNAL(finished()), this, SLOT(exitApplication()));
    }
    else
    {
        connect(opacityAnimation, SIGNAL(finished()), this, SLOT(minimiseParent()));
        connect(geometryAnimation, SIGNAL(finished()), this, SLOT(restoreParentRect()));
    }
}

void TitleBar::exitApplication()
{
    QCoreApplication::exit(0);
}

void TitleBar::minimiseParent()
{
    parentWidget()->setWindowState(Qt::WindowMinimized);
    parentWidget()->setWindowOpacity(1);
    delete opacityAnimation;
}

void TitleBar::restoreParentRect()
{
    parentWidget()->setGeometry(m_currentWindow);
    delete geometryAnimation;
}
