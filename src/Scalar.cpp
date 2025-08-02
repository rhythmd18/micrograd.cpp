#include "../headers/Scalar.h"

void Scalar::backward()
{
    Scalar* self = this;
    self->grad = 1;
    BuildTopo(self, topo, visited);
    for (auto iter = topo.rbegin(); iter != topo.rend(); ++iter)
        (*iter)->_backward();
}

Scalar operator+(
    Scalar& lhs,
    Scalar& rhs
    )
{
    auto out = Scalar(lhs.data + rhs.data, { &lhs, &rhs }, "+");
    out._backward = [&lhs, &rhs, &out]()
        {
            lhs.grad += 1.0 * out.grad;
            rhs.grad += 1.0 * out.grad;
        };
    return out;
}

Scalar operator*(
    Scalar& lhs,
    Scalar& rhs
    )
{
    auto out = Scalar(lhs.data * rhs.data, { &lhs, &rhs }, "*");
    out._backward = [&lhs, &rhs, &out]()
        {
            lhs.grad += rhs.data * out.grad;
            rhs.grad += lhs.data * out.grad;
        };
    return out;
}

Scalar Scalar::tanh()
{
    double x = this->data;
    double t = (std::exp(2 * x) - 1) / (std::exp(2 * x) + 1);
    auto out = Scalar(t, { this }, "tanh");
    out._backward = [self = this, t, &out]()
        {
            self->grad += (1 - std::pow(t, 2)) * out.grad;
        };
    return out;
}