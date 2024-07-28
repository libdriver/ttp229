/**
 * Copyright (c) 2015 - present LibDriver All rights reserved
 * 
 * The MIT License (MIT)
 *
 * Permission is hereby granted, free of charge, to any person obtaining a copy
 * of this software and associated documentation files (the "Software"), to deal
 * in the Software without restriction, including without limitation the rights
 * to use, copy, modify, merge, publish, distribute, sublicense, and/or sell
 * copies of the Software, and to permit persons to whom the Software is
 * furnished to do so, subject to the following conditions:
 *
 * The above copyright notice and this permission notice shall be included in all
 * copies or substantial portions of the Software.
 *
 * THE SOFTWARE IS PROVIDED "AS IS", WITHOUT WARRANTY OF ANY KIND, EXPRESS OR
 * IMPLIED, INCLUDING BUT NOT LIMITED TO THE WARRANTIES OF MERCHANTABILITY,
 * FITNESS FOR A PARTICULAR PURPOSE AND NONINFRINGEMENT. IN NO EVENT SHALL THE
 * AUTHORS OR COPYRIGHT HOLDERS BE LIABLE FOR ANY CLAIM, DAMAGES OR OTHER
 * LIABILITY, WHETHER IN AN ACTION OF CONTRACT, TORT OR OTHERWISE, ARISING FROM,
 * OUT OF OR IN CONNECTION WITH THE SOFTWARE OR THE USE OR OTHER DEALINGS IN THE
 * SOFTWARE. 
 *
 * @file      driver_ttp229.h
 * @brief     driver ttp229 header file
 * @version   1.0.0
 * @author    Shifeng Li
 * @date      2024-07-30
 *
 * <h3>history</h3>
 * <table>
 * <tr><th>Date        <th>Version  <th>Author      <th>Description
 * <tr><td>2024/07/30  <td>1.0      <td>Shifeng Li  <td>first upload
 * </table>
 */

#ifndef DRIVER_TTP229_H
#define DRIVER_TTP229_H

#include <stdio.h>
#include <stdint.h>
#include <string.h>

