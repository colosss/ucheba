#include "mainwindow.h"
#include <QOpenGLShader>
#include <QOpenGLTexture>
#include <QKeyEvent>
#include <QTimer>
#include <cmath>
#include <stdio.h>

using namespace std;

bool keys[256];
bool lightl;
bool lp;
bool fp;
GLfloat yrot=1;
GLfloat xrot;


OpenGLWidget::OpenGLWidget(QWidget *parent)
    : QOpenGLWidget(parent), program(nullptr), rotationAngle(0.0f)
{
    startTimer(16);
    QSurfaceFormat format;
    format.setVersion(3, 3);
    format.setProfile(QSurfaceFormat::CoreProfile);
    setFormat(format);

    // Инициализация массива клавиш
    memset(keys, 0, sizeof(keys));

    // Включаем отслеживание клавиатуры
    setFocusPolicy(Qt::StrongFocus);

    // Инициализация параметров сферы
    sphereRadius = 1.0f;
    sphereAlpha = 1.0f;
    sphereDiffuse = 0.7f;
    sphereSpecular = 0.5f;
    sphereShininess = 32.0f;
    sphereColor = QVector3D(0.2f, 0.4f, 0.8f);
    spherePosition = QVector3D(0.0f, 1.0f, 0.0f);

    // Инициализация параметров освещения
    lightRotationAngle = 0.0f;
    lightRotationSpeed = 1.0f;
    isLightRotating = false;
    lightOrbitRadius = 5.0f;
}

OpenGLWidget::~OpenGLWidget()
{
    makeCurrent();
    delete program;
    doneCurrent();
}

void OpenGLWidget::initializeGL()
{
    initializeOpenGLFunctions();
    glClearColor(0.1f, 0.1f, 0.1f, 1.0f);
    glEnable(GL_DEPTH_TEST);

    // Включаем смешивание для корректной прозрачности
    glEnable(GL_BLEND);
    glBlendFunc(GL_SRC_ALPHA, GL_ONE_MINUS_SRC_ALPHA);

    setupShaders();

    cameraPosition = QVector3D(5.0f, 5.0f, 5.0f);
    cameraTarget = QVector3D(0.0f, 0.0f, 0.0f);
    cameraUp = QVector3D(0.0f, 1.0f, 0.0f);

    updateCamera();
}

void OpenGLWidget::updateCamera()
{
    view.setToIdentity();
    view.lookAt(cameraPosition, cameraTarget, cameraUp);
}

void OpenGLWidget::keyPressEvent(QKeyEvent *event)
{
    if (event->key() >= 0 && event->key() < 256) {
        keys[event->key()] = true;
    }

    // Обработка специальных клавиш для управления сферой и освещением
    switch (event->key()) {
    case Qt::Key_Space:
        toggleLightRotation();
        break;
    case Qt::Key_Plus:
        changeSphereSize(0.1f);
        break;
    case Qt::Key_Minus:
        changeSphereSize(-0.1f);
        break;
    case Qt::Key_1:
        changeSphereTransparency(0.1f);
        break;
    case Qt::Key_2:
        changeSphereTransparency(-0.1f);
        break;
    case Qt::Key_3:
        changeSphereReflection(0.1f);
        break;
    case Qt::Key_4:
        changeSphereReflection(-0.1f);
        break;
    case Qt::Key_5:
        changeSphereAlpha(0.1f);  // Новая функция для альфа-прозрачности
        break;
    case Qt::Key_6:
        changeSphereAlpha(-0.1f); // Новая функция для альфа-прозрачности
        break;
    }

    qDebug() << "Key pressed:" << event->key() << "char:" << char(event->key());
    update();
}

void OpenGLWidget::keyReleaseEvent(QKeyEvent *event)
{
    if (event->key() >= 0 && event->key() < 256) {
        keys[event->key()] = false;
    }
}

