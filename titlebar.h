#ifndef TITLEBAR_H
#define TITLEBAR_H

#include <QWidget>
#include <QPropertyAnimation>

namespace Ui {
class TitleBar;
}

class TitleBar : public QWidget
{
    Q_OBJECT

public:
    explicit TitleBar(QWidget *parent = 0);
    ~TitleBar();

private slots:
    void on_closeButton_clicked();

    void on_maximiseButton_clicked();

    void on_minimiseButton_clicked();

    void minimiseParent();

    void restoreParentRect();

    void exitApplication();

private:
    Ui::TitleBar *ui;
    bool eventFilter(QObject *watched, QEvent *event);

    void animateWindowClosing(bool exit);

    enum CURRENT_WINDOW_STATE
    {
        NORMAL,
        MINIMIZED,
        MAXIMIZED
    } m_currentWindowState;
    QPropertyAnimation *geometryAnimation;
    QPropertyAnimation *opacityAnimation;
    QRect m_currentWindow;
    QRect m_newWindow;
    int animationOffset = 5;
};

#endif // TITLEBAR_H
