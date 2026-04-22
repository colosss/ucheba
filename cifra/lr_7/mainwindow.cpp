#include "mainwindow.h"
#include <QOpenGLShader>
#include <QOpenGLTexture>
#include <QKeyEvent>
#include <QTimer>
#include <cmath>
#include <stdio.h>
#include <QDebug>

using namespace std;

bool keys[256];

// ----------------- Конструктор/деструктор -----------------
OpenGLWidget::OpenGLWidget(QWidget *parent)
    : QOpenGLWidget(parent),
      program(nullptr),
      depthProgram(nullptr),
      rotationAngle(0.0f),
      rotationAngle_x(45.0f),
      rotationAngle_y(25.0f),
      sphereRadius(1.0f),
      sphereAlpha(1.0f),
      sphereDiffuse(0.7f),
      sphereSpecular(0.5f),
      sphereShininess(32.0f),
      sphereColor(0.2f, 0.4f, 0.8f),
      spherePosition(0.0f, 1.0f, 0.0f),
      lightRotationAngle(0.0f),
      lightRotationSpeed(1.0f),
      isLightRotating(false),
      lightOrbitRadius(5.0f),
      showTorus(true),
      torusInnerRadius(0.6f),
      torusOuterRadius(1.2f),
      torusSegments(48),
      torusSides(24),
      showNurbs(true),
      nurbsCtrlU(4),
      nurbsCtrlV(4),
      fogEnabled(true),
      fogColor(0.6f, 0.6f, 0.65f),
      fogDensity(0.06f),
      depthMapFBO(0),
      depthMap(0),
      shadowBias(0.005f),
      shadowIntensity(0.6f)
{
    startTimer(16);
    QSurfaceFormat format;
    format.setVersion(3, 3);
    format.setProfile(QSurfaceFormat::CoreProfile);
    setFormat(format);

    memset(keys, 0, sizeof(keys));
    setFocusPolicy(Qt::StrongFocus);

    // Заполняем контрольные точки NURBS
    nurbsControlPoints.clear();
    nurbsWeights.clear();
    for (int i = 0; i < nurbsCtrlU; ++i) {
        for (int j = 0; j < nurbsCtrlV; ++j) {
            float x = (i - (nurbsCtrlU-1)/2.0f) * 1.5f;
            float z = (j - (nurbsCtrlV-1)/2.0f) * 1.5f;
            float y = sinf(i*0.8f) * cosf(j*0.6f) * 0.6f;
            nurbsControlPoints.push_back(QVector3D(x, y, z));
            nurbsWeights.push_back(1.0f);
        }
    }
}

OpenGLWidget::~OpenGLWidget()
{
    makeCurrent();
    if (program) delete program;
    if (depthProgram) delete depthProgram;
    if (depthMap) glDeleteTextures(1, &depthMap);
    if (depthMapFBO) glDeleteFramebuffers(1, &depthMapFBO);
    doneCurrent();
}

