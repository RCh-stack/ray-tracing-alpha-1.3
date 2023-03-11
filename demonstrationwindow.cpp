#include "demonstrationwindow.h"
#include "ui_demonstrationwindow.h"

DemonstrationWindow::DemonstrationWindow(QWidget *parent) :
    QDialog(parent),
    ui(new Ui::DemonstrationWindow)
{
    ui->setupUi(this);
    set_window_options();
    step = 0, width = 1048, height = 498;
    ui->button_next_step->setEnabled(0);
    ui->button_prev_step->setEnabled(0);
}

DemonstrationWindow::~DemonstrationWindow()
{
    delete ui;
}

void DemonstrationWindow::set_window_options()
{
    QPixmap start (":/icons/images/start-button.png");
    QPixmap leftArrow (":/icons/images/prev-page.png");
    QPixmap rightArrow (":/icons/images/next-page.png");
    QPixmap help(":/icons/images/help-button.png");

    QIcon ButtonStart(start);
    QIcon ButtonNextStep(rightArrow);
    QIcon ButtonPrevStep(leftArrow);
    QIcon ButtonInformation(help);

    ui->button_start_demo->setIcon(ButtonStart);
    ui->button_next_step->setIcon(ButtonNextStep);
    ui->button_prev_step->setIcon(ButtonPrevStep);
    ui->button_help->setIcon(ButtonInformation);

    QPixmap bkgnd(":/icons/images/mainwindow_background.jpg");
    bkgnd = bkgnd.scaled(size(), Qt::IgnoreAspectRatio);
    QPalette p = palette();
    p.setBrush(QPalette::Background, bkgnd);
    setPalette(p);
}

// 1.1
void DemonstrationWindow::open_and_output_image()
{
    QGraphicsScene *scene = new QGraphicsScene();
    QPixmap image("C:/Program Files (x86)/Qt Project/RayTracing/out.ppm");
    scene->addPixmap(image);
    ui->view_demo->setScene(scene);
    ui->view_demo->showFullScreen();
}

// 1.1
Vec3f DemonstrationWindow::get_background_color()
{
    return id_background_color == 0 ? Vec3f(0.2, 0.7, 0.8) :
              id_background_color == 1 ? Vec3f(0.3, 0.9, 0.7) :
              id_background_color == 2 ? Vec3f(0.2, 0.7, 0.7) :
              id_background_color == 3 ? Vec3f(0.2, 0.6, 0.9) : Vec3f(0.2, 0.5, 0.8);
}

// 1.1
Vec3f DemonstrationWindow::get_sphere_color(int id_color)
{
    return id_color == 0 ? Vec3f(0.4, 0.4, 0.3) :
              id_color == 1 ? Vec3f(0.3, 0.1, 0.1) : Vec3f(0.2, 0.2, 0.2);
}

// 1.1
Vec2f DemonstrationWindow::get_albedo_2f(int id_color)
{
    return id_color == 0 ? Vec2f(0.6, 0.3) :
              id_color == 1 ? Vec2f(0.9, 0.1) : Vec2f(0.5, 0.5);
}

// 1.1
Vec3f DemonstrationWindow::get_albedo_3f(int id_color)
{
    return id_color == 0 ? Vec3f(0.6, 0.3, 0.1) :
              id_color == 1 ? Vec3f(0.9, 0.1, 0.0) : Vec3f(0.5, 0.5, 0.2);
}

// 1.1
float DemonstrationWindow::get_specular_exponent(int id_color)
{
    return id_color == 0 ? 50. :
              id_color == 1 ? 10. : 60.;
}

// 1.1
void DemonstrationWindow::set_enabled_button(int numStep)
{
    if(numStep == 1)
        ui->button_prev_step->setEnabled(0);
    else
        ui->button_prev_step->setEnabled(1);

    if(numStep == 5)
        ui->button_next_step->setEnabled(0);
    else
        ui->button_next_step->setEnabled(1);
}

void DemonstrationWindow::open_and_output_htmlFile(QString path)
{
    ui->text_description->clear();
    QFile file(path);
    QTextStream html(&file);
    html.setCodec(QTextCodec::codecForName("UTF-8"));

    if ((file.exists()) && (file.open(QIODevice::ReadOnly | QIODevice::Text)))
    {
        QString str = html.readAll();
        ui->text_description->setText(str);
        file.close();
    }
}

