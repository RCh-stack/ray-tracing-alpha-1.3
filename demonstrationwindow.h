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

    void open_and_output_htmlFile(QString path);

    void start_render(const std::vector<Sphere> &spheres);
    void start_render(const std:: vector<Sphere> &spheres, const std::vector<Light> &lights);
    void start_render_light(const std:: vector<Sphere> &spheres, const std::vector<Light> &lights);
    void start_render_light2(const std:: vector<Sphere> &spheres, const std::vector<Light> &lights);
    void start_render_light3(const std:: vector<Sphere> &spheres, const std::vector<Light> &lights);

private slots:
    void on_button_start_demo_clicked();

    void on_button_next_step_clicked();

    void on_button_prev_step_clicked();

    void on_button_help_clicked();

private:
    Ui::DemonstrationWindow *ui;
    int step;
};

#endif // DEMONSTRATIONWINDOW_H
