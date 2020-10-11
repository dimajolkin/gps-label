#pragma once

typedef struct {
    public:
        float lan;
        float lng;
        uint8_t n;

        uint8_t validate() {
            return lan != 0 && lng != 0;
        }

        float getLan() {
            return lan;
        }

        float getLng() {
            return lng;
        }
}

Package;