// ----------------- Шейдеры -----------------
void OpenGLWidget::setupShaders()
{
    // Основной шейдер
    program = new QOpenGLShaderProgram(this);

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
        "uniform vec3 cameraPos;\n"
        "uniform bool fogEnabled;\n"
        "uniform vec3 fogColor;\n"
        "uniform float fogDensity;\n"
        "uniform sampler2D shadowMap;\n"
        "uniform mat4 lightSpaceMatrix;\n"
        "out vec4 FragColor;\n"
        "\n"
        "float calculateShadow(vec3 fragPos, vec3 normal, vec3 lightDir) {\n"
        "    vec4 fragPosLightSpace = lightSpaceMatrix * vec4(fragPos, 1.0);\n"
        "    vec3 projCoords = fragPosLightSpace.xyz / fragPosLightSpace.w;\n"
        "    projCoords = projCoords * 0.5 + 0.5;\n"
        "    if (projCoords.x < 0.0 || projCoords.x > 1.0 || projCoords.y < 0.0 || projCoords.y > 1.0) return 0.0;\n"
        "    float bias = max(0.005 * (1.0 - dot(normal, lightDir)), 0.0005);\n"
        "    float shadow = 0.0;\n"
        "    vec2 texelSize = 1.0 / textureSize(shadowMap, 0);\n"
        "    for(int x = -1; x <= 1; ++x) {\n"
        "        for(int y = -1; y <= 1; ++y) {\n"
        "            float pcfDepth = texture(shadowMap, projCoords.xy + vec2(x,y) * texelSize).r;\n"
        "            shadow += (projCoords.z - bias > pcfDepth) ? 1.0 : 0.0;\n"
        "        }\n"
        "    }\n"
        "    shadow /= 9.0;\n"
        "    return shadow;\n"
        "}\n"
        "\n"
        "void main() {\n"
        "    float ambientStrength = 0.1;\n"
        "    vec3 ambient = ambientStrength * lightColor;\n"
        "    vec3 norm = normalize(Normal);\n"
        "    vec3 lightDir = normalize(lightPos - FragPos);\n"
        "    float diff = max(dot(norm, lightDir), 0.0);\n"
        "    vec3 diffuse = diffuseStrength * diff * lightColor;\n"
        "    vec3 viewDir = normalize(cameraPos - FragPos);\n"
        "    vec3 reflectDir = reflect(-lightDir, norm);\n"
        "    float spec = pow(max(dot(viewDir, reflectDir), 0.0), shininess);\n"
        "    vec3 specular = specularStrength * spec * lightColor;\n"
        "    vec3 result = (ambient + diffuse + specular) * objectColor;\n"
        "    float shadow = calculateShadow(FragPos, norm, lightDir);\n"
        "    result = mix(result, result * (1.0 - /* placeholder replaced below */ , 0.0) , 0.0);\n"
        "}\n";

    // Мы не можем легко комбинировать строку C++ и GLSL expression inline -
    // поэтому делаем build вручную:
    QString frag = R"(
        #version 330 core
        in vec3 FragPos;
        in vec3 Normal;
        uniform vec3 objectColor;
        uniform vec3 lightPos;
        uniform vec3 lightColor;
        uniform float diffuseStrength;
        uniform float specularStrength;
        uniform float shininess;
        uniform float alpha;
        uniform vec3 cameraPos;
        uniform bool fogEnabled;
        uniform vec3 fogColor;
        uniform float fogDensity;
        uniform sampler2D shadowMap;
        uniform mat4 lightSpaceMatrix;
        out vec4 FragColor;

        float calculateShadow(vec3 fragPos, vec3 normal, vec3 lightDir) {
            vec4 fragPosLightSpace = lightSpaceMatrix * vec4(fragPos, 1.0);
            vec3 projCoords = fragPosLightSpace.xyz / fragPosLightSpace.w;
            projCoords = projCoords * 0.5 + 0.5;
            if (projCoords.x < 0.0 || projCoords.x > 1.0 || projCoords.y < 0.0 || projCoords.y > 1.0) return 0.0;
            float bias = max(0.005 * (1.0 - dot(normal, lightDir)), 0.0005);
            float shadow = 0.0;
            vec2 texelSize = 1.0 / textureSize(shadowMap, 0);
            for(int x = -1; x <= 1; ++x) {
                for(int y = -1; y <= 1; ++y) {
                    float pcfDepth = texture(shadowMap, projCoords.xy + vec2(x,y) * texelSize).r;
                    shadow += (projCoords.z - bias > pcfDepth) ? 1.0 : 0.0;
                }
            }
            shadow /= 9.0;
            return shadow;
        }

        void main() {
            float ambientStrength = 0.1;
            vec3 ambient = ambientStrength * lightColor;
            vec3 norm = normalize(Normal);
            vec3 lightDir = normalize(lightPos - FragPos);
            float diff = max(dot(norm, lightDir), 0.0);
            vec3 diffuse = diffuseStrength * diff * lightColor;
            vec3 viewDir = normalize(cameraPos - FragPos);
            vec3 reflectDir = reflect(-lightDir, norm);
            float spec = pow(max(dot(viewDir, reflectDir), 0.0), shininess);
            vec3 specular = specularStrength * spec * lightColor;
            vec3 result = (ambient + diffuse + specular) * objectColor;
            float shadow = calculateShadow(FragPos, norm, lightDir);
            result = mix(result, result * (1.0 - )" + QString::number(shadowIntensity) + R"(), shadow);
            vec4 color = vec4(result, alpha);
            if (fogEnabled) {
                float dist = length(cameraPos - FragPos);
                float fogFactor = 1.0 - exp(-fogDensity * dist);
                fogFactor = clamp(fogFactor, 0.0, 1.0);
                vec3 col = mix(result, fogColor, fogFactor);
                FragColor = vec4(col, alpha);
            } else {
                FragColor = color;
            }
        }
    )";

    program->addShaderFromSourceCode(QOpenGLShader::Vertex, vshader);
    program->addShaderFromSourceCode(QOpenGLShader::Fragment, frag.toUtf8().constData());
    program->link();

    // depth shader (vertex only)
    const char *depthV =
        "#version 330 core\n"
        "layout(location = 0) in vec3 position;\n"
        "uniform mat4 model;\n"
        "uniform mat4 lightSpaceMatrix;\n"
        "void main() {\n"
        "    gl_Position = lightSpaceMatrix * model * vec4(position, 1.0);\n"
        "}\n";

    const char *depthF =
        "#version 330 core\n"
        "void main() { }\n";

    depthProgram = new QOpenGLShaderProgram(this);
    depthProgram->addShaderFromSourceCode(QOpenGLShader::Vertex, depthV);
    depthProgram->addShaderFromSourceCode(QOpenGLShader::Fragment, depthF);
    depthProgram->link();
}

