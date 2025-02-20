#include "mainwindow.h"

#include "ui_mainwindow.h"

namespace s21 {

MainWindow::MainWindow(QWidget *parent)
    : QMainWindow(parent),
      ui(new Ui::MainWindow),
      controller(&ObjController::Instance()),
      settingsFacade(nullptr) {
  ui->setupUi(this);
  view = new ObjView(controller, this);
  view->setSizePolicy(QSizePolicy::Expanding, QSizePolicy::Expanding);
  ui->horizontalLayout->addWidget(view);
  settingsFacade = new SettingsFacade(view, this);  // Создаем фасад настроек
  settingsFacade->loadSettings();  // Загружаем настройки при запуске программы

  // Подключаем события вращения
  connect(ui->lineEdit_rotateX, &QLineEdit::returnPressed, this,
          &MainWindow::rotate);
  connect(ui->lineEdit_rotateY, &QLineEdit::returnPressed, this,
          &MainWindow::rotate);
  connect(ui->lineEdit_rotateZ, &QLineEdit::returnPressed, this,
          &MainWindow::rotate);
  connect(ui->pushButton_rotate, &QPushButton::pressed, this,
          &MainWindow::rotate);

  // Подключаем события перемещения
  connect(ui->lineEdit_moveX, &QLineEdit::returnPressed, this,
          &MainWindow::move);
  connect(ui->lineEdit_moveY, &QLineEdit::returnPressed, this,
          &MainWindow::move);
  connect(ui->lineEdit_moveZ, &QLineEdit::returnPressed, this,
          &MainWindow::move);
  connect(ui->pushButton_move, &QPushButton::pressed, this, &MainWindow::move);

  // Подключаем события загрузки файла
  connect(ui->pushButton_loadFile, &QPushButton::clicked, this,
          &MainWindow::on_pushButton_loadFile_clicked);

  // Подключаем события изменения режима вершин
  connect(ui->comboBox_vertexMode, &QComboBox::textActivated, this,
          &MainWindow::on_comboBox_vertexMode_textActivated);

  // Подключаем события изменения примитивного режима
  connect(ui->comboBox_PrimitiveMode, &QComboBox::textActivated, this,
          &MainWindow::on_comboBox_PrimitiveMode_textActivated);

  // Подключаем события сброса настроек
  connect(ui->pushButton_default, &QPushButton::clicked, this,
          &MainWindow::on_pushButton_default_clicked);
  connect(ui->pushButton_reset, &QPushButton::pressed, this,
          &MainWindow::on_pushButton_reset_pressed);

  // Подключаем события изменения режима проекции
  connect(ui->comboBox_ProjectionMode, &QComboBox::textActivated, this,
          &MainWindow::on_comboBox_ProjectionMode_textActivated);

  // Подключаем события изменения масштаба
  connect(ui->lineEdit_scale, &QLineEdit::returnPressed, this,
          &MainWindow::on_lineEdit_scale_returnPressed);
  connect(ui->pushButton_scale, &QPushButton::clicked, this,
          &MainWindow::on_pushButton_scale_clicked);

  // Подключаем события изменения режима линий
  connect(ui->comboBox_lineMode, &QComboBox::textActivated, this,
          &MainWindow::on_comboBox_lineMode_textActivated);

  // Подключаем события изменения размера линий и вершин
  connect(ui->pushButton_lineSize, &QPushButton::pressed, this,
          &MainWindow::on_pushButton_lineSize_pressed);
  connect(ui->pushButton_vertexSize, &QPushButton::pressed, this,
          &MainWindow::on_pushButton_vertexSize_pressed);

  // Подключаем события изменения цветов
  connect(ui->pushButton_lineColor, &QPushButton::pressed, this,
          &MainWindow::on_pushButton_lineColor_pressed);
  connect(ui->pushButton_vertexColor, &QPushButton::pressed, this,
          &MainWindow::on_pushButton_vertexColor_pressed);
  connect(ui->pushButton_backGround, &QPushButton::pressed, this,
          &MainWindow::on_pushButton_backGround_pressed);

  // Подключаем события изменения значений слайдеров
  connect(ui->horizontalSlider_scale, &QSlider::valueChanged, this,
          &MainWindow::on_horizontalSlider_scale_valueChanged);
  connect(ui->horizontal_lineSize, &QSlider::valueChanged, this,
          &MainWindow::on_horizontal_lineSize_valueChanged);
  connect(ui->horizontalSlider_vertexSize, &QSlider::valueChanged, this,
          &MainWindow::on_horizontalSlider_vertexSize_valueChanged);

  // Подключаем события сохранения изображений и GIF
  connect(ui->pushButton_saveImage, &QPushButton::pressed, this,
          &MainWindow::on_pushButton_saveImage_pressed);
  connect(ui->pushButton_saveGif, &QPushButton::pressed, this,
          &MainWindow::on_pushButton_saveGif_pressed);
}

MainWindow::~MainWindow() {
  settingsFacade
      ->saveSettings();  // Сохраняем настройки при завершении работы программы
  delete ui;
}

Ui::MainWindow *MainWindow::getUI() const { return ui; }

void MainWindow::updateStatusBar(const QString &fileName, int vertexCount,
                                 int edgeCount) {
  QString statusText = QString("File: %1 | Vertices: %2 | Edges: %3")
                           .arg(fileName)
                           .arg(vertexCount)
                           .arg(edgeCount);
  statusBar()->showMessage(statusText);
}

void MainWindow::on_pushButton_loadFile_clicked() {
  QString fileName = QFileDialog::getOpenFileName(this, tr("Open OBJ File"), "",
                                                  tr("OBJ Files (*.obj)"));
  if (!fileName.isEmpty()) {
    if (controller->openFile(fileName)) {
      int vertexCount = controller->getVertices().size() / 3;
      int edgeCount = controller->getIndices().size() / 2;
      updateStatusBar(fileName, vertexCount, edgeCount);
      //  resetDefault();
      fileLoad = true;
      view->update();
      resetDefault();
    }
  }
}

void MainWindow::resetDefault() {
  processScale(1.0);
  processRotate(0.0, 0.0, 0.0);
  processMove(0.0, 0.0, 0.0);
}

void MainWindow::on_comboBox_PrimitiveMode_textActivated(const QString &arg1) {
  if (view) {
    view->setPrimitiveMode(arg1);
  }
}

void MainWindow::on_pushButton_default_clicked() {
  if (view) settingsFacade->setDefaultSettings();
}

void MainWindow::on_comboBox_ProjectionMode_textActivated(const QString &arg1) {
  if (view) {
    view->setProjectionMode(arg1);
  }
}

// Scale

void MainWindow::on_pushButton_scale_clicked() {
  if (setScale()) processScale(scale);
}

void MainWindow::on_lineEdit_scale_returnPressed() {
  if (setScale()) processScale(scale);
}

void MainWindow::on_horizontalSlider_scale_valueChanged(int value) {
  if (!sliderChanged) {
    scale = 0.1 + value * 0.099;
    processScale(scale);
  }
}

bool MainWindow::setScale() {
  bool ok;
  double inputScale = ui->lineEdit_scale->text().toDouble(&ok);
  if (ok && inputScale > 0) scale = inputScale;
  return ok;
}

void MainWindow::processScale(double scale_) {
  if (fileLoad) {
    scale = scale_;
    controller->setTransformationStrategy(
        new ScaleTransformationStrategy(scale));
    controller->applyTransformation();
    ui->lineEdit_scale->setText(QString::number(scale, 'f', 2));
    int sliderValue = static_cast<int>(round((scale - 0.1) / 0.099));
    sliderChanged = true;
    ui->horizontalSlider_scale->setValue(sliderValue);
    sliderChanged = false;
    view->update();
  }
}

void MainWindow::wheelEvent(QWheelEvent *event) {
  if (view) {
    double angle = event->angleDelta().y() / 120.0;
    scale = scale * (1.0 + angle * 0.1);
    if (scale < 0.1) scale = 0.1;
    processScale(scale);
  }
}
// scale end

// Move
void MainWindow::move() {
  if (setMove()) {
    processMove(moveX, moveY, moveZ);
  }
}

bool MainWindow::setMove() {
  bool okX, okY, okZ;
  moveX = ui->lineEdit_moveX->text().toDouble(&okX);
  moveY = ui->lineEdit_moveY->text().toDouble(&okY);
  moveZ = ui->lineEdit_moveZ->text().toDouble(&okZ);
  return okX && okY && okZ;
}

void MainWindow::processMove(double moveX_, double moveY_, double moveZ_) {
  if (fileLoad) {
    moveX = moveX_;
    moveY = moveY_;
    moveZ = moveZ_;
    controller->setTransformationStrategy(
        new MoveTransformationStrategy(moveX, moveY, moveZ));
    controller->applyTransformation();
    ui->lineEdit_moveX->setText(QString::number(moveX, 'f', 1));
    ui->lineEdit_moveY->setText(QString::number(moveY, 'f', 1));
    ui->lineEdit_moveZ->setText(QString::number(moveZ, 'f', 1));
    view->update();
  }
}

// Move end

// Rotate
void MainWindow::rotate() {
  if (setRotate()) {
    processRotate(rotateX, rotateY, rotateZ);
  }
}

bool MainWindow::setRotate() {
  bool okX, okY, okZ;
  rotateX = ui->lineEdit_rotateX->text().toDouble(&okX);
  rotateY = ui->lineEdit_rotateY->text().toDouble(&okY);
  rotateZ = ui->lineEdit_rotateZ->text().toDouble(&okZ);
  return okX && okY && okZ;
}

void MainWindow::processRotate(double rotateX_, double rotateY_,
                               double rotateZ_) {
  if (fileLoad) {
    rotateX = normalizeAngle(rotateX_);
    rotateY = normalizeAngle(rotateY_);
    rotateZ = normalizeAngle(rotateZ_);
    controller->setTransformationStrategy(
        new RotateTransformationStrategy(rotateX, rotateY, rotateZ));
    controller->applyTransformation();
    ui->lineEdit_rotateX->setText(QString::number(rotateX, 'f', 0));
    ui->lineEdit_rotateY->setText(QString::number(rotateY, 'f', 0));
    ui->lineEdit_rotateZ->setText(QString::number(rotateZ, 'f', 0));
    view->update();
  }
}

double MainWindow::normalizeAngle(double angle) {
  while (angle < 0) {
    angle += 360;
  }
  while (angle >= 360) {
    angle -= 360;
  }
  return angle;
}

// Rotate end

// Mouse move rotate

void MainWindow::mouseMoveEvent(QMouseEvent *event) {
  if (dragging) {
    QPoint delta = event->pos() - lastMousePosition;

    // Если левая кнопка мыши нажата
    if (event->buttons() & Qt::LeftButton) {
      if (QApplication::keyboardModifiers() & Qt::ShiftModifier) {
        // Перемещение по оси Z
        moveZ += delta.y() * 0.01;  // Чувствительность
        processMove(0, 0, moveZ);  // Обрабатываем перемещение только по оси Z
      } else if (QApplication::keyboardModifiers() & Qt::ControlModifier) {
        // Вращение по оси Z
        rotateZ += delta.x();
        processRotate(0, 0, rotateZ);  // Обрабатываем вращение только по оси Z
      } else {
        // Вращение по осям X и Y
        rotateX += delta.y();
        rotateY += delta.x();
        processRotate(rotateX, rotateY,
                      rotateZ);  // Обрабатываем вращение по осям X и Y
      }
    }
    // Если правая кнопка мыши нажата
    else if (event->buttons() & Qt::RightButton) {
      moveX += delta.x() * 0.01;
      moveY += -delta.y() * 0.01;
      processMove(moveX, moveY,
                  moveZ);  // Обрабатываем перемещение по осям X и Y
    }
    // Обновляем последнюю позицию мыши
    lastMousePosition = event->pos();
    // Обновляем отображение
    view->update();
  }
}

void MainWindow::mousePressEvent(QMouseEvent *event) {
  dragging = true;
  lastMousePosition = event->pos();
}

void MainWindow::mouseReleaseEvent(QMouseEvent *event) {
  Q_UNUSED(event);
  dragging = false;
}
// Mouse move rotate end

//----LineMode

void MainWindow::on_comboBox_lineMode_textActivated(const QString &arg1) {
  if (view) {
    view->setLineMode(arg1);
  }
}
void MainWindow::updateLineThickness(int thickness) {
  ui->lineEdit_lineSize->setText(QString::number(thickness));
  sliderChangedLine = true;
  ui->horizontal_lineSize->setValue(thickness);
  sliderChangedLine = false;
  view->setLineThickness(thickness);
  view->update();
}

void MainWindow::on_horizontal_lineSize_valueChanged(int value) {
  if (!sliderChangedLine) {
    updateLineThickness(value);
  }
}

void MainWindow::on_pushButton_lineSize_pressed() {
  bool ok;
  int thickness = ui->lineEdit_lineSize->text().toInt(&ok);
  if (ok) {
    updateLineThickness(thickness);
  }
}

void MainWindow::on_pushButton_lineColor_pressed() {
  QColor color = QColorDialog::getColor(Qt::white, this, "Выберите цвет линии");
  if (color.isValid() && view) {
    view->setEdgeColor(color);
    view->update();
  }
}

//----VertexMode

void MainWindow::on_comboBox_vertexMode_textActivated(const QString &arg1) {
  if (view) {
    view->setVertexMode(arg1);
  }
}

void MainWindow::updateVertexSize(int vertexSize) {
  ui->lineEdit_vertexSize->setText(QString::number(vertexSize));
  sliderChangedVertex = true;
  ui->horizontalSlider_vertexSize->setValue(vertexSize);
  sliderChangedVertex = false;
  view->setVertexSize(vertexSize);
  view->update();
}

void MainWindow::on_horizontalSlider_vertexSize_valueChanged(int value) {
  if (!sliderChangedVertex) {
    updateVertexSize(value);
  }
}

void MainWindow::on_pushButton_vertexSize_pressed() {
  bool ok;
  int vertexSize = ui->lineEdit_vertexSize->text().toInt(&ok);
  if (ok) updateVertexSize(vertexSize);
}

void MainWindow::on_pushButton_vertexColor_pressed() {
  QColor color =
      QColorDialog::getColor(Qt::white, this, "Выберите цвет вершин");
  if (color.isValid() && view) {
    view->setVertexColor(color);
    view->update();
  }
}

void MainWindow::on_pushButton_backGround_pressed() {
  QColor color = QColorDialog::getColor(Qt::white, this, "Выберите цвет фона");
  if (color.isValid() && view) {
    view->setBackgroundColor(color);
    view->update();
  }
}

void MainWindow::closeEvent(QCloseEvent *event) {
  settingsFacade->saveSettings();
  QMainWindow::closeEvent(event);
}

void MainWindow::on_pushButton_reset_pressed() { resetDefault(); }

void MainWindow::on_pushButton_saveImage_pressed() { saveRenderedImage(); }

void MainWindow::saveRenderedImage() {
  QFileDialog dialog(this, tr("Save Image"));
  dialog.setAcceptMode(QFileDialog::AcceptSave);
  dialog.setNameFilters(QStringList() << "BMP Files (*.bmp)"
                                      << "JPEG Files (*.jpg)");

  if (dialog.exec() == QDialog::Accepted) {
    QString fileName = dialog.selectedFiles().first();
    QString selectedFilter = dialog.selectedNameFilter();
    QString extension;
    if (selectedFilter.contains("*.bmp")) {
      extension = ".bmp";
    } else if (selectedFilter.contains("*.jpg")) {
      extension = ".jpg";
    }
    if (!fileName.endsWith(extension, Qt::CaseInsensitive)) {
      fileName += extension;
    }

    // Захватываем содержимое виджета view в виде QPixmap и преобразуем в QImage
    QPixmap pixmap = view->grab();
    QImage image = pixmap.toImage();
    if (image.save(fileName)) {
      QMessageBox::information(this, tr("Save Image"),
                               tr("Image successfully saved as ") + fileName);
    } else {
      QMessageBox::warning(this, tr("Save Image"),
                           tr("Failed to save image as ") + extension + ".");
    }
  }
}

// -- from gif.hpp
// bool GifBegin(GifWriter* writer, const char* filename, uint32_t width,
//               uint32_t height, uint32_t delay, int32_t bitDepth = 8,
//               bool dither = false);
// bool GifWriteFrame(GifWriter* writer, const uint8_t* image, uint32_t width,
//                    uint32_t height, uint32_t delay, int bitDepth = 8,
//                    bool dither = false);
// bool GifEnd(GifWriter* writer);
// --

void MainWindow::on_pushButton_saveGif_pressed() { saveGif(); }

void MainWindow::saveGif() {
  QFileDialog dialog(this, tr("Save GIF"));
  dialog.setAcceptMode(QFileDialog::AcceptSave);
  dialog.setNameFilter("GIF Files (*.gif)");
  if (dialog.exec() == QDialog::Accepted) {
    QStringList selectedFiles = dialog.selectedFiles();
    QString fileName = selectedFiles.first();
    QString extension = ".gif";
    if (!fileName.endsWith(extension, Qt::CaseInsensitive)) {
      fileName += extension;
    }

    const int gifWidth = 640;
    const int gifHeight = 480;

    // Проверка на успешное создание GIF-файла
    if (!GifBegin(&gifFigure, fileName.toStdString().c_str(), gifWidth,
                  gifHeight, 0)) {
      QMessageBox::warning(this, tr("Save GIF"),
                           tr("Failed to create GIF file."));
      return;
    }

    // Устанавливаем требуемые значения трансформаций
    setScale();
    setMove();
    setRotate();
    double dRotateX = rotateX;
    double dRotateY = rotateY;
    double dRotateZ = rotateZ;
    double dMoveX = moveX;
    double dMoveY = moveY;
    double dMoveZ = moveZ;
    double dScale = scale - 1;

    // Проходим по кадрам
    for (int i = 0; i < frameCount; i++) {
      double t = static_cast<double>(i) / (frameCount - 1);
      // Применяем изменения
      processScale(1 + t * dScale);
      processMove(t * dMoveX, t * dMoveY, t * dMoveZ);
      processRotate(t * dRotateX, t * dRotateY, t * dRotateZ);

      // Создаем изображение GIF размером 640x480
      QImage image(gifWidth, gifHeight, QImage::Format_RGBA8888);
      image.fill(Qt::transparent);  // Устанавливаем фон как прозрачный

      QPainter painter(&image);
      painter.setRenderHint(QPainter::Antialiasing);
      painter.setRenderHint(QPainter::SmoothPixmapTransform);

      // Центрируем view в изображении
      QRect viewRect = view->rect();
      QRect targetRect((gifWidth - viewRect.width()) / 2,
                       (gifHeight - viewRect.height()) / 2, viewRect.width(),
                       viewRect.height());

      // Рендерим содержимое view в центр изображения
      view->render(&painter, targetRect.topLeft(), viewRect);

      // Пишем кадр в GIF
      if (!GifWriteFrame(&gifFigure, image.mirrored(false, true).bits(),
                         gifWidth, gifHeight, 10)) {
        QMessageBox::warning(this, tr("Save GIF"),
                             tr("Failed to write frame to GIF file."));
        GifEnd(&gifFigure);
        return;
      }
    }

    // Завершаем создание GIF
    GifEnd(&gifFigure);
    QMessageBox::information(this, tr("Save GIF"),
                             tr("GIF successfully saved as ") + fileName);
  }
}

}  // namespace s21
