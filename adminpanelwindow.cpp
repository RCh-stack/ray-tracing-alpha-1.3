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
    ui->use_selection->setChecked(1);
    output_list_users_with_selection(0, 0, 0);
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

// 1.3
void AdminPanelWindow::on_table_users_cellDoubleClicked(int row, int column)
{
    column = 1;
    QTableWidgetItem *item = ui->table_users->item(row, column);

    UserProfileWindow *upw = new UserProfileWindow;
    upw->set_fullname(item->text());
    upw->set_group(ui->comboBox_groups->currentText());
    upw->set_role(ui->comboBox_roles->currentText());

    upw->exec();
    upw->deleteLater();
}

// 1.3
void AdminPanelWindow::clear_table()
{
    ui->table_users->clearContents();
    ui->table_users->setRowCount(0);
}

// 1.3
void AdminPanelWindow::on_comboBox_roles_currentIndexChanged(int index)
{
    clear_table();
    output_list_users_with_selection(index, ui->comboBox_groups->currentIndex(), ui->comboBox_status->currentIndex());
}

// 1.2
QString AdminPanelWindow::get_group(int id_group)
{
    return id_group == 1 ? "ДИПРБ_21/1" :
              id_group == 2 ? "ДИПРБ_21/2" : "АСОИУ";
}

// 1.3
QString AdminPanelWindow::get_status(int id_status)
{
    return id_status == 1 ? "Активен" : "Удален";
}

// 1.3
void AdminPanelWindow::output_list_users_with_selection(int id_role, int id_group, int id_status)
{
    QSqlQuery query;
    query.prepare(select_all_users_with_selections());
    query.bindValue(":id_role",      id_role + 1);
    query.bindValue(":id_group",   id_group + 1);
    query.bindValue(":id_status",  id_status + 1);
    query.exec();

    for(int i = 0; query.next(); i++)
    {
        ui->table_users->insertRow(i);
        ui->table_users->setItem(i, 0, new QTableWidgetItem(query.value("ID_User").toString()));
        ui->table_users->setItem(i, 1, new QTableWidgetItem(query.value("Fullname").toString()));
        ui->table_users->setItem(i, 2, new QTableWidgetItem(get_group(query.value("ID_Group").toInt())));
        ui->table_users->setItem(i, 3, new QTableWidgetItem(get_status(query.value("Status").toInt())));
    }
}

// 1.3
void AdminPanelWindow::output_list_users()
{
    QSqlQuery query;
    query.prepare(select_all_users());
    query.exec();

    for(int i = 0; query.next(); i++)
    {
        ui->table_users->insertRow(i);
        ui->table_users->setItem(i, 0, new QTableWidgetItem(query.value("ID_User").toString()));
        ui->table_users->setItem(i, 1, new QTableWidgetItem(query.value("Fullname").toString()));
        ui->table_users->setItem(i, 2, new QTableWidgetItem(get_group(query.value("ID_Group").toInt())));
        ui->table_users->setItem(i, 3, new QTableWidgetItem(get_status(query.value("Status").toInt())));
    }
}

// 1.3
void AdminPanelWindow::on_use_selection_clicked()
{
    clear_table();
    if(ui->use_selection->isChecked())
    {
        set_enabled_combobox(1);
        output_list_users_with_selection(ui->comboBox_roles->currentIndex(), ui->comboBox_groups->currentIndex(), ui->comboBox_status->currentIndex());
    }
    else
    {
        set_enabled_combobox(0);
        output_list_users();
    }
}

// 1.3
void AdminPanelWindow::set_enabled_combobox(bool status)
{
    ui->comboBox_roles->setEnabled(status);
    ui->comboBox_groups->setEnabled(status);
    ui->comboBox_status->setEnabled(status);
}

// 1.3
void AdminPanelWindow::on_comboBox_groups_currentIndexChanged(int index)
{
    clear_table();
    output_list_users_with_selection(ui->comboBox_roles->currentIndex(), index, ui->comboBox_status->currentIndex());
}

