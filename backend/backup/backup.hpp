#pragma once
#include <string>

#include "backend/calc_exec/calc_exec.hpp"

namespace BU {

void MakeBackup(const CE::Calc& to_backup, const std::string& file_path);

CE::Calc RestoreFromBackup(const std::string& file_path);

}  // namespace BU