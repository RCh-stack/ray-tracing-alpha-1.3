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

// 1.4
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

    set_list_of_background_colors();
    set_list_of_sphere_colors();

    QPixmap bkgnd(":/icons/images/mainwindow_background.jpg");
    bkgnd = bkgnd.scaled(size(), Qt::IgnoreAspectRatio);
    QPalette p = palette();
    p.setBrush(QPalette::Background, bkgnd);
    setPalette(p);
}

// 1.4
void OptionDemoWindow::set_list_of_background_colors()
{
    QPixmap blue_ground(":/icons/images/blue_ground_icon.png");
    QPixmap eucalypt_ground(":/icons/images/eucalyptus_ground_icon.png");
    QPixmap verdigris_ground(":/icons/images/verdigris_ground_icon.png");
    QPixmap light_blue_ground(":/icons/images/light_blue_ground_icon.png");
    QPixmap dark_blue_ground(":/icons/images/dark_blue_ground_icon.png");

    QIcon BlueGround(blue_ground);
    QIcon EucalyptGround(eucalypt_ground);
    QIcon VerdigrisGround(verdigris_ground);
    QIcon LightBlueGround(light_blue_ground);
    QIcon DarkBlueGround(dark_blue_ground);

    ui->global_color->setItemIcon(0, BlueGround);
    ui->global_color->setItemIcon(1, EucalyptGround);
    ui->global_color->setItemIcon(2, VerdigrisGround);
    ui->global_color->setItemIcon(3, LightBlueGround);
    ui->global_color->setItemIcon(4, DarkBlueGround);
}

// 1.4
void OptionDemoWindow::set_list_of_sphere_colors()
{
    QPixmap olive_color(":/icons/images/olive_sphere_icon.png");
    QPixmap dark_red_color(":/icons/images/dark_red_sphere_icon.png");
    QPixmap grey_color(":/icons/images/grey_sphere_icon.png");
    QPixmap light_grey_color(":/icons/images/light_grey_sphere_icon.png");
    QPixmap pink_color(":/icons/images/pink_sphere_icon.png");
    QPixmap orange_color(":/icons/images/orange_sphere_icon.png");
    QPixmap yellow_color(":/icons/images/yellow_sphere_icon.png");

    QIcon OliveSphere(olive_color);
    QIcon DarkRedSphere(dark_red_color);
    QIcon GreySphere(grey_color);
    QIcon LightGreySphere(light_grey_color);
    QIcon PinkSphere(pink_color);
    QIcon OrangeSphere(orange_color);
    QIcon YellowSphere(yellow_color);

    set_sphere_colors_to_lists(OliveSphere, DarkRedSphere, GreySphere, LightGreySphere, PinkSphere, OrangeSphere, YellowSphere);
}

// 1.4
void OptionDemoWindow::set_sphere_colors_to_lists(QIcon olive, QIcon dark_red, QIcon grey, QIcon light_grey, QIcon pink, QIcon orange, QIcon yellow)
{
    ui->value1_color->setItemIcon(0, olive);
    ui->value1_color->setItemIcon(1, dark_red);
    ui->value1_color->setItemIcon(2, grey);
    ui->value1_color->setItemIcon(3, light_grey);
    ui->value1_color->setItemIcon(4, pink);
    ui->value1_color->setItemIcon(5, orange);
    ui->value1_color->setItemIcon(6, yellow);

    ui->value2_color->setItemIcon(0, olive);
    ui->value2_color->setItemIcon(1, dark_red);
    ui->value2_color->setItemIcon(2, grey);
    ui->value2_color->setItemIcon(3, light_grey);
    ui->value2_color->setItemIcon(4, pink);
    ui->value2_color->setItemIcon(5, orange);
    ui->value2_color->setItemIcon(6, yellow);

    ui->value3_color->setItemIcon(0, olive);
    ui->value3_color->setItemIcon(1, dark_red);
    ui->value3_color->setItemIcon(2, grey);
    ui->value3_color->setItemIcon(3, light_grey);
    ui->value3_color->setItemIcon(4, pink);
    ui->value3_color->setItemIcon(5, orange);
    ui->value3_color->setItemIcon(6, yellow);

    ui->value4_color->setItemIcon(0, olive);
    ui->value4_color->setItemIcon(1, dark_red);
    ui->value4_color->setItemIcon(2, grey);
    ui->value4_color->setItemIcon(3, light_grey);
    ui->value4_color->setItemIcon(4, pink);
    ui->value4_color->setItemIcon(5, orange);
    ui->value4_color->setItemIcon(6, yellow);
}

