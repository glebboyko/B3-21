#pragma once

#include <memory>

#include "backend/calc_exec/calc_exec.hpp"
¬ namespace IV {
  // класс - визуализатор
  class Visualization {
   public:
    // конструкторы и деструкторы
    Visualization();
    Visualization(const Visualization&);
    Visualization(Visualization&&);

    ~Visualization();

    // операторы присваивания
    Visualization& operator=(const Visualization&);
    Visualization& operator=(Visualization&&);

    // интерфейс взаимодействия
    void UpdateData(const CE::Calc& calc);

   private:
  };

  // функция, следящая за изменениями в калькуляторе (отдельный поток)
  void Updater(std::shared_ptr<CE::Calc> calc);

}  // namespace IV