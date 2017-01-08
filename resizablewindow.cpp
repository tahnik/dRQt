#include "resizablewindow.h"
#include "ui_resizablewindow.h"
#include <QHoverEvent>
#include <QDebug>
#include <titlebar.h>

ResizableWindow::ResizableWindow(QWidget *parent) :
    QWidget(parent),
    ui(new Ui::ResizableWindow)
{
    ui->setupUi(this);
    setWindowFlags(Qt::Window|Qt::FramelessWindowHint|Qt::WindowMinMaxButtonsHint);
    setAttribute(Qt::WA_Hover);
}

ResizableWindow::~ResizableWindow()
{
    delete ui;
}

void ResizableWindow::mousePressEvent(QMouseEvent *event)
{
    checkMousePosition();
}

bool ResizableWindow::checkMousePosition()
{
    m_mainWindowRect = this->geometry();

    m_resizeInfo.clickedMousePos = QCursor::pos();
    m_mainWindowRect.getCoords(&m_resizeInfo.clickedWindowLeftPos,
                               &m_resizeInfo.clickedWindowTopPos,
                               &m_resizeInfo.clickedWindowRightPos,
                               &m_resizeInfo.clickedWindowBottomPos);

    int currentMouseXPos = m_resizeInfo.clickedMousePos.x();
    int currentMouseYPos = m_resizeInfo.clickedMousePos.y();

    int validRightBorder = m_resizeInfo.clickedWindowRightPos - m_resizeOffset;
    int validBottomBorder = m_resizeInfo.clickedWindowBottomPos - m_resizeOffset;

    bool rightBorderActive = (currentMouseXPos > validRightBorder) && (currentMouseXPos < m_resizeInfo.clickedWindowRightPos) && (currentMouseYPos > m_resizeInfo.clickedWindowTopPos + ui->TitlebarWidget->height());
    bool bottomBorderActive = (currentMouseYPos > validBottomBorder) && (currentMouseYPos < m_resizeInfo.clickedWindowBottomPos);

    if(rightBorderActive)
    {
        activeBorder = RIGHT_BORDER;
        QApplication::setOverrideCursor(Qt::SizeHorCursor);
    }
    else if(bottomBorderActive)
    {
        activeBorder = BOTTOM_BORDER;
        QApplication::setOverrideCursor(Qt::SizeVerCursor);
    }
    else
    {
        activeBorder = INVALID_BORDER;
        QApplication::restoreOverrideCursor();
    }

    return true;

}


bool ResizableWindow::event(QEvent *event)
{
    switch (event->type()) {
    case QHoverEvent::HoverMove:
        if(!m_beingResized)
        {
            checkMousePosition();
        }
        break;
    default:
        break;
    }
    return QWidget::event(event);
}

void ResizableWindow::mouseMoveEvent(QMouseEvent *event)
{
    m_beingResized = true;

    QPoint globalMousePosition = event->globalPos();

    int globalMouseXPosition = globalMousePosition.x();
    int globalMouseYPosition = globalMousePosition.y();

    int difference = 0;

    switch (activeBorder) {
    case RIGHT_BORDER:
        difference = (globalMouseXPosition - m_resizeInfo.clickedMousePos.x()) - (m_mainWindowRect.right() - m_resizeInfo.clickedWindowRightPos);
        if(m_mainWindowRect.right() + difference >= 800)
        {
            m_mainWindowRect.setRight(m_mainWindowRect.right() + difference);
        }
        this->setGeometry(m_mainWindowRect);
        break;
    case BOTTOM_BORDER:
        difference = (globalMouseYPosition - m_resizeInfo.clickedMousePos.y()) - (m_mainWindowRect.bottom() - m_resizeInfo.clickedWindowBottomPos);
        if(m_mainWindowRect.bottom() + difference >= 600)
        {
            m_mainWindowRect.setBottom(m_mainWindowRect.bottom() + difference);
        }
        this->setGeometry(m_mainWindowRect);
        break;
    default:
        int xOffset = m_resizeInfo.clickedWindowLeftPos - m_resizeInfo.clickedMousePos.x();
        int yOffset = m_resizeInfo.clickedWindowTopPos - m_resizeInfo.clickedMousePos.y();
        int xPos = event->globalX() + xOffset;
        int yPos = event->globalY() + yOffset;
        if(this->y() <= 0)
        {
            if(this->windowState() != Qt::WindowMaximized)
            {
                setGeometry(m_mainWindowRect);
                setWindowState(Qt::WindowMaximized);
            }
        }
        if(this->windowState() == Qt::WindowNoState)
        {
            qInfo() << xPos;
            move(xPos, yPos);
        }
        else if(windowState() == Qt::WindowMaximized)
        {
            if(event->globalY() > m_resizeInfo.clickedMousePos.y() + 10)
            {
                setWindowState(Qt::WindowNoState);
            }
        }
        break;
    }
    previousXPos = event->globalX();
}

void ResizableWindow::mouseReleaseEvent(QMouseEvent *event)
{
    activeBorder = INVALID_BORDER;
    m_beingResized = false;
    QApplication::restoreOverrideCursor();
}
