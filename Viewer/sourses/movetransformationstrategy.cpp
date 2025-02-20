#include "movetransformationstrategy.h"

#include "objmodel.h"

namespace s21 {
MoveTransformationStrategy::MoveTransformationStrategy(double dx, double dy,
                                                       double dz)
    : dx(dx), dy(dy), dz(dz) {}

void MoveTransformationStrategy::apply(ObjModel* model) {
  model->moveModelX(dx);
  model->moveModelY(dy);
  model->moveModelZ(dz);
}

}  // namespace s21
