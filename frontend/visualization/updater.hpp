#pragma once

#include <wx/stattext.h>
#include <wx/wx.h>

#include <memory>
#include <string>

#include "backend/calc_exec/calc_exec.hpp"
#include "frontend/interface/definition/interface_def.hpp"

// функция, следящая за изменениями в калькуляторе (отдельный поток)
void Updater(std::shared_ptr<CE::Calc> calc,
             ID::VisualisationTemplate visualisation_template);
