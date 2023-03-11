#ifndef DEMONSTRATIONWINDOW_H
#define DEMONSTRATIONWINDOW_H

#include <QDialog>
#include <QFile>
#include <QTextStream>
#include <QTextCodec>

#include <limits>
#include <cmath>
#include <iostream>
#include <fstream>
#include <vector>

#include "geometry.h"
#include "sphere.h"
#include "light.h"
#include "material.h"

namespace Ui {
class DemonstrationWindow;
}

class DemonstrationWindow : public QDialog
{
    Q_OBJECT

public:
    explicit DemonstrationWindow(QWidget *parent = 0);
    ~DemonstrationWindow();

    // Rus:
    //      Область дополнительных функций
    void set_window_options();
    void set_enabled_button(int numStep);
    void open_and_output_image();
    void open_and_output_htmlFile(QString path);
    //      Конец области дополнительных функций

    // Rus:
    //      Область работы с числовыми параметрами
    void set_radius(float r_1, float r_2, float r_3, float r_4) { radius[0] = r_1; radius[1] = r_2; radius[2] = r_3; radius[3] = r_4; }
    float get_radius(int index) { return radius[index]; }

    void set_x(float x_1, float x_2, float x_3, float x_4) { x[0] = x_1 ; x[1] = x_2; x[2] = x_3; x[3] = x_4;}
    float get_x(int index) { return x[index]; }

    void set_y(float y_1, float y_2, float y_3, float y_4) { y[0] = y_1 ; y[1] = y_2; y[2] = y_3; y[3] = y_4;}
    float get_y(int index) { return y[index]; }

    void set_z(float z_1, float z_2, float z_3, float z_4) { z[0] = z_1 ; z[1] = z_2; z[2] = z_3; z[3] = z_4;}
    float get_z(int index) { return z[index]; }

    void set_x_light(float x_1, float x_2, float x_3) { xLigth[0] = x_1 ; xLigth[1] = x_2; xLigth[2] = x_3; }
    float get_x_ligth(int index) { return xLigth[index]; }

    void set_y_light(float y_1, float y_2, float y_3) { yLigth[0] = y_1 ; yLigth[1] = y_2; yLigth[2] = y_3; }
    float get_y_ligth(int index) { return yLigth[index]; }

    void set_z_light(float z_1, float z_2, float z_3) { zLigth[0] = z_1 ; zLigth[1] = z_2; zLigth[2] = z_3; }
    float get_z_ligth(int index) { return zLigth[index]; }

    void set_d_light(float d_1, float d_2, float d_3) { d[0] = d_1 ; d[1] = d_2; d[2] = d_3; }
    float get_d_ligth(int index) { return d[index]; }
    //      Конец области работы с числовыми параметрами

    // Rus:
    //      Область работы с цветовыми характеристиками
    void set_background_color(int id_color) { id_background_color = id_color; }
    Vec3f get_background_color();

    void set_first_sphere_color(int id_color) { idFirstSphereColor = id_color; }
    void set_second_sphere_color(int id_color) { idSecondSphereColor = id_color; }
    void set_third_sphere_color(int id_color) { idThirdSphereColor = id_color; }
    void set_fourth_sphere_color(int id_color) { idFourthSphereColor = id_color; }
    Vec3f get_sphere_color(int id_color);

    Vec2f get_albedo_2f(int id_color);
    Vec3f get_albedo_3f(int id_color);
    float get_specular_exponent(int id_color);
    //      Конец области работы с цветовыми характеристиками

    // Rus:
    //      Область реализации алгоритма
    Vec3f cast_ray(const Vec3f &orig, const Vec3f &dir, const std::vector<Sphere> &spheres);
    Vec3f cast_ray(const Vec3f &orig, const Vec3f &dir, const std::vector<Sphere> &spheres, const std:: vector<Light> &lights);
    Vec3f cast_ray_light(const Vec3f &orig, const Vec3f &dir, const std:: vector<Sphere> &spheres, const std::vector<Light> &lights);
    Vec3f cast_ray_light2(const Vec3f &orig, const Vec3f &dir, const std::vector<Sphere> &spheres, const std:: vector<Light> &lights);
    Vec3f cast_ray_light3(const Vec3f &orig, const Vec3f &dir, const std:: vector<Sphere> &spheres, const std::vector<Light> &lights, size_t depth = 0);
    //      Конец области реализации алгоритма

    // Rus:
    //      Область пошаговой демонстрации
    void initialize_scene_elements();
    void initialize_standard_objects();
    void initialize_objects_with_albedo2f();
    void initialize_objects_with_albedo3f();

    void start_render(const std::vector<Sphere> &spheres);
    void start_render(const std:: vector<Sphere> &spheres, const std::vector<Light> &lights);
    void start_render_light(const std:: vector<Sphere> &spheres, const std::vector<Light> &lights);
    void start_render_light2(const std:: vector<Sphere> &spheres, const std::vector<Light> &lights);
    void start_render_light3(const std:: vector<Sphere> &spheres, const std::vector<Light> &lights);
    //      Конец области пошаговой демонстрации

private slots:
    // Rus:
    //      Область системных функций
    void on_button_start_demo_clicked();

    void on_button_next_step_clicked();

    void on_button_prev_step_clicked();

    void on_button_help_clicked();
    //      Конец области системных функций

private:
    Ui::DemonstrationWindow *ui;
    int step; // шаг алгоритма
    int id_background_color; // цвет фона
    int idFirstSphereColor, idSecondSphereColor, idThirdSphereColor, idFourthSphereColor; // id цвета сферы
    unsigned int width, height; // ширина и высота буффера для сохр. изобр.
    std::vector<Sphere> spheres; // -- сферы --
    std::vector<Light> lights; // -- источники освещения --
    float radius[4], x[4], y[4], z[4];  // -- параметры сфер --
    float xLigth[3], yLigth[3], zLigth[3], d[3]; // -- параметры источников освещения --
};

#endif // DEMONSTRATIONWINDOW_H