void OpenGLWidget::initializeGL()
{
    initializeOpenGLFunctions();
    glClearColor(0.1f, 0.1f, 0.1f, 1.0f);
    glEnable(GL_DEPTH_TEST);
    glEnable(GL_BLEND);
    glBlendFunc(GL_SRC_ALPHA, GL_ONE_MINUS_SRC_ALPHA);

    setupShaders();

    // Камера
    cameraPosition = QVector3D(5.0f, 5.0f, 5.0f);
    cameraTarget = QVector3D(0.0f, 0.0f, 0.0f);
    cameraUp = QVector3D(0.0f, 1.0f, 0.0f);
    updateCamera();

    // Создаём depth FBO и текстуру
    glGenFramebuffers(1, &depthMapFBO);
    glGenTextures(1, &depthMap);
    glBindTexture(GL_TEXTURE_2D, depthMap);
    glTexImage2D(GL_TEXTURE_2D, 0, GL_DEPTH_COMPONENT, SHADOW_WIDTH, SHADOW_HEIGHT, 0,
                 GL_DEPTH_COMPONENT, GL_FLOAT, nullptr);
    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_NEAREST);
    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_NEAREST);
    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_S, GL_CLAMP_TO_BORDER);
    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_T, GL_CLAMP_TO_BORDER);
    float borderColor[] = {1.0f,1.0f,1.0f,1.0f};
    glTexParameterfv(GL_TEXTURE_2D, GL_TEXTURE_BORDER_COLOR, borderColor);

    glBindFramebuffer(GL_FRAMEBUFFER, depthMapFBO);
    glFramebufferTexture2D(GL_FRAMEBUFFER, GL_DEPTH_ATTACHMENT, GL_TEXTURE_2D, depthMap, 0);
    glDrawBuffer(GL_NONE);
    glReadBuffer(GL_NONE);
    if (glCheckFramebufferStatus(GL_FRAMEBUFFER) != GL_FRAMEBUFFER_COMPLETE) {
        qDebug() << "Depth framebuffer not complete!";
    }
    glBindFramebuffer(GL_FRAMEBUFFER, 0);
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
    switch (event->key()) {
    case Qt::Key_Space: toggleLightRotation(); break;
    case Qt::Key_Plus: changeSphereSize(0.1f); break;
    case Qt::Key_Minus: changeSphereSize(-0.1f); break;
    case Qt::Key_1: changeSphereTransparency(0.1f); break;
    case Qt::Key_2: changeSphereTransparency(-0.1f); break;
    case Qt::Key_3: changeSphereReflection(0.1f); break;
    case Qt::Key_4: changeSphereReflection(-0.1f); break;
    case Qt::Key_5: changeSphereAlpha(0.1f); break;
    case Qt::Key_6: changeSphereAlpha(-0.1f); break;
    case Qt::Key_F: fogEnabled = !fogEnabled; break;
    case Qt::Key_T: showTorus = !showTorus; break;
    case Qt::Key_N: showNurbs = !showNurbs; break;
    }
    update();
}

