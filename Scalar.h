#pragma once
#include <iostream>
#include <vector>
#include <set>
#include <string>
#include <memory>
#include <functional>

class Scalar : public std::enable_shared_from_this<Scalar>
{
	std::vector<std::shared_ptr<Scalar>> topo;
	std::set<std::shared_ptr<Scalar>> visited;

	void BuildTopo(
		std::shared_ptr<Scalar>& v,
		std::vector<std::shared_ptr<Scalar>>& topo,
		std::set<std::shared_ptr<Scalar>>& visited
	)
	{
		if (visited.find(v) == visited.end())
		{
			visited.insert(v);
			for (std::shared_ptr<Scalar> child : v->prev)
				BuildTopo(child, topo, visited);
			topo.push_back(v);
		}
	}
public:
	double data;
	double grad;
	std::function<void()> _backward;
	std::vector<std::shared_ptr<Scalar>> prev;
	std::string op;
	std::string label;

	Scalar(double _data, std::vector<std::shared_ptr<Scalar>> _prev = {}, std::string _op = "", std::string _label = "") :
		data(_data), grad(0.0), prev(_prev), op(_op), label(_label), _backward([](){}) {
	};

	static std::shared_ptr<Scalar> create(
		double _data,
		std::vector<std::shared_ptr<Scalar>> _prev = {},
		std::string _op = "",
		std::string _label = ""
	);

	void backward();
	std::shared_ptr<Scalar> tanh();
};

std::shared_ptr<Scalar> operator+(const std::shared_ptr<Scalar>& lhs, const std::shared_ptr<Scalar>& rhs);
std::shared_ptr<Scalar> operator*(const std::shared_ptr<Scalar>& lhs, const std::shared_ptr<Scalar>& rhs);

