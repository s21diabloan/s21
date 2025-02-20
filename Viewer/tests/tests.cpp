#include <gtest/gtest.h>

#include "objmodel.h"

using namespace s21;

TEST(loadFromFile, base) {
  ObjModel model;
  QString filename = "../obj/cube.obj";
  bool result = false;
  result = model.loadFromFile(filename);
  ASSERT_TRUE(result);
}

TEST(loadFromFile, empty) {
  ObjModel model;
  QString filename = "";
  bool result = false;
  result = model.loadFromFile(filename);
  ASSERT_FALSE(result);
}

TEST(loadFromFile, normalize) {
  ObjModel model;
  QString filename = "../obj/cube.obj";
  model.loadFromFile(filename);
  bool result = true;
  for (int i = 0; i < 24; i++) {
    double val = model.getVertices()[i];
    if (val < -1.0 || val > 1.0) result = false;
  }
  ASSERT_TRUE(result);
}

TEST(scale, scale) {
  ObjModel model;
  QString filename = "../obj/cube.obj";
  model.loadFromFile(filename);
  model.scaleModel(0.5);
  bool result = true;
  for (int i = 0; i < 24; i++) {
    double val = model.getVertices()[i];
    if (val < -0.5 || val > 0.5) result = false;
  }
  ASSERT_TRUE(result);
}

TEST(move, move) {
  ObjModel model;
  QString filename = "../obj/cube.obj";
  model.loadFromFile(filename);
  model.moveModelX(1);
  model.moveModelY(1);
  model.moveModelZ(1);
  bool result = true;
  for (int i = 0; i < 24; i++) {
    double val = model.getVertices()[i];
    if (val != 1.0) result = false;
  }
  ASSERT_TRUE(result);
}

TEST(Scale, Scale) {
  ObjModel model;
  QString filename = "../obj/cube.obj";
  model.loadFromFile(filename);
  model.scaleModel(1.2);
  bool result = true;
  for (int i = 0; i < 24; i++) {
    double val = model.getVertices()[i];
    if (val != 1.2 && val != -1.2) result = false;
  }
  ASSERT_TRUE(result);
}

TEST(Rotate, Rotate) {
  ObjModel model;
  QString filename = "../obj/cube.obj";
  model.loadFromFile(filename);
  model.scaleModel(1.2);
  model.rotateModelX(45);
  model.rotateModelY(45);
  model.rotateModelZ(45);
  bool result = true;
  for (int i = 0; i < 24; i++) {
    double val = model.getVertices()[i];
    if (std::abs(val) > 2.1) {
      result = false;
    }
  }
  model.clear();
  ASSERT_TRUE(result);
}

int main(int argc, char** argv) {
  ::testing::InitGoogleTest(&argc, argv);
  return RUN_ALL_TESTS();
}
