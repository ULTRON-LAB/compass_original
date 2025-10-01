#!/bin/bash
# 這是一個用來自動編譯並合併 ESP32C3 韌體的腳本

# 如果中途有任何指令出錯，就立刻停止執行 (安全機制)
set -e

echo "合併所有 .bin 檔案為 production.bin..."
esptool.py --chip esp32c3 merge_bin -o production.bin --flash_mode dio --flash_freq 80m --flash_size 4MB 0x0 ".pio/build/airm2m_core_esp32c3/bootloader.bin" 0x8000 ".pio/build/airm2m_core_esp32c3/partitions.bin" 0x10000 ".pio/build/airm2m_core_esp32c3/firmware.bin" 0x210000 ".pio/build/airm2m_core_esp32c3/littlefs.bin"

echo "✅ 'production.bin' 成功生成！"