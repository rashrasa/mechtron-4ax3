#include <iostream>
#include <fstream>
#include <stdexcept>
#include <Eigen/Dense>
#include <cmath>

// Global declarations for continuous version
static Eigen::MatrixXd cont_A(4, 4);
static Eigen::MatrixXd cont_B(4, 1);
static Eigen::MatrixXd cont_u(1, 1);
static Eigen::MatrixXd cont_x0(4, 1);

// Physical constants and initial conditions
const double g = 9.8;
const double V_0 = 35;
const double theta = (1 * 3.1415926 / 3);

// Initialize continuous A, B, u, x0 matrices and/or vectors
static void initialize(void) {
	cont_A <<
		0, 1, 0, 0, // x
		0, 0, 0, 0, // x .
		0, 0, 0, 1, // y
		0, 0, 0, 0; // y .

	cont_B << 0, 0, 0, 1;
	cont_u << -g;
	cont_x0 << 0, V_0* cos(theta), 0, V_0* sin(theta);
}

// dX/dt = AX + Bu
static Eigen::VectorXd state_update_function(double t, const Eigen::VectorXd& state, const Eigen::VectorXd& input) {
	return cont_A * state + cont_B * input;
}

// RK-4 Solver
static Eigen::VectorXd run(double t, const Eigen::VectorXd& state, const Eigen::VectorXd& input, double h) {
	Eigen::VectorXd k1, k2, k3, k4;
	k1 = state_update_function(t, state, input);
	k2 = state_update_function(t + h / 2, state + (h / 2) * k1, input);
	k3 = state_update_function(t + h / 2, state + (h / 2) * k2, input);
	k4 = state_update_function(t + h, state + h * k3, input);

	return state + h * (k1 + 2 * k2 + 2 * k3 + k4) / 6;
}

// Run and create outputs for discrete system
static void solve_lti(double h, double time) {
	Eigen::MatrixXd lti_A(4, 4);
	Eigen::MatrixXd lti_B(4, 1);
	Eigen::MatrixXd lti_x(4, 1);
	Eigen::MatrixXd lti_u(1, 1);

	lti_A <<
		1, h, 0, 0, // x
		0, 1, 0, 0, // x .
		0, 0, 1, h, // y
		0, 0, 0, 1; // y .

	lti_B << 0, 0, 0, 1;

	lti_x << 0, V_0* cos(theta), 0, V_0* sin(theta);
	lti_u << -g * h;

	double t = 0;

	Eigen::IOFormat fmt(8, 0, ", ", "\t", "", "", "", "");
	std::ofstream myfile;
	myfile.open("OUT_LTI.tsv");
	myfile << "time\tpos_x\tvel_x\tpos_y\tvel_y" << std::endl;

	// 1.0/h == number of simulations per second
	for (int i = 0; i < (time * (1.0 / h)); i++) {
		lti_x = lti_A * lti_x + lti_B * lti_u;
		myfile << t << "\t" << (lti_x).format(fmt) << std::endl;
		t += h;

	};
	myfile.close();
}

// Run and create outputs for continuous system
static void solve_cont(double h, double time) {
	Eigen::IOFormat fmt(8, 0, ", ", "\t", "", "", "", "");
	std::ofstream myfile;
	myfile.open("OUT.tsv");

	myfile << "time\tpos_x\tvel_x\tpos_y\tvel_y" << std::endl;

	int i;
	double  t;
	t = 0;
	Eigen::VectorXd x = cont_x0;

	while (t < time) {
		x = run(t, x, cont_u, h);
		myfile << t << "\t" << x.format(fmt) << std::endl;
		t = t + h;
	}
}

int main(void) {
	initialize();
	solve_cont(.01, 10.0);
	solve_lti(.01, 10.0);
}