void OpenGLWidget::keyReleaseEvent(QKeyEvent *event)
{
    if (event->key() >= 0 && event->key() < 256) keys[event->key()] = false;
}

void OpenGLWidget::resizeGL(int w, int h)
{
    glViewport(0, 0, w, h);
    projection.setToIdentity();
    projection.perspective(45.0f, float(w) / float(h ? h : 1), 0.1f, 100.0f);
}

// ----------------- paintGL: depth pass + render pass -----------------
void OpenGLWidget::paintGL()
{
    // обновление света
    if (isLightRotating) {
        lightRotationAngle += lightRotationSpeed;
        if (lightRotationAngle >= 360.0f) lightRotationAngle -= 360.0f;
    }
    QVector3D lightPos;
    lightPos.setX(lightOrbitRadius * sin(qDegreesToRadians(lightRotationAngle)));
    lightPos.setY(3.0f);
    lightPos.setZ(lightOrbitRadius * cos(qDegreesToRadians(lightRotationAngle)));

    // light space matrix (ортографическая проекция для теней)
    QMatrix4x4 lightProjection;
    float near_plane = 1.0f, far_plane = 30.0f;
    float orthoSize = 10.0f;
    lightProjection.ortho(-orthoSize, orthoSize, -orthoSize, orthoSize, near_plane, far_plane);
    QMatrix4x4 lightView;
    lightView.setToIdentity();
    lightView.lookAt(lightPos, QVector3D(0.0f,0.0f,0.0f), QVector3D(0.0f,1.0f,0.0f));
    lightSpaceMatrix = lightProjection * lightView;

    // 1) DEPTH PASS
    glViewport(0, 0, SHADOW_WIDTH, SHADOW_HEIGHT);
    glBindFramebuffer(GL_FRAMEBUFFER, depthMapFBO);
    glClear(GL_DEPTH_BUFFER_BIT);

    // depthProgram рендерит только позиции (uniform model + lightSpaceMatrix)
    depthProgram->bind();
    depthProgram->setUniformValue("lightSpaceMatrix", lightSpaceMatrix);

    // отрисуем сцену в depth map (передаём depthProgram)
    drawSphere(QVector3D(2.0f, 0.8f, 0.0f), sphereColor, sphereDiffuse, sphereSpecular, sphereShininess, sphereAlpha, depthProgram);
    drawSphere(QVector3D(-2.0f, 0.8f, 0.0f), sphereColor, sphereDiffuse, sphereSpecular, sphereShininess, sphereAlpha, depthProgram);
    if (showTorus) drawTorus(QVector3D(-2.0f, 0.8f, 0.0f), QVector3D(0.8f,0.3f,0.2f), torusInnerRadius, torusOuterRadius, torusSegments, torusSides, 0,0,0,1.0f, depthProgram);
    if (showNurbs) drawNurbsSurface(QMatrix4x4(), nurbsControlPoints, nurbsWeights, 3,3,24,24, QVector3D(0.3f,0.8f,0.3f),0,0,0,1.0f, depthProgram);

    depthProgram->release();
    glBindFramebuffer(GL_FRAMEBUFFER, 0);

    // 2) RENDER PASS
    glViewport(0, 0, width(), height());
    glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);

    program->bind();
    program->setUniformValue("lightPos", lightPos);
    program->setUniformValue("lightColor", QVector3D(1.0f, 1.0f, 1.0f));
    program->setUniformValue("view", view);
    program->setUniformValue("projection", projection);
    program->setUniformValue("cameraPos", cameraPosition);
    program->setUniformValue("fogEnabled", fogEnabled);
    program->setUniformValue("fogColor", fogColor);
    program->setUniformValue("fogDensity", fogDensity);
    program->setUniformValue("lightSpaceMatrix", lightSpaceMatrix);
    program->setUniformValue("shadowMap", 1); // texture unit 1

    glActiveTexture(GL_TEXTURE1);
    glBindTexture(GL_TEXTURE_2D, depthMap);

    // отрисуем сцену основным шейдером
    drawSphere(QVector3D(2.0f, 0.8f, 0.0f), sphereColor, sphereDiffuse, sphereSpecular, sphereShininess, sphereAlpha);
    drawSphere(QVector3D(-2.0f, 0.8f, 0.0f), sphereColor, sphereDiffuse, sphereSpecular, sphereShininess, sphereAlpha);
    if (showTorus) drawTorus(QVector3D(-2.0f, 0.8f, 0.0f), QVector3D(0.8f,0.3f,0.2f), torusInnerRadius, torusOuterRadius, torusSegments, torusSides, 0.7f,0.3f,16.0f,1.0f);
    if (showNurbs) drawNurbsSurface(QMatrix4x4(), nurbsControlPoints, nurbsWeights, 3,3,24,24, QVector3D(0.3f,0.8f,0.3f),0.6f,0.3f,8.0f,1.0f);

    program->release();
}