void OpenGLWidget::setupShaders()
{
    program = new QOpenGLShaderProgram(this);

    // Вершинный шейдер
    const char *vshader =
        "#version 330 core\n"
        "layout(location = 0) in vec3 position;\n"
        "layout(location = 1) in vec3 normal;\n"
        "uniform mat4 model;\n"
        "uniform mat4 view;\n"
        "uniform mat4 projection;\n"
        "out vec3 FragPos;\n"
        "out vec3 Normal;\n"
        "void main() {\n"
        "    FragPos = vec3(model * vec4(position, 1.0));\n"
        "    Normal = mat3(transpose(inverse(model))) * normal;\n"
        "    gl_Position = projection * view * model * vec4(position, 1.0);\n"
        "}";

    // Фрагментный шейдер
    const char *fshader =
        "#version 330 core\n"
        "in vec3 FragPos;\n"
        "in vec3 Normal;\n"
        "uniform vec3 objectColor;\n"
        "uniform vec3 lightPos;\n"
        "uniform vec3 lightColor;\n"
        "uniform float diffuseStrength;\n"
        "uniform float specularStrength;\n"
        "uniform float shininess;\n"
        "uniform float alpha;\n"
        "out vec4 FragColor;\n"
        "void main() {\n"
        "    // Ambient\n"
        "    float ambientStrength = 0.1;\n"
        "    vec3 ambient = ambientStrength * lightColor;\n"
        "    \n"
        "    // Diffuse\n"
        "    vec3 norm = normalize(Normal);\n"
        "    vec3 lightDir = normalize(lightPos - FragPos);\n"
        "    float diff = max(dot(norm, lightDir), 0.0);\n"
        "    vec3 diffuse = diffuseStrength * diff * lightColor;\n"
        "    \n"
        "    // Specular\n"
        "    vec3 viewDir = normalize(-FragPos);\n"
        "    vec3 reflectDir = reflect(-lightDir, norm);\n"
        "    float spec = pow(max(dot(viewDir, reflectDir), 0.0), shininess);\n"
        "    vec3 specular = specularStrength * spec * lightColor;\n"
        "    \n"
        "    vec3 result = (ambient + diffuse + specular) * objectColor;\n"
        "    FragColor = vec4(result, alpha);\n"
        "}";

    program->addShaderFromSourceCode(QOpenGLShader::Vertex, vshader);
    program->addShaderFromSourceCode(QOpenGLShader::Fragment, fshader);
    program->link();
}

void OpenGLWidget::resizeGL(int w, int h)
{
    glViewport(0, 0, w, h);
    projection.setToIdentity();
    projection.perspective(45.0f, float(w) / float(h), 0.1f, 100.0f);
}

void OpenGLWidget::paintGL()
{
    glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);

    program->bind();

    // Обновление позиции освещения если вращение активно
    if (isLightRotating) {
        lightRotationAngle += lightRotationSpeed;
        if (lightRotationAngle >= 360.0f) lightRotationAngle -= 360.0f;
    }

    // Вычисление позиции освещения
    QVector3D lightPos;
    lightPos.setX(lightOrbitRadius * sin(qDegreesToRadians(lightRotationAngle)));
    lightPos.setY(3.0f);
    lightPos.setZ(lightOrbitRadius * cos(qDegreesToRadians(lightRotationAngle)));

    program->setUniformValue("lightPos", lightPos);
    program->setUniformValue("lightColor", QVector3D(1.0f, 1.0f, 1.0f));

    program->setUniformValue("view", view);
    program->setUniformValue("projection", projection);


    // Сначала рисуем непрозрачные объекты (кубы)
    drawCube(QVector3D(-2.0f, 0.0f, 0.0f),
             QVector3D(0.0f, 1.0f, 0.0f),
             0.8f, 0.2f, 32.0f);

    drawCube(QVector3D(0.0f, 0.0f, 0.0f),
             QVector3D(1.0f, 1.0f, 0.0f),
             1.0f, 1.0f, 0.1f);

    drawCube(QVector3D(2.0f, 0.0f, 0.0f),
             QVector3D(1.0f, 0.0f, 0.0f),
             0.5f, 0.5f, 64.0f);

    drawCube(QVector3D(2.0f, 1.0f, 0.0f),
             QVector3D(1.0f, 0.0f, 0.5f),
             0.9f, 0.1f, 16.0f);

    drawCube(QVector3D(0.0f, 2.0f, 0.0f),
             QVector3D(0.5f, 0.5f, 0.5f),
             0.9f, 0.1f, 16.0f);

    drawCube(QVector3D(0.0f, 0.0f, 2.0f),
             QVector3D(0.0f, 0.5f, 0.5f),
             0.9f, 0.1f, 16.0f);

    drawCube(QVector3D(0.0f, 0.0f, -2.0f),
             QVector3D(0.5f, 0.0f, 0.5f),
             0.9f, 0.1f, 16.0f);

    // Затем рисуем сферу (может быть прозрачной)
    drawSphere(spherePosition, sphereColor, sphereDiffuse, sphereSpecular, sphereShininess, sphereAlpha);

    program->release();
}

