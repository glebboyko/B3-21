#include "backup.hpp"
#include <fstream>


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

  std::ofstream output_file(file_path, std::ofstream::out | std::ofstream::trunc);
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
  return CE::Calc();
}
