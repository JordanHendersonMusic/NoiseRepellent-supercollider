// PluginNoiseRepellent.cpp
// Jordan Henderson (j.henderson.music@outlook.com)

#include "SC_PlugIn.hpp"
#include "NoiseRepellent.hpp"

static InterfaceTable* ft;

namespace NoiseRepellent {

NoiseRepellent::NoiseRepellent() {
    mCalcFunc = make_calc_function<NoiseRepellent, &NoiseRepellent::next>();
    next(1);
}

void NoiseRepellent::next(int nSamples) {
    const float* input = in(0);
    const float* gain = in(1);
    float* outbuf = out(0);

    // simple gain function
    for (int i = 0; i < nSamples; ++i) {
        outbuf[i] = input[i] * gain[i];
    }
}

} // namespace NoiseRepellent

PluginLoad(NoiseRepellentUGens) {
    // Plugin magic
    ft = inTable;
    registerUnit<NoiseRepellent::NoiseRepellent>(ft, "NoiseRepellent", false);
}
