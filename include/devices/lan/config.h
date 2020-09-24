
#define LAN_CONFIG_SAVE_CHANNEL_ADDRESS 1

class LanConfig {
    public:
        void init() {
            if (getChannel() == 255) {
                setChannel(1);
            }
        }

        void setChannel(uint8_t n) {
            EEPROM.update(LAN_CONFIG_SAVE_CHANNEL_ADDRESS, n);
        }

        uint8_t getChannel() {
            return EEPROM.read(LAN_CONFIG_SAVE_CHANNEL_ADDRESS);
        }
};