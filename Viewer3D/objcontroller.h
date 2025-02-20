#ifndef OBJCONTROLLER_H
#define OBJCONTROLLER_H

#include <QString>
#include <QVector>

#include "objmodel.h"
#include "reset_command.hpp"
#include "sourses/movetransformationstrategy.h"
#include "sourses/rotatetransformationstrategy.h"
#include "sourses/scaletransformationstrategy.h"
#include "sourses/transformationstrategy.h"

namespace s21 {

/**
 * @brief Класс-контроллер для работы с моделью в формате OBJ.
 *
 * Этот класс отвечает за взаимодействие с моделью OBJ, управление стратегиями
 * трансформаций и выполнение операций, таких как открытие файла, применение
 * трансформаций и сброс модели.
 */
class ObjController {
 public:
  /**
   * @brief Получает экземпляр контроллера.
   *
   * Этот метод реализует паттерн Singleton, создавая и возвращая единственный
   * экземпляр контроллера. Экземпляр создается лениво и потокобезопасно.
   *
   * @return Ссылка на единственный экземпляр контроллера.
   */
  static ObjController& Instance() {
    // Согласно стандарту, этот код ленивый и потокобезопасный
    static ObjController s;
    s.model = new ObjModel();
    return s;
  }

  /**
   * @brief Открывает файл модели.
   *
   * Этот метод загружает модель из указанного файла.
   *
   * @param filename Имя файла с моделью.
   *
   * @return true, если файл был успешно открыт; иначе false.
   */
  bool openFile(const QString& filename);

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
   * @brief Устанавливает стратегию трансформации.
   *
   * @param strategy Указатель на объект стратегии трансформации.
   */
  void setTransformationStrategy(TransformationStrategy* strategy);

  /**
   * @brief Применяет текущую стратегию трансформации.
   */
  void applyTransformation();

  /**
   * @brief Сбрасывает модель к исходным параметрам.
   */
  void resetModel();

 private:
  ObjController();
  ~ObjController();
  ObjController(ObjController const&) = delete;
  ObjController& operator=(ObjController const&) = delete;

  ObjModel* model;       ///< Указатель на модель OBJ
  ResetCommand m_reset;  ///< Объект для сброса модели
  TransformationStrategy*
      transformationStrategy;  ///< Указатель на текущую стратегию трансформации
};

}  // namespace s21

#endif  // OBJCONTROLLER_H
