#pragma once
#include <memory>
#include <set>
#include <string>
#include "Scalar.h"

void trace(
    const std::shared_ptr<Scalar>& root,
    std::set<std::shared_ptr<Scalar>>& nodes,
    std::set<std::pair<std::shared_ptr<Scalar>, std::shared_ptr<Scalar>>>& edges
);

void draw_dot(const std::shared_ptr<Scalar>& root, const std::string& filename = "graph");