#ifndef MOVETRANSFORMATIONSTRATEGY_H
#define MOVETRANSFORMATIONSTRATEGY_H

#include "transformationstrategy.h"

namespace s21 {

/**
 * @brief Класс стратегии трансформации для перемещения модели.
 */
class MoveTransformationStrategy : public TransformationStrategy {
 public:
  MoveTransformationStrategy(double dx, double dy, double dz);
  void apply(ObjModel* model) override;

 private:
  double dx, dy, dz;
};

}  // namespace s21

#endif  // MOVETRANSFORMATIONSTRATEGY_H
