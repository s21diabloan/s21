#ifndef TRANSFORMATIONSTRATEGY_H
#define TRANSFORMATIONSTRATEGY_H

#include "objmodel.h"

namespace s21 {

class ObjModel;  // Forward declaration

/**
 * @brief Абстрактный класс стратегии трансформации модели.
 *
 * Этот абстрактный класс задает интерфейс для различных стратегий трансформации
 * модели. Конкретные стратегии должны реализовать метод apply(), который
 * применяется к объекту модели (ObjModel).
 */
class TransformationStrategy {
 public:
  virtual ~TransformationStrategy() {}

  /**
   * @brief Применяет трансформацию к модели.
   *
   * Этот чисто виртуальный метод должен быть реализован в конкретных стратегиях
   * трансформации. Метод применяется к объекту модели и изменяет его состояние
   * в зависимости от выбранной стратегии трансформации.
   *
   * @param model Указатель на объект модели, к которому применяется
   * трансформация.
   */
  virtual void apply(ObjModel* model) = 0;
};

}  // namespace s21

#endif  // TRANSFORMATIONSTRATEGY_H
