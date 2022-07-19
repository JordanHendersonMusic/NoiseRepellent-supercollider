// PluginNoiseRepellent.hpp
// Jordan Henderson (j.henderson.music@outlook.com)

#pragma once

#include "SC_PlugIn.hpp"

namespace NoiseRepellent {

class NoiseRepellent : public SCUnit {
public:
    NoiseRepellent();

    // Destructor
    // ~NoiseRepellent();

private:
    // Calc function
    void next(int nSamples);

    // Member variables
};

} // namespace NoiseRepellent
