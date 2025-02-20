#include "objcontroller.h"

namespace s21 {

ObjController::ObjController()
    : model(new ObjModel()), transformationStrategy(nullptr) {
  m_reset.setModel(model);
}

ObjController::~ObjController() {
  delete model;
  delete transformationStrategy;
}

/**
 * @brief Открытие и загрузка файла модели.
 * @param filename - имя файла модели.
 * @return, файл успешно загружен, false в противном случае.
 */
bool ObjController::openFile(const QString& filename) {
  resetModel();
  return model->loadFromFile(filename);
}

/**
 * @brief Получение вершин модели.
 * @return вектор с вершинами модели.
 */
const QVector<double>& ObjController::getVertices() const {
  return model->getVertices();
}

/**
 * @brief Получение индексов вершин модели.
 * @return вектор с индексами вершин модели.
 */
const QVector<unsigned int>& ObjController::getIndices() const {
  return model->getIndices();
}

/**
 * @brief Установка стратегии трансформации модели.
 * @param strategy - указатель на стратегию трансформации.
 */
void ObjController::setTransformationStrategy(
    TransformationStrategy* strategy) {
  if (transformationStrategy) {
    delete transformationStrategy;
  }
  transformationStrategy = strategy;
}

/**
 * @brief Применение текущей стратегии трансформации модели.
 */
void ObjController::applyTransformation() {
  if (transformationStrategy) {
    transformationStrategy->apply(model);
  }
}

/**
 * @brief Сброс модели.
 */
void ObjController::resetModel() { m_reset.execute(); }

}  // namespace s21
