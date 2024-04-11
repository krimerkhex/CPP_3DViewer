#ifndef GL_H
#define GL_H
#define GL_SILENCE_DEPRECATION

#include <QtOpenGLWidgets/QtOpenGLWidgets>

#include "controler.h"

class gl : public QOpenGLWidget {
 public:
  gl(QWidget* parent = nullptr);
  void setDataReferences(const s21::allSetings& structura,
                         const s21::matrix<int>& facets,
                         const s21::matrix<double>& matrix);

 private:
  const s21::allSetings* settings_;
  const s21::matrix<int>* facets_;
  const s21::matrix<double>* matrix_;

  void drawPoints();
  void drawLines();

 protected:
  void initializeGL() override;
  void resizeGL(int nWidth, int nHeight) override;
  void paintGL() override;
};

#endif  // GL_H
