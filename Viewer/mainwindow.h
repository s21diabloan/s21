#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include <QColorDialog>
#include <QFileDialog>
#include <QImage>
#include <QImageReader>
#include <QMainWindow>
#include <QMessageBox>
#include <QMouseEvent>
#include <QPainter>
#include <QSettings>
#include <QWheelEvent>

#include "./giflib/gif.hpp"
#include "objcontroller.h"
#include "objview.h"
#include "sourses/settingsfacade.h"

QT_BEGIN_NAMESPACE
namespace Ui {
class MainWindow;
}
QT_END_NAMESPACE

namespace s21 {

/**
 * @brief Основной класс окна приложения.
 *
 * Этот класс представляет основное окно приложения и управляет интерфейсом
 * пользователя. Он обрабатывает пользовательские события, такие как нажатия
 * кнопок, перемещения мыши и изменения значений в слайдерах. Класс также
 * взаимодействует с контроллером и объектом представления, а также управляет
 * настройками и сохранением изображений и GIF-файлов.
 */
class MainWindow : public QMainWindow {
  Q_OBJECT

 public:
  /**
   * @brief Конструктор класса MainWindow.
   *
   * Инициализирует окно приложения, настраивает элементы интерфейса и создает
   * контроллер и объект представления.
   *
   * @param parent Указатель на родительский виджет.
   */
  MainWindow(QWidget *parent = nullptr);

  /**
   * @brief Деструктор класса MainWindow.
   *
   * Очищает ресурсы, выделенные для данного окна приложения.
   */
  ~MainWindow();

  /**
   * @brief Получает указатель на пользовательский интерфейс.
   *
   * @return Указатель на объект пользовательского интерфейса.
   */
  Ui::MainWindow *getUI() const;

 protected:
  void closeEvent(QCloseEvent *event) override;
  void wheelEvent(QWheelEvent *event) override;
  void mousePressEvent(QMouseEvent *event) override;
  void mouseMoveEvent(QMouseEvent *event) override;
  void mouseReleaseEvent(QMouseEvent *event) override;

 private:
  /**
   * @brief Перемещает объект модели.
   */
  void move();

  /**
   * @brief Поворачивает объект модели.
   */
  void rotate();

  /**
   * @brief Обрабатывает нажатие кнопки для загрузки файла.
   */
  void on_pushButton_loadFile_clicked();

  /**
   * @brief Обрабатывает изменение режима вершин в выпадающем списке.
   *
   * @param arg1 Новый режим вершин.
   */
  void on_comboBox_vertexMode_textActivated(const QString &arg1);

  /**
   * @brief Обрабатывает изменение режима примитивов в выпадающем списке.
   *
   * @param arg1 Новый режим примитивов.
   */
  void on_comboBox_PrimitiveMode_textActivated(const QString &arg1);

  /**
   * @brief Восстанавливает настройки по умолчанию.
   */
  void on_pushButton_default_clicked();

  /**
   * @brief Обрабатывает изменение режима проекции в выпадающем списке.
   *
   * @param arg1 Новый режим проекции.
   */
  void on_comboBox_ProjectionMode_textActivated(const QString &arg1);

  /**
   * @brief Обрабатывает нажатие клавиши для изменения масштаба.
   */
  void on_lineEdit_scale_returnPressed();

  /**
   * @brief Обрабатывает нажатие кнопки для изменения масштаба.
   */
  void on_pushButton_scale_clicked();

  /**
   * @brief Обрабатывает изменение режима линии в выпадающем списке.
   *
   * @param arg1 Новый режим линии.
   */
  void on_comboBox_lineMode_textActivated(const QString &arg1);

  /**
   * @brief Обрабатывает нажатие кнопки для изменения толщины линии.
   */
  void on_pushButton_lineSize_pressed();

  /**
   * @brief Обрабатывает нажатие кнопки для изменения размера вершин.
   */
  void on_pushButton_vertexSize_pressed();

  /**
   * @brief Обрабатывает нажатие кнопки для изменения цвета линии.
   */
  void on_pushButton_lineColor_pressed();

  /**
   * @brief Обрабатывает нажатие кнопки для изменения цвета вершин.
   */
  void on_pushButton_vertexColor_pressed();

  /**
   * @brief Обрабатывает нажатие кнопки для изменения цвета фона.
   */
  void on_pushButton_backGround_pressed();

  /**
   * @brief Обрабатывает изменение значения слайдера масштаба.
   *
   * @param value Новое значение слайдера масштаба.
   */
  void on_horizontalSlider_scale_valueChanged(int value);

