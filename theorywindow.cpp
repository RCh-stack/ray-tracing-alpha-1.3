#include "theorywindow.h"
#include "ui_theorywindow.h"
#include "userhelpwindow.h"

TheoryWindow::TheoryWindow(QWidget *parent) :
    QDialog(parent),
    ui(new Ui::TheoryWindow)
{
    ui->setupUi(this);

    set_window_options();
    set_system_options();

    selected_item = nullptr;
    id_color_selected = 0;
}

TheoryWindow::~TheoryWindow()
{
    delete ui;
}

void TheoryWindow::set_window_options()
{
    QPixmap leftArrow (":/icons/images/prev-page.png");
    QPixmap rightArrow (":/icons/images/next-page.png");
    QPixmap help(":/icons/images/help-button.png");

    QIcon ButtonNextPage(rightArrow);
    QIcon ButtonPrevPage(leftArrow);
    QIcon ButtonInformation(help);

    ui->button_next_page->setIcon(ButtonNextPage);
    ui->button_prev_page->setIcon(ButtonPrevPage);
    ui->button_help->setIcon(ButtonInformation);

    QPixmap bkgnd(":/icons/images/mainwindow_background.jpg");
    bkgnd = bkgnd.scaled(size(), Qt::IgnoreAspectRatio);
    QPalette p = palette();
    p.setBrush(QPalette::Background, bkgnd);
    setPalette(p);
}

void TheoryWindow::set_system_options()
{
    QSqlQuery query;
    query.prepare(select_system_options());
    query.exec();

    if(query.next())
    {
        pages_read = query.value("NumberPrimaryPage").toInt() - 1;
        open_file_by_code(pages_read);
        set_enabled_button(pages_read);

        if(query.value("UseMoreTheoryPages").toBool())
            set_list_themes();

        if(!query.value("UseCopySelectPage").toBool())
        {
            ui->text_theory->setReadOnly(true);
            ui->text_theory->setTextInteractionFlags(Qt::NoTextInteraction);
        }

        if(query.value("UseSelectPageInList").toBool())
        {
            id_color_selected = query.value("NumberColorSelectedPage").toInt();
            ui->list_of_contents->header()->setStyleSheet("font-size: 16px; font-family: 'Segoe UI';");
            ui->list_of_contents->setStyleSheet("QTreeWidget::item:selected { background-color: rgb(" + get_code_color(id_color_selected) + "); color: #000000;}");
        }
    }
}

QString TheoryWindow::get_code_color(int id_color)
{
    QSqlQuery query;
    query.prepare(select_rgb_color());
    query.bindValue(":id_color",    id_color);

    query.exec();

    if(query.next())
        return query.value("RGB").toString();

    return "0, 0, 0";
}

int TheoryWindow::get_max_num()
{
    QSqlQuery query;
    query.prepare(select_last_num_theory_page());
    query.exec();

    if(query.next())
        return query.value("LastNum").toInt();

    return 1;
}

// 1.6
void TheoryWindow::set_list_themes()
{
    QSqlQuery query;
    query.prepare(select_more_theory_pages());
    query.exec();

    while(query.next())
        ui->list_of_contents->addTopLevelItem(new QTreeWidgetItem(QStringList(query.value("Name_Theme").toString())));
}

// 1.1
void TheoryWindow::set_enabled_button(int id_page)
{
    if(id_page == 0)
        ui->button_prev_page->setEnabled(0);
    else
        ui->button_prev_page->setEnabled(1);

    if(id_page == get_max_num())
        ui->button_next_page->setEnabled(0);
    else
        ui->button_next_page->setEnabled(1);
}

// 1.1
void TheoryWindow::output_table_of_contents(QString path)
{
    if(path[0] != ':')
        path = QDir().absolutePath() + path;
    QFile file(path);
    QTextStream html(&file);
    if ((file.exists())&&(file.open(QIODevice::ReadOnly | QIODevice::Text)))
    {
        QString str = html.readAll();
        ui->text_theory->setText(str);
        file.close();
    }
}

// 1.1
void TheoryWindow::on_button_prev_page_clicked()
{
    if(pages_read > 0 && pages_read <= get_max_num())
        pages_read--;
    open_file_by_code(pages_read);
    set_enabled_button(pages_read);

    if (selected_item != nullptr)
        ui->list_of_contents->setCurrentItem(selected_item);

    if (id_color_selected != 0)
        selected_item->setBackgroundColor(0, QColor(get_code_color(id_color_selected)));
}

// 1.1
void TheoryWindow::on_button_next_page_clicked()
{
    if(pages_read >= 0 && pages_read < get_max_num())
        pages_read++;
    open_file_by_code(pages_read);
    set_enabled_button(pages_read);

    if (selected_item != nullptr)
        ui->list_of_contents->setCurrentItem(selected_item);

    if (id_color_selected != 0)
        selected_item->setBackgroundColor(0, QColor(get_code_color(id_color_selected)));
}

// 1.1
void TheoryWindow::open_file_by_code(int row_index)
{
    QSqlQuery query;
    query.prepare(select_theorypage_by_id());
    query.bindValue(":id",  row_index);
    query.exec();
    if(!query.next())
        QMessageBox::warning(this, "Теоретический материал", "Страница не найдена!");
    else
    {
        QList<QTreeWidgetItem *> items  = ui->list_of_contents->findItems(query.value("Name_Theme").toString(), Qt::MatchExactly | Qt::MatchRecursive, 0);
        if (!items.isEmpty())
            selected_item = items.first();
        output_table_of_contents(query.value("Path").toString());
    }
}

// 1.1
void TheoryWindow::open_file_by_name(QString name)
{
    QSqlQuery query;
    query.prepare(select_theorypage_by_name());
    query.bindValue(":name",  name);
    query.exec();
    if(!query.next())
        QMessageBox::warning(this, "Теоретический материал", "Страница не найдена!");
    else
    {
        output_table_of_contents(query.value("Path").toString());
        pages_read = query.value("ID_Page").toInt();
        set_enabled_button(pages_read);
    }
}

// 1.1
void TheoryWindow::on_list_of_contents_itemClicked(QTreeWidgetItem *item)
{
    QString itemToAppendName = item->text(0);
    open_file_by_name(itemToAppendName);
    selected_item = item;
}

void TheoryWindow::on_button_help_clicked()
{
    UserHelpWindow *uhw = new UserHelpWindow;
    uhw->setWindowFlags(Qt::MSWindowsFixedSizeDialogHint);
    uhw->open_file_by_code(0); // -- УКАЗАТЬ НУЖНЫЙ --

    uhw->exec();
    uhw->deleteLater();
}
