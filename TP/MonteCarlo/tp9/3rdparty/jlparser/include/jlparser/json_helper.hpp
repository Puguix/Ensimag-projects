#pragma once

#include <nlohmann/json.hpp>
#include "pnl/pnl_vector.h"
#include "pnl/pnl_matrix.h"

void from_json(const nlohmann::json &j, PnlVect *&vect);
void from_json(const nlohmann::json &j, PnlMat *&mat);
void to_json(nlohmann::json &j, const PnlVect *vect);
void to_json(nlohmann::json &j, const PnlMat *mat);
