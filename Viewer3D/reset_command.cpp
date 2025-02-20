#include "reset_command.hpp"

namespace s21 {
ResetCommand::ResetCommand() { m_model = nullptr; }

void ResetCommand::setModel(ObjModel *model) { m_model = model; }

void ResetCommand::execute() {
  if (m_model != nullptr) m_model->clear();
}
}  // namespace s21