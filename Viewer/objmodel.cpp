#include "objmodel.h"

#include <QDebug>
#include <QFile>
#include <QRegularExpression>
#include <QStringList>
#include <QTextStream>

namespace s21 {

/**
 * @brief Загрузка модели из файла.
 * @param filename - путь к файлу модели.
 * @return true, если модель успешно загружена, false в противном случае.
 */
bool ObjModel::loadFromFile(const QString& filename) {
  clear();
  QFile file(filename);
  bool success = false;

  if (file.open(QIODevice::ReadOnly | QIODevice::Text)) {
    QTextStream in(&file);
    success = true;
    while (!in.atEnd()) {
      QString line = in.readLine();
      if (!parseLine(line)) {
        success = false;
        break;
      }
    }
    if (success) {
      normalizeModel();
      verticesBase = vertices;
    }
  }
  return success;
}

/**
 * @brief Получение вершин модели.
 * @return вектор вершин модели.
 */
const QVector<double>& ObjModel::getVertices() const { return vertices; }

/**
 * @brief Получение индексов вершин для граней модели.
 * @return вектор индексов вершин для граней модели.
 */
const QVector<unsigned int>& ObjModel::getIndices() const { return indices; }

/**
 * @brief Очистка модели.
 */
void ObjModel::clear() {
  vertices.clear();
  indices.clear();
  verticesBase.clear();
  scale = 0.0;
  dx = 0.0;
  dy = 0.0;
  dz = 0.0;
  angleX = 0.0;
  angleY = 0.0;
  angleZ = 0.0;
}

/**
 * @brief Парсинг строки из файла OBJ.
 * @param line - строка из файла OBJ.
 * @return, строка успешно парсится, false в противном случае.
 */

bool ObjModel::parseLine(const QString& line) {
  QStringList tokens = line.split(' ');
  tokens.removeAll("");

  bool success = true;

  if (!tokens.isEmpty()) {
    if (tokens[0] == "v") {
      if (tokens.size() != 4) {
        success = false;
      } else {
        bool ok;
        double x = tokens[1].toDouble(&ok);
        success = success && ok;
        double y = tokens[2].toDouble(&ok);
        success = success && ok;
        double z = tokens[3].toDouble(&ok);
        success = success && ok;

        if (success) {
          vertices << x << y << z;
        }
      }
    } else if (tokens[0] == "f") {
      if (tokens.size() < 4) {
        success = false;
      } else {
        currentFaceIndices.clear();
        for (int i = 1; i < tokens.size(); ++i) {
          QStringList faceTokens = tokens[i].split('/');
          if (faceTokens.size() < 1) {
            success = false;
            break;
          }
          bool ok;
          int vertexIndex = faceTokens[0].toInt(&ok);
          if (!ok) {
            success = false;
            break;
          }

          if (vertexIndex > 0) {
            currentFaceIndices << (vertexIndex - 1);
          } else if (vertexIndex < 0) {
            currentFaceIndices << (vertices.size() / 3 + vertexIndex);
          } else {
            success = false;
            break;
          }
        }

        if (success && currentFaceIndices.size() >= 3) {
          for (int i = 1; i < currentFaceIndices.size() - 1; ++i) {
            indices << currentFaceIndices[0] << currentFaceIndices[i]
                    << currentFaceIndices[i + 1];
          }
        } else {
          success = false;
        }
      }
    }
  }
  return success;
}

//-----------
/**
 * @brief Нормализация модели.
 */
void ObjModel::normalizeModel() {
  if (vertices.isEmpty()) return;
  // Инициализируем min и max значениями первой вершины
  minX = maxX = vertices[0];
  minY = maxY = vertices[1];
  minZ = maxZ = vertices[2];
  // Вычисляем bounding box, обновляем min и max
  for (int i = 0; i < vertices.size() / 3; ++i) {
    double x = vertices[i * 3];
    double y = vertices[i * 3 + 1];
    double z = vertices[i * 3 + 2];
    if (x < minX) minX = x;
    if (x > maxX) maxX = x;
    if (y < minY) minY = y;
    if (y > maxY) maxY = y;
    if (z < minZ) minZ = z;
    if (z > maxZ) maxZ = z;
  }
  // Центрируем модель на основе вычисленного bounding box
  double centerX = (minX + maxX) / 2.0;
  double centerY = (minY + maxY) / 2.0;
  double centerZ = (minZ + maxZ) / 2.0;

  // Находим максимальное измерение для нормализации масштаба
  double maxDimension = 0.5 * qMax(maxX - minX, qMax(maxY - minY, maxZ - minZ));

  // Центрируем и нормализуем вершины
  for (int i = 0; i < vertices.size() / 3; ++i) {
    vertices[i * 3] = (vertices[i * 3] - centerX) / maxDimension;
    vertices[i * 3 + 1] = (vertices[i * 3 + 1] - centerY) / maxDimension;
    vertices[i * 3 + 2] = (vertices[i * 3 + 2] - centerZ) / maxDimension;
  }
}

/**
 * @brief Применение трансформаций к модели.
 */
void ObjModel::transformModel() {
  vertices = verticesBase;

  // Подготовка углов для вращения
  double radX = qDegreesToRadians(angleX);
  double radY = qDegreesToRadians(angleY);
  double radZ = qDegreesToRadians(angleZ);

  // Коэффициенты вращения
  double cosX = cos(radX), sinX = sin(radX);
  double cosY = cos(radY), sinY = sin(radY);
  double cosZ = cos(radZ), sinZ = sin(radZ);

  for (int i = 0; i < vertices.size(); i += 3) {
    // Масштабирование
    double x = vertices[i] * scale;
    double y = vertices[i + 1] * scale;
    double z = vertices[i + 2] * scale;

    // Вращение вокруг оси X
    double yRot = y * cosX - z * sinX;
    double zRot = y * sinX + z * cosX;

    // Вращение вокруг оси Y
    double xRot = x * cosY + zRot * sinY;
    z = -x * sinY + zRot * cosY;

    // Вращение вокруг оси Z
    x = xRot * cosZ - yRot * sinZ;
    y = xRot * sinZ + yRot * cosZ;

    // Перемещение
    vertices[i] = x + dx;
    vertices[i + 1] = y + dy;
    vertices[i + 2] = z + dz;
  }
}

/**
 * @brief Масштабирование модели.
 * @param scale - фактор масштабирования.
 */
void ObjModel::scaleModel(double scale) {
  this->scale = scale;
  transformModel();
}

/**
 * @brief Перемещение модели по оси X.
 * @param dx - смещение по оси X.
 */
void ObjModel::moveModelX(double dx) {
  this->dx = dx;
  transformModel();
}

/**
 * @brief Перемещение модели по оси Y.
 * @param dy - смещение по оси Y.
 */
void ObjModel::moveModelY(double dy) {
  this->dy = dy;
  transformModel();
}

/**
 * @brief Перемещение модели по оси Z.
 * @param dz - смещение по оси Z.
 */
void ObjModel::moveModelZ(double dz) {
  this->dz = dz;
  transformModel();
}

/**
 * @brief Поворот модели вокруг оси X.
 * @param angleX - угол поворота вокруг оси X.
 */
void ObjModel::rotateModelX(double angleX) {
  this->angleX = angleX;
  transformModel();
}

/**
 * @brief Поворот модели вокруг оси Y.
 * @param angleY - угол поворота вокруг оси Y.
 */
void ObjModel::rotateModelY(double angleY) {
  this->angleY = angleY;
  transformModel();
}

/**
 * @brief Поворот модели вокруг оси Z.
 * @param angleZ - угол поворота вокруг оси Z.
 */
void ObjModel::rotateModelZ(double angleZ) {
  this->angleZ = angleZ;
  transformModel();
}

}  // namespace s21
