#pragma once

#include <nlohmann/json.hpp>
#include "pnl/pnl_vector.h"
#include "pnl/pnl_matrix.h"

void to_json(nlohmann::ordered_json &j, PnlVect *vect);
void to_json(nlohmann::json &j, PnlVect *vect);
void from_json(const nlohmann::json &j, PnlVect *&vect);
void from_json(const nlohmann::json &j, PnlMat *&mat);
