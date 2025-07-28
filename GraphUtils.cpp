#include "GraphUtils.h"
#include <fstream>
#include <cstdlib>
#include <iostream>

void trace(
    const std::shared_ptr<Scalar>& root,
    std::set<std::shared_ptr<Scalar>>& nodes,
    std::set<std::pair<std::shared_ptr<Scalar>, std::shared_ptr<Scalar>>>& edges
) {
    if (nodes.find(root) == nodes.end()) {
        nodes.insert(root);
        for (auto& child : root->prev) {
            edges.insert({ child, root });
            trace(child, nodes, edges);
        }
    }
}

void draw_dot(const std::shared_ptr<Scalar>& root, const std::string& filename) {
    std::string dotFilename = filename + ".dot";
    std::string pngFilename = filename + ".png";

    std::ofstream file(dotFilename);
    file << "digraph G {\n";
    file << "  rankdir=LR;\n";

    std::set<std::shared_ptr<Scalar>> nodes;
    std::set<std::pair<std::shared_ptr<Scalar>, std::shared_ptr<Scalar>>> edges;

    trace(root, nodes, edges);

    for (const auto& n : nodes) {
        std::string uid = std::to_string(reinterpret_cast<uintptr_t>(n.get()));
        file << "  \"" << uid << "\" [label=\"{"
            << n->label << " | data " << n->data << " | grad " << n->grad << "}\" shape=record];\n";

        if (!n->op.empty()) {
            std::string op_node = uid + n->op;
            file << "  \"" << op_node << "\" [label=\"" << n->op << "\"];\n";
            file << "  \"" << op_node << "\" -> \"" << uid << "\";\n";
        }
    }

    for (const auto& edge : edges) {
        std::shared_ptr<Scalar> n1 = edge.first;
        std::shared_ptr<Scalar> n2 = edge.second;
        std::string from = std::to_string(reinterpret_cast<uintptr_t>(n1.get()));
        std::string to_op = std::to_string(reinterpret_cast<uintptr_t>(n2.get())) + n2->op;
        file << "  \"" << from << "\" -> \"" << to_op << "\";\n";
    }

    file << "}\n";
    file.close();

    std::string command = "dot -Tpng " + dotFilename + " -o " + pngFilename;
    int result = system(command.c_str());
    if (result)
    {
        std::cerr << "Failed to generate png." << std::endl;
    }
}