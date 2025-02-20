#ifndef SETTINGSFACADE_H
#define SETTINGSFACADE_H

#include <QColor>
#include <QString>

#include "objview.h"

namespace s21 {

class MainWindow;

/**
 * @brief Класс фасада для управления настройками.
 *
 * Этот класс предоставляет интерфейс для установки, загрузки и сохранения
 * настроек для модели и представления. Он взаимодействует с объектами типа
 * ObjView и MainWindow для управления пользовательскими настройками и их
 * сохранением.
 */
class SettingsFacade {
 public:
  /**
   * @brief Конструктор для класса SettingsFacade.
   *
   * @param view Указатель на объект представления модели (ObjView).
   * @param mainWindow Указатель на главный окно приложения (MainWindow).
   */
  SettingsFacade(ObjView* view, MainWindow* mainWindow);

  /**
   * @brief Устанавливает настройки по умолчанию.
   *
   * Этот метод устанавливает начальные значения настроек для представления
   * модели и интерфейса пользователя.
   */
  void setDefaultSettings();

  /**
   * @brief Загружает настройки из сохраненного файла.
   *
   * Этот метод загружает настройки из файла конфигурации и применяет их
   * к объекту представления модели и интерфейсу пользователя.
   */
  void loadSettings();

  /**
   * @brief Сохраняет текущие настройки в файл.
   *
   * Этот метод сохраняет текущие настройки объекта представления модели
   * и интерфейса пользователя в файл конфигурации.
   */
  void saveSettings();

 private:
  ObjView* view;  ///< Указатель на объект представления модели.
  MainWindow* mainWindow;  ///< Указатель на главный окно приложения.
};

}  // namespace s21

#endif  // SETTINGSFACADE_H
