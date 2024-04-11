#ifndef VEIW_H
#define VEIW_H

#include <QMainWindow>
#include <QPushButton>
#include <memory>

#include "gl.h"

namespace Ui {
class Veiw;
}

namespace s21 {

class Veiw : public QMainWindow {
  Q_OBJECT

 public:
  Veiw(s21::Controler& Control, QWidget* parent = nullptr);
  Veiw(const Veiw&) = delete;
  Veiw(Veiw&&) = delete;
  Veiw& operator=(const Veiw&) = delete;
  Veiw& operator=(Veiw&&) = delete;
  ~Veiw();

 private slots:
  void on_selectModel_clicked();
  void on_pushButton_clicked();
  void on_skrin_button_clicked();
  void getSettings_();

 private:
  std::unique_ptr<Ui::Veiw> ui_;
  s21::Controler& controler_;

  void gif_grap_();
  double* rotationReceiving_();
  double* moveReceiving_();
  void setLoadParam_();
};
}  // namespace s21

#endif  // VEIW_H
