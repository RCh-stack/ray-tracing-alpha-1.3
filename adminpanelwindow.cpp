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

    db = QSqlDatabase::addDatabase("QSQLITE");
    db.setDatabaseName("C:/Program Files (x86)/Qt Project/RayTracing/EducationSystem.sqlite");

    if (!db.open())
        QMessageBox::critical(NULL, QObject::tr("Ошибка!"), db.lastError().text());

    set_window_options();
    output_list_users(0);
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

// 1.2
void AdminPanelWindow::on_listWidget_doubleClicked(const QModelIndex &)
{
    // -- ПОД ТЕКУЩИХ ЮЗЕРОВ СДЕЛАТЬ!!! --
    UserProfileWindow *upw = new UserProfileWindow;

    QListWidgetItem *item = ui->listWidget->currentItem();
    QMessageBox::information(this, "a", item->text());

   // upw->set_group();
   // upw->set_fullname();
    upw->set_role(ui->comboBox_users->currentText());
    upw->exec();
}

// 1.2
void AdminPanelWindow::on_comboBox_users_currentIndexChanged(int index)
{
    ui->listWidget->clear();
    output_list_users(index);
}

// 1.2
QString AdminPanelWindow::get_group(int id_group)
{
    return id_group == 1 ? "ДИПРБ_21/1" :
              id_group == 2 ? "ДИПРБ_21/2" : "АСОИУ";
}

// 1.2
void AdminPanelWindow::output_list_users(int id_role)
{
    QSqlQuery query;
    query.prepare("SELECT * FROM User WHERE Role = :id_role");
    query.bindValue(":id_role", id_role + 1);
    query.exec();

    while(query.next())
        ui->listWidget->addItem(query.value("ID_User").toString() + " | " + query.value("Fullname").toString()
                                + " | " + get_group(query.value("ID_Group").toInt()));
}

// 1.2
void AdminPanelWindow::on_button_add_clicked()
{
    AddUserWindow *auw = new AddUserWindow;
    auw->exec();
}


// 1.3 (?)
void AdminPanelWindow::on_button_edit_clicked()
{
    EditUserWindow *euw = new EditUserWindow;

    // передаваемые параметры ...

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
