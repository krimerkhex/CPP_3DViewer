#include "gl.h"
gl::gl(QWidget* parent) : QOpenGLWidget(parent) { ; }

void gl::initializeGL() { glEnable(GL_DEPTH_TEST); }

void gl::resizeGL(int nWidth, int nHeight) {
  glViewport(0, 0, nWidth, nHeight);
}

void gl::paintGL() {
  glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
  glClearColor(settings_->color_p[0] / 255.0, settings_->color_p[1] / 255.0,
               settings_->color_p[2] / 255.0, 1);
  glMatrixMode(GL_PROJECTION);
  glLoadIdentity();

  if (!settings_->frum) {
    glOrtho(-1.5, 1.5, -1.5, 1.5, -2, 1000);
  } else {
    glFrustum(-1.5, 1.5, -1.5, 1.5, 0.8, 1000);
    glTranslatef(0, 0, -2);
  }
  if (matrix_->size() && facets_->size()) {
    glEnableClientState(GL_VERTEX_ARRAY);
    if (settings_->verticesPrint) drawPoints();
    if (settings_->edgesPrint) drawLines();
    glDisableClientState(GL_VERTEX_ARRAY);
  }
}

void gl::drawPoints() {
  if (settings_->edgesFormat) {
    glEnable(GL_POINT_SMOOTH);
  }
  glPointSize(settings_->sizeEdges);
  glColor3f(settings_->color_e[0] / 255.0, settings_->color_e[1] / 255.0,
            settings_->color_e[2] / 255.0);
  glVertexPointer(3, GL_DOUBLE, 0, **matrix_);
  glDrawElements(GL_POINTS, facets_->size(), GL_UNSIGNED_INT, **facets_);
  if (settings_->edgesFormat) {
    glDisable(GL_POINT_SMOOTH);
  }
}

void gl::drawLines() {
  if (!settings_->verticesFormat) {
    glEnable(GL_LINE_STIPPLE);
  }
  glLineWidth(settings_->sizeVertices);
  glColor3f(settings_->color_v[0] / 255.0, settings_->color_v[1] / 255.0,
            settings_->color_v[2] / 255.0);
  glLineStipple(2, 0X00FF);
  glDrawElements(GL_LINES, facets_->size(), GL_UNSIGNED_INT, **facets_);
  if (!settings_->verticesFormat) {
    glDisable(GL_LINE_STIPPLE);
  }
}

void gl::setDataReferences(const s21::allSetings& structura,
                           const s21::matrix<int>& facets,
                           const s21::matrix<double>& matrix) {
  settings_ = &structura;
  facets_ = &facets;
  matrix_ = &matrix;
}