  /**
   * @brief Обрабатывает нажатие кнопки для сохранения изображения.
   */
  void on_pushButton_saveImage_pressed();

  /**
   * @brief Обрабатывает нажатие кнопки для сброса настроек.
   */
  void on_pushButton_reset_pressed();

  /**
   * @brief Обрабатывает изменение значения слайдера толщины линии.
   *
   * @param value Новое значение слайдера толщины линии.
   */
  void on_horizontal_lineSize_valueChanged(int value);

  /**
   * @brief Обрабатывает изменение значения слайдера размера вершин.
   *
   * @param value Новое значение слайдера размера вершин.
   */
  void on_horizontalSlider_vertexSize_valueChanged(int value);

  /**
   * @brief Обрабатывает нажатие кнопки для сохранения GIF-файла.
   */
  void on_pushButton_saveGif_pressed();

  /**
   * @brief Обновляет строку состояния с информацией о файле и количестве вершин
   * и ребер.
   *
   * @param fileName Имя файла.
   * @param vertexCount Количество вершин.
   * @param edgeCount Количество ребер.
   */
  void updateStatusBar(const QString &fileName, int vertexCount, int edgeCount);

  /**
   * @brief Сбрасывает настройки по умолчанию при загрузке файла.
   */
  void resetDefault();

  /**
   * @brief Устанавливает масштаб.
   *
   * @return true, если масштаб был установлен успешно; иначе false.
   */
  bool setScale();

  /**
   * @brief Обрабатывает изменение масштаба.
   *
   * @param scale Новый масштаб.
   */
  void processScale(double scale);

  /**
   * @brief Устанавливает перемещение.
   *
   * @return true, если перемещение было установлено успешно; иначе false.
   */
  bool setMove();

  /**
   * @brief Обрабатывает перемещение модели.
   *
   * @param moveX Перемещение по оси X.
   * @param moveY Перемещение по оси Y.
   * @param moveZ Перемещение по оси Z.
   */
  void processMove(double moveX, double moveY_, double moveZ_);

  /**
   * @brief Устанавливает вращение.
   *
   * @return true, если вращение было установлено успешно; иначе false.
   */
  bool setRotate();

  /**
   * @brief Обрабатывает вращение модели.
   *
   * @param rotateX Вращение вокруг оси X.
   * @param rotateY Вращение вокруг оси Y.
   * @param rotateZ Вращение вокруг оси Z.
   */
  void processRotate(double rotateX, double rotateY, double rotateZ);

  /**
   * @brief Нормализует угол вращения.
   *
   * @param angle Угол для нормализации.
   *
   * @return Нормализованный угол.
   */
  double normalizeAngle(double angle);

  /**
   * @brief Обновляет толщину линии.
   *
   * @param thickness Новая толщина линии.
   */
  void updateLineThickness(int thickness);

  /**
   * @brief Обновляет размер вершин.
   *
   * @param vertexSize Новый размер вершин.
   */
  void updateVertexSize(int vertexSize);

  /**
   * @brief Сохраняет текущее изображение.
   */
  void saveRenderedImage();

  /**
   * @brief Сохраняет текущее изображение как GIF.
   */
  void saveGif();

  Ui::MainWindow *ui;  ///< Указатель на объект пользовательского интерфейса
  ObjView *view;  ///< Указатель на объект представления
  ObjController *controller;  ///< Указатель на объект контроллера
  SettingsFacade *settingsFacade;  ///< Фасад для настроек

  double scale = 1;       ///< Масштаб модели
  double moveX = 0.0;     ///< Перемещение по оси X
  double moveY = 0.0;     ///< Перемещение по оси Y
  double moveZ = 0.0;     ///< Перемещение по оси Z
  double rotateX = 0.0;   ///< Вращение вокруг оси X
  double rotateY = 0.0;   ///< Вращение вокруг оси Y
  double rotateZ = 0.0;   ///< Вращение вокруг оси Z
  bool fileLoad = false;  ///< Флаг загрузки файла
  QPoint lastMousePosition = QPoint(0, 0);  ///< Последняя позиция мыши
  bool dragging = false;  ///< Флаг перетаскивания
  bool sliderChanged = false;  ///< Флаг изменения слайдера масштаба
  bool sliderChangedLine = false;  ///< Флаг изменения слайдера толщины линии
  bool sliderChangedVertex = false;  ///< Флаг изменения слайдера размера вершин
  int frameCount = 50;  ///< Количество кадров для GIF
  GifWriter gifFigure;  ///< Объект для записи GIF
};

}  // namespace s21

#endif  // MAINWINDOW_H