bool scene_intersect(const Vec3f &orig, const Vec3f &dir, const std:: vector<Sphere> &spheres, Vec3f &hit, Vec3f&N, Material &material)
{
    float spheres_dist = std::numeric_limits<float>:: max();
    for (size_t i = 0; i < spheres.size(); i++)
    {
        float dist_i;
        if (spheres[i].rayCrossingTest(orig, dir, dist_i) && dist_i < spheres_dist)
        {
            spheres_dist = dist_i;
            hit = orig + dir * dist_i;
            N = (hit - spheres[i].center).normalize();
            material = spheres[i].material;
        }
    }

    return spheres_dist < 1000;
}

bool scene_intersect3f(const Vec3f &orig, const Vec3f&dir, const std:: vector<Sphere> &spheres, Vec3f &hit, Vec3f &N, Material3f &material)
{
    float spheres_dist = std:: numeric_limits<float>:: max();
    for (size_t i = 0; i < spheres.size(); i++)
    {
        float dist_i;
        if (spheres[i].rayCrossingTest(orig, dir, dist_i) && dist_i < spheres_dist)
        {
            spheres_dist = dist_i;
            hit = orig + dir * dist_i;
            N = (hit - spheres[i].center).normalize();
            material = spheres[i].material3f;
        }
    }

    return spheres_dist < 1000;
}


Vec3f reflect(const Vec3f &I, const Vec3f &N)
{
    return I - N * 2.f * (I * N);
}

// -- ПЕРВЫЙ ШАГ --
// -- Vec3f(0.2, 0.5, 0.8);  - синий темнее --
// -- Vec3f(0.2, 0.7, 0.8);  - голубой (стандарт)--
// -- Vec3f(0.2, 0.6, 0.9);  - синий светлее
// -- Vec3f(0.2, 0.7, 0.7);  - зеленый (болотный)
// -- Vec3f(0.3, 0.9, 0.7);  - зеленый (светлее)
Vec3f DemonstrationWindow::cast_ray(const Vec3f &orig, const Vec3f &dir, const std::vector<Sphere> &spheres)
{
    Vec3f point, N;
    Material material;
    if (!scene_intersect(orig, dir, spheres, point, N, material))
        return get_background_color(); // background color

    return material.diffuse_color;
}

Vec3f DemonstrationWindow::cast_ray(const Vec3f &orig, const Vec3f &dir, const std::vector<Sphere> &spheres, const std:: vector<Light> &lights)
{
    Vec3f point, N;
    Material material;
    if (!scene_intersect(orig, dir, spheres, point, N, material))
        return get_background_color(); // background color

    float diffuse_light_intensity = 0;
    for (size_t i = 0; i < lights.size(); i++)
    {
        Vec3f light_dir = (lights[i].stand - point).normalize();
        diffuse_light_intensity += lights[i].depth * std::max(0.f, light_dir * N);
    }

    return material.diffuse_color * diffuse_light_intensity;
}

Vec3f DemonstrationWindow::cast_ray_light(const Vec3f &orig, const Vec3f &dir, const std:: vector<Sphere> &spheres, const std::vector<Light> &lights)
{
    Vec3f point, N;
    Material material;
    if (!scene_intersect(orig, dir, spheres, point, N, material))
        return get_background_color(); // background color

    float diffuse_light_intensity = 0, specular_light_intensity = 0;
    for (size_t i = 0; i < lights.size(); i++)
    {
        Vec3f light_dir = (lights[i].stand - point).normalize();
        diffuse_light_intensity += lights[i].depth * std::max(0.f, light_dir * N);
        specular_light_intensity += powf(std:: max(0.f, -reflect(-light_dir, N) * dir), material.specular_exponent) * lights[i].depth;
    }

    return material.diffuse_color * diffuse_light_intensity * material.albedo[0] + Vec3f(1., 1., 1.) * specular_light_intensity * material.albedo[1];
}

