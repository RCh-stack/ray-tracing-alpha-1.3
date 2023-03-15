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
        QMessageBox::critical(this, "Ошибка", db.lastError().text());

    set_window_options();
    output_list_users(0, 0);
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
    QPixmap update(":/icons/images/update-button.png");

    QIcon ButtonAdd(add);
    QIcon ButtonEdit(edit);
    QIcon ButtonRemove(remove);
    QIcon ButtonExit(exit);
    QIcon ButtonInformation(help);
    QIcon ButtonUpdate(update);

    ui->button_add->setIcon(ButtonAdd);
    ui->button_edit->setIcon(ButtonEdit);
    ui->button_delete->setIcon(ButtonRemove);
    ui->button_exit->setIcon(ButtonExit);
    ui->button_help->setIcon(ButtonInformation);
    ui->button_update->setIcon(ButtonUpdate);

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

    //QListWidgetItem *item = ui->listWidget->currentItem();
    //QMessageBox::information(this, "a", item->text());

    //upw->();
    //upw->set_fullname();
    upw->set_role(ui->comboBox_roles->currentText());
    upw->exec();
}

void AdminPanelWindow::clear_table()
{
    ui->table_users->clearContents();
    for(int i = 0; i < ui->table_users->rowCount(); i++)
        ui->table_users->removeRow(i);
}

// 1.3
void AdminPanelWindow::on_comboBox_roles_currentIndexChanged(int index)
{
    clear_table();
    output_list_users(index, ui->comboBox_groups->currentIndex());
}

// 1.2
QString AdminPanelWindow::get_group(int id_group)
{
    return id_group == 1 ? "ДИПРБ_21/1" :
              id_group == 2 ? "ДИПРБ_21/2" : "АСОИУ";
}

// 1.3
void AdminPanelWindow::output_list_users(int id_role, int id_group)
{
    QSqlQuery query;
    query.prepare(select_all_users());
    query.bindValue(":id_role",     id_role + 1);
    query.bindValue(":id_group",  id_group + 1);
    query.exec();

    for(int i = 0; query.next(); i++)
    {
        ui->table_users->insertRow(i);
        ui->table_users->setItem(i, 0, new QTableWidgetItem(query.value("ID_User").toString()));
        ui->table_users->setItem(i, 1, new QTableWidgetItem(query.value("Fullname").toString()));
        ui->table_users->setItem(i, 2, new QTableWidgetItem(get_group(query.value("ID_Group").toInt())));
    }
}

// 1.3
void AdminPanelWindow::on_comboBox_groups_currentIndexChanged(int index)
{
    clear_table();
    output_list_users(ui->comboBox_roles->currentIndex(), index);
}

// 1.2
void AdminPanelWindow::on_button_add_clicked()
{
    AddUserWindow *auw = new AddUserWindow;
    auw->exec();
}

// 1.3
void AdminPanelWindow::on_button_update_clicked()
{
    clear_table();
    output_list_users(ui->comboBox_roles->currentIndex(), ui->comboBox_groups->currentIndex());
}

// 1.3 (+1.4?)
void AdminPanelWindow::on_button_edit_clicked()
{
    EditUserWindow *euw = new EditUserWindow;
    euw->set_current_id("20190731");
    euw->set_user_data_by_id();
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