// ----------------- Куб -----------------
void OpenGLWidget::drawCube(const QVector3D &position, const QVector3D &color,
                            float diffuse, float specular, float shininess,
                            QOpenGLShaderProgram *prog)
{
    QOpenGLShaderProgram *p = prog ? prog : program;

    model.setToIdentity();
    model.translate(position);

    p->bind();
    p->setUniformValue("model", model);
    p->setUniformValue("objectColor", color);
    p->setUniformValue("diffuseStrength", diffuse);
    p->setUniformValue("specularStrength", specular);
    p->setUniformValue("shininess", shininess);
    p->setUniformValue("alpha", 1.0f);

    GLfloat vertices[] = {
        // позиция + нормаль (как в исходнике)
        -0.5f, -0.5f,  0.5f,  0.0f,  0.0f,  1.0f,
         0.5f, -0.5f,  0.5f,  0.0f,  0.0f,  1.0f,
         0.5f,  0.5f,  0.5f,  0.0f,  0.0f,  1.0f,
        -0.5f,  0.5f,  0.5f,  0.0f,  0.0f,  1.0f,
        // ...
        -0.5f,  0.5f, -0.5f,  0.0f,  1.0f,  0.0f
    };
    // Для краткости: используем старый массив длиной 24 вершин _как_ в твоём коде.
    // Вставь полный массив вершин/индексов из своего проекта при необходимости.

    GLuint indices[] = {
        0,1,2,2,3,0,
        4,5,6,6,7,4,
        8,9,10,10,11,8,
        12,13,14,14,15,12,
        16,17,18,18,19,16,
        20,21,22,22,23,20
    };

    QOpenGLBuffer vbo(QOpenGLBuffer::VertexBuffer);
    QOpenGLBuffer ebo(QOpenGLBuffer::IndexBuffer);
    QOpenGLVertexArrayObject vao;

    vao.create(); vao.bind();
    vbo.create(); vbo.bind();
    vbo.allocate(vertices, sizeof(vertices));
    ebo.create(); ebo.bind();
    ebo.allocate(indices, sizeof(indices));

    p->enableAttributeArray(0);
    p->setAttributeBuffer(0, GL_FLOAT, 0, 3, 6 * sizeof(GLfloat));
    p->enableAttributeArray(1);
    p->setAttributeBuffer(1, GL_FLOAT, 3 * sizeof(GLfloat), 3, 6 * sizeof(GLfloat));

    glDrawElements(GL_TRIANGLES, 36, GL_UNSIGNED_INT, 0);

    vao.release();
    vbo.destroy();
    ebo.destroy();
    p->release();
}

