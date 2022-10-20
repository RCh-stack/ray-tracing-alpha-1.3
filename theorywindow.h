#ifndef THEORYWINDOW_H
#define THEORYWINDOW_H

#include <QDialog>

namespace Ui {
class TheoryWindow;
}

class TheoryWindow : public QDialog
{
    Q_OBJECT

public:
    explicit TheoryWindow(QWidget *parent = 0);
    ~TheoryWindow();

private:
    Ui::TheoryWindow *ui;
};

#endif // THEORYWINDOW_H
