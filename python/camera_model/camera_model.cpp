#include "camera-models/CameraModelBase.h"
#include <pybind11/eigen.h>
#include <pybind11/numpy.h>
#include <pybind11/pybind11.h>
#include <pybind11/stl.h>
#include <utility>
namespace camera_models {
template <typename T>
std::pair<Eigen::Matrix<int, Eigen::Dynamic, 1>,
          Eigen::Matrix<T, Eigen::Dynamic, 2>>
Fisheye624UndistortPoints(
    const Eigen::Matrix<T, Eigen::Dynamic, 2> &distorted_pts,
    const Eigen::Matrix<T, 2, 1> &fc, const Eigen::Matrix<T, 2, 1> &cc,
    const Eigen::Matrix<T, 12, 1> &kc,
    const Eigen::Matrix<T, 2, 1> &new_fc = {1, 1},
    const Eigen::Matrix<T, 2, 1> &new_cc = {0, 0}) {
  Eigen::Matrix<T, Eigen::Dynamic, Eigen::Dynamic> undistorted_pts;
  undistorted_pts.resize(distorted_pts.rows(), 2);
  Eigen::MatrixXi flags;
  flags.resize(distorted_pts.rows(), 1);
  for (long i = 0; i < distorted_pts.rows(); i++) {
    Eigen::Matrix<T, 2, 1> undistorted_pt = Eigen::Matrix<T, 2, 1>::Zero();
    bool flag = CameraModelFisheye624<T>::StaticUndistort(
        distorted_pts.row(i).transpose(), fc, cc, kc, undistorted_pt);
    undistorted_pts.row(i) =
        (undistorted_pt.array() * new_fc.array() + new_cc.array()).transpose();
    flags(i) = static_cast<int>(flag);
  }
  return std::make_pair(flags, undistorted_pts);
}
template <typename T>
Eigen::Matrix<T, Eigen::Dynamic, 2> Fisheye624distortPoints(
    const Eigen::Matrix<T, Eigen::Dynamic, 2> &undistorted_pts,
    const Eigen::Matrix<T, 2, 1> &fc, const Eigen::Matrix<T, 2, 1> &cc,
    const Eigen::Matrix<T, 12, 1> &kc) {
  Eigen::Matrix<T, Eigen::Dynamic, Eigen::Dynamic> distorted_pts;
  distorted_pts.resize(undistorted_pts.rows(), 2);
  for (long i = 0; i < undistorted_pts.rows(); i++) {
    Eigen::Matrix<T, 2, 1> distorted_pt = Eigen::Matrix<T, 2, 1>::Zero();
    CameraModelFisheye624<T>::StaticDistort(undistorted_pts.row(i).transpose(),
                                            fc, cc, kc, distorted_pt);
    distorted_pts.row(i) = distorted_pt.transpose();
  }
  return distorted_pts;
}
namespace py = pybind11;
PYBIND11_MODULE(_pycamera_model, m) {
  m.doc() = "xreal camera models";
  m.def("Fisheye624UndistortPoints", &Fisheye624UndistortPoints<float>,
        py::arg("distorted_pts"), py::arg("fc"), py::arg("cc"), py::arg("kc"),
        py::arg("new_fc")=Eigen::Vector2f::Ones(), py::arg("new_cc")=Eigen::Vector2f::Zero());
  m.def("Fisheye624UndistortPoints", &Fisheye624UndistortPoints<double>,
        py::arg("distorted_pts"), py::arg("fc"), py::arg("cc"), py::arg("kc"),
        py::arg("new_fc")=Eigen::Vector2d::Ones(), py::arg("new_cc")=Eigen::Vector2d::Zero());
  m.def("Fisheye624distortPoints", &Fisheye624distortPoints<float>,
        py::arg("undistorted_pts"), py::arg("fc"), py::arg("cc"),
        py::arg("kc"));
  m.def("Fisheye624distortPoints", &Fisheye624distortPoints<double>,
        py::arg("undistorted_pts"), py::arg("fc"), py::arg("cc"),
        py::arg("kc"));
}

} // namespace camera_models