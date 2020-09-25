
// 9 byte
class Package
{
    private:
        float lan;
        float lng;
        uint8_t n;
    public:
        Package(float lan, float lng, uint8_t n): lan(lan), lng(lng), n(n) {}

        float getLan() {
            return lan;
        }

        float getLng() {
            return lng;
        }

        float getNumber() {
            return n;
        }
    
};
