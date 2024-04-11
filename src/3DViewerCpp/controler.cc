#include "controler.h"

s21::Controler::Controler(model& modelObject) : modelObject_(modelObject) { ; }

s21::Controler::~Controler() {}

void s21::Controler::functionHandler(const std::string& path) {
  modelObject_.handlerParsFile(path);
}

void s21::Controler::functionHandler(
    const double angel[3], const double bias[3], const double mesh,
    const double color_v[3], const double color_e[3], const double color_p[3],
    const bool edgesFormat, const bool verticesFormat, const bool verticesPrint,
    const bool edgesPrint, const int sizeVertices, const int sizeEdges,
    const bool frum) {
  modelObject_.handlerInitSettings(angel, bias, mesh, color_v, color_e, color_p,
                                   edgesFormat, verticesFormat, verticesPrint,
                                   edgesPrint, sizeVertices, sizeEdges, frum);
}

void s21::Controler::handlerAfin() { modelObject_.handlerAfine(); }

const s21::allSetings& s21::Controler::handlerGetSettings() {
  return modelObject_.handlerGetSettings();
}

void s21::Controler::handlerSaveSattings() {
  modelObject_.handlerSaveSettings();
}

void s21::Controler::handlerLoadSettings() {
  modelObject_.handlerLoadSettings();
}

void s21::Controler::functionHandler(QString filePath, QPixmap imagen) {
  modelObject_.handlerSaveImagen(filePath, imagen);
}

const std::string& s21::Controler::handlerGetFileName() {
  return modelObject_.getFileName();
}

const s21::matrix<int>& s21::Controler::handlerGetFacets() {
  return modelObject_.getFacets();
}

const s21::matrix<double>& s21::Controler::handlerGetMatrixForGl() {
  return modelObject_.getMatrixForGl();
}

size_t s21::Controler::handlerGetCount(bool vertexOrFacets) {
  return vertexOrFacets ? modelObject_.getCountOfVertexes()
                        : modelObject_.getCountOfFacets();
}
