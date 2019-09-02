#include <iostream>
#include <eigen3/Eigen/Eigen>
#include <sophus/so3.h>

int main() {
    // Step0: RANSAC
    int N = 100; // frame number;
    double fx = 1;
    double fy = 1;
    double cx = 1;
    double cy = 1;
    std::vector<Eigen::Matrix3d> Rcw(N);
    std::vector<Eigen::Vector3d> tcw(N);
    std::vector<Eigen::Vector2d> uv(N);
    Eigen::Matrix3d K = Eigen::Matrix3d::Zero();
    K << fx, 0, cx,
         0, fy, cy,
         0, 0, 1;

    int numIter = 1000;
    for (int iter = 0; iter < numIter; ++iter) {
        int i = rand() % numIter;
        int j = rand() % numIter;
        while (i == j) {
            j = rand() % numIter;
        }

        // Step1: 建立系数矩阵A的后一项
        Eigen::Matrix<double, 3, 4> T1 = Eigen::Matrix<double, 3, 4>::Zero();
        T1.topLeftCorner(3, 3) = Rcw[i];
        T1.col(3) = tcw[i];
        T1 = K * T1;
        Eigen::Matrix<double, 3, 4> T2 = Eigen::Matrix<double, 3, 4>::Zero();
        T2.topLeftCorner(3, 3) = Rcw[j];
        T2.col(3) = tcw[j];
        T2 = K * T2;
        Eigen::Matrix<double, 6, 4> T3 = Eigen::Matrix<double, 6, 4>::Zero();
        T3.topRows(3) = T1;
        T3.bottomRows(3) = T2;

        // Step2: 建立系数矩阵的前一项
        Eigen::Matrix<double, 4, 6> B = Eigen::Matrix<double, 4, 6>::Zero();
        auto p1 = uv[i];
        auto p2 = uv[j];
        Eigen::Matrix3d p1Hat = Sophus::SO3::hat(Eigen::Vector3d(p1.x(), p1.y(), 1));
        Eigen::Matrix3d p2Hat = Sophus::SO3::hat(Eigen::Vector3d(p2.x(), p2.y(), 1));
        B.topLeftCorner(2,3) = p1Hat.topRows(2);
        B.bottomRightCorner(2,3) = p2Hat.topRows(2);
        Eigen::Matrix<double, 4, 4> A = B * T3;

        // Step3: SVD分解系数矩阵，求出mapPoint坐标
        Eigen::JacobiSVD<Eigen::Matrix<double, 4, 4>> svd(A, Eigen::ComputeFullV | Eigen::ComputeFullU);
        Eigen::Matrix<double, 4, 4> V = svd.matrixV();
        Eigen::Matrix<double, 4, 1> pt = V.col(3);
        Eigen::Vector3d mp = (pt/pt[3]).topRows(3);   //　只取前三维，第四维是补充的齐次坐标，一定为1

        // Step4: 验证所求mappoint的质量
        int num = 0;
        for (int i = 0; i < N; ++i) {
            Eigen::Matrix3d R = Rcw[i];
            Eigen::Vector3d t = tcw[i];
            Eigen::Vector3d Xc = R * mp + t;
            Xc /= Xc.z();
            Eigen::Vector3d UV = K * Xc;
            if ((UV.topRows(2) - uv[i]).norm() < 10) {  // 重投影误差小于10个像素
                num++;
            }
        }

        if (num > numIter * 0.5) {
            std::cout << "answer is " << mp << std::endl;
            break;
        }
    }

    // Step6: 这里还可以做一个BA，把camera pose fix住，用ceres实现

}