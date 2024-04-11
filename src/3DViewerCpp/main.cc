#include <QApplication>

#include "veiw.h"

int main(int argc, char* argv[]) {
  QApplication a(argc, argv);
  s21::model& model = s21::model::getInstance();
  s21::Controler control(model);
  s21::Veiw w(control);
  w.show();
  return a.exec();
}
