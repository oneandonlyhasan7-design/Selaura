#pragma once
#include <api/mc/client/gui/GuiData.hpp>

class ClientInstance {
public:
    std::byte pad_4[1368];
    std::unique_ptr<GuiData> mGuiData;
public:
    void* $ctor(
        void* a1,
        void* a2,
        void* a3,
        void* a4,
        void* a5,
        void* a6,
        void* a7,
        void* a8,
        void* a9
    );
};
