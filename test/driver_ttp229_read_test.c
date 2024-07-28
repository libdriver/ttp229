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
 * @file      driver_ttp229_read_test.c
 * @brief     driver ttp229 read test source file
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

#include "driver_ttp229_read_test.h"

static ttp229_handle_t gs_handle;        /**< ttp229 handle */

/**
 * @brief     read test
 * @param[in] interface is the set interface
 * @param[in] active_level is the set active level
 * @param[in] times is the read times
 * @return    status code
 *            - 0 success
 *            - 1 test failed
 * @note      none
 */
uint8_t ttp229_read_test(ttp229_interface_t interface, ttp229_active_t active_level, uint32_t times)
{
    uint8_t res;
    uint32_t i;
    ttp229_info_t info;
    
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
    
    /* get ttp229 info */
    res = ttp229_info(&info);
    if (res != 0)
    {
        ttp229_interface_debug_print("ttp229: get info failed.\n");
       
        return 1;
    }
    else
    {
        /* print ttp229 */
        ttp229_interface_debug_print("ttp229: chip is %s.\n", info.chip_name);
        ttp229_interface_debug_print("ttp229: manufacturer is %s.\n", info.manufacturer_name);
        ttp229_interface_debug_print("ttp229: interface is %s.\n", info.interface);
        ttp229_interface_debug_print("ttp229: driver version is %d.%d.\n", info.driver_version / 1000, (info.driver_version % 1000) / 100);
        ttp229_interface_debug_print("ttp229: min supply voltage is %0.1fV.\n", info.supply_voltage_min_v);
        ttp229_interface_debug_print("ttp229: max supply voltage is %0.1fV.\n", info.supply_voltage_max_v);
        ttp229_interface_debug_print("ttp229: max current is %0.2fmA.\n", info.max_current_ma);
        ttp229_interface_debug_print("ttp229: max temperature is %0.1fC.\n", info.temperature_max);
        ttp229_interface_debug_print("ttp229: min temperature is %0.1fC.\n", info.temperature_min);
    }
    
    /* start read test */
    ttp229_interface_debug_print("ttp229: start read test.\n");
    
    /* set interface */
    res = ttp229_set_interface(&gs_handle, interface);
    if (res != 0)
    {
        ttp229_interface_debug_print("ttp229: set interface failed.\n");
       
        return 1;
    }
    
    /* init */
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
    
    /* read 16 keys test */
    ttp229_interface_debug_print("ttp229: read 16 keys test.\n");
    
    /* loop */
    for (i = 0; i < times; i++)
    {
        uint8_t keys[16];
        
        /* read 16 keys */
        res = ttp229_read_16_keys(&gs_handle, keys);
        if (res != 0)
        {
            ttp229_interface_debug_print("ttp229: read 16 keys failed.\n");
            (void)ttp229_deinit(&gs_handle); 
            
            return 1;
        }
        
        /* delay 1000ms */
        ttp229_interface_delay_ms(1000);
        
        /* output */
        ttp229_interface_debug_print("ttp229: key[0] key[1] key[2] key[3] is %d %d %d %d.\n", keys[0], keys[1], keys[2], keys[3]);
        ttp229_interface_debug_print("ttp229: key[4] key[5] key[6] key[7] is %d %d %d %d.\n", keys[4], keys[5], keys[6], keys[7]);
        ttp229_interface_debug_print("ttp229: key[8] key[9] key[10] key[11] is %d %d %d %d.\n", keys[8], keys[9], keys[10], keys[11]);
        ttp229_interface_debug_print("ttp229: key[12] key[13] key[14] key[15] is %d %d %d %d.\n", keys[12], keys[13], keys[14], keys[15]);
        ttp229_interface_debug_print("----------------------------------------------------\n");
    }
    
    /* read 8 keys test */
    ttp229_interface_debug_print("ttp229: read 8 keys test.\n");
    
    /* loop */
    for (i = 0; i < times; i++)
    {
        uint8_t keys[8];
        
        /* read 8 keys */
        res = ttp229_read_8_keys(&gs_handle, keys);
        if (res != 0)
        {
            ttp229_interface_debug_print("ttp229: read 8 keys failed.\n");
            (void)ttp229_deinit(&gs_handle); 
            
            return 1;
        }
        
        /* delay 1000ms */
        ttp229_interface_delay_ms(1000);
        
        /* output */
        ttp229_interface_debug_print("ttp229: key[0] key[1] key[2] key[3] is %d %d %d %d.\n", keys[0], keys[1], keys[2], keys[3]);
        ttp229_interface_debug_print("ttp229: key[4] key[5] key[6] key[7] is %d %d %d %d.\n", keys[4], keys[5], keys[6], keys[7]);
        ttp229_interface_debug_print("------------------------------------------------\n");
    }
    
    /* finish read test */
    ttp229_interface_debug_print("ttp229: finish read test.\n");
    (void)ttp229_deinit(&gs_handle); 
    
    return 0;
}