Vec3f DemonstrationWindow::cast_ray_light2(const Vec3f &orig, const Vec3f &dir, const std::vector<Sphere> &spheres, const std:: vector<Light> &lights)
{
    Vec3f point, N;
    Material material;
    if (!scene_intersect(orig, dir, spheres, point, N, material))
        return get_background_color(); // background color

    float diffuse_light_intensity = 0, specular_light_intensity = 0;
    for (size_t i = 0; i < lights.size(); i++)
    {
        Vec3f light_dir = (lights[i].stand - point).normalize();
        float light_distance = (lights[i].stand - point).norm();
        Vec3f shadow_orig = light_dir * N < 0 ? point - N * 1e-3 : point + N * 1e-3;

        Vec3f shadow_pt, shadow_N;
        Material tmpmaterial;
        if (scene_intersect(shadow_orig, light_dir, spheres, shadow_pt, shadow_N, tmpmaterial) && (shadow_pt - shadow_orig).norm() < light_distance)
            continue;
        diffuse_light_intensity += lights[i].depth * std::max(0.f, light_dir * N);
        specular_light_intensity += powf(std::max(0.f, - reflect(-light_dir, N) * dir), material.specular_exponent) * lights[i].depth;
    }

    return material.diffuse_color * diffuse_light_intensity * material.albedo[0] + Vec3f(1., 1., 1.) * specular_light_intensity * material.albedo[1];
}

Vec3f DemonstrationWindow::cast_ray_light3(const Vec3f &orig, const Vec3f &dir, const std:: vector<Sphere> &spheres, const std::vector<Light> &lights, size_t depth)
{
    Vec3f point, N;
    Material3f material;
    if (depth > 4 || !scene_intersect3f(orig, dir, spheres, point, N, material))
        return get_background_color(); // background color

    Vec3f reflect_dir = reflect(dir, N).normalize();
    Vec3f reflect_orig = reflect_dir * N < 0 ? point - N * 1e-3 : point + N * 1e-3;
    Vec3f reflect_color = cast_ray_light3(reflect_orig, reflect_dir, spheres, lights, depth + 1);

    float diffuse_light_intensity = 0, specular_light_intensity = 0;
    for (size_t i = 0; i < lights.size(); i++)
    {
        Vec3f light_dir = (lights[i].stand - point).normalize();
        float light_distance = (lights[i].stand - point).norm();
        Vec3f shadow_orig = light_dir * N < 0 ? point - N * 1e-3 : point + N * 1e-3;

        Vec3f shadow_pt, shadow_N;
        Material3f tmpmaterial;

        if(scene_intersect3f(shadow_orig, light_dir, spheres, shadow_pt, shadow_N, tmpmaterial) && (shadow_pt - shadow_orig).norm() < light_distance)
            continue;

        diffuse_light_intensity += lights[i].depth * std::max(0.f, light_dir * N);
        specular_light_intensity += powf(std:: max(0.f, - reflect(-light_dir, N) * dir), material.specular_exponent) * lights[i].depth;
    }

    return material.diffuse_color * diffuse_light_intensity * material.albedo[0] + Vec3f(1., 1., 1.) * specular_light_intensity * material.albedo[1] + reflect_color * material.albedo[2];
}

void DemonstrationWindow::start_render(const std::vector<Sphere> &spheres)
{
    const int fov = 1.5;

    std::vector<Vec3f> framebuffer(width * height);
    for (size_t j = 0; j < height; j++)
    {
        for (size_t i = 0; i < width; i++)
        {
            float x = (2 * (i + 0.5)/(float)width - 1) * tan (fov/2.) * width/(float)height;
            float y = -(2 * (j + 0.5)/(float)height - 1) * tan(fov/2.);
            Vec3f dir = Vec3f(x, y, -1).normalize();
            framebuffer[i + j * width] = cast_ray(Vec3f(0,0,0), dir, spheres);
        }
    }

    std::ofstream ofs; // save the framebuffer to file
    ofs.open("C:/Program Files (x86)/Qt Project/RayTracing/out.ppm", std::ios::binary);
    ofs << "P6\n" << width << " " << height << "\n 255\n";
    for (size_t i = 0; i < height * width; ++i)
    {
        for (size_t j = 0; j < 3; j++)
        {
            ofs << (char)(255 * std::max(0.f, std::min(1.f, framebuffer[i][j])));
        }
    }
    ofs.close();
}

