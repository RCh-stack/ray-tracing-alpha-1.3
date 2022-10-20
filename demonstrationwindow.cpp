#include "demonstrationwindow.h"
#include "ui_demonstrationwindow.h"

DemonstrationWindow::DemonstrationWindow(QWidget *parent) :
    QDialog(parent),
    ui(new Ui::DemonstrationWindow)
{
    ui->setupUi(this);

    step = 0;
    QPixmap start (":/icons/images/start-button.png");
    QPixmap leftArrow (":/icons/images/left-arrow.png");
    QPixmap rightArrow (":/icons/images/right-arrow.png");
    QPixmap help(":/icons/images/help-button.png");

    QIcon ButtonStart(start);
    QIcon ButtonNextStep(rightArrow);
    QIcon ButtonPrevStep(leftArrow);
    QIcon ButtonInformation(help);

    ui->button_start_demo->setIcon(ButtonStart);
    ui->button_next_step->setIcon(ButtonNextStep);
    ui->button_prev_step->setIcon(ButtonPrevStep);
    ui->button_help->setIcon(ButtonInformation);
}

DemonstrationWindow::~DemonstrationWindow()
{
    delete ui;
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

Vec3f cast_ray(const Vec3f &orig, const Vec3f &dir, const std::vector<Sphere> &spheres)
{
    Vec3f point, N;
    Material material;
    if (!scene_intersect(orig, dir, spheres, point, N, material))
    {
        return Vec3f(0.2, 0.7, 0.8); // background color
    }
    return material.diffuse_color;
}

Vec3f cast_ray(const Vec3f &orig, const Vec3f &dir, const std::vector<Sphere> &spheres, const std:: vector<Light> &lights)
{
    Vec3f point, N;
    Material material;
    if (!scene_intersect(orig, dir, spheres, point, N, material))
        return Vec3f(0.2, 0.7, 0.8); // background color

    float diffuse_light_intensity = 0;
    for (size_t i = 0; i < lights.size(); i++)
    {
        Vec3f light_dir = (lights[i].stand - point).normalize();
        diffuse_light_intensity += lights[i].depth * std::max(0.f, light_dir * N);
    }

    return material.diffuse_color * diffuse_light_intensity;
}

Vec3f cast_ray_light(const Vec3f &orig, const Vec3f &dir, const std:: vector<Sphere> &spheres, const std::vector<Light> &lights)
{
    Vec3f point, N;
    Material material;
    if (!scene_intersect(orig, dir, spheres, point, N, material))
        return Vec3f(0.2, 0.7, 0.8); // background color

    float diffuse_light_intensity = 0, specular_light_intensity = 0;
    for (size_t i = 0; i < lights.size(); i++)
    {
        Vec3f light_dir = (lights[i].stand - point).normalize();
        diffuse_light_intensity += lights[i].depth * std::max(0.f, light_dir * N);
        specular_light_intensity += powf(std:: max(0.f, -reflect(-light_dir, N) * dir), material.specular_exponent) * lights[i].depth;
    }

    return material.diffuse_color * diffuse_light_intensity * material.albedo[0] + Vec3f(1., 1., 1.) * specular_light_intensity * material.albedo[1];
}

Vec3f cast_ray_light2(const Vec3f &orig, const Vec3f &dir, const std::vector<Sphere> &spheres, const std:: vector<Light> &lights)
{
    Vec3f point, N;
    Material material;
    if (!scene_intersect(orig, dir, spheres, point, N, material))
        return Vec3f(0.2, 0.7, 0.8); // background color

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

Vec3f cast_ray_light3(const Vec3f &orig, const Vec3f &dir, const std:: vector<Sphere> &spheres, const std::vector<Light> &lights, size_t depth = 0)
{
    Vec3f point, N;
    Material3f material;
    if (depth > 4 || !scene_intersect3f(orig, dir, spheres, point, N, material))
        return Vec3f(0.2, 0.7, 0.8); // background color

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
    const int width = 800;
    const int height = 600;
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
    const int width = 800;
    const int height = 600;
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
    const int width = 800;
    const int height = 600;
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
    const int width = 800;
    const int height = 600;
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
    const int width = 800;
    const int height = 600;
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

void DemonstrationWindow::on_button_start_demo_clicked()
{
    step = 1; // -- номер шага --
    open_and_output_htmlFile(":/demo_files/files/step_first.html");

    Material ivory(Vec3f(0.4, 0.4, 0.3));
    Material red_rubber(Vec3f(0.3, 0.1, 0.1));

    std::vector<Sphere> spheres;
    spheres.push_back(Sphere(Vec3f(-3, 0, -16), 2, ivory));
    spheres.push_back(Sphere(Vec3f(-1.0, -1.5, -12), 2, red_rubber));
    spheres.push_back(Sphere(Vec3f( 1.5, -0.5, -18), 3, red_rubber));
    spheres.push_back(Sphere(Vec3f( 7, 5, -18), 4, ivory));

    start_render(spheres);

    QGraphicsScene *scene = new QGraphicsScene();
    QPixmap image("C:/Program Files (x86)/Qt Project/RayTracing/out.ppm");
    scene->addPixmap(image);
    ui->view_demo->setScene(scene);
    ui->view_demo->showFullScreen(); // -- отобразить на экране --
}

void DemonstrationWindow::on_button_next_step_clicked()
{
    if(step > 0)
        step++;

    if(step == 2)
    {
        open_and_output_htmlFile(":/demo_files/files/step_second.html");
        Material ivory(Vec3f(0.4, 0.4, 0.3));
        Material red_rubber(Vec3f(0.3, 0.1, 0.1));

        std::vector<Sphere> spheres;
        spheres.push_back(Sphere(Vec3f(-3, 0, -16), 2, ivory));
        spheres.push_back(Sphere(Vec3f(-1.0, -1.5, -12), 2, red_rubber));
        spheres.push_back(Sphere(Vec3f( 1.5, -0.5, -18), 3, red_rubber));
        spheres.push_back(Sphere(Vec3f( 7, 5, -18), 4, ivory));

        std::vector<Light> lights;
        lights.push_back(Light(Vec3f(-20, 20, 20), 1.5));

        start_render(spheres, lights);
    }

    if(step == 3)
    {
        open_and_output_htmlFile(":/demo_files/files/step_third.html");
        Material ivory(Vec2f(0.6, 0.3), Vec3f(0.4, 0.4, 0.3), 50.);
        Material red_rubber(Vec2f(0.9, 0.1), Vec3f(0.3, 0.1, 0.1), 10.);

        std::vector<Sphere> spheres;
        spheres.push_back(Sphere(Vec3f(-3, 0, -16), 2, ivory));
        spheres.push_back(Sphere(Vec3f(-1.0, -1.5, -12), 2, red_rubber));
        spheres.push_back(Sphere(Vec3f( 1.5, -0.5, -18), 3, red_rubber));
        spheres.push_back(Sphere(Vec3f( 7, 5, -18), 4, ivory));

        std:: vector<Light> lights;
        lights.push_back(Light(Vec3f(-20, 20, 20), 1.5));
        lights.push_back(Light(Vec3f( 30, 50, -25), 1.8));
        lights.push_back(Light(Vec3f( 30, 20, 30), 1.7));

        start_render_light(spheres, lights);
    }
    if(step == 4)
    {
        open_and_output_htmlFile(":/demo_files/files/step_four.html");
        Material ivory(Vec2f(0.6, 0.3), Vec3f(0.4, 0.4, 0.3), 50.);
        Material red_rubber(Vec2f(0.9, 0.1), Vec3f(0.3, 0.1, 0.1), 10.);

        std::vector<Sphere> spheres;
        spheres.push_back(Sphere(Vec3f(-3, 0, -16), 2, ivory));
        spheres.push_back(Sphere(Vec3f(-1.0, -1.5, -12), 2, red_rubber));
        spheres.push_back(Sphere(Vec3f( 1.5, -0.5, -18), 3, red_rubber));
        spheres.push_back(Sphere(Vec3f( 7, 5, -18), 4, ivory));

        std::vector<Light> lights;
        lights.push_back(Light(Vec3f(-20, 20, 20), 1.5));
        lights.push_back(Light(Vec3f( 30, 50, -25), 1.8));
        lights.push_back(Light(Vec3f( 30, 20, 30), 1.7));

        start_render_light2(spheres, lights);
    }
    if(step == 5)
    {
        open_and_output_htmlFile(":/demo_files/files/step_fifth.html");
        Material3f ivory(Vec3f(0.6, 0.3, 0.1), Vec3f(0.4, 0.4, 0.3), 50.);
        Material3f red_rubber(Vec3f(0.9, 0.1, 0.0), Vec3f(0.3, 0.1, 0.1), 10.);
        Material3f mirror(Vec3f(0.0, 10.0, 0.8), Vec3f(1.0, 1.0, 1.0), 1425.);

        std::vector<Sphere> spheres;
        spheres.push_back(Sphere(Vec3f(-3, 0, -16), 2,  ivory));
        spheres.push_back(Sphere(Vec3f(-1.0, -1.5, -12), 2, mirror));
        spheres.push_back(Sphere(Vec3f( 1.5, -0.5, -18), 3, red_rubber));
        spheres.push_back(Sphere(Vec3f( 7, 5, -18), 4, mirror));

        std::vector<Light> lights;
        lights.push_back(Light(Vec3f(-20, 20, 20), 1.5));
        lights.push_back(Light(Vec3f( 30, 50, -25), 1.8));
        lights.push_back(Light(Vec3f( 30, 20, 30), 1.7));

        start_render_light3(spheres, lights);
    }

    if(step > 0)
    {
        QGraphicsScene *scene = new QGraphicsScene();
        QPixmap image("C:/Program Files (x86)/Qt Project/RayTracing/out.ppm");
        scene->addPixmap(image);
        ui->view_demo->setScene(scene);
        ui->view_demo->showFullScreen();
    }
}

void DemonstrationWindow::on_button_prev_step_clicked()
{

}

void DemonstrationWindow::on_button_help_clicked()
{

}
