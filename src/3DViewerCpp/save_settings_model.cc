#include <iostream>

#include "save_settings_model.h"

s21::saveSettingsModel::saveSettingsModel() { ; }

s21::saveSettingsModel::~saveSettingsModel() { ; }

void s21::saveSettingsModel::initBuffSettings(
    const double angel[3], const double bias[3], const double mesh,
    const double color_v[3], const double color_e[3], const double color_p[3],
    const bool edgesFormat, const bool verticesFormat, const bool verticesPrint,
    const bool edgesPrint, const int sizeVertices, const int sizeEdges,
    const bool frum) {
  buffSettings_.angel[0] = angel[0];
  buffSettings_.angel[1] = angel[1];
  buffSettings_.angel[2] = angel[2];
  buffSettings_.bias[0] = bias[0];
  buffSettings_.bias[1] = bias[1];
  buffSettings_.bias[2] = bias[2];
  buffSettings_.mesh = mesh;
  buffSettings_.color_v[0] = color_v[0];
  buffSettings_.color_v[1] = color_v[1];
  buffSettings_.color_v[2] = color_v[2];
  buffSettings_.color_e[0] = color_e[0];
  buffSettings_.color_e[1] = color_e[1];
  buffSettings_.color_e[2] = color_e[2];
  buffSettings_.color_p[0] = color_p[0];
  buffSettings_.color_p[1] = color_p[1];
  buffSettings_.color_p[2] = color_p[2];
  buffSettings_.edgesFormat = edgesFormat;
  buffSettings_.edgesPrint = edgesPrint;
  buffSettings_.verticesFormat = verticesFormat;
  buffSettings_.verticesPrint = verticesPrint;
  buffSettings_.sizeVertices = sizeVertices;
  buffSettings_.sizeEdges = sizeEdges;
  buffSettings_.frum = frum;
}

void s21::saveSettingsModel::saveSettings() {
  QSettings settings("settings_3D", "Conf");
  settings.setValue("X_os", buffSettings_.angel[0]);
  settings.setValue("Y_os", buffSettings_.angel[1]);
  settings.setValue("Z_os", buffSettings_.angel[2]);
  settings.setValue("X_mv", buffSettings_.bias[0]);
  settings.setValue("Y_mv", buffSettings_.bias[1]);
  settings.setValue("Z_mv", buffSettings_.bias[2]);
  settings.setValue("vertices_r", buffSettings_.color_v[0]);
  settings.setValue("vertices_g", buffSettings_.color_v[1]);
  settings.setValue("vertices_b", buffSettings_.color_v[2]);
  settings.setValue("edges_r", buffSettings_.color_e[0]);
  settings.setValue("edges_g", buffSettings_.color_e[1]);
  settings.setValue("edges_b", buffSettings_.color_e[2]);
  settings.setValue("pole_r", buffSettings_.color_p[0]);
  settings.setValue("pole_g", buffSettings_.color_p[1]);
  settings.setValue("pole_b", buffSettings_.color_p[2]);
  settings.setValue("edges_format", buffSettings_.edgesFormat);
  settings.setValue("vertices_format", buffSettings_.verticesFormat);
  settings.setValue("Mash", buffSettings_.mesh);
  settings.setValue("vertices_p", buffSettings_.verticesPrint);
  settings.setValue("edges_p", buffSettings_.edgesPrint);
  settings.setValue("size_v", buffSettings_.sizeVertices);
  settings.setValue("size_e", buffSettings_.sizeEdges);
  settings.setValue("frum", buffSettings_.frum);
}
// settings.value("X_os", 0).toInt()
void s21::saveSettingsModel::loadSettings() {
  QSettings settings("settings_3D", "Conf");
  buffSettings_.angel[0] = settings.value("X_os", 0).toDouble();
  buffSettings_.angel[1] = settings.value("Y_os", 0).toDouble();
  buffSettings_.angel[2] = settings.value("Z_os", 0).toDouble();
  buffSettings_.bias[0] = settings.value("X_mv", 0).toDouble();
  buffSettings_.bias[1] = settings.value("Y_mv", 0).toDouble();
  buffSettings_.bias[2] = settings.value("Z_mv", 0).toDouble();
  buffSettings_.color_v[0] = settings.value("vertices_r", 0).toDouble();
  buffSettings_.color_v[1] = settings.value("vertices_g", 0).toDouble();
  buffSettings_.color_v[2] = settings.value("vertices_b", 0).toDouble();
  buffSettings_.color_e[0] = settings.value("edges_r", 0).toDouble();
  buffSettings_.color_e[1] = settings.value("edges_g", 0).toDouble();
  buffSettings_.color_e[2] = settings.value("edges_b", 0).toDouble();
  buffSettings_.color_p[0] = settings.value("pole_r", 255).toDouble();
  buffSettings_.color_p[1] = settings.value("pole_g", 255).toDouble();
  buffSettings_.color_p[2] = settings.value("pole_b", 255).toDouble();
  buffSettings_.mesh = settings.value("Mash", 1).toDouble();
  buffSettings_.sizeVertices = settings.value("size_v", 1).toInt();
  buffSettings_.sizeEdges = settings.value("size_e", 1).toInt();
  buffSettings_.verticesPrint = settings.value("vertices_p", 1).toInt();
  buffSettings_.edgesPrint = settings.value("edges_p", 1).toInt();
  buffSettings_.frum = settings.value("frum", 1).toInt();
  buffSettings_.edgesFormat = settings.value("edges_format", 1).toInt();
  buffSettings_.verticesFormat = settings.value("vertices_format", 1).toInt();
}

const s21::allSetings& s21::saveSettingsModel::getSettings() {
  return buffSettings_;
}
