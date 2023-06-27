#ifndef DEMONSTRATIONWINDOW_H
#define DEMONSTRATIONWINDOW_H

#include <QDialog>
#include <QKeyEvent>
#include <QFile>
#include <QTextStream>
#include <QTextCodec>
#include <QSqlQuery>
#include <QMessageBox>

#include <limits>
#include <cmath>
#include <iostream>
#include <fstream>
#include <locale>
#include <vector>

#include "geometry.h"
#include "model.h"
#include "sphere.h"
#include "triangle.h"
#include "light.h"
#include "material.h"
#include "sql_requests.h"

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

    // 1.2
    void set_path_to_image(std::string path) { path_to_image = path; }
    std::string get_path_to_image()  { return path_to_image; }

    void open_and_output_image();
    void open_file_by_code(int code);
    void output_step_information(QString string);
    void output_table_of_contents(QString path);
    void save_image_in_framebuffer(std::vector<Vec3f> &framebuffer);
    void save_image_in_framebuffer_with_lighting(std::vector<Vec3f> &framebuffer);

    void set_code_format_output(int code) { id_format_output = code; }
    int get_code_format_output() { return id_format_output; }

    void set_reflection_flag(bool flag) { flag_reflections = flag; }
    void set_lighting_flag(bool flag) { flag_lighting = flag; }
    void set_refraction_flag(bool flag) { flag_refraction = flag; }
    void set_flag_output_scene(bool flag) { flag_output_scene = flag; }
    void set_flag_plane(bool flag) { flag_plane = flag; }

    bool get_reflection_flag() { return flag_reflections; }
    bool get_lighting_flag() { return flag_lighting; }
    bool get_refraction_flag() { return flag_refraction; }
    bool get_flag_output_scene() { return flag_output_scene; }
    bool get_flag_plane() { return flag_plane; }
    //      Конец области дополнительных функций

    // Rus:
    //      Область работы с числовыми параметрами
    void set_id_type(int id) { id_type = id; }
    int get_id_type() { return id_type; }

    void set_radius(float r_1, float r_2, float r_3, float r_4) { radius[0] = r_1; radius[1] = r_2; radius[2] = r_3; radius[3] = r_4; }
    float get_radius(int index) { return radius[index]; }

    void set_refraction_index(float r_1, float r_2, float r_3, float r_4) { refraction[0] = r_1; refraction[1] = r_2; refraction[2] = r_3; refraction[3] = r_4;}
    float get_refraction_index(int index) { return refraction[index]; }

    void set_x(float x_1, float x_2, float x_3, float x_4) { x[0] = x_1 ; x[1] = x_2; x[2] = x_3; x[3] = x_4;}
    void set_y(float y_1, float y_2, float y_3, float y_4) { y[0] = y_1 ; y[1] = y_2; y[2] = y_3; y[3] = y_4;}
    void set_z(float z_1, float z_2, float z_3, float z_4) { z[0] = z_1 ; z[1] = z_2; z[2] = z_3; z[3] = z_4;}

    void set_a_x(float x_1, float x_2, float x_3, float x_4) { a_x[0] = x_1 ; a_x[1] = x_2; a_x[2] = x_3; a_x[3] = x_4; }
    void set_a_y(float y_1, float y_2, float y_3, float y_4) { a_y[0] = y_1 ; a_y[1] = y_2; a_y[2] = y_3; a_y[3] = y_4; }
    void set_a_z(float z_1, float z_2, float z_3, float z_4) { a_z[0] = z_1 ; a_z[1] = z_2; a_z[2] = z_3; a_z[3] = z_4; }

    void set_b_x(float x_1, float x_2, float x_3, float x_4) { b_x[0] = x_1 ; b_x[1] = x_2; b_x[2] = x_3; b_x[3] = x_4; }
    void set_b_y(float y_1, float y_2, float y_3, float y_4) { b_y[0] = y_1 ; b_y[1] = y_2; b_y[2] = y_3; b_y[3] = y_4; }
    void set_b_z(float z_1, float z_2, float z_3, float z_4) { b_z[0] = z_1 ; b_z[1] = z_2; b_z[2] = z_3; b_z[3] = z_4; }

    void set_c_x(float x_1, float x_2, float x_3, float x_4) { c_x[0] = x_1 ; c_x[1] = x_2; c_x[2] = x_3; c_x[3] = x_4; }
    void set_c_y(float y_1, float y_2, float y_3, float y_4) { c_y[0] = y_1 ; c_y[1] = y_2; c_y[2] = y_3; c_y[3] = y_4; }
    void set_c_z(float z_1, float z_2, float z_3, float z_4) { c_z[0] = z_1 ; c_z[1] = z_2; c_z[2] = z_3; c_z[3] = z_4; }

    float get_x(int index) { return x[index]; }
    float get_y(int index) { return y[index]; }
    float get_z(int index) { return z[index]; }

    float get_a_x(int index) { return a_x[index]; }
    float get_a_y(int index) { return a_y[index]; }
    float get_a_z(int index) { return a_z[index]; }

    float get_b_x(int index) { return b_x[index]; }
    float get_b_y(int index) { return b_y[index]; }
    float get_b_z(int index) { return b_z[index]; }

    float get_c_x(int index) { return c_x[index]; }
    float get_c_y(int index) { return c_y[index]; }
    float get_c_z(int index) { return c_z[index]; }

    void set_x_light(float x_1, float x_2, float x_3) { xLigth[0] = x_1 ; xLigth[1] = x_2; xLigth[2] = x_3; }
    void set_y_light(float y_1, float y_2, float y_3) { yLigth[0] = y_1 ; yLigth[1] = y_2; yLigth[2] = y_3; }
    void set_z_light(float z_1, float z_2, float z_3) { zLigth[0] = z_1 ; zLigth[1] = z_2; zLigth[2] = z_3; }
    void set_d_light(float d_1, float d_2, float d_3) { d[0] = d_1 ; d[1] = d_2; d[2] = d_3; }

    float get_y_ligth(int index) { return yLigth[index]; }
    float get_x_ligth(int index) { return xLigth[index]; }
    float get_z_ligth(int index) { return zLigth[index]; }
    float get_d_ligth(int index) { return d[index]; }
    //      Конец области работы с числовыми параметрами

    // Rus:
    //      Область работы с цветовыми характеристиками
    void set_background_color(int id_color) { id_background_color = id_color; }
    Vec3f get_background_color();

    void set_sphere_color(int s1, int s2, int s3, int s4) { color[0] = s1; color[1] = s2; color[2] = s3; color[3] = s4; }
    int get_id_color(int index) { return color[index]; }
    Vec3f get_sphere_color(int id_color);

    Vec2f get_albedo_2f(int id_color);
    Vec3f get_albedo_3f(int id_color);
    Vec4f get_albedo_4f(int id_color);
    float get_specular_exponent(int id_color);
    //      Конец области работы с цветовыми характеристиками

    // Rus:
    //      Область реализации алгоритма

    bool scene_intersect(const Vec3f &orig, const Vec3f &dir, const std:: vector<Sphere> &spheres, Vec3f &hit, Vec3f&N, Material &material);
    bool scene_intersect(const Vec3f &orig, const Vec3f &dir, const std::vector<Triangle> &triangles, Vec3f &hit, Vec3f &N, Material &material);
    bool scene_intersect(const Vec3f &orig, const Vec3f&dir, const std:: vector<Sphere> &spheres, Vec3f &hit, Vec3f &N, Material3f &material);
    bool scene_intersect(const Vec3f &orig, const Vec3f&dir, const std:: vector<Sphere> &spheres, Vec3f &hit, Vec3f &N, Material4f &material);

    bool generate_scene(const Vec3f &orig, const Vec3f &dir, Vec3f &hit, float spheres_dist, Vec3f &N, Material &material);
    bool generate_scene(const Vec3f &orig, const Vec3f &dir, Vec3f &hit, float spheres_dist, Vec3f &N, Material3f &material);
    bool generate_scene(const Vec3f &orig, const Vec3f &dir, Vec3f &hit, float spheres_dist, Vec3f &N, Material4f &material);

    Vec3f cast_ray(const Vec3f &orig, const Vec3f &dir, const std::vector<Sphere> &spheres);
    Vec3f cast_ray(const Vec3f &orig, const Vec3f &dir, const std::vector<Sphere> &spheres, const std:: vector<Light> &lights);
    Vec3f cast_ray_light(const Vec3f &orig, const Vec3f &dir, const std:: vector<Sphere> &spheres, const std::vector<Light> &lights);
    Vec3f cast_ray_light2(const Vec3f &orig, const Vec3f &dir, const std::vector<Sphere> &spheres, const std:: vector<Light> &lights);
    Vec3f cast_ray_light3(const Vec3f &orig, const Vec3f &dir, const std:: vector<Sphere> &spheres, const std::vector<Light> &lights, size_t depth = 0);
    Vec3f cast_ray_light4(const Vec3f &orig, const Vec3f &dir, const std:: vector<Sphere> &spheres, const std::vector<Light> &lights, size_t depth = 0);
    //      Конец области реализации алгоритма

    // Rus:
    //      Область пошаговой демонстрации
    void initialize_scene_elements();
    void initialize_standard_objects();
    void initialize_objects_with_albedo2f();
    void initialize_objects_with_albedo3f();
    void initialize_objects_with_albedo4f();

    void execute_step_algorithm(int num_step);
    void start_render(const std::vector<Sphere> &spheres);
    void start_render(const std:: vector<Sphere> &spheres, const std::vector<Light> &lights);
    //      Конец области пошаговой демонстрации

