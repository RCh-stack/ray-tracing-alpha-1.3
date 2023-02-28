#include "adminpanelwindow.h"
#include "ui_adminpanelwindow.h"
#include "userprofilewindow.h"
#include "adduserwindow.h"
#include "edituserwindow.h"

AdminPanelWindow::AdminPanelWindow(QWidget *parent) :
    QDialog(parent),
    ui(new Ui::AdminPanelWindow)
{
    ui->setupUi(this);    

    set_window_options();
    ui->listWidget->addItem("20190731 | Тест_Студент | ДИПРБ-21/1");
}

AdminPanelWindow::~AdminPanelWindow()
{
    delete ui;
}

void AdminPanelWindow::set_window_options()
{
    QPixmap add (":/icons/images/add-user-button.png");
    QPixmap edit (":/icons/images/edit-user-button.png");
    QPixmap remove (":/icons/images/delete-user-button.png");
    QPixmap exit (":/icons/images/exit-button.png");
    QPixmap help(":/icons/images/help-button.png");

    QIcon ButtonAdd(add);
    QIcon ButtonEdit(edit);
    QIcon ButtonRemove(remove);
    QIcon ButtonExit(exit);
    QIcon ButtonInformation(help);

    ui->button_add->setIcon(ButtonAdd);
    ui->button_edit->setIcon(ButtonEdit);
    ui->button_delete->setIcon(ButtonRemove);
    ui->button_exit->setIcon(ButtonExit);
    ui->button_help->setIcon(ButtonInformation);

    QPixmap bkgnd(":/icons/images/mainwindow_background.jpg");
    bkgnd = bkgnd.scaled(size(), Qt::IgnoreAspectRatio);
    QPalette p = palette();
    p.setBrush(QPalette::Background, bkgnd);
    setPalette(p);
}

void AdminPanelWindow::on_listWidget_doubleClicked(const QModelIndex &index)
{
    // -- ПОД ТЕКУЩИХ ЮЗЕРОВ СДЕЛАТЬ!!! --
    UserProfileWindow *upw = new UserProfileWindow;
    if(ui->comboBox_users->currentIndex() == 0)
    {
        upw->set_fullname("Тест_Студент");
        upw->set_role("Студент");
        upw->set_group("ДИПРБ-21/1");
    }
    else
    {
        upw->set_fullname("Администратор");
        upw->set_role("Преподаватель");
        upw->set_group("АСОИУ");
    }
    upw->exec();
}

void AdminPanelWindow::on_comboBox_users_currentIndexChanged(int index)
{
    // -- ПОДПРАВИТЬ! --
    ui->listWidget->clear();
    if(index == 0)
    {
        ui->listWidget->addItem("20190731 | Тест_Студент | ДИПРБ-21/1");
    }
    if(index == 1)
    {
        ui->listWidget->addItem("10000000 | Администратор | АСОИУ");
    }
}

void AdminPanelWindow::on_button_add_clicked()
{
    AddUserWindow *auw = new AddUserWindow;
    auw->exec();
}

void AdminPanelWindow::on_button_edit_clicked()
{
    EditUserWindow *euw = new EditUserWindow;
    euw->exec();
}

void AdminPanelWindow::on_button_delete_clicked()
{

}

void AdminPanelWindow::on_button_help_clicked()
{

}

void AdminPanelWindow::on_button_exit_clicked()
{
    this->close();
}
