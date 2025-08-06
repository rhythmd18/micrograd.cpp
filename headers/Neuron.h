#pragma once
#include <vector>
#include <random>
#include "Scalar.h"

class Neuron
{
    double generate_random()
    {
        static std::mt19937 gen(std::random_device{}());
        static std::uniform_real_distribution<> dist(-1, 1);
        return dist(gen);
    }
public:
	std::vector<Scalar> W;
	Scalar b;

    Neuron() : W(), b(0.0) {};

    Neuron(int n_inputs) : W(n_inputs), b(0.0)
    {
        for (int i = 0; i < n_inputs; i++)
            W[i] = generate_random();
        b = generate_random();
    }

    Scalar operator()(const std::vector<double>& X)
    {
        Scalar sum = b;
        for (size_t i = 0; i < W.size(); i++)
            sum = sum + (W[i] * X[i]);
        return sum.tanh();
    }
};
