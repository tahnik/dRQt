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

private:
    Ui::TitleBar *ui;
    bool eventFilter(QObject *watched, QEvent *event);

    enum CURRENT_WINDOW_STATE
    {
        NORMAL,
        MINIMIZED,
        MAXIMIZED
    } m_currentWindowState;
    QPropertyAnimation *animation;
};

#endif // TITLEBAR_H
