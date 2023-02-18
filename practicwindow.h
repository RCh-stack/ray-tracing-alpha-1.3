#ifndef PRACTICWINDOW_H
#define PRACTICWINDOW_H

#include <QDialog>

namespace Ui {
class PracticWindow;
}

class PracticWindow : public QDialog
{
    Q_OBJECT

public:
    explicit PracticWindow(QWidget *parent = 0);
    ~PracticWindow();

private:
    Ui::PracticWindow *ui;
};

#endif // PRACTICWINDOW_H
