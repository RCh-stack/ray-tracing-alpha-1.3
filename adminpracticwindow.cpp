#include "adminpracticwindow.h"
#include "ui_adminpracticwindow.h"
#include "checkpracticworkwindow.h"
#include "createpracticwindow.h"
#include "changepracticwindow.h"
#include "openpracticfile.h"
#include "userpracticstatswindow.h"
#include "adminhelpwindow.h"

AdminPracticWindow::AdminPracticWindow(QWidget *parent) :
    QMainWindow(parent),
    ui(new Ui::AdminPracticWindow)
{
    ui->setupUi(this);

    set_window_options();
}

AdminPracticWindow::~AdminPracticWindow()
{
    delete ui;
}

// 1.6
void AdminPracticWindow::set_window_options()
{
    QPixmap add(":/icons/images/add-work-button.png");
    QPixmap edit(":/icons/images/edit-work-button.png");
    QPixmap stats(":/icons/images/stats-users-button.png");
    QPixmap check(":/icons/images/check-work-button.png");
    QPixmap help(":/icons/images/help-button.png");

    QIcon ButtonAdd(add);
    QIcon ButtonEdit(edit);
    QIcon ButtonStats(stats);
    QIcon ButtonCheck(check);
    QIcon ButtonInformation(help);

    ui->button_add_work->setIcon(ButtonAdd);
    ui->button_edit_work->setIcon(ButtonEdit);
    ui->button_check_work->setIcon(ButtonCheck);
    ui->button_statistics->setIcon(ButtonStats);
    ui->button_help->setIcon(ButtonInformation);

    QPixmap bkgnd(":/icons/images/mainwindow_background.jpg");
    bkgnd = bkgnd.scaled(size(), Qt::IgnoreAspectRatio);
    QPalette p = palette();
    p.setBrush(QPalette::Background, bkgnd);
    setPalette(p);
}

// 1.6
void AdminPracticWindow::on_button_add_work_clicked()
{
    CreatePracticWindow *cpw = new CreatePracticWindow;
    cpw->setWindowFlags(Qt::MSWindowsFixedSizeDialogHint);
    cpw->exec();
    cpw->deleteLater();
}

// 1.6
void AdminPracticWindow::on_button_edit_work_clicked()
{
    OpenPracticFile *opf = new OpenPracticFile;
    opf->setWindowFlags(Qt::MSWindowsFixedSizeDialogHint);
    opf->output_data();
    opf->exec();

    set_id_work(opf->get_id_work());
    opf->deleteLater();

    if(get_id_work() != 0)
    {
        ChangePracticWindow *cpw = new ChangePracticWindow;
        cpw->setWindowFlags(Qt::MSWindowsFixedSizeDialogHint);
        cpw->set_id_work(get_id_work());
        cpw->get_data_from_db();
        cpw->exec();

        cpw->deleteLater();
    }
}

// 1.6
void AdminPracticWindow::on_button_check_work_clicked()
{
    CheckPracticWorkWindow *cpww = new CheckPracticWorkWindow;
    cpww->setWindowFlags(Qt::MSWindowsFixedSizeDialogHint);
    cpww->output_data_to_form();

    cpww->exec();
    cpww->deleteLater();
}

// 1.6
void AdminPracticWindow::on_button_statistics_clicked()
{
    UserPracticStatsWindow *upsw = new UserPracticStatsWindow;
    upsw->setWindowFlags(Qt::MSWindowsFixedSizeDialogHint);
    upsw->output_data_in_lists_to_form();
    upsw->output_list_works();

    upsw->exec();
    upsw->deleteLater();
}

void AdminPracticWindow::on_button_help_clicked()
{
    AdminHelpWindow *ahw = new AdminHelpWindow;
    ahw->setWindowFlags(Qt::MSWindowsFixedSizeDialogHint);
    ahw->open_file_by_code(0); // -- УКАЗАТЬ НУЖНЫЙ --

    ahw->exec();
    ahw->deleteLater();
}

void AdminPracticWindow::on_action_help_triggered()
{
    AdminHelpWindow *ahw = new AdminHelpWindow;
    ahw->setWindowFlags(Qt::MSWindowsFixedSizeDialogHint);
    ahw->open_file_by_code(0); // -- УКАЗАТЬ НУЖНЫЙ --

    ahw->exec();
    ahw->deleteLater();
}

void AdminPracticWindow::on_action_manual_triggered()
{

}
