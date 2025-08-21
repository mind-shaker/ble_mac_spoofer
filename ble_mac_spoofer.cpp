#include "esphome.h"
#include "esp_bt.h"
#include "esp_gap_ble_api.h"

class BLEMACSpoofer : public Component {
 public:
  std::string mac_address;

  void setup() override {
    ESP_LOGI("ble_mac_spoofer", "Setting custom BLE MAC: %s", mac_address.c_str());

    // Конвертуємо "AA:BB:CC:DD:EE:FF" у масив байтів
    uint8_t addr[6];
    sscanf(mac_address.c_str(), "%hhx:%hhx:%hhx:%hhx:%hhx:%hhx",
           &addr[0], &addr[1], &addr[2],
           &addr[3], &addr[4], &addr[5]);

    // ⚡ Встановлюємо як Random Static MAC
    esp_err_t err = esp_ble_gap_set_rand_addr(addr);
    if (err == ESP_OK) {
      ESP_LOGI("ble_mac_spoofer", "Random MAC applied successfully");
    } else {
      ESP_LOGE("ble_mac_spoofer", "Failed to set MAC, error: %d", err);
    }
  }
};
