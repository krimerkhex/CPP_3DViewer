#ifndef SAVE_SETTINGS_MODEL_H
#define SAVE_SETTINGS_MODEL_H

#include <QSettings>

namespace s21 {

struct allSetings {
  double angel[3];
  double bias[3];
  double mesh = 0;
  double color_v[3];
  double color_e[3];
  double color_p[3];
  int edgesFormat;
  int verticesFormat;
  int verticesPrint;
  int edgesPrint;
  int sizeVertices;
  int sizeEdges;
  int frum;
};

class saveSettingsModel {
 public:
  saveSettingsModel();
  ~saveSettingsModel();

  saveSettingsModel(const saveSettingsModel&) = delete;
  saveSettingsModel(saveSettingsModel&&) = delete;
  saveSettingsModel& operator=(const saveSettingsModel&) = delete;
  saveSettingsModel& operator=(saveSettingsModel&&) = delete;

  void initBuffSettings(const double angel[3], const double bias[3],
                        const double mesh, const double color_v[3],
                        const double color_e[3], const double color_p[3],
                        const bool edgesFormat, const bool verticesFormat,
                        const bool verticesPrint, const bool edgesPrint,
                        const int sizeVertices, const int sizeEdges,
                        const bool frum);

  void saveSettings();
  void loadSettings();

  const allSetings& getSettings();

 private:
  allSetings buffSettings_;
};
};  // namespace s21

#endif  // SAVE_SETTINGS_MODEL_H
