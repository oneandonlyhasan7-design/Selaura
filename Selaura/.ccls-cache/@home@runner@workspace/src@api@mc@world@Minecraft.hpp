#pragma once
#include <api/mc/world/Timer.hpp>

class Minecraft {
public:
    std::byte _pad0[216];
    Timer& mSimTimer;
    Timer& mRealTimer;
public:
    Minecraft* $ctor(
        void* app,
        void* gameCallbacks,
        void* allowList,
        void* permissionsFile,
        void* filePathManager,
        void* maxPlayerIdleTime,
        void* eventing,
        void* network,
        void* packetSender,
        void* clientSubId,
        void* simTimer,
        void* realTimer,
        void* contentTierManager,
        void* serverMetrics
    );
};