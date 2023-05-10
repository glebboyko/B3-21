#include "backup.hpp"

#include <fstream>
#include <string>
#include <vector>

void BU::MakeBackup(const CE::Calc& to_backup, const std::string& file_path) {
  CP::Program program = to_backup.GetProgram();
  CM::Buffer buffer = to_backup.GetRegisterBuffer();
  int button = to_backup.GetCurrFuncButton();
  int mode = to_backup.GetMode();

  std::vector<CP::OperationCodes> program_data = program.GetProgram();
  int program_step = program.GetStep();
  int program_transfer = program.GetTransferStatus();

  std::vector<CN::Number> buffer_body = buffer.GetNumeratedBuffer();
  std::vector<CN::Number> round_body = buffer.GetRoundedBuffer();

  std::ofstream output_file(file_path,
                            std::ofstream::out | std::ofstream::trunc);
  if (!output_file.is_open()) {
    std::cerr << "Не удалось открыть файл для записи." << std::endl;
    throw errno;
  }

  output_file << button << std::endl;
  output_file << mode << std::endl;

  for (size_t i = 0; i < program_data.size(); ++i) {
    output_file << program_data[i] << std::endl;
  }

  output_file << program_step << std::endl;
  output_file << program_transfer << std::endl;

  for (size_t i = 0; i < buffer_body.size(); ++i) {
    CN::Number::BackUpIng num = buffer_body[i].GetClass();
    output_file << num.sign << std::endl;
    output_file << num.number << std::endl;
    output_file << num.characteristic << std::endl;
    output_file << num.new_characteristic << std::endl;
    output_file << num.mode << std::endl;
  }

  for (size_t i = 0; i < round_body.size(); ++i) {
    CN::Number::BackUpIng num = round_body[i].GetClass();
    output_file << num.sign << std::endl;
    output_file << num.number << std::endl;
    output_file << num.characteristic << std::endl;
    output_file << num.new_characteristic << std::endl;
    output_file << num.mode << std::endl;
  }

  output_file.close();
}

CE::Calc BU::RestoreFromBackup(const std::string& file_path) {
  std::ifstream file(file_path);
  if (!file) {
    throw std::invalid_argument("Файл не открылся");
  }

  int button_cp;
  file >> button_cp;
  int mode_cp;
  file >> mode_cp;

  std::vector<int> program_data_cp(CP::kProgBufferSize);
  for (int i = 0; i < CP::kProgBufferSize; ++i) {
    file >> program_data_cp[i];
  }

  int program_step_cp;
  file >> program_step_cp;
  int program_transfer_cp;
  file >> program_transfer_cp;

  std::vector<CN::Number::BackUpIng> backUping_cp(CM::kNumeratedBuffSize);
  for (int i = 0; i < backUping_cp.size(); ++i) {
    file >> backUping_cp[i].sign;
    file >> backUping_cp[i].number;
    file >> backUping_cp[i].characteristic;
    file >> backUping_cp[i].new_characteristic;
    int mode;
    file >> mode;
    backUping_cp[i].mode = static_cast<CN::EnterMode>(mode);
  }

  std::vector<CN::Number::BackUpIng> backUping_cp_round(CM::kRoundedBuffSize);
  for (int i = 0; i < backUping_cp_round.size(); ++i) {
    file >> backUping_cp_round[i].sign;
    file >> backUping_cp_round[i].number;
    file >> backUping_cp_round[i].characteristic;
    file >> backUping_cp_round[i].new_characteristic;
    int mode;
    file >> mode;
    backUping_cp_round[i].mode = static_cast<CN::EnterMode>(mode);
  }
}