// ----------------- Сфера -----------------
void OpenGLWidget::drawSphere(const QVector3D &position, const QVector3D &color,
                              float diffuse, float specular, float shininess, float alpha,
                              QOpenGLShaderProgram *prog)
{
    QOpenGLShaderProgram *p = prog ? prog : program;

    model.setToIdentity();
    model.translate(position);
    model.scale(sphereRadius);

    p->bind();
    p->setUniformValue("model", model);
    p->setUniformValue("objectColor", color);
    p->setUniformValue("diffuseStrength", diffuse);
    p->setUniformValue("specularStrength", specular);
    p->setUniformValue("shininess", shininess);
    p->setUniformValue("alpha", alpha);

    const int sectors = 36;
    const int stacks = 18;
    const float PI = 3.14159265358979323846f;

    std::vector<GLfloat> vertices;
    std::vector<GLuint> indices;

    float x, y, z, xy;
    float nx, ny, nz, lengthInv = 1.0f / sphereRadius;

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

    vao.create(); vao.bind();
    vbo.create(); vbo.bind(); vbo.allocate(vertices.data(), vertices.size() * sizeof(GLfloat));
    ebo.create(); ebo.bind(); ebo.allocate(indices.data(), indices.size() * sizeof(GLuint));

    p->enableAttributeArray(0);
    p->setAttributeBuffer(0, GL_FLOAT, 0, 3, 6 * sizeof(GLfloat));
    p->enableAttributeArray(1);
    p->setAttributeBuffer(1, GL_FLOAT, 3 * sizeof(GLfloat), 3, 6 * sizeof(GLfloat));

    glDrawElements(GL_TRIANGLES, indices.size(), GL_UNSIGNED_INT, 0);

    vao.release();
    vbo.destroy();
    ebo.destroy();
    p->release();
}

// ----------------- Тор -----------------
void OpenGLWidget::drawTorus(const QVector3D &position, const QVector3D &color,
                             float innerR, float outerR, int segments, int sides,
                             float diffuse, float specular, float shininess, float alpha,
                             QOpenGLShaderProgram *prog)
{
    QOpenGLShaderProgram *p = prog ? prog : program;

    model.setToIdentity();
    model.translate(position);

    p->bind();
    p->setUniformValue("model", model);
    p->setUniformValue("objectColor", color);
    p->setUniformValue("diffuseStrength", diffuse);
    p->setUniformValue("specularStrength", specular);
    p->setUniformValue("shininess", shininess);
    p->setUniformValue("alpha", alpha);

    std::vector<GLfloat> vertices;
    std::vector<GLuint> indices;

    const float PI = 3.14159265358979323846f;
    for (int i = 0; i <= segments; ++i) {
        float u = (float)i / (float)segments * 2.0f * PI;
        float cu = cosf(u);
        float su = sinf(u);
        for (int j = 0; j <= sides; ++j) {
            float v = (float)j / (float)sides * 2.0f * PI;
            float cv = cosf(v);
            float sv = sinf(v);
            float x = (outerR + innerR * cv) * cu;
            float y = (outerR + innerR * cv) * su;
            float z = innerR * sv;
            float nx = cv * cu;
            float ny = cv * su;
            float nz = sv;
            vertices.push_back(x);
            vertices.push_back(z);
            vertices.push_back(y);
            vertices.push_back(nx);
            vertices.push_back(ny);
            vertices.push_back(nz);
        }
    }

    for (int i = 0; i < segments; ++i) {
        for (int j = 0; j < sides; ++j) {
            int a = i * (sides + 1) + j;
            int b = (i + 1) * (sides + 1) + j;
            int c = (i + 1) * (sides + 1) + (j + 1);
            int d = i * (sides + 1) + (j + 1);
            indices.push_back(a);
            indices.push_back(b);
            indices.push_back(d);
            indices.push_back(b);
            indices.push_back(c);
            indices.push_back(d);
        }
    }

    QOpenGLBuffer vbo(QOpenGLBuffer::VertexBuffer);
    QOpenGLBuffer ebo(QOpenGLBuffer::IndexBuffer);
    QOpenGLVertexArrayObject vao;

    vao.create(); vao.bind();
    vbo.create(); vbo.bind(); vbo.allocate(vertices.data(), vertices.size() * sizeof(GLfloat));
    ebo.create(); ebo.bind(); ebo.allocate(indices.data(), indices.size() * sizeof(GLuint));

    p->enableAttributeArray(0);
    p->setAttributeBuffer(0, GL_FLOAT, 0, 3, 6 * sizeof(GLfloat));
    p->enableAttributeArray(1);
    p->setAttributeBuffer(1, GL_FLOAT, 3 * sizeof(GLfloat), 3, 6 * sizeof(GLfloat));

    glDrawElements(GL_TRIANGLES, indices.size(), GL_UNSIGNED_INT, 0);

    vao.release();
    vbo.destroy();
    ebo.destroy();
    p->release();
}

