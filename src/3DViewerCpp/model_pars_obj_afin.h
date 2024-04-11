#ifndef MODEL_PARS_OBJ_AFIN_H
#define MODEL_PARS_OBJ_AFIN_H

#include <math.h>

#include <fstream>
#include <string>

#include "matrix_lite.h"

namespace s21 {

class parsObjFile {
 public:
  std::string parsControl(const std::string &pathFile, s21::matrix<int> &facets,
                          s21::matrix<double> &matrix);

 private:
  std::pair<size_t, size_t> firstRunFile(std::ifstream &file);
  void facetsCount(std::string &line, s21::matrix<int> &facets, size_t &sizeV,
                   size_t &sizeF);
  size_t facetsCountNum(std::string &line);
  void nextNumF(std::string::iterator &end, std::string::iterator &i);
  void nextNumV(std::string::iterator &end, std::string::iterator &i);
  inline bool checkLine(std::string &line, char ch);
  bool firstCheckLineV(std::string &line);
  void vertexCount(std::string &line, s21::matrix<double> &matrix,
                   size_t &size);
  inline bool isNum(const char &ch);
};

class afinMetod {
 public:
  void calculateAfine(s21::matrix<double> &matrix,
                      s21::matrix<double> &vectorForGl, const double angel[3],
                      const double bias[3], const double mash);

 private:
  void calculateRotate(s21::matrix<double> &vectorForGl, const double *angel);
  void calculateBias(s21::matrix<double> &matrix,
                     s21::matrix<double> &vectorForGl, const double *bias,
                     const double &mash);
  void rotationByOx(s21::matrix<double> &vectorForGl, const double &angle_i);
  void rotationByOy(s21::matrix<double> &vectorForGl, const double &angle_i);
  void rotationByOz(s21::matrix<double> &vectorForGl, const double &angle_i);
};
};  // namespace s21

#endif  // MODEL_PARS_OBJ_AFIN_H