void OpenGLWidget::drawCube(const QVector3D &position, const QVector3D &color,
                            float diffuse, float specular, float shininess)
{
    model.setToIdentity();
    model.translate(position);

    program->setUniformValue("model", model);
    program->setUniformValue("objectColor", color);
    program->setUniformValue("diffuseStrength", diffuse);
    program->setUniformValue("specularStrength", specular);
    program->setUniformValue("shininess", shininess);
    program->setUniformValue("alpha", 1.0f); // Кубы всегда непрозрачны

    // Вершины куба (позиция + нормаль)
    GLfloat vertices[] = {
        // Передняя грань
        -0.5f, -0.5f,  0.5f,  0.0f,  0.0f,  1.0f,
        0.5f, -0.5f,  0.5f,  0.0f,  0.0f,  1.0f,
        0.5f,  0.5f,  0.5f,  0.0f,  0.0f,  1.0f,
        -0.5f,  0.5f,  0.5f,  0.0f,  0.0f,  1.0f,

        // Задняя грань
        -0.5f, -0.5f, -0.5f,  0.0f,  0.0f, -1.0f,
        0.5f, -0.5f, -0.5f,  0.0f,  0.0f, -1.0f,
        0.5f,  0.5f, -0.5f,  0.0f,  0.0f, -1.0f,
        -0.5f,  0.5f, -0.5f,  0.0f,  0.0f, -1.0f,

        // Левая грань
        -0.5f, -0.5f, -0.5f, -1.0f,  0.0f,  0.0f,
        -0.5f, -0.5f,  0.5f, -1.0f,  0.0f,  0.0f,
        -0.5f,  0.5f,  0.5f, -1.0f,  0.0f,  0.0f,
        -0.5f,  0.5f, -0.5f, -1.0f,  0.0f,  0.0f,

        // Правая грань
        0.5f, -0.5f, -0.5f,  1.0f,  0.0f,  0.0f,
        0.5f, -0.5f,  0.5f,  1.0f,  0.0f,  0.0f,
        0.5f,  0.5f,  0.5f,  1.0f,  0.0f,  0.0f,
        0.5f,  0.5f, -0.5f,  1.0f,  0.0f,  0.0f,

        // Нижняя грань
        -0.5f, -0.5f, -0.5f,  0.0f, -1.0f,  0.0f,
        0.5f, -0.5f, -0.5f,  0.0f, -1.0f,  0.0f,
        0.5f, -0.5f,  0.5f,  0.0f, -1.0f,  0.0f,
        -0.5f, -0.5f,  0.5f,  0.0f, -1.0f,  0.0f,

        // Верхняя грань
        -0.5f,  0.5f, -0.5f,  0.0f,  1.0f,  0.0f,
        0.5f,  0.5f, -0.5f,  0.0f,  1.0f,  0.0f,
        0.5f,  0.5f,  0.5f,  0.0f,  1.0f,  0.0f,
        -0.5f,  0.5f,  0.5f,  0.0f,  1.0f,  0.0f
    };

    GLuint indices[] = {
        0, 1, 2, 2, 3, 0,       // Передняя грань
        4, 5, 6, 6, 7, 4,       // Задняя грань
        8, 9, 10, 10, 11, 8,    // Левая грань
        12, 13, 14, 14, 15, 12, // Правая грань
        16, 17, 18, 18, 19, 16, // Нижняя грань
        20, 21, 22, 22, 23, 20  // Верхняя грань
    };

    QOpenGLBuffer vbo(QOpenGLBuffer::VertexBuffer);
    QOpenGLBuffer ebo(QOpenGLBuffer::IndexBuffer);
    QOpenGLVertexArrayObject vao;

    vao.create();
    vao.bind();

    vbo.create();
    vbo.bind();
    vbo.allocate(vertices, sizeof(vertices));

    ebo.create();
    ebo.bind();
    ebo.allocate(indices, sizeof(indices));

    // Установка атрибутов
    program->enableAttributeArray(0);
    program->setAttributeBuffer(0, GL_FLOAT, 0, 3, 6 * sizeof(GLfloat));

    program->enableAttributeArray(1);
    program->setAttributeBuffer(1, GL_FLOAT, 3 * sizeof(GLfloat), 3, 6 * sizeof(GLfloat));

    glDrawElements(GL_TRIANGLES, 36, GL_UNSIGNED_INT, 0);

    vao.release();
    vbo.destroy();
    ebo.destroy();
}