private slots:
    // Rus:
    //      Область системных функций
    void on_button_start_demo_clicked();
    void on_button_next_step_clicked();
    void on_button_prev_step_clicked();
    void on_button_help_clicked();
    //      Конец области системных функций

protected:
    void keyPressEvent(QKeyEvent *event);

private:
    Ui::DemonstrationWindow *ui;
    int step; // -- шаг алгоритма --
    std::string path_to_image; // -- путь к изображению --
    int id_background_color; // -- цвет фона --
    unsigned int width, height, fov; // -- ширина и высота буффера для сохр. изобр., поле зрения --
    std::vector<Sphere> spheres; // -- сферы --
    std::vector<Triangle> triangles;
    std::vector<Light> lights; // -- источники освещения --
    int color[4]; // -- коды цветов сфер --
    float radius[4], x[4], y[4], z[4], refraction[4];  // -- параметры сфер --
    float a_x[4], a_y[4], a_z[4], b_x[4], b_y[4], b_z[4], c_x[4], c_y[4], c_z[4];
    float xLigth[3], yLigth[3], zLigth[3], d[3]; // -- параметры источников освещения --
    int id_format_output; // -- код формата вывода поясняющей информации к алгоритму --
    int id_type; // тип объектов
    bool flag_reflections, flag_lighting, flag_refraction, flag_plane; // -- флаги использования отражений и освещения + преломления --
    bool flag_output_scene; // отображать сцену или нет
};

#endif // DEMONSTRATIONWINDOW_H
