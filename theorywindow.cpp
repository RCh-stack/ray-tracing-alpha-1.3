#include "theorywindow.h"
#include "ui_theorywindow.h"

TheoryWindow::TheoryWindow(QWidget *parent) :
    QDialog(parent),
    ui(new Ui::TheoryWindow)
{
    ui->setupUi(this);
    pages_read = 0;

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

    open_file(":/theory_files/files/theory/content.html");
}

TheoryWindow::~TheoryWindow()
{
    delete ui;
}

void TheoryWindow::output_table_of_contents(int row_index)
{
    pages_read = row_index;
    if(pages_read == 0)
        open_file(":/theory_files/files/theory/content.html");
    else if(pages_read == 1)
        open_file(":/theory_files/files/theory/first.html");
}

void TheoryWindow::on_button_prev_page_clicked()
{
    if(pages_read > 0 && pages_read <= 6)
                pages_read--;
        output_table_of_contents(pages_read);
}

void TheoryWindow::on_button_next_page_clicked()
{
    if(pages_read >= 0 && pages_read < 6)
                pages_read++;
        output_table_of_contents(pages_read);
}

void TheoryWindow::open_file(QString path)
{
    QFile file(path);
    QTextStream html(&file);
    if ((file.exists())&&(file.open(QIODevice::ReadOnly | QIODevice::Text)))
    {
        QString str = html.readAll();
        ui->text_theory->setText(str);
        file.close();
    }
}

void TheoryWindow::on_list_of_contents_itemClicked(QTreeWidgetItem *item)
{
    QModelIndex index = item->treeWidget()->currentIndex();
    output_table_of_contents(index.row());
}