#ifdef __cplusplus
extern "C"{
#endif

/**
 * @defgroup ttp229_driver ttp229 driver function
 * @brief    ttp229 driver modules
 * @{
 */

/**
 * @addtogroup ttp229_basic_driver
 * @{
 */

/**
 * @brief ttp229 interface enumeration definition
 */
typedef enum
{
    TTP229_INTERFACE_IIC = 0x00,        /**< iic interface */
    TTP229_INTERFACE_SPI = 0x01,        /**< spi interface */
} ttp229_interface_t;

/**
 * @brief ttp229 active enumeration definition
 */
typedef enum
{
    TTP229_ACTIVE_LOW  = 0x00,        /**< active low */
    TTP229_ACTIVE_HIGH = 0x01,        /**< active high */
} ttp229_active_t;

/**
 * @brief ttp229 handle structure definition
 */
typedef struct ttp229_handle_s
{
    uint8_t (*iic_init)(void);                                                 /**< point to an iic_init function address */
    uint8_t (*iic_deinit)(void);                                               /**< point to an iic_deinit function address */
    uint8_t (*iic_read_cmd)(uint8_t addr, uint8_t *buf, uint16_t len);         /**< point to an iic_read_cmd function address */
    uint8_t (*spi_init)(void);                                                 /**< point to a spi_init function address */
    uint8_t (*spi_deinit)(void);                                               /**< point to a spi_deinit function address */
    uint8_t (*spi_read_cmd)(uint8_t *buf, uint16_t len);                       /**< point to a spi_read_cmd function address */
    void (*delay_ms)(uint32_t ms);                                             /**< point to a delay_ms function address */
    void (*debug_print)(const char *const fmt, ...);                           /**< point to a debug_print function address */
    uint8_t inited;                                                            /**< inited flag */
    uint8_t active;                                                            /**< active flag */
    uint8_t iic_spi;                                                           /**< iic spi interface */
} ttp229_handle_t;

/**
 * @brief ttp229 information structure definition
 */
typedef struct ttp229_info_s
{
    char chip_name[32];                /**< chip name */
    char manufacturer_name[32];        /**< manufacturer name */
    char interface[8];                 /**< chip interface name */
    float supply_voltage_min_v;        /**< chip min supply voltage */
    float supply_voltage_max_v;        /**< chip max supply voltage */
    float max_current_ma;              /**< chip max current */
    float temperature_min;             /**< chip min operating temperature */
    float temperature_max;             /**< chip max operating temperature */
    uint32_t driver_version;           /**< driver version */
} ttp229_info_t;

/**
 * @}
 */

/**
 * @defgroup ttp229_link_driver ttp229 link driver function
 * @brief    ttp229 link driver modules
 * @ingroup  ttp229_driver
 * @{
 */

/**
 * @brief     initialize ttp229_handle_t structure
 * @param[in] HANDLE points to a ttp229 handle structure
 * @param[in] STRUCTURE is ttp229_handle_t
 * @note      none
 */
#define DRIVER_TTP229_LINK_INIT(HANDLE, STRUCTURE)          memset(HANDLE, 0, sizeof(STRUCTURE))

/**
 * @brief     link iic_init function
 * @param[in] HANDLE points to a ttp229 handle structure
 * @param[in] FUC points to an iic_init function address
 * @note      none
 */
#define DRIVER_TTP229_LINK_IIC_INIT(HANDLE, FUC)           (HANDLE)->iic_init = FUC

/**
 * @brief     link iic_deinit function
 * @param[in] HANDLE points to a ttp229 handle structure
 * @param[in] FUC points to an iic_deinit function address
 * @note      none
 */
#define DRIVER_TTP229_LINK_IIC_DEINIT(HANDLE, FUC)         (HANDLE)->iic_deinit = FUC

/**
 * @brief     link iic_read_cmd function
 * @param[in] HANDLE points to a ttp229 handle structure
 * @param[in] FUC points to an iic_read_cmd function address
 * @note      none
 */
#define DRIVER_TTP229_LINK_IIC_READ_CMD(HANDLE, FUC)       (HANDLE)->iic_read_cmd = FUC

/**
 * @brief     link spi_init function
 * @param[in] HANDLE points to a ttp229 handle structure
 * @param[in] FUC points to an spi_init function address
 * @note      none
 */
#define DRIVER_TTP229_LINK_SPI_INIT(HANDLE, FUC)           (HANDLE)->spi_init = FUC

/**
 * @brief     link spi_deinit function
 * @param[in] HANDLE points to a ttp229 handle structure
 * @param[in] FUC points to an spi_deinit function address
 * @note      none
 */
#define DRIVER_TTP229_LINK_SPI_DEINIT(HANDLE, FUC)         (HANDLE)->spi_deinit = FUC

/**
 * @brief     link spi_read_cmd function
 * @param[in] HANDLE points to a ttp229 handle structure
 * @param[in] FUC points to an spi_read_cmd function address
 * @note      none
 */
#define DRIVER_TTP229_LINK_SPI_READ_CMD(HANDLE, FUC)       (HANDLE)->spi_read_cmd = FUC

/**
 * @brief     link delay_ms function
 * @param[in] HANDLE points to a ttp229 handle structure
 * @param[in] FUC points to a delay_ms function address
 * @note      none
 */
#define DRIVER_TTP229_LINK_DELAY_MS(HANDLE, FUC)           (HANDLE)->delay_ms = FUC

/**
 * @brief     link debug_print function
 * @param[in] HANDLE points to a ttp229 handle structure
 * @param[in] FUC points to a debug_print function address
 * @note      none
 */
#define DRIVER_TTP229_LINK_DEBUG_PRINT(HANDLE, FUC)        (HANDLE)->debug_print = FUC

/**
 * @}
 */

/**
 * @defgroup ttp229_basic_driver ttp229 basic driver function
 * @brief    ttp229 basic driver modules
 * @ingroup  ttp229_driver
 * @{
 */

/**
 * @brief      get chip's information
 * @param[out] *info points to a ttp229 info structure
 * @return     status code
 *             - 0 success
 *             - 2 handle is NULL
 * @note       none
 */
uint8_t ttp229_info(ttp229_info_t *info);

/**
 * @brief     set the interface
 * @param[in] *handle points to a ttp229 handle structure
 * @param[in] interface is the chip interface
 * @return    status code
 *            - 0 success
 *            - 2 handle is NULL
 * @note      none
 */
uint8_t ttp229_set_interface(ttp229_handle_t *handle, ttp229_interface_t interface);

/**
 * @brief      get the interface
 * @param[in]  *handle points to a ttp229 handle structure
 * @param[out] *interface points to a chip interface buffer
 * @return     status code
 *             - 0 success
 *             - 2 handle is NULL
 * @note       none
 */
uint8_t ttp229_get_interface(ttp229_handle_t *handle, ttp229_interface_t *interface);

/**
 * @brief     initialize the chip
 * @param[in] *handle points to a ttp229 handle structure
 * @return    status code
 *            - 0 success
 *            - 1 iic or spi initialization failed
 *            - 2 handle is NULL
 *            - 3 linked functions is NULL
 * @note      none
 */
uint8_t ttp229_init(ttp229_handle_t *handle);

/**
 * @brief     close the chip
 * @param[in] *handle points to a ttp229 handle structure
 * @return    status code
 *            - 0 success
 *            - 1 iic or spi deinit failed
 *            - 2 handle is NULL
 *            - 3 handle is not initialized
 * @note      none
 */
uint8_t ttp229_deinit(ttp229_handle_t *handle);

/**
 * @brief     set the active level
 * @param[in] *handle points to a ttp229 handle structure
 * @param[in] active_level is the set active level
 * @return    status code
 *            - 0 success
 *            - 2 handle is NULL
 *            - 3 handle is not initialized
 * @note      none
 */
uint8_t ttp229_set_active(ttp229_handle_t *handle, ttp229_active_t active_level);

/**
 * @brief      get the active level
 * @param[in]  *handle points to a ttp229 handle structure
 * @param[out] *active_level points to an active level buffer
 * @return     status code
 *             - 0 success
 *             - 2 handle is NULL
 *             - 3 handle is not initialized
 * @note       none
 */
uint8_t ttp229_get_active(ttp229_handle_t *handle, ttp229_active_t *active_level);

/**
 * @brief      read 16 keys
 * @param[in]  *handle points to a ttp229 handle structure
 * @param[out] *keys points to a key buffer
 * @return     status code
 *             - 0 success
 *             - 1 read 16 keys failed
 *             - 2 handle is NULL
 *             - 3 handle is not initialized
 * @note       active is 1
 */
uint8_t ttp229_read_16_keys(ttp229_handle_t *handle, uint8_t keys[16]);

/**
 * @brief      read 8 keys
 * @param[in]  *handle points to a ttp229 handle structure
 * @param[out] *keys points to a key buffer
 * @return     status code
 *             - 0 success
 *             - 1 read 8 keys failed
 *             - 2 handle is NULL
 *             - 3 handle is not initialized
 * @note       active is 1
 */
uint8_t ttp229_read_8_keys(ttp229_handle_t *handle, uint8_t keys[8]);

/**
 * @}
 */

/**
 * @defgroup ttp229_extern_driver ttp229 extern driver function
 * @brief    ttp229 extern driver modules
 * @ingroup  ttp229_driver
 * @{
 */

/**
 * @brief      get the chip register
 * @param[in]  *handle points to a ttp229 handle structure
 * @param[out] *buf points to a data buffer
 * @param[in]  len is the data length
 * @return     status code
 *             - 0 success
 *             - 1 read failed
 *             - 2 handle is NULL
 *             - 3 handle is not initialized
 * @note       none
 */
uint8_t ttp229_get_reg(ttp229_handle_t *handle, uint8_t *buf, uint16_t len);

/**
 * @}
 */

/**
 * @}
 */

#ifdef __cplusplus
}
#endif

#endif
