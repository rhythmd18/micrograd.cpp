#include "Scalar.h"

std::shared_ptr<Scalar> Scalar::create(
    double _data,
    std::vector<std::shared_ptr<Scalar>> _prev,
    std::string _op,
    std::string _label
)
{
    return std::make_shared<Scalar>(_data, _prev, _op, _label);
}

void Scalar::backward()
{
    std::shared_ptr<Scalar> self = shared_from_this();
    self->grad = 1;
    BuildTopo(self, topo, visited);
    for (auto iter = topo.rbegin(); iter != topo.rend(); ++iter)
        (*iter)->_backward();
}

std::shared_ptr<Scalar> operator+(
    const std::shared_ptr<Scalar>& lhs, 
    const std::shared_ptr<Scalar>& rhs
) 
{
    auto out = Scalar::create(lhs->data + rhs->data, {lhs, rhs}, "+");
    out->_backward = [lhs, rhs, out]()
        {
            lhs->grad += 1.0 * out->grad;
            rhs->grad += 1.0 * out->grad;
        };
    return out;
}

std::shared_ptr<Scalar> operator*(
    const std::shared_ptr<Scalar>& lhs, 
    const std::shared_ptr<Scalar>& rhs
) 
{
    auto out = Scalar::create(lhs->data * rhs->data, {lhs, rhs}, "*");
    out->_backward = [lhs, rhs, out]()
        {
            lhs->grad += rhs->data * out->grad;
            rhs->grad += lhs->data * out->grad;
        };
    return out;
}

std::shared_ptr<Scalar> Scalar::tanh()
{
    double x = this->data;
    double t = (std::exp(2 * x) - 1) / (std::exp(2 * x) + 1);
    auto out = Scalar::create(t, { shared_from_this() }, "tanh");
    out->_backward = [self = shared_from_this(), t, out]()
        {
            self->grad += (1 - std::pow(t, 2)) * out->grad;
        };
    return out;
}