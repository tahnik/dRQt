#include "resizablewindow.h"
#include "ui_resizablewindow.h"
#include <QHoverEvent>

ResizableWindow::ResizableWindow(QWidget *parent) :
    QWidget(parent),
    ui(new Ui::ResizableWindow)
{
    ui->setupUi(this);
    setWindowFlags( Qt::FramelessWindowHint );
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
        m_mainWindowRect.setRight(m_mainWindowRect.right() + difference);
        this->setGeometry(m_mainWindowRect);
        break;
    case BOTTOM_BORDER:
        difference = (globalMouseYPosition - m_resizeInfo.clickedMousePos.y()) - (m_mainWindowRect.bottom() - m_resizeInfo.clickedWindowBottomPos);
        m_mainWindowRect.setBottom(m_mainWindowRect.bottom() + difference);
        this->setGeometry(m_mainWindowRect);
        break;
    default:
        break;
    }
}

void ResizableWindow::mouseReleaseEvent(QMouseEvent *event)
{
    activeBorder = INVALID_BORDER;
    m_beingResized = false;
    QApplication::restoreOverrideCursor();
}
