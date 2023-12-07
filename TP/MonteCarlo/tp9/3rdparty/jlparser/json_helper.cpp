#include <iostream>
#include <fstream>
#include <string>
#include <vector>
#include "jlparser/json_helper.hpp"

void from_json(const nlohmann::json &j, PnlVect *&vect) {
    if (j.is_number()) {
        double value = j.get<double>();
        vect = pnl_vect_create_from_double(1, value);
    } else {
        std::vector<double> stl_v = j.get<std::vector<double>>();
        vect = pnl_vect_create_from_ptr(stl_v.size(), stl_v.data());
    }
}

void to_json(nlohmann::json &j, const PnlVect *vect) {
    j = nlohmann::json::array();
    for (int i = 0; i < vect->size; i++) {
        j.push_back(GET(vect, i));
    }
}

void from_json(const nlohmann::json &j, PnlMat *&mat) {
    std::vector<std::vector<double>> stl_m = j.get<std::vector<std::vector<double>>>();
    int nLines = stl_m.size();
    if (nLines == 0) {
        mat = pnl_mat_create(0, 0);
        return;
    }
    int nColumns = stl_m[0].size();
    for (auto it : stl_m) {
        if (nColumns != it.size()) {
            std::cerr << "Matrix is not regular" << std::endl;
            mat = NULL;
            return;
        }
    }
    mat = pnl_mat_create(nLines, nColumns);
    int m = 0;
    for (auto row : stl_m) {
        pnl_mat_set_row_from_ptr(mat, row.data(), m);
        m++;
    }
}

void to_json(nlohmann::json &j, const PnlMat *mat) {
    j = nlohmann::json::array();
    for (int i = 0; i < mat->m; i++) {
        PnlVect row = pnl_vect_wrap_mat_row(mat, i);
        nlohmann::json j_row;
        to_json(j_row, &row);
        j.push_back(j_row);
    }
}