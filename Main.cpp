#include <iostream>
#include <vector>
#include <set>
#include <memory>
#include "Scalar.h"
#include "GraphUtils.h"

int main()
{
    
    //auto x1 = Scalar::create(2.0, {}, "", "x1");
    //auto x2 = Scalar::create(0.0, {}, "", "x2");
    //
    //// Weights w1, w2
    //auto w1 = Scalar::create(-3.0, {}, "", "w1");
    //auto w2 = Scalar::create(1.0, {}, "", "w2");
    //
    //// Bias b
    //auto b = Scalar::create(6.8813735870195432, {}, "", "b");

    //auto x1w1 = x1 * w1; x1w1->label = "x1*w1";
    //auto x2w2 = x2 * w2; x2w2->label = "x2*w2";
    //auto x1w1x2w2 = x1w1 + x2w2; x1w1x2w2->label = "x1*w1 + x2*w2";
    //auto n = x1w1x2w2 + b; n->label = "n";
    //auto o = n->tanh(); o->label = "o";

    auto a = Scalar::create(3.0, {}, "", "a");
    auto b = a + a; b->label = "b";

    b->backward();

    draw_dot(b);

    return 0;
}