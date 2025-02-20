#ifndef SCALETRANSFORMATIONSTRATEGY_H
#define SCALETRANSFORMATIONSTRATEGY_H

#include "transformationstrategy.h"

namespace s21 {

/**
 * @brief Класс стратегии трансформации для масштабирования модели.
 *
 * Этот класс реализует стратегию масштабирования модели. Он применяется для
 * изменения размера модели в зависимости от заданного коэффициента
 * масштабирования.
 */
class ScaleTransformationStrategy : public TransformationStrategy {
 public:
  /**
   * @brief Конструктор для класса ScaleTransformationStrategy.
   *
   * @param scale Коэффициент масштабирования.
   */
  ScaleTransformationStrategy(double scale);

  /**
   * @brief Применяет масштабирование к модели.
   *
   * Этот метод изменяет размер модели на основе заданного коэффициента
   * масштабирования.
   *
   * @param model Указатель на объект модели, к которому будет применено
   * масштабирование.
   */
  void apply(ObjModel* model) override;

 private:
  double scale;  ///< Коэффициент масштабирования.
};

}  // namespace s21

#endif  // SCALETRANSFORMATIONSTRATEGY_H
