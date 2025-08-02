#pragma once
#include <iostream>
#include <vector>
#include <set>
#include <string>
#include <memory>
#include <functional>

class Scalar
{
    std::vector<Scalar*> topo;
    std::set<Scalar*> visited;

    void BuildTopo(
        Scalar* v,
        std::vector<Scalar*>& topo,
        std::set<Scalar*>& visited
    )
    {
        if (visited.find(v) == visited.end())
        {
            visited.insert(v);
            for (Scalar* child : v->prev)
                BuildTopo(child, topo, visited);
            topo.push_back(v);
        }
    }
public:
    double data;
    double grad;
    std::function<void()> _backward;
    std::vector<Scalar*> prev;
    std::string op;
    std::string label;

    Scalar(double _data, std::vector<Scalar*> _prev = {}, std::string _op = "", std::string _label = "") :
        data(_data), grad(0.0), prev(_prev), op(_op), label(_label), _backward([](){}) {
    }

    void backward();
    Scalar tanh();
};

Scalar operator+(Scalar& lhs, Scalar& rhs);
Scalar operator*(Scalar& lhs, Scalar& rhs);