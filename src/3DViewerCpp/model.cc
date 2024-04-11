#include "model.h"

s21::model& s21::model::getInstance() {
  static model Model;
  return Model;
}

s21::model::model() : saveImage_(s21::modelSaveImg::getInstance()) { ; }

s21::model::~model() { ; }

void s21::model::handlerParsFile(const std::string& filePatch) {
  static parsObjFile parser;
  fileName_ = parser.parsControl(filePatch, facets_, matrix_);
  matrixForGl_.resize(1, matrix_.size());
}

void s21::model::handlerAfine() {
  static afinMetod afin;
  const allSetings& temp = saveModel_.getSettings();
  afin.calculateAfine(matrix_, matrixForGl_, temp.angel, temp.bias, temp.mesh);
}

void s21::model::handlerInitSettings(
    const double angel[3], const double bias[3], const double mesh,
    const double color_v[3], const double color_e[3], const double color_p[3],
    const bool edgesFormat, const bool verticesFormat, const bool verticesPrint,
    const bool edgesPrint, const int sizeVertices, const int sizeEdges,
    const bool frum) {
  saveModel_.initBuffSettings(angel, bias, mesh, color_v, color_e, color_p,
                              edgesFormat, verticesFormat, verticesPrint,
                              edgesPrint, sizeVertices, sizeEdges, frum);
}

const s21::allSetings& s21::model::handlerGetSettings() {
  return saveModel_.getSettings();
}

void s21::model::handlerSaveSettings() { saveModel_.saveSettings(); }

void s21::model::handlerSaveImagen(QString filePath, QPixmap imagen) {
  saveImage_.saveImagen(filePath, imagen);
}

void s21::model::handlerLoadSettings() { saveModel_.loadSettings(); }

const std::string& s21::model::getFileName() { return fileName_; }

const s21::matrix<int>& s21::model::getFacets() { return facets_; }

const s21::matrix<double>& s21::model::getMatrixForGl() { return matrixForGl_; }

size_t s21::model::getCountOfVertexes() { return matrix_.getCollumns(); }

size_t s21::model::getCountOfFacets() { return facets_.getRows(); }
