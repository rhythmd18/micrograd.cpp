#pragma once
#include <vector>
#include "Neuron.h"

class Layer
{
public:
	int m_input_dims;
	int m_output_dims;
	std::vector<Neuron> neurons;

	Layer(int input_dims, int output_dims) : 
		m_input_dims(input_dims), m_output_dims(output_dims)
	{
		for (int i = 0; i < output_dims; i++)
			neurons.emplace_back(input_dims);
	}

	std::vector<Scalar> operator()(const std::vector<double>& X)
	{
		std::vector<Scalar> outs(m_output_dims, 0);
		for (size_t i = 0; i < m_output_dims; i++)
			outs[i] = neurons[i](X);
		return outs;
	}
};

