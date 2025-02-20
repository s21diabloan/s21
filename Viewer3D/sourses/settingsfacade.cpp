#include "settingsfacade.h"

#include <QSettings>

#include "mainwindow.h"
#include "ui_mainwindow.h"

namespace s21 {

SettingsFacade::SettingsFacade(ObjView* view, MainWindow* mainWindow)
    : view(view), mainWindow(mainWindow) {}

void SettingsFacade::setDefaultSettings() {
  if (view) {
    view->setPrimitiveMode("Lines");
    view->setProjectionMode("Parallel");
    view->setLineMode("Solid");
    view->setVertexMode("Empty");

    view->setLineThickness(1);
    view->setVertexSize(1);

    view->setEdgeColor(QColor(0, 0, 255));
    view->setVertexColor(QColor(255, 0, 0));
    view->setBackgroundColor(QColor(200, 200, 200));

    // Получаем доступ к интерфейсу через метод getUI()
    Ui::MainWindow* ui = mainWindow->getUI();
    if (ui) {
      ui->comboBox_PrimitiveMode->setCurrentText(view->getPrimitiveMode());
      ui->comboBox_ProjectionMode->setCurrentText(view->getProjectionMode());
      ui->comboBox_lineMode->setCurrentText(view->getLineMode());
      ui->comboBox_vertexMode->setCurrentText(view->getVertexMode());
      ui->lineEdit_lineSize->setText(QString::number(view->getLineThickness()));
      ui->horizontal_lineSize->setValue(view->getLineThickness());
      ui->lineEdit_vertexSize->setText(QString::number(view->getVertexSize()));
      ui->horizontalSlider_vertexSize->setValue(view->getVertexSize());
    }
  }
}

void SettingsFacade::loadSettings() {
  QSettings settings("3DApp", "3DViewer");

  view->setPrimitiveMode(settings.value("primitiveMode", "Lines").toString());
  view->setProjectionMode(
      settings.value("projectionMode", "Parallel").toString());
  view->setLineMode(settings.value("lineMode", "Solid").toString());
  view->setVertexMode(settings.value("vertexMode", "Empty").toString());
  view->setLineThickness(settings.value("lineThickness", 1).toInt());
  view->setVertexSize(settings.value("vertexSize", 1).toInt());
  view->setEdgeColor(
      settings.value("edgeColor", QColor(0, 0, 255)).value<QColor>());
  view->setVertexColor(
      settings.value("vertexColor", QColor(255, 0, 0)).value<QColor>());
  view->setBackgroundColor(
      settings.value("backgroundColor", QColor(200, 200, 200)).value<QColor>());

  if (mainWindow) {
    Ui::MainWindow* ui = mainWindow->getUI();
    ui->comboBox_PrimitiveMode->setCurrentText(view->getPrimitiveMode());
    ui->comboBox_ProjectionMode->setCurrentText(view->getProjectionMode());
    ui->comboBox_lineMode->setCurrentText(view->getLineMode());
    ui->comboBox_vertexMode->setCurrentText(view->getVertexMode());
    ui->lineEdit_lineSize->setText(QString::number(view->getLineThickness()));
    ui->horizontal_lineSize->setValue(view->getLineThickness());
    ui->lineEdit_vertexSize->setText(QString::number(view->getVertexSize()));
    ui->horizontalSlider_vertexSize->setValue(view->getVertexSize());
  }
}

void SettingsFacade::saveSettings() {
  QSettings settings("3DApp", "3DViewer");

  settings.setValue("primitiveMode", view->getPrimitiveMode());
  settings.setValue("projectionMode", view->getProjectionMode());
  settings.setValue("lineMode", view->getLineMode());
  settings.setValue("vertexMode", view->getVertexMode());
  settings.setValue("lineThickness", view->getLineThickness());
  settings.setValue("vertexSize", view->getVertexSize());
  settings.setValue("edgeColor", view->getEdgeColor());
  settings.setValue("vertexColor", view->getVertexColor());
  settings.setValue("backgroundColor", view->getBackgroundColor());
}

}  // namespace s21
