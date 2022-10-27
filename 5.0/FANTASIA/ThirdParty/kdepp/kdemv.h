#pragma once

#include <algorithm>
#include <cmath>
#include <numeric>
#include <string>
#include <vector>

#include <Eigen/Core>
#include <Eigen/Geometry>

#include "kdepp/kde.h"

namespace kdepp {

namespace kdemath {

/// @brief Calculates covariance matrix.
Eigen::MatrixXf covariance(std::vector<Eigen::VectorXf> const & data)
{
    // TODO add checks that we have data at all?
    auto dim = data.front().size();
    Eigen::VectorXf mean = Eigen::VectorXf::Zero(dim);
    for (auto i : data) {
        mean += i;
    }
    mean = mean / (1.0 * data.size());

    Eigen::MatrixXf cov = Eigen::MatrixXf::Zero(dim, dim);
    for (auto x_j : data) {
        Eigen::MatrixXf tmp((x_j - mean) * (x_j - mean).transpose());
        cov += tmp;
    }
    cov = (1.0 / (data.size() - 1)) * cov;  // should be n - 1?
    return cov;
}

}  // namespace kdemath

class Kdemv {
 public:
    Kdemv(std::vector<Eigen::VectorXf> data,
        std::string bandwidth_method = "scott")
        : data_(data)
        , h_(Eigen::MatrixXf::Zero(data_.front().size(), data.front().size()))
        , dim_(data_.front().size())
    {
        init_bandwidth(bandwidth_method);
        pre_calculate_terms();
    };

    void set_bandwidth(Eigen::MatrixXf h)
    {
        h_ = h;
        h_inv_ = h_.inverse();
        pre_calculate_terms();
    };

    double eval(Eigen::VectorXf point)
    {
        double sum = 0;
        for (auto const & i : data_) {
            sum += kernel(point - i);
        }
        double n = 1.0 * data_.size();
        return sum / n;
    };

 private:
    using index_t = std::ptrdiff_t;  // core guidelines

    double kernel(Eigen::VectorXf diff)
    {
        return pow_pi_term_ * h_pow_term_ * std::exp((-1.0/2.0) * diff.transpose() * h_inv_ * diff);
    }


    void init_bandwidth(std::string bandwidth_method)
    {
        auto cov = kdemath::covariance(data_);
        double n_term = std::pow(data_.size(), -1.0 / (dim_ + 4.0));

        if (bandwidth_method == "silverman") {
            double silverman_term = std::pow(4 / (dim_ + 2), -1.0 / (dim_ + 4.0));
            h_ = cov * (silverman_term * n_term * silverman_term * n_term);
        } else {
            // scott:
            h_ =  cov * n_term * n_term;
        }
        h_inv_ = h_.inverse();
    }

    void pre_calculate_terms()
    {
        // for optimization do some pre calcs of power constants:
        pow_pi_term_ = std::pow(2 * kdemath::pi<double>(), -1.0 * dim_/2.0);
        h_pow_term_ = std::pow(h_.determinant(), -1.0/2.0);
    }

    std::vector<Eigen::VectorXf> data_;
    Eigen::MatrixXf h_;
    Eigen::MatrixXf h_inv_;

    // number of dimensions in problem:
    double dim_;

    // Pre calculated terms for efficiency only:
    double pow_pi_term_;
    double h_pow_term_;
};

}  // namespace kdepp

