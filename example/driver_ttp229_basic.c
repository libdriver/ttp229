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
 * @file      driver_ttp229_basic.c
 * @brief     driver ttp229 basic source file
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

#include "driver_ttp229_basic.h"

static ttp229_handle_t gs_handle;        /**< ttp229 handle */

/**
 * @brief     basic example init
 * @param[in] interface is the set interface
 * @param[in] active_level is the set active level
 * @return    status code
 *            - 0 success
 *            - 1 init failed
 * @note      none
 */
uint8_t ttp229_basic_init(ttp229_interface_t interface, ttp229_active_t active_level)
{
    uint8_t res;
    
    /* link interface function */
    DRIVER_TTP229_LINK_INIT(&gs_handle, ttp229_handle_t); 
    DRIVER_TTP229_LINK_IIC_INIT(&gs_handle, ttp229_interface_iic_init);
    DRIVER_TTP229_LINK_IIC_DEINIT(&gs_handle, ttp229_interface_iic_deinit);
    DRIVER_TTP229_LINK_IIC_READ_CMD(&gs_handle, ttp229_interface_iic_read_cmd);
    DRIVER_TTP229_LINK_SPI_INIT(&gs_handle, ttp229_interface_spi_init);
    DRIVER_TTP229_LINK_SPI_DEINIT(&gs_handle, ttp229_interface_spi_deinit);
    DRIVER_TTP229_LINK_SPI_READ_CMD(&gs_handle, ttp229_interface_spi_read_cmd);
    DRIVER_TTP229_LINK_DELAY_MS(&gs_handle, ttp229_interface_delay_ms);
    DRIVER_TTP229_LINK_DEBUG_PRINT(&gs_handle, ttp229_interface_debug_print);
    
    /* set interface */
    res = ttp229_set_interface(&gs_handle, interface);
    if (res != 0)
    {
        ttp229_interface_debug_print("ttp229: set interface failed.\n");
       
        return 1;
    }
    
    /* ttp229 init */
    res = ttp229_init(&gs_handle);
    if (res != 0)
    {
        ttp229_interface_debug_print("ttp229: init failed.\n");
        
        return 1;
    }
    
    /* set active */
    res = ttp229_set_active(&gs_handle, active_level);
    if (res != 0)
    {
        ttp229_interface_debug_print("ttp229: set active failed.\n");
        (void)ttp229_deinit(&gs_handle); 
        
        return 1;
    }
    
    return 0;
}

/**
 * @brief      basic example read 16 keys
 * @param[out] *keys points to a key buffer
 * @return     status code
 *             - 0 success
 *             - 1 read failed
 * @note       active is 1
 */
uint8_t ttp229_basic_read_16_keys(uint8_t keys[16])
{
    /* read keys */
    if (ttp229_read_16_keys(&gs_handle, keys) != 0)
    {
        return 1;
    }
    
    return 0;
}

/**
 * @brief      basic example read 8 keys
 * @param[out] *keys points to a key buffer
 * @return     status code
 *             - 0 success
 *             - 1 read failed
 * @note       active is 1
 */
uint8_t ttp229_basic_read_8_keys(uint8_t keys[8])
{
    /* read keys */
    if (ttp229_read_8_keys(&gs_handle, keys) != 0)
    {
        return 1;
    }
    
    return 0;
}

/**
 * @brief  basic example deinit
 * @return status code
 *         - 0 success
 *         - 1 deinit failed
 * @note   none
 */
uint8_t ttp229_basic_deinit(void)
{
    /* close ttp229 */
    if (ttp229_deinit(&gs_handle) != 0)
    {
        return 1;
    }
    
    return 0;
}
