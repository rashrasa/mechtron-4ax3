#include <iostream>
#include <stdexcept>

#include "LTI.h"

LTISystem::LTISystem(
	const Eigen::MatrixXd& A,
	const Eigen::MatrixXd& B,
	const Eigen::VectorXd& K,
	const Eigen::MatrixXd& C)
	: A(A), B(B), K(K), C(C)
{
	n = A.rows();
	m = C.rows();
	initialized = false;
}

//LTISystem::LTISystem() {}

void LTISystem::init(const Eigen::VectorXd& x0) {
	initialized = true;
	stateX = x0;
}


void LTISystem::update(const Eigen::VectorXd& u) {

	if (!initialized) throw std::runtime_error("Not initialized");

	stateX = A * stateX + B * u + K;
}


Eigen::VectorXd LTISystem::output()
{
	return(C * stateX);
};