void DemonstrationWindow::start_render(const std:: vector<Sphere> &spheres, const std::vector<Light> &lights)
{
    const int fov = 1.5;

    std::vector<Vec3f> framebuffer(width * height);
    for (size_t j = 0; j < height; j++)
    {
        for (size_t i = 0; i < width; i++)
        {
            float x = (2 * (i + 0.5)/(float)width - 1) * tan(fov/2.) * width/(float)height;
            float y = -(2 * (j + 0.5)/(float)height - 1) * tan(fov/2.);
            Vec3f dir = Vec3f(x, y, -1).normalize();
            framebuffer[i + j * width] = cast_ray(Vec3f (0,0,0), dir, spheres, lights);
        }
    }

    std:: ofstream ofs; // save the framebuffer to file
    ofs.open("C:/Program Files (x86)/Qt Project/RayTracing/out.ppm", std::ios::binary);
    ofs << "P6\n" << width << " " << height << "\n 255\n";
    for (size_t i = 0; i < height * width; ++i)
    {
        for (size_t j = 0; j < 3; j++)
        {
            ofs << (char)(255 * std::max(0.f, std:: min(1.f, framebuffer[i][j])));
        }
    }
    ofs.close();
}

void DemonstrationWindow::start_render_light(const std:: vector<Sphere> &spheres, const std::vector<Light> &lights)
{
    const int fov = 1.5;

    std::vector<Vec3f> framebuffer(width * height);
    for (size_t j = 0; j < height; j++)
    {
        for (size_t i = 0; i < width; i++)
        {
            float x = (2 * (i + 0.5)/(float)width - 1) * tan(fov/2.)*width/(float)height;
            float y = -(2 * (j + 0.5)/(float)height - 1) * tan(fov/2.);
            Vec3f dir = Vec3f(x, y, -1).normalize();
            framebuffer[i + j * width] = cast_ray_light(Vec3f(0,0,0), dir, spheres, lights);
        }
    }

    std:: ofstream ofs; // save the framebuffer to file
    ofs.open("C:/Program Files (x86)/Qt Project/RayTracing/out.ppm", std::ios:: binary);
    ofs << "P6\n" << width << " " << height << "\n 255\n";
    for (size_t i = 0; i < height * width; ++i) \
    {
        Vec3f &c = framebuffer[i];
        float max = std:: max(c[0], std:: max(c[1], c[2]));
        if (max > 1) c = c * (1./max);
        for (size_t j = 0; j < 3; j++)
            ofs << (char)(255 * std:: max(0.f, std:: min(1.f, framebuffer[i][j])));
    }

    ofs.close();
}

void DemonstrationWindow::start_render_light2(const std:: vector<Sphere> &spheres, const std::vector<Light> &lights)
{
    const int fov = 1.5;

    std::vector<Vec3f> framebuffer(width * height);
    for (size_t j = 0; j < height; j++)
    {
        for (size_t i = 0; i < width; i++)
        {
            float x = (2 * (i + 0.5)/(float)width - 1) * tan(fov/2.)*width/(float)height;
            float y = -(2 * (j + 0.5)/(float)height - 1) * tan(fov/2.);
            Vec3f dir = Vec3f(x, y, -1).normalize();
            framebuffer[i + j * width] = cast_ray_light2(Vec3f(0,0,0), dir, spheres, lights);
        }
    }

    std:: ofstream ofs; // save the framebuffer to file
    ofs.open("C:/Program Files (x86)/Qt Project/RayTracing/out.ppm", std::ios::binary);
    ofs << "P6\n" << width << " " << height << "\n255\n";

    for (size_t i = 0; i < height * width; ++i)
    {
        Vec3f &c = framebuffer[i];
        float max = std:: max(c[0], std::max(c[1], c[2]));
        if (max > 1) c = c * (1./max);
        for (size_t j = 0; j < 3; j++)
            ofs << (char)(255 * std:: max(0.f, std:: min(1.f, framebuffer[i][j])));
    }

    ofs. close();
}