void OpenGLWidget::drawSphere(const QVector3D &position, const QVector3D &color,
                              float diffuse, float specular, float shininess, float alpha)
{
    model.setToIdentity();
    model.translate(position);
    model.scale(sphereRadius); // Применяем масштаб для изменения размера сферы

    program->setUniformValue("model", model);
    program->setUniformValue("objectColor", color);
    program->setUniformValue("diffuseStrength", diffuse);
    program->setUniformValue("specularStrength", specular);
    program->setUniformValue("shininess", shininess);
    program->setUniformValue("alpha", alpha);

    // Генерация вершин сферы
    const int sectors = 36;
    const int stacks = 18;
    const float PI = 3.14159265358979323846f;

    std::vector<GLfloat> vertices;
    std::vector<GLuint> indices;

    float x, y, z, xy;
    float nx, ny, nz, lengthInv = 1.0f / sphereRadius;
    float s, t;

    float sectorStep = 2 * PI / sectors;
    float stackStep = PI / stacks;
    float sectorAngle, stackAngle;

    for(int i = 0; i <= stacks; ++i) {
        stackAngle = PI / 2 - i * stackStep;
        xy = sphereRadius * cosf(stackAngle);
        z = sphereRadius * sinf(stackAngle);

        for(int j = 0; j <= sectors; ++j) {
            sectorAngle = j * sectorStep;

            x = xy * cosf(sectorAngle);
            y = xy * sinf(sectorAngle);

            nx = x * lengthInv;
            ny = y * lengthInv;
            nz = z * lengthInv;

            vertices.push_back(x);
            vertices.push_back(y);
            vertices.push_back(z);
            vertices.push_back(nx);
            vertices.push_back(ny);
            vertices.push_back(nz);
        }
    }

    // Генерация индексов
    int k1, k2;
    for(int i = 0; i < stacks; ++i) {
        k1 = i * (sectors + 1);
        k2 = k1 + sectors + 1;

        for(int j = 0; j < sectors; ++j, ++k1, ++k2) {
            if(i != 0) {
                indices.push_back(k1);
                indices.push_back(k2);
                indices.push_back(k1 + 1);
            }

            if(i != (stacks-1)) {
                indices.push_back(k1 + 1);
                indices.push_back(k2);
                indices.push_back(k2 + 1);
            }
        }
    }

    QOpenGLBuffer vbo(QOpenGLBuffer::VertexBuffer);
    QOpenGLBuffer ebo(QOpenGLBuffer::IndexBuffer);
    QOpenGLVertexArrayObject vao;

    vao.create();
    vao.bind();

    vbo.create();
    vbo.bind();
    vbo.allocate(vertices.data(), vertices.size() * sizeof(GLfloat));

    ebo.create();
    ebo.bind();
    ebo.allocate(indices.data(), indices.size() * sizeof(GLuint));

    program->enableAttributeArray(0);
    program->setAttributeBuffer(0, GL_FLOAT, 0, 3, 6 * sizeof(GLfloat));

    program->enableAttributeArray(1);
    program->setAttributeBuffer(1, GL_FLOAT, 3 * sizeof(GLfloat), 3, 6 * sizeof(GLfloat));

    glDrawElements(GL_TRIANGLES, indices.size(), GL_UNSIGNED_INT, 0);

    vao.release();
    vbo.destroy();
    ebo.destroy();
}

