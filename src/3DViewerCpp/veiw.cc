#include "veiw.h"

#include "./ui_veiw.h"

s21::Veiw::Veiw(s21::Controler& Control, QWidget* parent)
    : QMainWindow(parent),
      ui_(std::make_unique<Ui::Veiw>()),
      controler_(Control) {
  ui_->setupUi(this);
  setLoadParam_();
  connect(ui_->size_e, SIGNAL(valueChanged(int)), this, SLOT(getSettings_()));
  connect(ui_->size_v, SIGNAL(valueChanged(int)), this, SLOT(getSettings_()));
  connect(ui_->verticesRed, SIGNAL(valueChanged(int)), this,
          SLOT(getSettings_()));
  connect(ui_->verticesGreen, SIGNAL(valueChanged(int)), this,
          SLOT(getSettings_()));
  connect(ui_->verticesBlu, SIGNAL(valueChanged(int)), this,
          SLOT(getSettings_()));
  connect(ui_->edgesRed, SIGNAL(valueChanged(int)), this, SLOT(getSettings_()));
  connect(ui_->edgesGreen, SIGNAL(valueChanged(int)), this,
          SLOT(getSettings_()));
  connect(ui_->edgesBlu, SIGNAL(valueChanged(int)), this, SLOT(getSettings_()));
  connect(ui_->poleRed, SIGNAL(valueChanged(int)), this, SLOT(getSettings_()));
  connect(ui_->poleGreen, SIGNAL(valueChanged(int)), this,
          SLOT(getSettings_()));
  connect(ui_->poleBlue, SIGNAL(valueChanged(int)), this, SLOT(getSettings_()));
  connect(ui_->moveX, SIGNAL(valueChanged(int)), this, SLOT(getSettings_()));
  connect(ui_->moveY, SIGNAL(valueChanged(int)), this, SLOT(getSettings_()));
  connect(ui_->moveZ, SIGNAL(valueChanged(int)), this, SLOT(getSettings_()));
  connect(ui_->rotationX, SIGNAL(valueChanged(int)), this,
          SLOT(getSettings_()));
  connect(ui_->rotationY, SIGNAL(valueChanged(int)), this,
          SLOT(getSettings_()));
  connect(ui_->rotationZ, SIGNAL(valueChanged(int)), this,
          SLOT(getSettings_()));
  connect(ui_->doubleSpinBox, SIGNAL(valueChanged(double)), this,
          SLOT(getSettings_()));
  connect(ui_->verticesP, SIGNAL(clicked()), this, SLOT(getSettings_()));
  connect(ui_->edgesP, SIGNAL(clicked()), this, SLOT(getSettings_()));
  connect(ui_->ver_ci, SIGNAL(clicked()), this, SLOT(getSettings_()));
  connect(ui_->ver_qa, SIGNAL(clicked()), this, SLOT(getSettings_()));
  connect(ui_->ed_pu, SIGNAL(clicked()), this, SLOT(getSettings_()));
  connect(ui_->ed_s, SIGNAL(clicked()), this, SLOT(getSettings_()));
  connect(ui_->ortho, SIGNAL(clicked()), this, SLOT(getSettings_()));
  connect(ui_->frum, SIGNAL(clicked()), this, SLOT(getSettings_()));
  ui_->openGLWidget->setDataReferences(controler_.handlerGetSettings(),
                                controler_.handlerGetFacets(),
                                controler_.handlerGetMatrixForGl());
}

s21::Veiw::~Veiw() { controler_.handlerSaveSattings(); }

void s21::Veiw::on_selectModel_clicked() {
  std::string patch =
      QFileDialog::getOpenFileName(this, "Выбор файла", "/Users", "*.obj")
          .toStdString();
  controler_.functionHandler(patch);
  if (!controler_.handlerGetCount(false) && !patch.empty()) {
    QMessageBox::warning(
        this, "Warning",
        "Not correct model. Check the structure of the .obj file.");
  } else {
    controler_.handlerAfin();
    ui_->nameModel->setText(
        QString::fromStdString(controler_.handlerGetFileName()));
    ui_->nameModel_3->setText(
        QString::number(controler_.handlerGetCount(false) / 2));
    ui_->vertices->setText(QString::number(controler_.handlerGetCount(true)));
  }
}

