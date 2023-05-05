#pragma once

#include <memory>
#include <string>

#include "backend/calc_exec/calc_exec.hpp"
#include "frontend/interface/definition/interface_def.hpp"

namespace IV {
class TextBlock {
 public:
  TextBlock();
  explicit TextBlock(const ID::TextBlock&);
  TextBlock(const TextBlock&) = delete;
  TextBlock(TextBlock&&) = delete;

  ~TextBlock();

  TextBlock& operator=(const TextBlock&) = delete;
  TextBlock& operator=(TextBlock&&);

  void Update(const std::string&);

 private:
};

// класс - визуализатор
class Visualization {
 public:
  // конструкторы и деструкторы
  Visualization() = delete;
  Visualization(std::shared_ptr<CE::Calc>,
                const ID::VisualisationTemplate& visualisation_template);
  Visualization(const Visualization&);
  Visualization(Visualization&&);

  ~Visualization();

  // операторы присваивания
  Visualization& operator=(const Visualization&);
  Visualization& operator=(Visualization&&);

  // интерфейс взаимодействия
  void UpdateData();

 private:
};

// функция, следящая за изменениями в калькуляторе (отдельный поток)
void Updater(std::shared_ptr<CE::Calc> calc,
             ID::VisualisationTemplate visualisation_template);

}  // namespace IV