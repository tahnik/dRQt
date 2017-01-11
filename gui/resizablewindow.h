#ifndef RESIZABLEWINDOW_H
#define RESIZABLEWINDOW_H

#include <QWidget>
#include <QPropertyAnimation>

namespace Ui {
class ResizableWindow;
}

class ResizableWindow : public QWidget
{
    Q_OBJECT

public:
    explicit ResizableWindow(QWidget *parent = 0);
    ~ResizableWindow();
    void animateWindowClosing(bool exit);
    void maximiseWindow();
private slots:
    void minimiseWindow();

    void restoreWindow();

    void exitApplication();

private:
    Ui::ResizableWindow *ui;
    void mousePressEvent(QMouseEvent *event);
    void mouseMoveEvent(QMouseEvent *event);
    void mouseReleaseEvent(QMouseEvent *event);

    void hoverEnter(QHoverEvent *event);
    void hoverLeave(QHoverEvent *event);
    void hoverMove(QHoverEvent *event);
    bool event(QEvent *event);
    bool m_beingResized = false;

    struct resizeInformations
    {
        QPoint clickedMousePos;
        int clickedWindowRightPos;
        int clickedWindowLeftPos;
        int clickedWindowTopPos;
        int clickedWindowBottomPos;
    } m_resizeInfo;

    QRect m_mainWindowRect;
    QRect m_saveBeforeMaximise;
    bool m_minimiseToMaximise = false;

    typedef enum mainWindowBorders
    {
        INVALID_BORDER,
        RIGHT_BORDER,
        LEFT_BORDER,
        TOP_BORDER,
        BOTTOM_BORDER
    } MainWindowBorders;

    bool checkMousePosition();
    MainWindowBorders activeBorder;

    bool m_XResizeActivated = false;
    bool m_YResizeActivated = false;

    int m_resizeOffset = 5;

    int previousXPos = 0;

    QPropertyAnimation *m_geometryAnimation;
    QPropertyAnimation *m_opacityAnimation;
    QRect m_currentWindow;
    int animationOffset = 5;
};

#endif // RESIZABLEWINDOW_H
