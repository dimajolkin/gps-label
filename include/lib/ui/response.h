#pragma once

class Response {
    private:
        uint8_t code;
    public:
        const uint8_t REFRESH = 1;
        const uint8_t REDIRECT = 2;

        Response(uint8_t code): code(code) {}

        uint8_t getCode() {
            return code;
        }
};