#include "optiondemowindow.h"
#include "ui_optiondemowindow.h"
#include "demonstrationwindow.h"
#include "ui_demonstrationwindow.h"

OptionDemoWindow::OptionDemoWindow(QWidget *parent) :
    QDialog(parent),
    ui(new Ui::OptionDemoWindow)
{
    ui->setupUi(this);
    set_window_options();

    ui->check_option->setChecked(1);
    set_default_settings_mode();
}

void OptionDemoWindow::set_window_options()
{
    QPixmap help(":/icons/images/help-button.png");
    QPixmap start(":/icons/images/start-button.png");
    QPixmap cancel(":/icons/images/cancel-button.png");

    QIcon ButtonInformation(help);
    QIcon ButtonStart(start);
    QIcon ButtonCancel(cancel);

    ui->button_help->setIcon(ButtonInformation);
    ui->button_start->setIcon(ButtonStart);
    ui->button_cancel->setIcon(ButtonCancel);

    QPixmap bkgnd(":/icons/images/mainwindow_background.jpg");
    bkgnd = bkgnd.scaled(size(), Qt::IgnoreAspectRatio);
    QPalette p = palette();
    p.setBrush(QPalette::Background, bkgnd);
    setPalette(p);
}

void OptionDemoWindow::set_default_settings_mode()
{
    ui->groupBox->setEnabled(0);
    ui->groupBox_2->setEnabled(0);
    ui->groupBox_3->setEnabled(0);
    ui->groupBox_4->setEnabled(0);
    ui->groupBox_5->setEnabled(0);
    ui->groupBox_6->setEnabled(0);
    ui->groupBox_7->setEnabled(0);

    ui->value2_color->setCurrentIndex(1);
    ui->value3_color->setCurrentIndex(1);

    ui->value1_R->setValue(2);
    ui->value1_X->setValue(-3);
    ui->value1_Y->setValue(0);
    ui->value1_Z->setValue(-16);

    ui->value2_R->setValue(2);
    ui->value2_X->setValue(-1);
    ui->value2_Y->setValue(-1.5);
    ui->value2_Z->setValue(-12);

    ui->value3_R->setValue(3);
    ui->value3_X->setValue(1.5);
    ui->value3_Y->setValue(-0.5);
    ui->value3_Z->setValue(-18);

    ui->value4_R->setValue(4);
    ui->value4_X->setValue(7);
    ui->value4_Y->setValue(5);
    ui->value4_Z->setValue(-18);

    ui->light1_X->setValue(-20);
    ui->light1_Y->setValue(20);
    ui->light1_Z->setValue(20);
    ui->light1_D->setValue(1.5);

    ui->global_color->setCurrentIndex(1);
    ui->other_format->setCurrentIndex(1);
    ui->global_is_reflex->setChecked(1);
    ui->other_path->setText("C:/Program Files (x86)/Qt Project/RayTracing/");
}

void OptionDemoWindow::set_users_settings_mode()
{
    ui->groupBox->setEnabled(1);
    ui->groupBox_2->setEnabled(1);
    ui->groupBox_3->setEnabled(1);
    ui->groupBox_4->setEnabled(1);
    ui->groupBox_5->setEnabled(1);
    ui->groupBox_6->setEnabled(1);
    ui->groupBox_7->setEnabled(1);
}

OptionDemoWindow::~OptionDemoWindow()
{
    delete ui;
}

void OptionDemoWindow::on_button_start_clicked()
{
    DemonstrationWindow *dw = new DemonstrationWindow;
    dw->exec();
}

void OptionDemoWindow::on_button_cancel_clicked()
{
    this->close();
}

void OptionDemoWindow::on_button_help_clicked()
{

}

void OptionDemoWindow::on_check_option_clicked()
{
    if(ui->check_option->isChecked())
        set_default_settings_mode();
    else
        set_users_settings_mode();
}

void OptionDemoWindow::on_button_path_clicked()
{
    //QString filePath = QFileDialog::getOpenFileName(this, "Открыть файл", QString(), "*.cpp ");
    QString filePath = QFileDialog::getExistingDirectory(this, "Путь к файлу", QString(), QFileDialog::ShowDirsOnly);
    ui->other_path->setText(filePath);
}
