#ifndef MATRIX_MATRIX_SPARSE_H_
#define MATRIX_MATRIX_SPARSE_H_

#include "matrix.h"

namespace pogs {

typedef int POGS_INT;

template <typename T>
class MatrixSparse : public Matrix<T> {
 public:
  int _sharedA;
  int _me;
  int _wDev;
  int _datatype;
  
 public:
  T *_data;
  T *_datay;
  T *_vdata;
  T *_vdatay;
  T * _de;
  enum Ord {ROW, COL};

 private:
  
  POGS_INT *_ptr, *_ind, _nnz;

  Ord _ord;

  // Get rid of assignment operator.
  MatrixSparse<T>& operator=(const MatrixSparse<T>& A);

 public:
  MatrixSparse(int wDev, char ord, POGS_INT m, POGS_INT n, POGS_INT nnz, const T *data,
      const POGS_INT *ptr, const POGS_INT *ind);
  MatrixSparse(char ord, POGS_INT m, POGS_INT n, POGS_INT nnz, const T *data,
      const POGS_INT *ptr, const POGS_INT *ind);
  MatrixSparse(int wDev, const MatrixSparse<T>& A);
  MatrixSparse(const MatrixSparse<T>& A);
  ~MatrixSparse();

  // Call this before any other method.
  int Init();

  // Method to equilibrate.
  int Equil(bool equillocal);

  // Method to multiply by A and A^T.
  int Mul(char trans, T alpha, const T *x, T beta, T *y) const;
  int Mulvalid(char trans, T alpha, const T *x, T beta, T *y) const;

  // Getters
  const T* Data() const { return _data; }
  const T* Datay() const { return _datay; }
  const T* vData() const { return _vdata; }
  const T* vDatay() const { return _vdatay; }
  const POGS_INT* Ptr() const { return _ptr; }
  const POGS_INT* Ind() const { return _ind; }
  POGS_INT Nnz() const { return _nnz; }
  Ord Order() const { return _ord; }
  int GetsharedA() const { return _sharedA; }
  int wDev() const { return _wDev; }
  int Getme() const { return _me; }
  int Datatype() const { return _datatype; }
};

}  // namespace pogs

#endif  // MATRIX_MATRIX_SPARSE_H_

