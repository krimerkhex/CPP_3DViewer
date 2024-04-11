#ifndef MODELSAVEIMG_H
#define MODELSAVEIMG_H
#include <QGraphicsPixmapItem>

namespace s21 {

class modelSaveImg {
 public:
  static modelSaveImg& getInstance();
  ~modelSaveImg();
  modelSaveImg(const modelSaveImg&) = delete;
  modelSaveImg(modelSaveImg&&) = delete;
  modelSaveImg& operator=(const modelSaveImg&) = delete;
  modelSaveImg& operator=(modelSaveImg&&) = delete;
  void saveImagen(QString filePath, QPixmap imagen);

 private:
  modelSaveImg();
};

};  // namespace s21

#endif  // MODELSAVEIMG_H
