#include "model_pars_obj_afin.h"

#include <ctime>

std::string s21::parsObjFile::parsControl(const std::string &pathFile,
                                          s21::matrix<int> &facets,
                                          s21::matrix<double> &matrix) {
  std::string line = "";
  std::ifstream file(pathFile);
  std::string::const_iterator nameFile = pathFile.end();
  ;
  if (file.is_open()) {
    std::pair<size_t, size_t> size = firstRunFile(file);
    if (size.first && size.second) {
      matrix.resize(size.first, 3);
      facets.resize(1, size.second);
      file.close();
      file.open(pathFile);
      size_t sizeV = size.first;
      while (std::getline(file, line)) {
        if (checkLine(line, 'v')) {
          vertexCount(line, matrix, sizeV);
        } else if (checkLine(line, 'f')) {
          facetsCount(line, facets, size.second, size.first);
        }
      }
      matrix.normalizationSet();
      if (facets.size() && static_cast<int>(matrix.size()) > facets.max() &&
          facets.min() >= 0) {
        while (*nameFile != '/' && nameFile != pathFile.begin()) {
          --nameFile;
        }
        nameFile += *nameFile == '/';
      } else {
        matrix.clearMatrix();
        facets.clearMatrix();
      }
    }
  }
  file.close();
  return &(*nameFile);
}

std::pair<size_t, size_t> s21::parsObjFile::firstRunFile(std::ifstream &file) {
  size_t vertex = 0, fac = 0;
  short checkResultF = 0;
  std::string line = "";
  while (std::getline(file, line)) {
    if ((checkLine(line, 'v'))) {
      if (firstCheckLineV(line)) {
        ++vertex;
      } else {
        vertex = 0;
        fac = 0;
        break;
      }
    } else if (checkLine(line, 'f')) {
      if ((checkResultF = facetsCountNum(line))) {
        fac += checkResultF;
      } else {
        vertex = 0;
        fac = 0;
        break;
      }
    }
  }
  return std::make_pair(vertex, fac * 2);
}

void s21::parsObjFile::facetsCount(std::string &line, s21::matrix<int> &facets,
                                   size_t &sizeF, size_t &sizeV) {
  int bufStartNum = 0, num1 = 0, num2 = 0;
  auto it = line.begin(), end = line.end();
  nextNumF(end, it);
  bufStartNum = std::stoi(&(*it));
  bufStartNum += bufStartNum < 0 ? sizeV : -1;
  while (it != end) {
    num1 = std::stoi(&(*it));
    num1 += num1 < 0 ? sizeV : -1;
    nextNumF(end, it);
    if (it != end) {
      num2 = std::stoi(&(*it));
      num2 += num2 < 0 ? sizeV : -1;
      facets(facets.getRows() - sizeF) = num1;
      facets(facets.getRows() + 1 - sizeF) = num2;
      sizeF -= 2;
    }
  }
  facets(facets.getRows() - sizeF) = num1;
  facets(facets.getRows() + 1 - sizeF) = bufStartNum;
  sizeF -= 2;
}

size_t s21::parsObjFile::facetsCountNum(std::string &line) {
  size_t result = 0;
  auto it = line.begin(), end = line.end();
  nextNumF(end, it);
  while (it != end) {
    ++result;
    nextNumF(end, it);
    if (it != end && !isNum(*it) && *it != '-') {
      result = 0;
      it = end;
    }
  }
  return result;
}

void s21::parsObjFile::nextNumF(std::string::iterator &end,
                                std::string::iterator &it) {
  while (it != end && (isNum(*it) || *it == '/' || *it == '-')) {
    ++it;
  }
  while (it != end &&
         (*it == ' ' || *it == 'f' || *it == '\r' || *it == '\n')) {
    ++it;
  }
}

void s21::parsObjFile::nextNumV(std::string::iterator &end,
                                std::string::iterator &it) {
  while (it != end && (isNum(*it) || *it == '-' || *it == '.')) {
    ++it;
  }
  while (it != end &&
         (*it == ' ' || *it == 'v' || *it == '\r' || *it == '\n')) {
    ++it;
  }
}