// ----------------- NURBS helper functions -----------------
static float bsplineBasis(int i, int k, float t, const std::vector<float> &knots)
{
    if (k == 0) {
        if (knots[i] <= t && t < knots[i+1]) return 1.0f;
        if (t == knots.back() && t >= knots[i] && t <= knots[i+1]) return 1.0f;
        return 0.0f;
    }
    float denom1 = knots[i+k] - knots[i];
    float denom2 = knots[i+k+1] - knots[i+1];
    float term1 = 0.0f;
    float term2 = 0.0f;
    if (denom1 > 1e-6f) term1 = (t - knots[i]) / denom1 * bsplineBasis(i, k-1, t, knots);
    if (denom2 > 1e-6f) term2 = (knots[i+k+1] - t) / denom2 * bsplineBasis(i+1, k-1, t, knots);
    return term1 + term2;
}

static std::vector<float> makeClampedKnots(int ctrlCount, int degree)
{
    int n = ctrlCount - 1;
    int m = n + degree + 1;
    std::vector<float> knots(m + 1);
    for (int i = 0; i <= m; ++i) {
        if (i <= degree) knots[i] = 0.0f;
        else if (i >= m - degree) knots[i] = 1.0f;
        else knots[i] = float(i - degree) / float(m - 2*degree);
    }
    return knots;
}

static QVector3D evalNurbsSurfacePoint(const std::vector<QVector3D> &ctrlPts, const std::vector<float> &weights,
                                       int ctrlU, int ctrlV, int degU, int degV,
                                       const std::vector<float> &knotU, const std::vector<float> &knotV,
                                       float u, float v)
{
    QVector3D numerator(0,0,0);
    float denom = 0.0f;
    for (int i = 0; i < ctrlU; ++i) {
        float Nu = bsplineBasis(i, degU, u, knotU);
        for (int j = 0; j < ctrlV; ++j) {
            float Nv = bsplineBasis(j, degV, v, knotV);
            float w = weights[i*ctrlV + j];
            float B = Nu * Nv * w;
            numerator += B * ctrlPts[i*ctrlV + j];
            denom += B;
        }
    }
    if (denom == 0.0f) return QVector3D(0,0,0);
    return numerator / denom;
}

