#include "userhelpwindow.h"
#include "ui_userhelpwindow.h"

UserHelpWindow::UserHelpWindow(QWidget *parent) :
    QDialog(parent),
    ui(new Ui::UserHelpWindow)
{
    ui->setupUi(this);

    set_window_options();
    selected_item = nullptr;
}

UserHelpWindow::~UserHelpWindow()
{
    delete ui;
}

void UserHelpWindow::set_window_options()
{
    QPixmap leftArrow (":/icons/images/prev-page.png");
    QPixmap rightArrow (":/icons/images/next-page.png");

    QIcon ButtonNextPage(rightArrow);
    QIcon ButtonPrevPage(leftArrow);

    ui->button_next_page->setIcon(ButtonNextPage);
    ui->button_prev_page->setIcon(ButtonPrevPage);

    QPixmap bkgnd(":/icons/images/mainwindow_background.jpg");
    bkgnd = bkgnd.scaled(size(), Qt::IgnoreAspectRatio);
    QPalette p = palette();
    p.setBrush(QPalette::Background, bkgnd);
    setPalette(p);
}

int UserHelpWindow::get_last_page()
{
    QSqlQuery query;
    query.prepare(select_last_user_help_page());
    query.exec();

    if(query.next())
        return query.value("LastNum").toInt();

    return 1;
}

void UserHelpWindow::set_enabled_button(int id_page)
{
    if(id_page == 0)
        ui->button_prev_page->setEnabled(0);
    else
        ui->button_prev_page->setEnabled(1);

    if(id_page == get_last_page())
        ui->button_next_page->setEnabled(0);
    else
        ui->button_next_page->setEnabled(1);
}

void UserHelpWindow::open_file_by_code(int row_index)
{
    QSqlQuery query;
    query.prepare(select_user_help_page_by_id());
    query.bindValue(":id",  row_index);
    query.exec();
    if(!query.next())
        QMessageBox::warning(this, "Справка", "Страница не найдена!");
    else
    {
        QList<QTreeWidgetItem *> items  = ui->list_of_contents->findItems(query.value("Name_Header").toString(), Qt::MatchExactly | Qt::MatchRecursive, 0);
        if (!items.isEmpty())
        {
            selected_item = items.first();
            ui->list_of_contents->setCurrentItem(selected_item);
        }
        output_table_of_contents(query.value("Path").toString());
    }
}

void UserHelpWindow::open_file_by_name(QString name)
{
    QSqlQuery query;
    query.prepare(select_user_help_page_by_name());
    query.bindValue(":name",  name);
    query.exec();
    if(!query.next())
        QMessageBox::warning(this, "Справка", "Страница не найдена!");
    else
    {
        output_table_of_contents(query.value("Path").toString());
        pages_read = query.value("ID_Page").toInt();
        set_enabled_button(pages_read);
    }
}

void UserHelpWindow::output_table_of_contents(QString path)
{
    QFile file(path);
    QTextStream html(&file);
    if ((file.exists())&&(file.open(QIODevice::ReadOnly | QIODevice::Text)))
    {
        QString str = html.readAll();
        ui->text_help->setText(str);
        file.close();
    }
}

void UserHelpWindow::on_button_prev_page_clicked()
{
    if(pages_read > 0 && pages_read <= get_last_page())
        pages_read--;
    open_file_by_code(pages_read);
    set_enabled_button(pages_read);

    if (selected_item != nullptr)
        ui->list_of_contents->setCurrentItem(selected_item);
}

void UserHelpWindow::on_button_next_page_clicked()
{
    if(pages_read >= 0 && pages_read < get_last_page())
        pages_read++;
    open_file_by_code(pages_read);
    set_enabled_button(pages_read);

    if (selected_item != nullptr)
        ui->list_of_contents->setCurrentItem(selected_item);
}

void UserHelpWindow::on_list_of_contents_itemClicked(QTreeWidgetItem *item)
{
    QString itemToAppendName = item->text(0);
    open_file_by_name(itemToAppendName);
}
