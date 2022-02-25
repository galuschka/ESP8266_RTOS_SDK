// Copyright 2015-2016 Espressif Systems (Shanghai) PTE LTD
//
// Licensed under the Apache License, Version 2.0 (the "License");
// you may not use this file except in compliance with the License.
// You may obtain a copy of the License at

//     http://www.apache.org/licenses/LICENSE-2.0
//
// Unless required by applicable law or agreed to in writing, software
// distributed under the License is distributed on an "AS IS" BASIS,
// WITHOUT WARRANTIES OR CONDITIONS OF ANY KIND, either express or implied.
// See the License for the specific language governing permissions and
// limitations under the License.
#ifndef __ESP_BIN_TYPES_H__
#define __ESP_BIN_TYPES_H__

#include <stdint.h>

#ifdef __cplusplus
extern "C"
{
#endif

#define ESP_PARTITION_TABLE_ADDR CONFIG_PARTITION_TABLE_OFFSET
#define ESP_PARTITION_MAGIC 0x50AA
#define ESP_PARTITION_MAGIC_MD5 0xEBEB

/* OTA selection structure (two copies in the OTA data partition.)
   Size of 32 bytes is friendly to flash encryption */
typedef struct {
    uint32_t ota_seq;
    uint8_t  seq_label[20];
    uint32_t test_stage;
    uint32_t crc; /* CRC32 of ota_seq field only */
} esp_ota_select_entry_t;

enum OTA_TEST_STAGE {
    OTA_TEST_STAGE_TO_TEST = 0x7f7f7f7f,  /* initial stage after flashing: image has to be tested
                                          ** when bootloader reads 7f, it clears 40 (-> 3f) and performs the test */
    OTA_TEST_STAGE_TESTING = 0x3f3f3f3f,  /* image has been used by bootloader and it is being tested
                                          ** when bootloader reads 3f, it clears 20 (-> 1f) and uses another image
                                          ** when app gets confirmation, it clears 10 (-> 2f) */
    OTA_TEST_STAGE_FAILED  = 0x1f1f1f1f,  /* test failed - image must **not** be used on further boots */
    OTA_TEST_STAGE_PASSED  = 0x2f2f2f2f,  /* test passed (same as any other value than 7f, 3f, or 1f) */
};


typedef struct {
    uint32_t offset;
    uint32_t size;
} esp_partition_pos_t;

/* Structure which describes the layout of partition table entry.
 * See docs/partition_tables.rst for more information about individual fields.
 */
typedef struct {
    uint16_t magic;
    uint8_t  type;
    uint8_t  subtype;
    esp_partition_pos_t pos;
    uint8_t  label[16];
    uint32_t flags;
} esp_partition_info_t;

#define PART_TYPE_APP 0x00
#define PART_SUBTYPE_FACTORY  0x00
#define PART_SUBTYPE_OTA_FLAG 0x10
#define PART_SUBTYPE_OTA_MASK 0x0f
#define PART_SUBTYPE_TEST     0x20

#define PART_TYPE_DATA 0x01
#define PART_SUBTYPE_DATA_OTA 0x00
#define PART_SUBTYPE_DATA_RF  0x01
#define PART_SUBTYPE_DATA_WIFI 0x02

#define PART_TYPE_END 0xff
#define PART_SUBTYPE_END 0xff

#define PART_FLAG_ENCRYPTED (1<<0)

#ifdef __cplusplus
}
#endif

#endif //__ESP_BIN_TYPES_H__
