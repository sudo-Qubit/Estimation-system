#include<iostream>
#include<cstdio>
#include<random>
#include<vector>
#include<fstream>

std::default_random_engine rand_;
std::normal_distribution<float> Normal_dis;

static std::vector<double> gps_bias_err = {0 , 0 , 0};

std::vector<double> AddNoise(const std::vector<double>& value){

  constexpr double gps_xy_noise_density = 2.0e-1;     // (m) / sqrt(hz)
  constexpr double gps_z_noise_density = 4.0e-1;      // (m) / sqrt(hz)
  constexpr double gps_xy_random_walk = 2.0;          // (m/s) / sqrt(hz)
  constexpr double gps_z_random_walk = 4.0;           // (m/s) / sqrt(hz)  

  constexpr double dt = 0.25;                         // s

  constexpr const double gps_corellation_time = 60.0; // s


  std::vector<double> noisy_value;
  std::vector<double> gps_pos_err;
  std::vector<double> gps_random_walk;

  gps_pos_err = {
      gps_xy_noise_density * sqrt(dt) * Normal_dis(rand_),
      gps_xy_noise_density * sqrt(dt) * Normal_dis(rand_),
      gps_z_noise_density  * sqrt(dt) * Normal_dis(rand_)
     };

  gps_random_walk = {
      gps_xy_random_walk * sqrt(dt) * Normal_dis(rand_),
      gps_xy_random_walk * sqrt(dt) * Normal_dis(rand_),
      gps_z_random_walk  * sqrt(dt) * Normal_dis(rand_)
    };

  gps_bias_err[0] += gps_random_walk[0] * dt * Normal_dis(rand_) - gps_bias_err[0] / gps_corellation_time;
  gps_bias_err[1] += gps_random_walk[1] * dt * Normal_dis(rand_) - gps_bias_err[1] / gps_corellation_time;
  gps_bias_err[2] += gps_random_walk[2] * dt * Normal_dis(rand_) - gps_bias_err[2] / gps_corellation_time;
  
  for (size_t i = 0; i < value.size(); ++i) {
    noisy_value.push_back(value[i] + gps_pos_err[i] + gps_bias_err[i]);
    }

return noisy_value;

}