#pragma once
#include <api/imports.hpp>
#include <hooks/memory.hpp>
#include <string>

class GuiData {
public:
    void displayLocalMessage(const std::string& message) {
        using fn_t = decltype(&GuiData::displayLocalMessage);
        // TODO: Broken
        static fn_t fn = std::bit_cast<fn_t>(selaura::find_signature<"40 55 53 56 57 41 56 48 8D AC 24 ? ? ? ? 48 81 EC ? ? ? ? 48 8B 05 ? ? ? ? 48 33 C4 48 89 85 ? ? ? ? 41 0F B6 F9">());
        return (this->*fn)(message);
    }
};
