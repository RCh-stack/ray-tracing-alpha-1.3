#include "mainwindow.h"
#include "theorywindow.h"
#include "optiondemowindow.h"
#include "optiontestwindow.h"
#include "practicwindow.h"
#include "ui_mainwindow.h"
#include "aboutwindowinformation.h"
#include "userprofilewindow.h"
#include "userhelpwindow.h"

MainWindow::MainWindow(QWidget *parent) :
    QMainWindow(parent),
    ui(new Ui::MainWindow)
{
    ui->setupUi(this);

    set_window_options();
}

MainWindow::~MainWindow()
{
    delete ui;
}

void MainWindow::set_window_options()
{
    QPixmap theory (":/icons/images/admin-theory-button.png");
    QPixmap demo(":/icons/images/admin-demo-button.png");
    QPixmap lab (":/icons/images/admin-lab-button.png");
    QPixmap test (":/icons/images/admin-test-button.png");
    QPixmap help(":/icons/images/help-button.png");

    QIcon ButtonTheory(theory);
    QIcon ButtonDemo(demo);
    QIcon ButtonLab(lab);
    QIcon ButtonTest(test);
    QIcon ButtonInformation(help);

    ui->button_theory->setIcon(ButtonTheory);
    ui->button_demo->setIcon(ButtonDemo);
    ui->button_practic->setIcon(ButtonLab);
    ui->button_test->setIcon(ButtonTest);
    ui->button_help->setIcon(ButtonInformation);

    QPixmap bkgnd(":/icons/images/mainwindow_background.jpg");
    bkgnd = bkgnd.scaled(size(), Qt::IgnoreAspectRatio);
    QPalette p = palette();
    p.setBrush(QPalette::Background, bkgnd);
    setPalette(p);
}

void MainWindow::on_button_theory_clicked()
{
    TheoryWindow *tw = new TheoryWindow;
    tw->setWindowFlags(Qt::MSWindowsFixedSizeDialogHint);

    tw->exec();
    tw->deleteLater();
}

void MainWindow::on_button_demo_clicked()
{
    OptionDemoWindow *odw = new OptionDemoWindow;
    odw->setWindowFlags(Qt::MSWindowsFixedSizeDialogHint);

    odw->exec();
    odw->deleteLater();
}

void MainWindow::on_button_test_clicked()
{
    OptionTestWindow *otw = new OptionTestWindow;
    otw->setWindowFlags(Qt::MSWindowsFixedSizeDialogHint);

    otw->set_id_user(get_id_user());
    otw->set_fullname_user(get_fullname_user());
    otw->set_visible_name_user();
    otw->set_list_tests();

    otw->exec();
    otw->deleteLater();
}

// 1.4 + 1.6
void MainWindow::on_button_practic_clicked()
{
    PracticWindow *pw = new PracticWindow;
    pw->setWindowFlags(Qt::MSWindowsFixedSizeDialogHint);

    pw->set_id_user(get_id_user());
    pw->set_fullname_user(get_fullname_user());
    pw->set_list_works();
    pw->output_table_of_contents(0); 

    pw->exec();
    pw->deleteLater();
}

void MainWindow::on_action_about_information_triggered()
{
    AboutWindowInformation *awi = new AboutWindowInformation;
    awi->setWindowFlags(Qt::MSWindowsFixedSizeDialogHint);

    awi->exec();
    awi->deleteLater();
}

// 1.6
QString MainWindow::get_name_group(int id)
{
    QSqlQuery query;
    query.prepare(select_group());
    query.bindValue(":id_group",    id);
    query.exec();

    if(query.next())
        return query.value("Name_Group").toString().simplified();

    return "АСОИУ";
}

void MainWindow::on_action_user_profile_triggered()
{
    UserProfileWindow *upw = new UserProfileWindow;
    upw->setWindowFlags(Qt::MSWindowsFixedSizeDialogHint);

    upw->set_fullname(get_fullname_user());
    upw->set_group(get_name_group(get_id_group()));
    upw->set_role("Студент");

    upw->exec();
    upw->deleteLater();
}

// 1.4
void MainWindow::on_action_exit_triggered()
{
    this->close();
}

void MainWindow::on_action_help_triggered()
{
    UserHelpWindow *uhw = new UserHelpWindow;
    uhw->setWindowFlags(Qt::MSWindowsFixedSizeDialogHint);
    uhw->open_file_by_code(0);

    uhw->exec();
    uhw->deleteLater();
}

void MainWindow::on_action_manual_triggered()
{

}

void MainWindow::on_button_help_clicked()
{
    UserHelpWindow *uhw = new UserHelpWindow;
    uhw->setWindowFlags(Qt::MSWindowsFixedSizeDialogHint);
    uhw->open_file_by_code(0);

    uhw->exec();
    uhw->deleteLater();
}

void MainWindow::keyPressEvent(QKeyEvent *event)
{
     if(event->key() == Qt::Key_F1)
        on_button_help_clicked();
    else
        QMainWindow::keyPressEvent(event);
}
