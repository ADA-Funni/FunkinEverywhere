#pragma once
#include <string>
#include <vector>

class BaseSound
{
    public:
        BaseSound() = default;
        virtual void create(const std::string& path, const std::string& type = "none") = 0;
        virtual ~BaseSound();

        void play(const std::string& name);
};