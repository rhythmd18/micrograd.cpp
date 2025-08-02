#include <iostream>
#include <vector>
#include <set>
#include <memory>
#include "../headers/Scalar.h"

int main()
{
    
    auto x1 = Scalar(2.0, {}, "", "x1");
    auto x2 = Scalar(0.0, {}, "", "x2");
    
    // Weights w1, w2
    auto w1 = Scalar(-3.0, {}, "", "w1");
    auto w2 = Scalar(1.0, {}, "", "w2");
    
    // Bias b
    auto b = Scalar(6.8813735870195432, {}, "", "b");

    auto x1w1 = x1 * w1; x1w1.label = "x1*w1";
    auto x2w2 = x2 * w2; x2w2.label = "x2*w2";
    auto x1w1x2w2 = x1w1 + x2w2; x1w1x2w2.label = "x1*w1 + x2*w2";
    auto n = x1w1x2w2 + b; n.label = "n";
    auto o = n.tanh(); o.label = "o";

    o.backward();

    std::cout << "do/dw1 = " << w1.grad << std::endl;
    std::cout << "do/dw2 = " << w2.grad << std::endl;

    std::cin.get();

    return 0;
}