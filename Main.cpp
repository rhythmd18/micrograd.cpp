#include <iostream>
#include <vector>
#include <set>
#include <memory>
//#include "../headers/Scalar.h"
//#include "headers/Layer.h"
#include "headers/MLP.h"

Scalar get_loss(std::vector<double>& y_true, std::vector<Scalar>& y_pred)
{
    Scalar sum = Scalar(0.0);
    int n = y_true.size();
    for (int i = 0; i < n; i++)
        sum = sum + (y_true[i] - y_pred[i]) * (y_true[i] - y_pred[i]);
    return sum / n;
}

int main()
{
    MLP model(3, { 4, 4, 1 });
    std::vector<std::vector<double>> X = {
        {2.0, 3.0, -1.0},
        {3.0, -1.0, 0.5},
        {0.5, 1.0, 1.0},
        {1.0, 1.0, -1.0}
    };
    std::vector<double> y = { 1.0, -1.0, -1.0, 1.0 };

    std::vector<Scalar> y_pred;
    for (std::vector<double> x : X)
    {
        y_pred.push_back(model(x)[0]);
    }
    Scalar loss = get_loss(y, y_pred);

    for (Scalar out : y_pred)
        std::cout << out.data << std::endl;

    std::cout << "Loss: " << loss.data << std::endl;

    loss.backward();

    std::cout << "Gradients: " << std::endl;
    for (Scalar* p : model.parameters())
        std::cout << p->grad << std::endl;

    std::cin.get();
    return 0;
}