// 1.1 + 1.3
void OptionDemoWindow::set_default_settings_mode()
{
    ui->group_sphere_1->setEnabled(0);
    ui->group_sphere_2->setEnabled(0);
    ui->group_sphere_3->setEnabled(0);
    ui->group_sphere_4->setEnabled(0);
    ui->group_lights->setEnabled(0);
    ui->group_demo->setEnabled(0);
    ui->group_other->setEnabled(0);
    ui->group_scene->setEnabled(0);

    set_default_color();
    set_default_value();
    set_default_light();

    ui->global_color->setCurrentIndex(1);
    ui->other_format->setCurrentIndex(2);
    ui->global_is_reflex->setChecked(1);
    ui->global_is_light->setChecked(1);
    ui->global_is_refraction->setChecked(1);
    ui->global_display_scene->setChecked(0);

    ui->other_path->setText("C:/Program Files (x86)/Qt Project/RayTracing");
}

// 1.3
void OptionDemoWindow::set_users_settings_mode()
{
    ui->group_sphere_1->setEnabled(1);
    ui->group_sphere_2->setEnabled(1);
    ui->group_sphere_3->setEnabled(1);
    ui->group_sphere_4->setEnabled(1);
    ui->group_lights->setEnabled(1);
    ui->group_demo->setEnabled(1);
    ui->group_other->setEnabled(1);
    ui->group_scene->setEnabled(1);
}

// 1.1
void OptionDemoWindow::set_default_color()
{
    ui->value1_color->setCurrentIndex(0);
    ui->value2_color->setCurrentIndex(1);
    ui->value3_color->setCurrentIndex(1);
    ui->value4_color->setCurrentIndex(0);
}

// 1.1 + 1.3
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

    ui->value1_P->setValue(1.0);
    ui->value2_P->setValue(1.5);
    ui->value3_P->setValue(1.0);
    ui->value4_P->setValue(1.0);
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

// 1.1 + 1.2 + 1.3
void OptionDemoWindow::on_button_start_clicked()
{
    DemonstrationWindow *dw = new DemonstrationWindow;

    // -- установка цветовых характеристик (фон, сферы) --
    dw->set_background_color(ui->global_color->currentIndex());
    dw->set_sphere_color(ui->value1_color->currentIndex(), ui->value2_color->currentIndex(), ui->value3_color->currentIndex(), ui->value4_color->currentIndex());

    // -- установка числовых характеристик (координаты, радиусы, интенсивность и т.д) --
    dw->set_radius(ui->value1_R->value(), ui->value2_R->value(), ui->value3_R->value(), ui->value4_R->value());
    dw->set_x(ui->value1_X->value(), ui->value2_X->value(), ui->value3_X->value(), ui->value4_X->value());
    dw->set_y(ui->value1_Y->value(), ui->value2_Y->value(), ui->value3_Y->value(), ui->value4_Y->value());
    dw->set_z(ui->value1_Z->value(), ui->value2_Z->value(), ui->value3_Z->value(), ui->value4_Z->value());
    dw->set_refraction_index(ui->value1_P->value(), ui->value2_P->value(), ui->value3_P->value(), ui->value4_P->value());
    dw->set_x_light(ui->light1_X->value(), ui->light2_X->value(), ui->light3_X->value());
    dw->set_y_light(ui->light1_Y->value(), ui->light2_Y->value(), ui->light3_Y->value());
    dw->set_z_light(ui->light1_Z->value(), ui->light2_Z->value(), ui->light3_Z->value());
    dw->set_d_light(ui->light1_D->value(), ui->light2_D->value(), ui->light3_D->value());

    // -- установка дополнительных параметров --
    dw->set_path_to_image(ui->other_path->text().simplified().toStdString());
    dw->set_flag_output_scene(ui->global_display_scene->isChecked());
    dw->set_reflection_flag(ui->global_is_reflex->isChecked());
    dw->set_lighting_flag(ui->global_is_light->isChecked());
    dw->set_refraction_flag(ui->global_is_refraction->isChecked());
    dw->set_code_format_output(ui->other_format->currentIndex());

    dw->setWindowFlags(Qt::MSWindowsFixedSizeDialogHint);
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