void DemonstrationWindow::start_render_light3(const std::vector<Sphere> &spheres, const std::vector<Light> &lights)
{
    const int fov = 1.5;

    std::vector<Vec3f> framebuffer(width * height);
    for (size_t j = 0; j < height; j++)
    {
        for (size_t i = 0; i < width; i++)
        {
            float x = (2 * (i + 0.5)/(float)width - 1) * tan(fov/2.)*width/(float)height;
            float y = -(2 * (j + 0.5)/(float)height - 1) * tan(fov/2.);
            Vec3f dir = Vec3f(x, y, -1).normalize();
            framebuffer[i + j * width] = cast_ray_light3(Vec3f(0,0,0), dir, spheres, lights);
        }
    }

    std:: ofstream ofs; // save the framebuffer to file
    ofs.open("C:/Program Files (x86)/Qt Project/RayTracing/out.ppm", std::ios::binary);
    ofs << "P6\n" << width << " " << height << "\n255\n";

    for (size_t i = 0; i < height * width; ++i)
    {
        Vec3f &c = framebuffer[i];
        float max = std:: max(c[0], std::max(c[1], c[2]));
        if (max > 1) c = c * (1./max);
        for (size_t j = 0; j < 3; j++)
            ofs << (char)(255 * std:: max(0.f, std:: min(1.f, framebuffer[i][j])));
    }

    ofs. close();
}

// 1.1
void DemonstrationWindow::initialize_scene_elements()
{
    spheres.clear();
    lights.clear();

    if(step == 1 || step == 2)
        initialize_standard_objects();
    else if(step == 3 || step == 4)
        initialize_objects_with_albedo2f();
    else
        initialize_objects_with_albedo3f();
}

// 1.1
void DemonstrationWindow::initialize_standard_objects()
{
    Material firstSphere(get_sphere_color(idFirstSphereColor));
    Material secondSphere(get_sphere_color(idSecondSphereColor));
    Material thirdSphere(get_sphere_color(idThirdSphereColor));
    Material fourthSphere(get_sphere_color(idFourthSphereColor));

    spheres.push_back(Sphere(Vec3f(get_x(0), get_y(0), get_z(0)), get_radius(0), firstSphere));
    spheres.push_back(Sphere(Vec3f(get_x(1), get_y(1), get_z(1)), get_radius(1), secondSphere));
    spheres.push_back(Sphere(Vec3f(get_x(2), get_y(2), get_z(2)), get_radius(2), thirdSphere));
    spheres.push_back(Sphere(Vec3f(get_x(3), get_y(3), get_z(3)), get_radius(3), fourthSphere));

    lights.push_back(Light(Vec3f(get_x_ligth(0), get_y_ligth(0), get_z_ligth(0)), get_d_ligth(0)));
}

// 1.1
void DemonstrationWindow::initialize_objects_with_albedo2f()
{
    Material firstSphere(get_albedo_2f(idFirstSphereColor), get_sphere_color(idFirstSphereColor), get_specular_exponent(idFirstSphereColor));
    Material secondSphere(get_albedo_2f(idSecondSphereColor), get_sphere_color(idSecondSphereColor), get_specular_exponent(idSecondSphereColor));
    Material thirdSphere(get_albedo_2f(idThirdSphereColor), get_sphere_color(idThirdSphereColor), get_specular_exponent(idThirdSphereColor));
    Material fourthSphere(get_albedo_2f(idFourthSphereColor), get_sphere_color(idFourthSphereColor), get_specular_exponent(idFourthSphereColor));

    spheres.push_back(Sphere(Vec3f(get_x(0), get_y(0), get_z(0)), get_radius(0), firstSphere));
    spheres.push_back(Sphere(Vec3f(get_x(1), get_y(1), get_z(1)), get_radius(1), secondSphere));
    spheres.push_back(Sphere(Vec3f(get_x(2), get_y(2), get_z(2)), get_radius(2), thirdSphere));
    spheres.push_back(Sphere(Vec3f(get_x(3), get_y(3), get_z(3)), get_radius(3), fourthSphere));

    lights.push_back(Light(Vec3f(get_x_ligth(0), get_y_ligth(0), get_z_ligth(0)), get_d_ligth(0)));
    lights.push_back(Light(Vec3f(get_x_ligth(1), get_y_ligth(1), get_z_ligth(1)), get_d_ligth(1)));
    lights.push_back(Light(Vec3f(get_x_ligth(2), get_y_ligth(2), get_z_ligth(2)), get_d_ligth(2)));
}

