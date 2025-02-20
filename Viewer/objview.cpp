#include "objview.h"

#include <GL/glu.h>  // Для gluPerspective

#include <QWheelEvent>

#include "objcontroller.h"

namespace s21 {

ObjView::ObjView(ObjController *ctrl, QWidget *parent)
    : QOpenGLWidget(parent),
      controller(ctrl)  // Используем переданный контроллер
{}

ObjView::~ObjView() {}

/**
 * @brief Инициализация OpenGL.
 */
void ObjView::initializeGL() {
  glEnable(GL_DEPTH_TEST);
  glMatrixMode(GL_PROJECTION);
  glLoadIdentity();
  setProjection();
}

/**
 * @brief Отрисовка OpenGL.
 */
void ObjView::paintGL() {
  glClearColor(backgroundColor.redF(), backgroundColor.greenF(),
               backgroundColor.blueF(), backgroundColor.alphaF());
  glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
  setupModelView();
  setProjection();
  drawPrimitive();
  drawVertexMarkers();
}

/**
 * @brief Установка матрицы модели-вью.
 */
void ObjView::setupModelView() {
  glMatrixMode(GL_MODELVIEW);
  glLoadIdentity();
  glScaled(0.5, 0.5, 0.5);
}

/**
 * @brief Отрисовка примитивов модели.
 */
void ObjView::drawPrimitive() {
  const QVector<double> &vertices = controller->getVertices();
  const QVector<unsigned int> &indices = controller->getIndices();
  if (vertices.isEmpty() || indices.isEmpty()) {
    return;
  }
  glLineWidth(edgeThickness);  // Устанавливаем толщину линии
  GLenum glMode;
  switch (currentMode) {
    case Lines:
      glMode = GL_LINES;
      break;
    case Triangles:
      glMode = GL_TRIANGLES;
      break;
    case Points:
      glMode = GL_POINTS;
      break;
    default:
      glMode = GL_LINES;
      break;
  }
  if (line_mode == Dashed) {
    glEnable(GL_LINE_STIPPLE);
    glLineStipple(1, 0x00FF);  // Пунктирная линия
  } else {
    glDisable(GL_LINE_STIPPLE);
  }
  if (!indices.isEmpty() && !vertices.isEmpty()) {
    glColor3f(edgeColor.redF(), edgeColor.greenF(), edgeColor.blueF());
    glEnableClientState(GL_VERTEX_ARRAY);
    glVertexPointer(3, GL_DOUBLE, 0, vertices.data());
    glDrawElements(glMode, indices.size(), GL_UNSIGNED_INT, indices.data());
    glDisableClientState(GL_VERTEX_ARRAY);
  }
  if (line_mode == Dashed) {
    glDisable(GL_LINE_STIPPLE);
  }
}

/**
 * @brief Отрисовка маркеров вершин.
 */
void ObjView::drawVertexMarkers() {
  if (vertexMode == Empty) {
    return;
  }

  glPointSize(verticleSize);
  const QVector<double> &vertices = controller->getVertices();
  if (vertices.isEmpty()) {
    return;  // Если нет вершин, выход
  }
  glEnableClientState(GL_VERTEX_ARRAY);
  glVertexPointer(3, GL_DOUBLE, 0, vertices.data());
  glColor3f(verticleColor.redF(), verticleColor.greenF(),
            verticleColor.blueF());  // Применяем цвет к вершинкам

  if (vertexMode == Circle) {
    glEnable(GL_POINT_SMOOTH);  // Включаем сглаживание точек
    glDrawArrays(GL_POINTS, 0, vertices.size() / 3);  // Рисуем все точки
    glDisable(GL_POINT_SMOOTH);  // Отключаем сглаживание после рисования
  } else if (vertexMode == Square) {
    glDrawArrays(GL_POINTS, 0, vertices.size() / 3);  // Рисуем все точки
  }
  glDisableClientState(GL_VERTEX_ARRAY);
}

/**
 * @brief Установка проекции.
 */
void ObjView::setProjection() {
  glMatrixMode(GL_PROJECTION);
  glLoadIdentity();
  double aspectRatio = double(width()) / height();
  if (projection_mode == Parallel) {
    glOrtho(-1.0 * aspectRatio, 1.0 * aspectRatio, -1.0, 1.0, -100.0, 100.0);
  } else if (projection_mode == Central) {
    gluPerspective(45.0, 1.0 * aspectRatio, 0.1, 100.0);
    glTranslated(0.0, 0.0, -2.5);
  }
}

void ObjView::setDefault() {
  projection_mode = Parallel;
  line_mode = Solid;
  currentMode = Lines;
  vertexMode = Empty;
  edgeThickness = 1;
  verticleSize = 1;
  backgroundColor = QColor(200, 200, 200);
  edgeColor = QColor(0, 0, 255);
  verticleColor = QColor(255, 0, 0);
  update();
}

void ObjView::setVertexMode(const QString &modeStr) {
  if (modeStr == "Empty") {
    vertexMode = Empty;
  } else if (modeStr == "Circle") {
    vertexMode = Circle;
  } else if (modeStr == "Square") {
    vertexMode = Square;
  } else {
    return;
  }
  update();
}

void ObjView::setPrimitiveMode(const QString &modeStr) {
  if (modeStr == "Lines") {
    currentMode = Lines;
  } else if (modeStr == "Triangles") {
    currentMode = Triangles;
  } else if (modeStr == "Points") {
    currentMode = Points;
  } else {
    return;
  }
  update();
}

void ObjView::setProjectionMode(const QString &modeStr) {
  if (modeStr == "Central") {
    projection_mode = Central;
  } else if (modeStr == "Parallel") {
    projection_mode = Parallel;
  } else {
    return;
  }
  update();
}

void ObjView::setLineMode(const QString &modeStr) {
  if (modeStr == "Solid") {
    line_mode = Solid;  // Устанавливаем сплошную линию
  } else if (modeStr == "Dashed") {
    line_mode = Dashed;  // Устанавливаем пунктирную линию
  } else {
    return;
  }
  update();
}

void ObjView::setLineThickness(int thickness) {
  edgeThickness = thickness;
  update();
}

void ObjView::setVertexSize(int size) {
  verticleSize = size;  // Устанавливаем новый размер вершин
  glPointSize(verticleSize);  // Устанавливаем размер точки в OpenGL
}

void ObjView::setEdgeColor(const QColor &color) {
  edgeColor = color;  // Устанавливаем новый цвет для линий
  update();
}
void ObjView::setVertexColor(const QColor &color) {
  verticleColor = color;  // Устанавливаем новый цвет для вершин
  update();
}

void ObjView::setBackgroundColor(const QColor &color) {
  backgroundColor = color;  // Устанавливаем новый цвет для фона
  update();
}

//----------
QString ObjView::getProjectionMode() const {
  return projection_mode == Central ? "Central" : "Parallel";
}

QString ObjView::getLineMode() const {
  return line_mode == Dashed ? "Dashed" : "Solid";
}

int ObjView::getLineThickness() const { return edgeThickness; }

QColor ObjView::getEdgeColor() const { return edgeColor; }

QString ObjView::getVertexMode() const {
  return vertexMode == Circle ? "Circle"
                              : (vertexMode == Square ? "Square" : "Empty");
}

int ObjView::getVertexSize() const { return verticleSize; }

QColor ObjView::getVertexColor() const { return verticleColor; }

QColor ObjView::getBackgroundColor() const { return backgroundColor; }

QString ObjView::getPrimitiveMode() const {
  return currentMode == Lines
             ? "Lines"
             : (currentMode == Triangles ? "Triangles" : "Points");
}
}  // namespace s21