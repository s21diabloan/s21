#include "rotatetransformationstrategy.h"

#include "objmodel.h"

namespace s21 {

RotateTransformationStrategy::RotateTransformationStrategy(double angleX,
                                                           double angleY,
                                                           double angleZ)
    : angleX(angleX), angleY(angleY), angleZ(angleZ) {}

void RotateTransformationStrategy::apply(ObjModel* model) {
  model->rotateModelX(angleX);
  model->rotateModelY(angleY);
  model->rotateModelZ(angleZ);
}

}  // namespace s21
