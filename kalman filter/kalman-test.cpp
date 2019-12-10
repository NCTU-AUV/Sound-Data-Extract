#include <iostream>
#include <iomanip>
#include <fstream>
#include <vector>
#include <Eigen/Dense>

#include "kalman.hpp"

const char* in_filename = "/mnt/f/auv/data/fourth/data/measurements_30l_N.txt";
const char* out_filename = "/mnt/f/auv/data/fourth/data/N_30l_kalman_output.txt";

int main(int argc, char* argv[]) {

	int n = 1; // Number of states  // origin: 3    // in AUV sound detect, there is only one state, sound amplitude
	int m = 1; // Number of measurements  
	
	double dt = 1.0/1000; // Time step
	
	Eigen::MatrixXd A(n, n); // System dynamics matrix
	Eigen::MatrixXd C(m, n); // Output matrix
	Eigen::MatrixXd Q(n, n); // Process noise covariance
	Eigen::MatrixXd R(m, m); // Measurement noise covariance
	Eigen::MatrixXd P(n, n); // Estimate error covariance
	
	// Discrete LTI projectile motion, measuring position only
	//A << 1, dt, 0, 0, 1, dt, 0, 0, 1;
	//C << 1, 0, 0;
	A << 1;
	C << 1;
	// Reasonable covariance matrices

	/*Q << .05, .05, .0, .05, .05, .0, .0, .0, .0;
	R << 5;
	P << .1, .1, .1, .1, 10000, 10, .1, 10, 100;*/
	
	Q << 0.05;
	R << 3;
	P << 0.01;
	
	std::cout << "A: \n" << A << std::endl;
	std::cout << "C: \n" << C << std::endl;
	std::cout << "Q: \n" << Q << std::endl;
	std::cout << "R: \n" << R << std::endl;
	std::cout << "P: \n" << P << std::endl;
	
	// Construct the filter
	KalmanFilter kf(dt, A, C, Q, R, P);
	
	// Read input file and output file
	std::ifstream file_in;
	std::ofstream file_out(out_filename);
	file_in.open(in_filename);
	
	if(!file_in){
		std::cout << "Unable to open file.\n";
		exit(-1);
	}
	
	// raw data we get from the mic
	// List of noisy position measurements (y)
	std::vector<double> measurements;
	double in;
	while(file_in >> in)
		measurements.push_back(in);
	
	file_in.close();
	
	// Best guess of initial states
	Eigen::VectorXd x0(n);
	//x0 << measurements[0], 0, -9.81;
	x0 << measurements[0];
	kf.init(dt, x0);
	
	// Feed measurements into filter, output estimated states
	double t = 0;
	Eigen::VectorXd y(m);
	
	printf("--------------------------------------------------------------------------------\n");
	printf("|   Time      |  Measurements Info   |     Estimaed States                     |\n");
	printf("|-------------|----------------------|------------------------------------------\n");
	printf("| t = %-6.4f  |                      |  x_hat[ 0   ] = ", t);
	std::cout << std::fixed << std::setprecision(4) << kf.state().transpose() << "  |\n"; 
	
	for(int i = 0; i < measurements.size(); i++) {
		t += dt;
		y << measurements[i];
		kf.update(y);
		printf("| t = %-6.4f  |  y[ %-4d] = %-9.4f ", t, i, y.transpose()[0]);
		printf("  |  x_hat[ %-4d] = ", i);
		std::cout << std::fixed << std::setprecision(4) << kf.state().transpose() << "  |\n";
		
		file_out << y.transpose()[0] << " " << kf.state().transpose() << '\n';
	}

	file_out.close();
	
	return 0;
}
