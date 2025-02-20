#ifndef OBJVIEW_H
#define OBJVIEW_H

#include <QColor>
#include <QOpenGLWidget>
#include <QString>
#include <QVector3D>
#include <QVector>

#include "objcontroller.h"

namespace s21 {

/**
 * @brief Класс представления модели в виде виджета OpenGL.
 *
 * Этот класс отображает 3D-модель с использованием OpenGL. Он предоставляет
 * методы для настройки различных аспектов визуализации, таких как режим
 * примитива, режим проекции, толщина линий и цвета.
 */
class ObjView : public QOpenGLWidget {
  Q_OBJECT

 public:
  /**
   * @brief Конструктор класса ObjView.
   *
   * @param ctrl Указатель на контроллер модели.
   * @param parent Родительский виджет.
   */
  ObjView(ObjController *ctrl, QWidget *parent = nullptr);

  /**
   * @brief Деструктор класса ObjView.
   */
  ~ObjView();

  /**
   * @brief Устанавливает значения по умолчанию.
   */
  void setDefault();

  /**
   * @brief Устанавливает режим примитива.
   *
   * @param modeStr Строка, представляющая режим примитива.
   */
  void setPrimitiveMode(const QString &modeStr);

  /**
   * @brief Получает текущий режим примитива.
   *
   * @return Строка, представляющая текущий режим примитива.
   */
  QString getPrimitiveMode() const;

  /**
   * @brief Устанавливает режим проекции.
   *
   * @param modeStr Строка, представляющая режим проекции.
   */
  void setProjectionMode(const QString &modeStr);

  /**
   * @brief Получает текущий режим проекции.
   *
   * @return Строка, представляющая текущий режим проекции.
   */
  QString getProjectionMode() const;

  /**
   * @brief Устанавливает режим линий.
   *
   * @param modeStr Строка, представляющая режим линий.
   */
  void setLineMode(const QString &modeStr);

  /**
   * @brief Получает текущий режим линий.
   *
   * @return Строка, представляющая текущий режим линий.
   */
  QString getLineMode() const;

  /**
   * @brief Устанавливает толщину линий.
   *
   * @param thickness Толщина линий.
   */
  void setLineThickness(int thickness);

  /**
   * @brief Получает текущую толщину линий.
   *
   * @return Толщина линий.
   */
  int getLineThickness() const;

  /**
   * @brief Устанавливает режим вершин.
   *
   * @param modeStr Строка, представляющая режим вершин.
   */
  void setVertexMode(const QString &modeStr);

  /**
   * @brief Получает текущий режим вершин.
   *
   * @return Строка, представляющая текущий режим вершин.
   */
  QString getVertexMode() const;

  /**
   * @brief Устанавливает размер вершин.
   *
   * @param size Размер вершин.
   */
  void setVertexSize(int size);

  /**
   * @brief Получает текущий размер вершин.
   *
   * @return Размер вершин.
   */
  int getVertexSize() const;

  /**
   * @brief Устанавливает цвет границ.
   *
   * @param color Цвет границ.
   */
  void setEdgeColor(const QColor &color);

  /**
   * @brief Получает текущий цвет границ.
   *
   * @return Цвет границ.
   */
  QColor getEdgeColor() const;

  /**
   * @brief Устанавливает цвет вершин.
   *
   * @param color Цвет вершин.
   */
  void setVertexColor(const QColor &color);

  /**
   * @brief Получает текущий цвет вершин.
   *
   * @return Цвет вершин.
   */
  QColor getVertexColor() const;

  /**
   * @brief Устанавливает цвет фона.
   *
   * @param color Цвет фона.
   */
  void setBackgroundColor(const QColor &color);

  /**
   * @brief Получает текущий цвет фона.
   *
   * @return Цвет фона.
   */
  QColor getBackgroundColor() const;

 protected:
  /**
   * @brief Инициализация OpenGL.
   */
  void initializeGL() override;

  /**
   * @brief Отрисовка сцены.
   */
  void paintGL() override;

 private:
  ObjController *controller;  ///< Указатель на контроллер модели

  /**
   * @brief Устанавливает параметры проекции.
   */
  void setProjection();

  /**
   * @brief Настраивает матрицу модели и вида.
   */
  void setupModelView();

  /**
   * @brief Рисует вершины модели.
   */
  void drawVertices();

  /**
   * @brief Рисует примитивы.
   */
  void drawPrimitive();

  /**
   * @brief Рисует маркеры вершин.
   */
  void drawVertexMarkers();

  // Переменные для настройки UI
  enum ProjectionMode { Central, Parallel };  ///< Режимы проекции
  enum LineMode { Solid, Dashed };            ///< Режимы линий
  enum VertexMode { Empty, Circle, Square };  ///< Режимы вершин
  enum PrimitiveMode { Lines, Triangles, Points };  ///< Режимы примитивов

  ProjectionMode projection_mode = Parallel;  ///< Текущий режим проекции
  LineMode line_mode = Solid;         ///< Текущий режим линий
  PrimitiveMode currentMode = Lines;  ///< Текущий режим примитива
  VertexMode vertexMode = Empty;  ///< Текущий режим вершин
  int edgeThickness = 1;          ///< Толщина линий
  int verticleSize = 1;           ///< Размер вершин
  QColor backgroundColor = QColor(200, 200, 200);  ///< Цвет фона
  QColor edgeColor = QColor(0, 0, 255);            ///< Цвет границ
  QColor verticleColor = QColor(255, 0, 0);        ///< Цвет вершин
};

}  // namespace s21

#endif  // OBJVIEW_H