// 1.1
void DemonstrationWindow::initialize_objects_with_albedo3f()
{
    Material3f firstSphere(get_albedo_3f(idFirstSphereColor), get_sphere_color(idFirstSphereColor), get_specular_exponent(idFirstSphereColor));
    Material3f thirdSphere(get_albedo_3f(idThirdSphereColor), get_sphere_color(idThirdSphereColor), get_specular_exponent(idThirdSphereColor));
    Material3f mirror(Vec3f(0.0, 10.0, 0.8), Vec3f(1.0, 1.0, 1.0), 1425.); // 2 and 4 - зеркальные

    spheres.push_back(Sphere(Vec3f(get_x(0), get_y(0), get_z(0)), get_radius(0), firstSphere));
    spheres.push_back(Sphere(Vec3f(get_x(1), get_y(1), get_z(1)), get_radius(1), mirror));
    spheres.push_back(Sphere(Vec3f(get_x(2), get_y(2), get_z(2)), get_radius(2), thirdSphere));
    spheres.push_back(Sphere(Vec3f(get_x(3), get_y(3), get_z(3)), get_radius(3), mirror));

    lights.push_back(Light(Vec3f(get_x_ligth(0), get_y_ligth(0), get_z_ligth(0)), get_d_ligth(0)));
    lights.push_back(Light(Vec3f(get_x_ligth(1), get_y_ligth(1), get_z_ligth(1)), get_d_ligth(1)));
    lights.push_back(Light(Vec3f(get_x_ligth(2), get_y_ligth(2), get_z_ligth(2)), get_d_ligth(2)));
}

void DemonstrationWindow::on_button_start_demo_clicked()
{
    step = 1; // -- номер шага --
    // -- вызов функции --
    open_and_output_htmlFile(":/demo_files/files/demo/step_first.html");
    initialize_scene_elements();
    start_render(spheres);
    open_and_output_image();
    set_enabled_button(step);
}

void DemonstrationWindow::on_button_next_step_clicked()
{
    if(step >= 1 && step < 5)
        step++;

    // func выполнить_шаг(int номер_шага) { .... }
    if(step == 2)
    {
        open_and_output_htmlFile(":/demo_files/files/demo/step_second.html");
        initialize_scene_elements();
        start_render(spheres, lights);
    }
    if(step == 3)
    {
        open_and_output_htmlFile(":/demo_files/files/demo/step_third.html");
        initialize_scene_elements();
        start_render_light(spheres, lights);
    }
    if(step == 4)
    {
        open_and_output_htmlFile(":/demo_files/files/demo/step_four.html");
        initialize_scene_elements();
        start_render_light2(spheres, lights);
    }
    if(step == 5)
    {
        open_and_output_htmlFile(":/demo_files/files/demo/step_fifth.html");
        initialize_scene_elements();
        start_render_light3(spheres, lights);
    }

    if(step > 0)
        open_and_output_image();

    set_enabled_button(step);
}

void DemonstrationWindow::on_button_prev_step_clicked()
{
    if(step > 1 && step <= 5)
        step--;

    if(step == 1)
    {
        open_and_output_htmlFile(":/demo_files/files/demo/step_first.html");
        initialize_scene_elements();
        start_render(spheres);
    }
    if(step == 2)
    {
        open_and_output_htmlFile(":/demo_files/files/demo/step_second.html");
        initialize_scene_elements();
        start_render(spheres, lights);
    }

    if(step == 3)
    {
        open_and_output_htmlFile(":/demo_files/files/demo/step_third.html");
        initialize_scene_elements();
        start_render_light(spheres, lights);
    }
    if(step == 4)
    {
        open_and_output_htmlFile(":/demo_files/files/demo/step_four.html");
        initialize_scene_elements();
        start_render_light2(spheres, lights);
    }
    if(step == 5)
    {
        open_and_output_htmlFile(":/demo_files/files/demo/step_fifth.html");
        initialize_scene_elements();
        start_render_light3(spheres, lights);
    }

    if(step > 0)
        open_and_output_image();

    set_enabled_button(step);
}

void DemonstrationWindow::on_button_help_clicked()
{

}
