#include "model_save_img.h"

s21::modelSaveImg::modelSaveImg() {}

s21::modelSaveImg::~modelSaveImg() {}

s21::modelSaveImg& s21::modelSaveImg::getInstance() {
  static s21::modelSaveImg modelSaveImg;
  return modelSaveImg;
}

void s21::modelSaveImg::saveImagen(QString filePath, QPixmap imagen) {
  imagen.save(filePath);
}
