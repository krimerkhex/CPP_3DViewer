#ifndef MATRIX_LITE_H
#define MATRIX_LITE_H

#include <iostream>
#include <memory>

namespace s21 {
template <class T>
class matrix {
 public:
  using value_type = T;
  using value_m = value_type*;
  using data_type = value_m*;

  matrix() noexcept;
  matrix(const matrix& other) = delete;
  matrix(matrix&& other) = delete;
  ~matrix();

  const matrix& operator=(matrix&& other) = delete;
  const matrix& operator=(const matrix& other) = delete;
  const value_m& operator[](const size_t x) const;
  const value_m& operator*() const;
  value_type& operator()(const size_t collumns, const size_t rows);
  value_type& operator()(const size_t rows);

  void resize(const size_t collumns, const size_t rows);

  size_t size() const noexcept;
  size_t getRows() const noexcept;
  size_t getCollumns() const noexcept;

  value_type max() const noexcept;
  value_type min() const noexcept;

  void normalizationSet();
  void clearMatrix();

 private:
  size_t collumns_;
  size_t rows_;
  data_type data_;

  void newData(data_type& data, const size_t collumns, const size_t rows);
  void clearData(data_type& data, size_t rows);
  void copyData(data_type& data, const size_t collumns, const size_t rows,
                const data_type& other, const size_t otherCollumns,
                const size_t otherRows);

  bool isEqualData(const value_m& data1, const value_m& data2) const;
};
};  // namespace s21

#include "matrix_lite.tpp"

#endif  // MATRIX_LITE_H