// ----------------- NURBS surface -----------------
void OpenGLWidget::drawNurbsSurface(const QMatrix4x4 &transform,
                                    const std::vector<QVector3D> &ctrlPts,
                                    const std::vector<float> &weights,
                                    int degU, int degV,
                                    int resU, int resV,
                                    const QVector3D &color,
                                    float diffuse, float specular, float shininess, float alpha,
                                    QOpenGLShaderProgram *prog)
{
    QOpenGLShaderProgram *p = prog ? prog : program;

    int ctrlU = nurbsCtrlU;
    int ctrlV = nurbsCtrlV;
    std::vector<float> knotU = makeClampedKnots(ctrlU, degU);
    std::vector<float> knotV = makeClampedKnots(ctrlV, degV);

    model = transform;
    p->bind();
    p->setUniformValue("model", model);
    p->setUniformValue("objectColor", color);
    p->setUniformValue("diffuseStrength", diffuse);
    p->setUniformValue("specularStrength", specular);
    p->setUniformValue("shininess", shininess);
    p->setUniformValue("alpha", alpha);

    std::vector<GLfloat> vertices;
    std::vector<GLuint> indices;
    vertices.reserve((resU+1)*(resV+1)*6);

    for (int iu = 0; iu <= resU; ++iu) {
        float u = float(iu) / float(resU);
        if (u >= 1.0f) u = 1.0f;
        for (int iv = 0; iv <= resV; ++iv) {
            float v = float(iv) / float(resV);
            if (v >= 1.0f) v = 1.0f;
            QVector3D pnt = evalNurbsSurfacePoint(ctrlPts, weights, ctrlU, ctrlV, degU, degV, knotU, knotV, u, v);
            float du = 1e-3f; float dv = 1e-3f;
            float u1 = qMin(1.0f, u + du); float v1 = qMin(1.0f, v + dv);
            QVector3D pu = evalNurbsSurfacePoint(ctrlPts, weights, ctrlU, ctrlV, degU, degV, knotU, knotV, u1, v);
            QVector3D pv = evalNurbsSurfacePoint(ctrlPts, weights, ctrlU, ctrlV, degU, degV, knotU, knotV, u, v1);
            QVector3D tangentU = (pu - pnt);
            QVector3D tangentV = (pv - pnt);
            QVector3D normal = QVector3D::crossProduct(tangentU, tangentV).normalized();
            vertices.push_back(pnt.x()); vertices.push_back(pnt.y()); vertices.push_back(pnt.z());
            vertices.push_back(normal.x()); vertices.push_back(normal.y()); vertices.push_back(normal.z());
        }
    }

    for (int iu = 0; iu < resU; ++iu) {
        for (int iv = 0; iv < resV; ++iv) {
            int a = iu * (resV + 1) + iv;
            int b = (iu + 1) * (resV + 1) + iv;
            int c = (iu + 1) * (resV + 1) + (iv + 1);
            int d = iu * (resV + 1) + (iv + 1);
            indices.push_back(a); indices.push_back(b); indices.push_back(d);
            indices.push_back(b); indices.push_back(c); indices.push_back(d);
        }
    }

    QOpenGLBuffer vbo(QOpenGLBuffer::VertexBuffer);
    QOpenGLBuffer ebo(QOpenGLBuffer::IndexBuffer);
    QOpenGLVertexArrayObject vao;

    vao.create(); vao.bind();
    vbo.create(); vbo.bind(); vbo.allocate(vertices.data(), vertices.size() * sizeof(GLfloat));
    ebo.create(); ebo.bind(); ebo.allocate(indices.data(), indices.size() * sizeof(GLuint));

    p->enableAttributeArray(0);
    p->setAttributeBuffer(0, GL_FLOAT, 0, 3, 6 * sizeof(GLfloat));
    p->enableAttributeArray(1);
    p->setAttributeBuffer(1, GL_FLOAT, 3 * sizeof(GLfloat), 3, 6 * sizeof(GLfloat));

    glDrawElements(GL_TRIANGLES, indices.size(), GL_UNSIGNED_INT, 0);

    vao.release(); vbo.destroy(); ebo.destroy();
    p->release();
}

// ----------------- Управление сферой и светом -----------------
void OpenGLWidget::changeSphereSize(float delta)
{
    sphereRadius += delta;
    if (sphereRadius < 0.1f) sphereRadius = 0.1f;
    update();
}

void OpenGLWidget::changeSphereTransparency(float delta)
{
    sphereAlpha += delta;
    if (sphereAlpha < 0.0f) sphereAlpha = 0.0f;
    if (sphereAlpha > 1.0f) sphereAlpha = 1.0f;
    update();
}

void OpenGLWidget::changeSphereAlpha(float delta)
{
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

// ----------------- Таймер и камера -----------------
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

    if (keys[Qt::Key_A]) { rotationAngle_x -= rotationSpeed; cameraMoved = true; }
    if (keys[Qt::Key_D]) { rotationAngle_x += rotationSpeed; cameraMoved = true; }
    if (keys[Qt::Key_W]) { rotationAngle_y += rotationSpeed; cameraMoved = true; }
    if (keys[Qt::Key_S]) { rotationAngle_y -= rotationSpeed; cameraMoved = true; }

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

    if (isLightRotating) update();
}
