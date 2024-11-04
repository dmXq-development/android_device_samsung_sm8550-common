/*
 * Copyright (C) 2024 The LineageOS Project
 *
 * SPDX-License-Identifier: Apache-2.0
 */

#include <fstream>

#include "GloveMode.h"

namespace vendor {
namespace lineage {
namespace touch {
namespace V1_0 {
namespace samsung {

bool GloveMode::isSupported() {
    std::ifstream file(TSP_CMD_LIST_NODE);
    if (file.is_open()) {
        std::string line;
        while (getline(file, line)) {
            if (!line.compare("glove_mode")) return true;
        }
        file.close();
    }
    return false;
}

// Methods from ::vendor::lineage::touch::V1_0::IGloveMode follow.
Return<bool> GloveMode::isEnabled() {
    std::ifstream file(TSP_CMD_RESULT_NODE);
    if (file.is_open()) {
        std::string line;
        getline(file, line);
        if (!line.compare("glove_mode,1:OK")) return true;
        file.close();
    }
    return false;
}

Return<bool> GloveMode::setEnabled(bool enabled) {
    std::ofstream file(TSP_CMD_NODE);
    file << "glove_mode," << (enabled ? "1" : "0");
    return true;
}

}  // namespace samsung
}  // namespace V1_0
}  // namespace touch
}  // namespace lineage
}  // namespace vendor
