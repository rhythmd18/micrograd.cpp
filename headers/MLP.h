#pragma once
#include <vector>
#include "Layer.h"

class MLP
{
public:
	std::vector<Layer> layers;

	MLP(int n_inputs, std::vector<int> n_outputs)
	{
		std::vector<int> dims = {n_inputs};
        dims.insert(dims.end(), n_outputs.begin(), n_outputs.end());
		for (int i = 0; i < dims.size() - 1; i++)
			layers.emplace_back(dims[i], dims[i + 1]);
	}

	std::vector<Scalar> operator()(const std::vector<double>& X)
	{
		std::vector<Scalar> out = layers[0](X);
		for (int i = 1; i < layers.size(); i++)
		{
			std::vector<double> out_d(out.size());
			for (size_t j = 0; j < out.size(); j++)
				out_d[j] = out[i].data;
			out = layers[i](out_d);
		}
		return out;
	}
};

