#include "matrix_lite.h"
#include <iostream>

template <class T>
s21::matrix<T>::matrix() noexcept
    : collumns_(0),
      rows_(0),
      data_(nullptr) { ; }

template <class T>
s21::matrix<T>::~matrix() {
  clearData(data_, collumns_);
  rows_ = 0;
}

template <class T>
const typename s21::matrix<T>::value_m& s21::matrix<T>::operator[](const size_t x) const {
    return data_[x];
}

template <class T>
const typename s21::matrix<T>::value_m& s21::matrix<T>::operator*() const {
  return data_[0];
}

template <class T>
typename s21::matrix<T>::value_type& s21::matrix<T>::operator()(const size_t collumns, const size_t rows) {
  return data_[collumns][rows];
}

template <class T>
typename s21::matrix<T>::value_type& s21::matrix<T>::operator()(const size_t rows) {
  return data_[0][rows];
}

template <class T>
void s21::matrix<T>::resize(const size_t collumns, const size_t rows) {
  data_type temp = data_;
  data_ = nullptr;
  newData(data_, collumns, rows);
  if (temp) copyData(data_, collumns, rows, temp, collumns_, rows_);
  clearData(temp, collumns_);
  collumns_ = collumns;
  rows_ = rows;
}

template <class T>
size_t s21::matrix<T>::size() const noexcept {
  return rows_ * collumns_;
}

template <class T>
size_t s21::matrix<T>::getRows() const noexcept {
  return rows_;
}

template <class T>
size_t s21::matrix<T>::getCollumns() const noexcept {
  return collumns_;
}

template <class T>
typename s21::matrix<T>::value_type s21::matrix<T>::max() const noexcept {
  value_type result = data_[0][0];
  const size_t size_i = rows_ * collumns_;
  for (size_t i = 0; i < size_i; ++i) {
    if (data_[i / rows_][i % rows_] > result) {
      result = data_[i / rows_][i % rows_];
    }
  }
  return result;
}

template <class T>
typename s21::matrix<T>::value_type s21::matrix<T>::min() const noexcept {
  value_type result = data_[0][0];
  const size_t size_i = rows_ * collumns_;
  for (size_t i = 0; i < size_i; ++i) {
    if (data_[i / rows_][i % rows_] < result) {
      result = data_[i / rows_][i % rows_];
    }
  }
  return result;
}

template <class T>
void s21::matrix<T>::normalizationSet() {
  const value_type max_i = this->max();
  const size_t size_i = rows_ * collumns_;
  for (size_t i = 0; i < size_i; ++i)
    data_[i / rows_][i % rows_] /= max_i;
}

template <class T>
void s21::matrix<T>::clearMatrix() {
    clearData(data_, collumns_);
    collumns_ = rows_ = 0;
}


template <class T>
void s21::matrix<T>::newData(data_type& data, const size_t collumns, const size_t rows) {
  data = new value_m[collumns];
  for (size_t i = 0; i < collumns; ++i)
    data[i] = new value_type[rows];
}

template <class T>
void s21::matrix<T>::clearData(data_type& data, size_t collumns) {
  if (data) {
    while (collumns != 0) {
      collumns -= 1;
      if (data[collumns]) delete[] data[collumns];
    }
    delete[] data;
    data = nullptr;
  }
}

template <class T>
void s21::matrix<T>::copyData(data_type& data, const size_t collumns, const size_t rows, const data_type& other, const size_t otherCollumns, const size_t otherRows) {
  const size_t size_i = (rows * collumns) > (otherCollumns * otherRows) ? (otherCollumns * otherRows) : (rows * collumns);
  for (size_t i = 0; i < size_i; ++i) {
    data[i / rows][i % rows] = other[i / otherRows][i % otherRows];
  }
}

template <class T>
bool s21::matrix<T>::isEqualData(const value_m& data1, const value_m& data2) const {
  bool result = true;
  for (size_t i = 0; i < rows_ && result; ++i)
    result = data1[i] == data2[i];
  return result;
}
