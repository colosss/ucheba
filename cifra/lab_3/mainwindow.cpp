#include "mainwindow.h"
#include <QOpenGLShader>
#include <QOpenGLTexture>
#include <QKeyEvent>
#include <QTimer>
#include <cmath>

OpenGLWidget::OpenGLWidget(QWidget *parent)
    : QOpenGLWidget(parent), program(nullptr)
{
    QSurfaceFormat format;
    format.setVersion(3, 3);
    format.setProfile(QSurfaceFormat::CoreProfile);
    setFormat(format);
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

    setupShaders();

    // Настройка камеры
    view.lookAt(QVector3D(5.0f, 5.0f, 5.0f),
                QVector3D(0.0f, 0.0f, 0.0f),
                QVector3D(0.0f, 1.0f, 0.0f));
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
        "    FragColor = vec4(result, 1.0);\n"
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

    // Установка параметров освещения
    program->setUniformValue("lightPos", QVector3D(2.0f, 3.0f, 5.0f));
    program->setUniformValue("lightColor", QVector3D(1.0f, 1.0f, 1.0f));

    program->setUniformValue("view", view);
    program->setUniformValue("projection", projection);

    // Рисуем несколько объектов с разными свойствами
    drawCube(QVector3D(-2.0f, 0.0f, 0.0f),
             QVector3D(0.0f, 1.0f, 0.0f), //
             0.8f,  // Сильное диффузное отражение
             0.2f,  // Слабое зеркальное
             32.0f); // Низкая блескость

    drawCube(QVector3D(0.0f, 0.0f, 0.0f),
             QVector3D(1.0f, 1.0f, 0.0f), //
             1.0f,  // Очень сильное диффузное
             1.0f,  // Очень сильное зеркальное
             0.1f); // очень низкая блескость
    drawCube(QVector3D(2.0f, 0.0f, 0.0f),
             QVector3D(1.0f, 0.0f, 0.0f), //
             0.5f,  // Среднее диффузное
             0.5f,  // Среднее зеркальное
             64.0f); // Средняя блескость

    drawCube(QVector3D(2.0f, 1.0f, 0.0f),
             QVector3D(0.0f, 0.0f, 0.5f), //
             0.9f,  // Очень сильное диффузное
             0.1f,  // Очень слабое зеркальное
             16.0f); // Очень низкая блескость

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

MainWindow::MainWindow(QWidget *parent)
    : QMainWindow(parent)
{
    setWindowTitle("3D Objects with Different Material Properties");
    setCentralWidget(new OpenGLWidget(this));
}
