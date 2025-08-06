#pragma once
#include <vector>
#include "Neuron.h"

class Layer
{
public:
	std::vector<Neuron> neurons;

	Layer(int n_inputs, int n_outputs)
	{
		for (int i = 0; i < n_outputs; i++)
			neurons.emplace_back(n_inputs);
	}

	std::vector<Scalar> operator()(const std::vector<double>& X)
	{
		std::vector<Scalar> outs(neurons.size());
		for (size_t i = 0; i < neurons.size(); i++)
			outs[i] = neurons[i](X);
		return outs;
	}
};

