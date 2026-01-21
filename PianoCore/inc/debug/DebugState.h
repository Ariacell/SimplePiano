#pragma once
#include <vector>

namespace Debug {
struct DebugLayerMainWindowData {
    bool isWireframeRenderingEnabled;
    std::vector<float> frameTimeData;
    DebugLayerMainWindowData() {
        isWireframeRenderingEnabled = false;
    }
};
struct DebugState {
    DebugLayerMainWindowData mainDebugWindowData;
};
}  // namespace Debug