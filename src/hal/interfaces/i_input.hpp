#pragma once

class IInput {
public:
    virtual ~IInput() = default;
    virtual bool isButtonPressed() = 0;
};