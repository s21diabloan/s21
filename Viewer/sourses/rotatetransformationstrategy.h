#ifndef ROTATETRANSFORMATIONSTRATEGY_H
#define ROTATETRANSFORMATIONSTRATEGY_H

#include "transformationstrategy.h"

namespace s21 {

/**
 * @brief Класс стратегии трансформации для вращения модели.
 */
class RotateTransformationStrategy : public TransformationStrategy {
 public:
  RotateTransformationStrategy(double angleX, double angleY, double angleZ);
  void apply(ObjModel* model) override;

 private:
  double angleX, angleY, angleZ;
};

}  // namespace s21
#endif  // ROTATETRANSFORMATIONSTRATEGY_H
