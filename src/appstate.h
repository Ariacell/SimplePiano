#include <ui/debugUI.h>

namespace State {

    struct DebugState {
        debugUI::DebugLayerMainWindowData mainDebugWindowData;
    };


    struct ApplicationState {
        State::DebugState debugState;
    };
}