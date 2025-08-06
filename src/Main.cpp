#include <iostream>
#include <vector>
#include <set>
#include <memory>
//#include "../headers/Scalar.h"
#include "../headers/Layer.h"

int main()
{
    
    //auto x1 = Scalar(2.0, {}, "", "x1");
    //auto x2 = Scalar(0.0, {}, "", "x2");
    //
    //// Weights w1, w2
    //auto w1 = Scalar(-3.0, {}, "", "w1");
    //auto w2 = Scalar(1.0, {}, "", "w2");
    //
    //// Bias b
    //auto b = Scalar(6.8813735870195432, {}, "", "b");

    //auto x1w1 = x1 * w1; x1w1.label = "x1*w1";
    //auto x2w2 = x2 * w2; x2w2.label = "x2*w2";
    //auto x1w1x2w2 = x1w1 + x2w2; x1w1x2w2.label = "x1*w1 + x2*w2";
    //auto n = x1w1x2w2 + b; n.label = "n";
    //auto o = n.tanh(); o.label = "o";

    //auto L = o + 1;

    //o.backward();

    //std::cout << "do/dw1 = " << w1.grad << std::endl;
    //std::cout << "do/dw2 = " << w2.grad << std::endl;

    /*Scalar a(2);
    Scalar b(3);
    Scalar c = a / b;
    Scalar o = 2 + c;

    o.backward();

    std::cout << "do/do = " << o.grad << std::endl;
    std::cout << "do/dc = " << c.grad << std::endl;
    std::cout << "do/db = " << b.grad << std::endl;
    std::cout << "do/da = " << a.grad << std::endl;*/

    Layer n(2, 3);
    std::vector<double> X = { 2.0, 3.0 };
    std::vector<Scalar> outs = n(X);

    for (Scalar out : outs)
        std::cout << out.data << std::endl;

    std::cin.get();

    return 0;
}