inline bool s21::parsObjFile::checkLine(std::string &line, char ch) {
  return line.length() > 2 && line[0] == ch && line[1] == ' ';
}

bool s21::parsObjFile::firstCheckLineV(std::string &line) {
  bool valid = true;
  for (auto it : line) {
    switch (it) {
      case '-':
      case '.':
      case ' ':
      case 'v':
      case '\r':
      case '\n':
        break;
      default:
        if (!isNum(it)) {
          valid = false;
        }
        break;
    }
    if (!valid) {
      break;
    }
  }
  return valid;
}

void s21::parsObjFile::vertexCount(std::string &line,
                                   s21::matrix<double> &matrix, size_t &size) {
  size_t k = 0;
  auto it = line.begin(), end = line.end();
  nextNumV(end, it);
  while (it != end && k != 3) {
    matrix(matrix.getCollumns() - size, k) = std::stod(&(*it));
    nextNumV(end, it);
    ++k;
  }
  --size;
}

inline bool s21::parsObjFile::isNum(const char &ch) {
  return ch >= '0' && ch <= '9';
}

void s21::afinMetod::calculateAfine(s21::matrix<double> &matrix,
                                    s21::matrix<double> &vectorForGl,
                                    const double angel[3], const double bias[3],
                                    const double mash) {
  calculateBias(matrix, vectorForGl, bias, mash);
  calculateRotate(vectorForGl, angel);
}

void s21::afinMetod::calculateRotate(s21::matrix<double> &vectorForGl,
                                     const double *angel) {
  rotationByOz(vectorForGl, angel[2]);
  rotationByOy(vectorForGl, angel[1]);
  rotationByOx(vectorForGl, angel[0]);
}

void s21::afinMetod::rotationByOx(s21::matrix<double> &vectorForGl,
                                  const double &angle_i) {
  double angle = (double)angle_i * (3.14f / 180.0f);
  for (unsigned long int i = 0; i < vectorForGl.size(); i += 3) {
    double temp_y = vectorForGl(i + 1);
    double temp_z = vectorForGl(i + 2);
    vectorForGl(i + 1) = cos(angle) * temp_y - sin(angle) * temp_z;
    vectorForGl(i + 2) = sin(angle) * temp_y + cos(angle) * temp_z;
  }
}

void s21::afinMetod::rotationByOy(s21::matrix<double> &vectorForGl,
                                  const double &angle_i) {
  double angle = (double)angle_i * (3.14f / 180.0f);
  for (unsigned long int i = 0; i < vectorForGl.size(); i += 3) {
    double temp_y = vectorForGl(i);
    double temp_z = vectorForGl(i + 2);
    vectorForGl(i) = cos(angle) * temp_y - sin(angle) * temp_z;
    vectorForGl(i + 2) = sin(angle) * temp_y + cos(angle) * temp_z;
  }
}

void s21::afinMetod::rotationByOz(s21::matrix<double> &vectorForGl,
                                  const double &angle_i) {
  double angle = (double)angle_i * (3.14f / 180.0f);
  for (unsigned long int i = 0; i < vectorForGl.size(); i += 3) {
    double temp_y = vectorForGl(i);
    double temp_z = vectorForGl(i + 1);
    vectorForGl(i) = cos(angle) * temp_y - sin(angle) * temp_z;
    vectorForGl(i + 1) = sin(angle) * temp_y + cos(angle) * temp_z;
  }
}

void s21::afinMetod::calculateBias(s21::matrix<double> &matrix,
                                   s21::matrix<double> &vectorForGl,
                                   const double *bias, const double &mash) {
  for (size_t i = 0, step = 0; i < matrix.getCollumns(); ++i, step += 3) {
    vectorForGl(step) = (matrix(i, 0) + (bias[0] / 100)) * mash;
    vectorForGl(1 + step) = (matrix(i, 1) + (bias[1] / 100)) * mash;
    vectorForGl(2 + step) = (matrix(i, 2) + (bias[2] / 100)) * mash;
  }
}