// Функции для управления сферой
void OpenGLWidget::changeSphereSize(float delta)
{
    sphereRadius += delta;
    if (sphereRadius < 0.1f) sphereRadius = 0.1f;
    update();
}

void OpenGLWidget::changeSphereTransparency(float delta)
{
    // Эта функция теперь меняет window-level прозрачность (старое поведение)
    // Оставлена для обратной совместимости
    sphereAlpha += delta;
    if (sphereAlpha < 0.0f) sphereAlpha = 0.0f;
    if (sphereAlpha > 1.0f) sphereAlpha = 1.0f;
    update();
}

void OpenGLWidget::changeSphereAlpha(float delta)
{
    // Новая функция для изменения альфа-прозрачности (прозрачность внутри сцены)
    sphereAlpha += delta;
    if (sphereAlpha < 0.0f) sphereAlpha = 0.0f;
    if (sphereAlpha > 1.0f) sphereAlpha = 1.0f;
    update();
}

void OpenGLWidget::changeSphereReflection(float delta)
{
    sphereSpecular += delta;
    if (sphereSpecular < 0.0f) sphereSpecular = 0.0f;
    if (sphereSpecular > 1.0f) sphereSpecular = 1.0f;
    update();
}

// Функции для управления освещением
void OpenGLWidget::toggleLightRotation()
{
    isLightRotating = !isLightRotating;
    update();
}

void OpenGLWidget::setLightRotationSpeed(float speed)
{
    lightRotationSpeed = speed;
    update();
}

MainWindow::MainWindow(QWidget *parent)
    : QMainWindow(parent)
{
    setWindowTitle("3D Objects with Sphere and Rotating Light");
    setCentralWidget(new OpenGLWidget(this));
}

void OpenGLWidget::timerEvent(QTimerEvent *event)
{
    bool cameraMoved = false;
    float rotationSpeed = 2.0f;

    if (keys[Qt::Key_A]) {
        rotationAngle_x -= rotationSpeed;
        cameraMoved = true;
    }
    if (keys[Qt::Key_D]) {
        rotationAngle_x += rotationSpeed;
        cameraMoved = true;
    }
    if (keys[Qt::Key_W]) {
        rotationAngle_y += rotationSpeed;
        cameraMoved = true;
    }
    if (keys[Qt::Key_S]) {
        rotationAngle_y -= rotationSpeed;
        cameraMoved = true;
    }

    // Ограничиваем углы
    if (rotationAngle_x > 360.0f) rotationAngle_x -= 360.0f;
    if (rotationAngle_x < 0.0f) rotationAngle_x += 360.0f;
    if (rotationAngle_y > 360.0f) rotationAngle_y -= 360.0f;
    if (rotationAngle_y < 0.0f) rotationAngle_y += 360.0f;

    if (cameraMoved) {
        float radius = 7.0f;
        float camX = sin(qDegreesToRadians(rotationAngle_x)) * cos(qDegreesToRadians(rotationAngle_y)) * radius;
        float camY = sin(qDegreesToRadians(rotationAngle_y)) * radius;
        float camZ = cos(qDegreesToRadians(rotationAngle_x)) * cos(qDegreesToRadians(rotationAngle_y)) * radius;

        cameraPosition = QVector3D(camX, camY, camZ);
        updateCamera();
        update();
    }

    // Обновляем сцену если освещение вращается
    if (isLightRotating) {
        update();
    }
}
