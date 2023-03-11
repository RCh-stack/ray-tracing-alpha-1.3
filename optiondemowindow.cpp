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

// 1.1
void OptionDemoWindow::set_default_settings_mode()
{
    ui->groupBox->setEnabled(0);
    ui->groupBox_2->setEnabled(0);
    ui->groupBox_3->setEnabled(0);
    ui->groupBox_4->setEnabled(0);
    ui->groupBox_5->setEnabled(0);
    ui->groupBox_6->setEnabled(0);
    ui->groupBox_7->setEnabled(0);
    ui->groupBox_8->setEnabled(0);
    ui->groupBox_9->setEnabled(0);

    set_default_color();
    set_default_value();
    set_default_light();

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
    ui->groupBox_8->setEnabled(1);
    ui->groupBox_9->setEnabled(1);
}

// 1.1
void OptionDemoWindow::set_default_color()
{
    ui->value1_color->setCurrentIndex(0);
    ui->value2_color->setCurrentIndex(1);
    ui->value3_color->setCurrentIndex(1);
    ui->value4_color->setCurrentIndex(0);
}

// 1.1
void OptionDemoWindow::set_default_value()
{
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
}

// 1.1
void OptionDemoWindow::set_default_light()
{
    ui->light1_X->setValue(-20);
    ui->light1_Y->setValue(20);
    ui->light1_Z->setValue(20);
    ui->light1_D->setValue(1.5);

    ui->light2_X->setValue(30);
    ui->light2_Y->setValue(50);
    ui->light2_Z->setValue(-25);
    ui->light2_D->setValue(1.8);

    ui->light3_X->setValue(30);
    ui->light3_Y->setValue(20);
    ui->light3_Z->setValue(30);
    ui->light3_D->setValue(1.7);
}

OptionDemoWindow::~OptionDemoWindow()
{
    delete ui;
}

// 1.1
void OptionDemoWindow::on_button_start_clicked()
{
    DemonstrationWindow *dw = new DemonstrationWindow;

    // -- установка цветовых характеристик (фон, сферы) --
    dw->set_background_color(ui->global_color->currentIndex());
    dw->set_first_sphere_color(ui->value1_color->currentIndex());
    dw->set_second_sphere_color(ui->value2_color->currentIndex());
    dw->set_third_sphere_color(ui->value3_color->currentIndex());
    dw->set_fourth_sphere_color(ui->value4_color->currentIndex());

    // -- установка числовых характеристик (координаты, радиусы, интенсивность и т.д) --
    dw->set_radius(ui->value1_R->value(), ui->value2_R->value(), ui->value3_R->value(), ui->value4_R->value());
    dw->set_x(ui->value1_X->value(), ui->value2_X->value(), ui->value3_X->value(), ui->value4_X->value());
    dw->set_y(ui->value1_Y->value(), ui->value2_Y->value(), ui->value3_Y->value(), ui->value4_Y->value());
    dw->set_z(ui->value1_Z->value(), ui->value2_Z->value(), ui->value3_Z->value(), ui->value4_Z->value());
    dw->set_x_light(ui->light1_X->value(), ui->light2_X->value(), ui->light3_X->value());
    dw->set_y_light(ui->light1_Y->value(), ui->light2_Y->value(), ui->light3_Y->value());
    dw->set_z_light(ui->light1_Z->value(), ui->light2_Z->value(), ui->light3_Z->value());
    dw->set_d_light(ui->light1_D->value(), ui->light2_D->value(), ui->light3_D->value());

    dw->exec(); // -- запуск демонстрации --
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

// 1.1
void OptionDemoWindow::on_button_path_clicked()
{
    QString filePath = QFileDialog::getExistingDirectory(this, "Путь к файлу", QString(), QFileDialog::ShowDirsOnly);
    if(filePath.length() != 0)
        ui->other_path->setText(filePath);
}
