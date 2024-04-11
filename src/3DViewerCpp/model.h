#ifndef MODEL_H
#define MODEL_H

#include <memory>

#include "model_pars_obj_afin.h"
#include "model_save_img.h"
#include "save_settings_model.h"

namespace s21 {

class model {
 public:
  static model& getInstance();
  ~model();

  model(const model&) = delete;
  model(model&&) = delete;
  model& operator=(const model&) = delete;
  model& operator=(model&&) = delete;

  void handlerParsFile(const std::string& filePatch);
  void handlerAfine();
  void handlerInitSettings(const double angel[3], const double bias[3],
                           const double mesh, const double color_v[3],
                           const double color_e[3], const double color_p[3],
                           const bool edgesFormat, const bool verticesFormat,
                           const bool verticesPrint, const bool edgesPrint,
                           const int sizeVertices, const int sizeEdges,
                           const bool frum);
  void handlerSaveImagen(QString filePath, QPixmap imagen);
  const allSetings& handlerGetSettings();

  void handlerSaveSettings();
  void handlerLoadSettings();

  const std::string& getFileName();
  const s21::matrix<int>& getFacets();
  const s21::matrix<double>& getMatrixForGl();
  size_t getCountOfVertexes();
  size_t getCountOfFacets();

 private:
  s21::matrix<int> facets_;
  s21::matrix<double> matrix_;
  s21::matrix<double> matrixForGl_;
  s21::saveSettingsModel saveModel_;
  s21::modelSaveImg& saveImage_;
  std::string fileName_;

  model();
};
};  // namespace s21

#endif  // MODEL_H