// 1.3
void AdminPanelWindow::on_comboBox_status_currentIndexChanged(int index)
{
    clear_table();
    output_list_users_with_selection(ui->comboBox_roles->currentIndex(), ui->comboBox_groups->currentIndex(), index);
}

// 1.2
void AdminPanelWindow::on_button_add_clicked()
{
    AddUserWindow *auw = new AddUserWindow;
    auw->setWindowFlags(Qt::MSWindowsFixedSizeDialogHint);

    auw->setModal(true);
    auw->show();

    connect(auw, SIGNAL(finished(int)), SLOT(close_add_edit_window(int)));
}

// 1.3
void AdminPanelWindow::on_button_update_clicked()
{
    clear_table();
    output_list_users_with_selection(ui->comboBox_roles->currentIndex(), ui->comboBox_groups->currentIndex(), ui->comboBox_status->currentIndex());
}

// 1.3
QString AdminPanelWindow::get_selected_id_user()
{
    if(ui->table_users->currentRow() != -1)
    {
        QTableWidgetItem *item = ui->table_users->item(ui->table_users->currentRow(), 0);
        return item->text();
    }
    else
        return "";
}

// 1.3
int AdminPanelWindow::get_status_by_id_user(QString id_user)
{
    QSqlQuery query;
    query.prepare(select_status_user_by_id());
    query.bindValue(":id_user",    id_user);
    query.exec();

    if (query.next() && query.value("Status").toInt() == 1)
        return 2;

    return 1;
}

// 1.3
void AdminPanelWindow::mark_unmark_user_for_deletion(int id_status, QString id_user)
{
    QSqlQuery query;
    query.prepare(mark_unmark_for_delete());
    query.bindValue(":id_user",     id_user);
    query.bindValue(":id_status",  id_status);
    query.exec();

    QMessageBox::information(this, "Уведомление", "Пометка на удаление снята/поставлена!");
    clear_table();
    output_list_users_with_selection(ui->comboBox_roles->currentIndex(), ui->comboBox_groups->currentIndex(), ui->comboBox_status->currentIndex());
}

// 1.3
void AdminPanelWindow::on_button_edit_clicked()
{
    if(get_selected_id_user().length() == 0)
        QMessageBox::critical(this, "Ошибка", "Не выбран пользователь для изменения!");
    else
    {
        EditUserWindow *euw = new EditUserWindow;
        euw->set_current_id(get_selected_id_user());
        euw->set_user_data_by_id();
        euw->setWindowFlags(Qt::MSWindowsFixedSizeDialogHint);

        euw->setModal(true);
        euw->show();

        connect(euw, SIGNAL(finished(int)), SLOT(close_add_edit_window(int)));
    }
}

// 1.3
void AdminPanelWindow::on_button_delete_clicked()
{
    QString id_user = get_selected_id_user();
    if(id_user.length() == 0)
        QMessageBox::critical(this, "Ошибка", "Не выбран пользователь для совершения операции!");
    else if(ui->comboBox_roles->currentIndex() == 1)
        QMessageBox::critical(this, "Ошибка", "В системе нельзя помечать/снимать пометки на удаление для преподавателей!\nОбратитесь к администратору.");
    else
    {
        int id_status = get_status_by_id_user(id_user);
        if(id_status != -1)
        {
            QMessageBox::StandardButton reply;
            reply = QMessageBox::question(this, "Уведомление", "Вы уверены, что хотите поставить/снять пометку на удаление пользователя в системы?",
                                          QMessageBox::Yes|QMessageBox::No);

            if (reply == QMessageBox::Yes)
                mark_unmark_user_for_deletion(id_status, id_user);
        }
    }
}

// 1.4
void AdminPanelWindow::close_add_edit_window(int result)
{
    if(result == 0)
    {
        clear_table();
        output_list_users_with_selection(ui->comboBox_roles->currentIndex(), ui->comboBox_groups->currentIndex(), ui->comboBox_status->currentIndex());
    }
}

void AdminPanelWindow::on_button_help_clicked()
{

}

void AdminPanelWindow::on_button_exit_clicked()
{
    this->close();
}
