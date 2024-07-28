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
 * @file      main.c
 * @brief     main source file
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
#include "driver_ttp229_basic.h"
#include <getopt.h>
#include <stdlib.h>

/**
 * @brief     ttp229 full function
 * @param[in] argc is arg numbers
 * @param[in] **argv is the arg address
 * @return    status code
 *            - 0 success
 *            - 1 run failed
 *            - 5 param is invalid
 * @note      none
 */
uint8_t ttp229(uint8_t argc, char **argv)
{
    int c;
    int longindex = 0;
    const char short_options[] = "hipe:t:";
    const struct option long_options[] =
    {
        {"help", no_argument, NULL, 'h'},
        {"information", no_argument, NULL, 'i'},
        {"port", no_argument, NULL, 'p'},
        {"example", required_argument, NULL, 'e'},
        {"test", required_argument, NULL, 't'},
        {"level", required_argument, NULL, 1},
        {"interface", required_argument, NULL, 2},
        {"times", required_argument, NULL, 3},
        {NULL, 0, NULL, 0},
    };
    char type[33] = "unknown";
    uint32_t times = 3;
    ttp229_interface_t interface = TTP229_INTERFACE_IIC;
    ttp229_active_t level = TTP229_ACTIVE_LOW;
    
    /* if no params */
    if (argc == 1)
    {
        /* goto the help */
        goto help;
    }
    
    /* init 0 */
    optind = 0;
    
    /* parse */
    do
    {
        /* parse the args */
        c = getopt_long(argc, argv, short_options, long_options, &longindex);
        
        /* judge the result */
        switch (c)
        {
            /* help */
            case 'h' :
            {
                /* set the type */
                memset(type, 0, sizeof(char) * 33);
                snprintf(type, 32, "h");
                
                break;
            }
            
            /* information */
            case 'i' :
            {
                /* set the type */
                memset(type, 0, sizeof(char) * 33);
                snprintf(type, 32, "i");
                
                break;
            }
            
            /* port */
            case 'p' :
            {
                /* set the type */
                memset(type, 0, sizeof(char) * 33);
                snprintf(type, 32, "p");
                
                break;
            }
            
            /* example */
            case 'e' :
            {
                /* set the type */
                memset(type, 0, sizeof(char) * 33);
                snprintf(type, 32, "e_%s", optarg);
                
                break;
            }
            
            /* test */
            case 't' :
            {
                /* set the type */
                memset(type, 0, sizeof(char) * 33);
                snprintf(type, 32, "t_%s", optarg);
                
                break;
            }
            
            /* running level */
            case 1 :
            {
                if (strcmp("low", optarg) == 0)
                {
                    level = TTP229_ACTIVE_LOW;
                }
                else if (strcmp("high", optarg) == 0)
                {
                    level = TTP229_ACTIVE_HIGH;
                }
                else
                {
                    return 5;
                }
                
                break;
            } 
            
            /* running interface */
            case 2 :
            {
                if (strcmp("iic", optarg) == 0)
                {
                    interface = TTP229_INTERFACE_IIC;
                }
                else if (strcmp("spi", optarg) == 0)
                {
                    interface = TTP229_INTERFACE_SPI;
                }
                else
                {
                    return 5;
                }
                
                break;
            } 
            
            /* running times */
            case 3 :
            {
                /* set the times */
                times = atol(optarg);
                
                break;
            } 
            
            /* the end */
            case -1 :
            {
                break;
            }
            
            /* others */
            default :
            {
                return 5;
            }
        }
    } while (c != -1);

    /* run the function */
    if (strcmp("t_read", type) == 0)
    {
        uint8_t res;
        
        /* run the read test */
        res = ttp229_read_test(interface, level, times);
        if (res != 0)
        {
            return 1;
        }
        
        return 0;
    }
    else if (strcmp("e_read16", type) == 0)
    {
        uint8_t res;
        uint32_t i;
        uint8_t keys[16];
        
        /* basic init */
        res = ttp229_basic_init(interface, level);
        if (res != 0)
        {
            return 1;
        }
        
        /* loop */
        for (i = 0; i < times; i++)
        {
            /* delay 1000ms */
            ttp229_interface_delay_ms(1000);
            
            /* read data */
            res = ttp229_basic_read_16_keys(keys);
            if (res != 0)
            {
                (void)ttp229_basic_deinit();
                
                return 1;
            }
            
            /* output */
            ttp229_interface_debug_print("ttp229: key[0] key[1] key[2] key[3] is %d %d %d %d.\n", keys[0], keys[1], keys[2], keys[3]);
            ttp229_interface_debug_print("ttp229: key[4] key[5] key[6] key[7] is %d %d %d %d.\n", keys[4], keys[5], keys[6], keys[7]);
            ttp229_interface_debug_print("ttp229: key[8] key[9] key[10] key[11] is %d %d %d %d.\n", keys[8], keys[9], keys[10], keys[11]);
            ttp229_interface_debug_print("ttp229: key[12] key[13] key[14] key[15] is %d %d %d %d.\n", keys[12], keys[13], keys[14], keys[15]);
            ttp229_interface_debug_print("----------------------------------------------------\n");
        }
        
        /* deinit */
        (void)ttp229_basic_deinit();
        
        return 0;
    }
    else if (strcmp("e_read8", type) == 0)
    {
        uint8_t res;
        uint32_t i;
        uint8_t keys[8];
        
        /* basic init */
        res = ttp229_basic_init(interface, level);
        if (res != 0)
        {
            return 1;
        }
        
        /* loop */
        for (i = 0; i < times; i++)
        {
            /* delay 1000ms */
            ttp229_interface_delay_ms(1000);
            
            /* read data */
            res = ttp229_basic_read_8_keys(keys);
            if (res != 0)
            {
                (void)ttp229_basic_deinit();
                
                return 1;
            }
            
            /* output */
            ttp229_interface_debug_print("ttp229: key[0] key[1] key[2] key[3] is %d %d %d %d.\n", keys[0], keys[1], keys[2], keys[3]);
            ttp229_interface_debug_print("ttp229: key[4] key[5] key[6] key[7] is %d %d %d %d.\n", keys[4], keys[5], keys[6], keys[7]);
            ttp229_interface_debug_print("----------------------------------------------------\n");
        }
        
        /* deinit */
        (void)ttp229_basic_deinit();
        
        return 0;
    }
    else if (strcmp("h", type) == 0)
    {
        help:
        ttp229_interface_debug_print("Usage:\n");
        ttp229_interface_debug_print("  ttp229 (-i | --information)\n");
        ttp229_interface_debug_print("  ttp229 (-h | --help)\n");
        ttp229_interface_debug_print("  ttp229 (-p | --port)\n");
        ttp229_interface_debug_print("  ttp229 (-t read | --test=read) [--level=<low | high>] [--interface=<iic | spi>] [--times=<num>]\n");
        ttp229_interface_debug_print("  ttp229 (-e read16 | --example=read16) [--level=<low | high>] [--interface=<iic | spi>] [--times=<num>]\n");
        ttp229_interface_debug_print("  ttp229 (-e read8 | --example=read8) [--level=<low | high>] [--interface=<iic | spi>] [--times=<num>]\n");
        ttp229_interface_debug_print("\n");
        ttp229_interface_debug_print("Options:\n");
        ttp229_interface_debug_print("      --level=<low | high>           Set the active level.([default: low])\n");
        ttp229_interface_debug_print("  -e <read16 | read8>, --example=<read16 | read8>\n");
        ttp229_interface_debug_print("                                     Run the driver example.\n");
        ttp229_interface_debug_print("  -h, --help                         Show the help.\n");
        ttp229_interface_debug_print("  -i, --information                  Show the chip information.\n");
        ttp229_interface_debug_print("      --interface=<iic | spi>        Set the chip interface.([default: iic])\n");
        ttp229_interface_debug_print("  -p, --port                         Display the pin connections of the current board.\n");
        ttp229_interface_debug_print("  -t <read>, --test=<read>           Run the driver test.\n");
        ttp229_interface_debug_print("      --times=<num>                  Set the running times.([default: 3])\n");
        
        return 0;
    }
    else if (strcmp("i", type) == 0)
    {
        ttp229_info_t info;
        
        /* print ttp229 info */
        ttp229_info(&info);
        ttp229_interface_debug_print("ttp229: chip is %s.\n", info.chip_name);
        ttp229_interface_debug_print("ttp229: manufacturer is %s.\n", info.manufacturer_name);
        ttp229_interface_debug_print("ttp229: interface is %s.\n", info.interface);
        ttp229_interface_debug_print("ttp229: driver version is %d.%d.\n", info.driver_version / 1000, (info.driver_version % 1000) / 100);
        ttp229_interface_debug_print("ttp229: min supply voltage is %0.1fV.\n", info.supply_voltage_min_v);
        ttp229_interface_debug_print("ttp229: max supply voltage is %0.1fV.\n", info.supply_voltage_max_v);
        ttp229_interface_debug_print("ttp229: max current is %0.2fmA.\n", info.max_current_ma);
        ttp229_interface_debug_print("ttp229: max temperature is %0.1fC.\n", info.temperature_max);
        ttp229_interface_debug_print("ttp229: min temperature is %0.1fC.\n", info.temperature_min);
        
        return 0;
    }
    else if (strcmp("p", type) == 0)
    {
        /* print pin connection */
        ttp229_interface_debug_print("ttp229: SPI interface SCK connected to GPIO11(BCM).\n");
        ttp229_interface_debug_print("ttp229: SPI interface MISO connected to GPIO9(BCM).\n");
        ttp229_interface_debug_print("ttp229: IIC interface SCL connected to GPIO3(BCM).\n");
        ttp229_interface_debug_print("ttp229: IIC interface SDA connected to GPIO2(BCM).\n");
        
        return 0;
    }
    else
    {
        return 5;
    }
}

/**
 * @brief     main function
 * @param[in] argc is arg numbers
 * @param[in] **argv is the arg address
 * @return    status code
 *             - 0 success
 * @note      none
 */
int main(uint8_t argc, char **argv)
{
    uint8_t res;

    res = ttp229(argc, argv);
    if (res == 0)
    {
        /* run success */
    }
    else if (res == 1)
    {
        ttp229_interface_debug_print("ttp229: run failed.\n");
    }
    else if (res == 5)
    {
        ttp229_interface_debug_print("ttp229: param is invalid.\n");
    }
    else
    {
        ttp229_interface_debug_print("ttp229: unknown status code.\n");
    }

    return 0;
}