void s21::Veiw::on_pushButton_clicked() {
  if (ui_->pushButton->text() == "⤃") {
    ui_->pushButton->setText("⤂");
    this->setFixedSize(1152, 872);
  } else {
    ui_->pushButton->setText("⤃");
    this->setFixedSize(811, 872);
  }
}

void s21::Veiw::on_skrin_button_clicked() {
  auto fullName = QFileDialog::getSaveFileName(0, "Coхранить как: ", "",
                                               ui_->img_format->currentText());
  if (!fullName.isEmpty()) {
    controler_.functionHandler(fullName, ui_->openGLWidget->grab());
  }
}

void s21::Veiw::getSettings_() {
  double moveBuf[3] = {static_cast<double>(ui_->moveX->value()),
                       static_cast<double>(ui_->moveY->value()),
                       static_cast<double>(ui_->moveZ->value())};
  double rotationBuf[3] = {static_cast<double>(ui_->rotationX->value()),
                           static_cast<double>(ui_->rotationY->value()),
                           static_cast<double>(ui_->rotationZ->value())};
  double color_v[3] = {static_cast<double>(ui_->verticesRed->value()),
                       static_cast<double>(ui_->verticesGreen->value()),
                       static_cast<double>(ui_->verticesBlu->value())};
  double color_e[3] = {static_cast<double>(ui_->edgesRed->value()),
                       static_cast<double>(ui_->edgesGreen->value()),
                       static_cast<double>(ui_->edgesBlu->value())};
  double color_p[3] = {static_cast<double>(ui_->poleRed->value()),
                       static_cast<double>(ui_->poleGreen->value()),
                       static_cast<double>(ui_->poleBlue->value())};
  controler_.functionHandler(
      rotationBuf, moveBuf, ui_->doubleSpinBox->value(), color_v, color_e,
      color_p, ui_->ver_qa->isChecked(), ui_->ed_s->isChecked(),
      ui_->verticesP->isChecked(), ui_->edgesP->isChecked(),
      ui_->size_v->value(), ui_->size_e->value(), ui_->frum->isChecked());
  controler_.handlerAfin();
  ui_->openGLWidget->setDataReferences(controler_.handlerGetSettings(),
                                controler_.handlerGetFacets(),
                                controler_.handlerGetMatrixForGl());
  ui_->openGLWidget->repaint();
}

void s21::Veiw::setLoadParam_() {
  controler_.handlerLoadSettings();
  s21::allSetings bufParam = controler_.handlerGetSettings();
  ui_->rotationX->setValue(bufParam.angel[0]);
  ui_->rotationY->setValue(bufParam.angel[1]);
  ui_->rotationZ->setValue(bufParam.angel[2]);
  ui_->moveX->setValue(bufParam.bias[0]);
  ui_->moveY->setValue(bufParam.bias[1]);
  ui_->moveZ->setValue(bufParam.bias[2]);
  ui_->verticesRed->setValue(bufParam.color_v[0]);
  ui_->verticesGreen->setValue(bufParam.color_v[1]);
  ui_->verticesBlu->setValue(bufParam.color_v[2]);
  ui_->edgesRed->setValue(bufParam.color_e[0]);
  ui_->edgesGreen->setValue(bufParam.color_e[1]);
  ui_->edgesBlu->setValue(bufParam.color_e[2]);
  ui_->poleRed->setValue(bufParam.color_p[0]);
  ui_->poleGreen->setValue(bufParam.color_p[1]);
  ui_->poleBlue->setValue(bufParam.color_p[2]);
  ui_->doubleSpinBox->setValue(bufParam.mesh);
  ui_->size_v->setValue(bufParam.sizeVertices);
  ui_->size_e->setValue(bufParam.sizeEdges);
  ui_->edgesP->setCheckState(bufParam.edgesPrint == true
                                 ? Qt::CheckState::Checked
                                 : Qt::CheckState::Unchecked);
  ui_->verticesP->setCheckState(bufParam.verticesPrint == true
                                    ? Qt::CheckState::Checked
                                    : Qt::CheckState::Unchecked);
  if (bufParam.edgesFormat) {
    ui_->ed_s->setChecked(true);
  } else {
    ui_->ed_pu->setChecked(true);
  }
  if (bufParam.verticesFormat) {
    ui_->ver_qa->setChecked(true);
  } else {
    ui_->ver_ci->setChecked(true);
  }
  if (bufParam.frum) {
    ui_->frum->setChecked(true);
  } else {
    ui_->ortho->setChecked(true);
  }
}
