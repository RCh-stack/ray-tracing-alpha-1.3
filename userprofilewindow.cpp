#include "userprofilewindow.h"
#include "ui_userprofilewindow.h"
#include "instructionwindow.h"

UserProfileWindow::UserProfileWindow(QWidget *parent) :
    QDialog(parent),
    ui(new Ui::UserProfileWindow)
{
    ui->setupUi(this);

    set_window_options();
}

UserProfileWindow::~UserProfileWindow()
{
    delete ui;
}

void UserProfileWindow::set_fullname(QString fullname)
{
    ui->label_fullname->setText(fullname);
}

void UserProfileWindow::set_role(QString role)
{
    ui->label_role->setText(role);
}

void UserProfileWindow::set_group(QString group)
{
    ui->label_group->setText(group);
}

void UserProfileWindow::set_window_options()
{
    QPixmap help(":/icons/images/help-button.png");
    QIcon ButtonInformation(help);
    ui->button_help->setIcon(ButtonInformation);

    QGraphicsScene *scene = new QGraphicsScene;
    scene->addPixmap(QPixmap(":/icons/images/user_icon.png"));
    ui->graphicsView->setScene(scene);

    QPixmap bkgnd(":/icons/images/mainwindow_background.jpg");
    bkgnd = bkgnd.scaled(size(), Qt::IgnoreAspectRatio);
    QPalette p = palette();
    p.setBrush(QPalette::Background, bkgnd);
    setPalette(p);
}

void UserProfileWindow::on_button_close_clicked()
{
    this->close();
}

void UserProfileWindow::on_button_help_clicked()
{
    InstructionWindow *iw = new InstructionWindow;
    iw->setWindowFlags(Qt::MSWindowsFixedSizeDialogHint);
    iw->open_file(0); // -- ВСТАВИТЬ НУЖНЫЙ --

    iw->exec();
    iw->deleteLater();
}

void UserProfileWindow::keyPressEvent(QKeyEvent *event)
{
     if(event->key() == Qt::Key_F1)
        on_button_help_clicked();
    else
        QDialog::keyPressEvent(event);
}
