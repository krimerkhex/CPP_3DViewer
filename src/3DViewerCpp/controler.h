#include "model.h"
#include "model_save_img.h"

namespace s21 {

class Controler {
 public:
  Controler(model& modelObject);
  Controler(const Controler&) = delete;
  Controler(Controler&&) = delete;
  Controler& operator=(const Controler&) = delete;
  Controler& operator=(Controler&&) = delete;
  ~Controler();

  void functionHandler(const std::string& path);
  void functionHandler(const double angel[3], const double bias[3],
                       const double mesh, const double color_v[3],
                       const double color_e[3], const double color_p[3],
                       const bool edgesFormat, const bool verticesFormat,
                       const bool verticesPrint, const bool edgesPrint,
                       const int sizeVertices, const int sizeEdges,
                       const bool frum);
  void functionHandler(QString filePath, QPixmap imagen);
  void handlerAfin();
  const s21::matrix<int>& handlerGetFacets();
  const s21::matrix<double>& handlerGetMatrixForGl();
  const std::string& handlerGetFileName();
  size_t handlerGetCount(bool vertexOrFacets);

  void handlerSaveSattings();
  void handlerLoadSettings();
  const allSetings& handlerGetSettings();

 private:
  model& modelObject_;
};
}  // namespace s21
