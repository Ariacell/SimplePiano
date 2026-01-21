#pragma once
#include "Component.h"

namespace Component {

class SelectableComponent : public Component {
public:
    bool SetSelected(bool shouldBeSelected) {
        m_IsSelected = shouldBeSelected;
        return m_IsSelected;
    }
    bool IsSelected() {
        return m_IsSelected;
    }

private:
    bool m_IsSelected;
};
}  // namespace Component