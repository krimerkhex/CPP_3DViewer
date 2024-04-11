#include <gtest/gtest.h>

#include "../3DViewerCpp/matrix_lite.h"
#include "../3DViewerCpp/model_pars_obj_afin.h"

using namespace s21;

class S213DViewer : public testing::Test {
 protected:
  parsObjFile *parsModel;
  afinMetod *afinModel;
  void TearDown() {}
};

TEST_F(S213DViewer, cub_parser) {
  std::vector<double> vertexes_cub = {0, 0, 0, 1, 0, 0, 1, 0, 1, 0, 0, 1,
                                      0, 1, 0, 1, 1, 0, 1, 1, 1, 0, 1, 1};
  std::vector<int> facets_cub = {0, 1, 1, 2, 2, 3, 3, 0, 4, 5, 5, 6,
                                 6, 7, 7, 4, 0, 4, 4, 7, 7, 3, 3, 0,
                                 1, 2, 2, 6, 6, 5, 5, 1, 5, 4, 4, 5};
  matrix<double> vertex;
  matrix<int> facets;
  parsModel->parsControl("cube.obj", facets, vertex);
  vertex.resize(1, vertex.size());

  for (size_t it = 0; it < vertex.size(); ++it)
    EXPECT_EQ(vertex(it), vertexes_cub[it]);

  for (size_t it = 0; it < facets.size(); ++it)
    EXPECT_EQ(facets(it), facets_cub[it]);
}

TEST_F(S213DViewer, afin_cub) {
  std::vector<double> vertexes_cub = {1, 2, -1, 2, 2, -1, 2, 2, 0, 1, 2, 0,
                                      1, 3, -1, 2, 3, -1, 2, 3, 0, 1, 3, 0};
  matrix<double> vertex;
  matrix<int> facets;
  parsModel->parsControl("cube.obj", facets, vertex);
  matrix<double> vertexAfin;
  vertexAfin.resize(1, vertex.size());
  double angel[3] = {0, 0, 0}, bias[3] = {1, 2, -1};
  afinModel->calculateAfine(vertex, vertexAfin, angel, bias, 1);

  for (size_t it = 0; it < vertex.size(); ++it)
    EXPECT_EQ(vertex(it), vertexes_cub[it]);
}

int main(int argc, char **argv) {
  ::testing::InitGoogleTest(&argc, argv);
  return RUN_ALL_TESTS();
}