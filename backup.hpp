#pragma once
#include "for_society.hpp"

namespace backup {

void MakeBackup(const calc_exec::Calc& to_backup, const std::string& file_path);

calc_exec::Calc RestoreFromBackup(const std::string& file_path);

}