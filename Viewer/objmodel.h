#ifndef OBJMODEL_H
#define OBJMODEL_H

#include <QString>
#include <QVector>

namespace s21 {

/**
 * @brief Класс для работы с моделью в формате OBJ.
 *
 * Этот класс предоставляет методы для загрузки модели из файла, получения её
 * вершин и индексов, а также для применения различных трансформаций, таких как
 * масштабирование, перемещение и поворот.
 */
class ObjModel {
 public:
  /**
   * @brief Загружает модель из указанного файла.
   *
   * @param filename Имя файла с моделью.
   *
   * @return true, если модель успешно загружена; иначе false.
   */
  bool loadFromFile(const QString& filename);

  /**
   * @brief Получает вершины модели.
   *
   * @return Ссылка на вектор вершин модели.
   */
  const QVector<double>& getVertices() const;

  /**
   * @brief Получает индексы модели.
   *
   * @return Ссылка на вектор индексов модели.
   */
  const QVector<unsigned int>& getIndices() const;

  /**
   * @brief Масштабирует модель.
   *
   * @param scale Коэффициент масштабирования.
   */
  void scaleModel(double scale);

  /**
   * @brief Перемещает модель по оси X.
   *
   * @param dx Смещение по оси X.
   */
  void moveModelX(double dx);

  /**
   * @brief Перемещает модель по оси Y.
   *
   * @param dy Смещение по оси Y.
   */
  void moveModelY(double dy);

  /**
   * @brief Перемещает модель по оси Z.
   *
   * @param dz Смещение по оси Z.
   */
  void moveModelZ(double dz);

  /**
   * @brief Поворачивает модель вокруг оси X.
   *
   * @param angle Угол поворота в градусах.
   */
  void rotateModelX(double angle);

  /**
   * @brief Поворачивает модель вокруг оси Y.
   *
   * @param angle Угол поворота в градусах.
   */
  void rotateModelY(double angle);

  /**
   * @brief Поворачивает модель вокруг оси Z.
   *
   * @param angle Угол поворота в градусах.
   */
  void rotateModelZ(double angle);

  /**
   * @brief Применяет все трансформации к модели.
   */
  void transformModel();

  /**
   * @brief Очищает данные модели.
   */
  void clear();

 private:
  QVector<double> vertices;  ///< Вершины модели
  QVector<double> verticesBase;  ///< Исходные координаты вершин
  QVector<unsigned int> indices;  ///< Индексы вершин для граней
  QVector<unsigned int> currentFaceIndices;  ///< Индексы текущих граней

  /**
   * @brief Парсит строку из файла модели.
   *
   * @param line Строка для парсинга.
   *
   * @return true, если строка успешно распарсена; иначе false.
   */
  bool parseLine(const QString& line);

  /**
   * @brief Нормализует модель, чтобы она поместилась в единичный куб.
   */
  void normalizeModel();

  double minX = 0.0;   ///< Минимальное значение X
  double maxX = 0.0;   ///< Максимальное значение X
  double minY = 0.0;   ///< Минимальное значение Y
  double maxY = 0.0;   ///< Максимальное значение Y
  double minZ = 0.0;   ///< Минимальное значение Z
  double maxZ = 0.0;   ///< Максимальное значение Z
  double scale = 1.0;  ///< Коэффициент масштабирования
  double dx = 0.0;     ///< Смещение по оси X
  double dy = 0.0;     ///< Смещение по оси Y
  double dz = 0.0;     ///< Смещение по оси Z
  double angleX = 0.0;  ///< Угол поворота вокруг оси X
  double angleY = 0.0;  ///< Угол поворота вокруг оси Y
  double angleZ = 0.0;  ///< Угол поворота вокруг оси Z
};

}  // namespace s21

#endif  // OBJMODEL_H
