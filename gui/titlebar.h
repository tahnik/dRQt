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


    enum CURRENT_WINDOW_STATE
    {
        NORMAL,
        MINIMIZED,
        MAXIMIZED
    };
    static CURRENT_WINDOW_STATE m_currentWindowState;


private slots:
    void on_closeButton_clicked();

    void on_maximiseButton_clicked();

    void on_minimiseButton_clicked();


private:
    Ui::TitleBar *ui;
    bool eventFilter(QObject *watched, QEvent *event);
};

#endif // TITLEBAR_H
