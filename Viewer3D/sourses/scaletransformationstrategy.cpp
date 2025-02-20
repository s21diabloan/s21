#include "scaletransformationstrategy.h"

#include "objmodel.h"

namespace s21 {

ScaleTransformationStrategy::ScaleTransformationStrategy(double scale)
    : scale(scale) {}

void ScaleTransformationStrategy::apply(ObjModel* model) {
  model->scaleModel(scale);
}

}  // namespace s21
