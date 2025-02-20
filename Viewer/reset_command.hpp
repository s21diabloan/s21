#ifndef RESET_COMMAND_HPP
#define RESET_COMMAND_HPP

#include "objmodel.h"

namespace s21 {
/**
 * @brief Класс команды сброса модели.
 */
class ResetCommand {
 public:
  ResetCommand();
  void setModel(ObjModel* model);
  void execute();

 private:
  ObjModel* m_model;
};

}  // namespace s21
#endif  // RESET_COMMAND_HPP