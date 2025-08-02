#include "../headers/Scalar.h"

void Scalar::backward()
{
    Scalar* self = this;
    self->grad = 1;
    BuildTopo(self, topo, visited);
    for (auto iter = topo.rbegin(); iter != topo.rend(); ++iter)
        (*iter)->_backward();
}

Scalar Scalar::operator+(Scalar& other)
{
    auto out = Scalar(this->data + other.data, { this, &other }, "+");
    out._backward = [this, &other, &out]()
        {
            this->grad += out.grad;
            other.grad += out.grad;
        };
    return out;
}

Scalar Scalar::operator+(double n)
{
    auto out = Scalar(this->data + n, { this }, "+");
    out._backward = [this, &out]()
        {
            this->grad += out.grad;
        };
    return out;
}

Scalar operator+(double n, Scalar& other)
{
    auto out = Scalar(n + other.data, { &other }, "+");
    out._backward = [&other, &out]()
        {
            other.grad += out.grad;
        };
    return out;
}

Scalar Scalar::operator-(Scalar& other)
{
    auto out = Scalar(this->data - other.data, { this, &other }, "-");
    out._backward = [this, &other, &out]()
        {
            this->grad += out.grad;
            other.grad -= out.grad;
        };
    return out;
}

Scalar Scalar::operator-(double n)
{
    auto out = Scalar(this->data - n, { this }, "-");
    out._backward = [this, &out]()
        {
            this->grad += out.grad;
        };
    return out;
}

Scalar operator-(double n, Scalar& other)
{
    auto out = Scalar(n - other.data, { &other }, "-");
    out._backward = [&other, &out]()
        {
            other.grad -= out.grad;
        };
    return out;
}

Scalar Scalar::operator*(Scalar& other)
{
    auto out = Scalar(this->data * other.data, { this, &other }, "*");
    out._backward = [this, &other, &out]()
        {
            this->grad += other.data * out.grad;
            other.grad += this->data * out.grad;
        };
    return out;
}

Scalar Scalar::operator*(double n)
{
    auto out = Scalar(this->data / n, { this }, "*");
    out._backward = [this, n, &out]()
        {
            this->grad += n * out.grad;
        };
    return out;
}

Scalar operator*(double n, Scalar& other)
{;
    auto out = Scalar(n * other.data, { &other }, "*");
    out._backward = [n, &other, &out]()
        {
            other.grad += n * out.grad;
        };
    return out;
}

Scalar Scalar::operator/(Scalar& other)
{
    auto out = Scalar(this->data / other.data, { this, &other }, "/");
    out._backward = [this, &other, &out]()
        {
            this->grad += (1.0 / other.data) * out.grad;
            other.grad += (-1.0 * this->data / (other.data * other.data)) * out.grad;
        };
    return out;
}

Scalar Scalar::operator/(double n)
{
    auto out = Scalar(this->data / n, { this }, "/");
    out._backward = [this, n, &out]()
        {
            this->grad += (1 / n) * out.grad;
        };
    return out;
}

Scalar operator/(double n, Scalar& other)
{
    ;
    auto out = Scalar(n * other.data, { &other }, "/");
    out._backward = [n, &other, &out]()
        {
            other.grad += (-n / (other.data * other.data))*out.grad;
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