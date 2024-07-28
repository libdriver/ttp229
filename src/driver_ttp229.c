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
 * @file      driver_ttp229.c
 * @brief     driver ttp229 source file
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

#include "driver_ttp229.h"

/**
 * @brief chip information definition
 */
#define CHIP_NAME                 "Tontek TTP229"        /**< chip name */
#define MANUFACTURER_NAME         "Tontek"               /**< manufacturer name */
#define SUPPLY_VOLTAGE_MIN        2.4f                   /**< chip min supply voltage */
#define SUPPLY_VOLTAGE_MAX        5.5f                   /**< chip max supply voltage */
#define MAX_CURRENT               8.0f                   /**< chip max current */
#define TEMPERATURE_MIN           -40.0f                 /**< chip min operating temperature */
#define TEMPERATURE_MAX           85.0f                  /**< chip max operating temperature */
#define DRIVER_VERSION            1000                   /**< driver version */

/**
 * @brief chip address definition
 */
#define TTP229_ADDRESS        (0x57 << 1)        /**< iic device address */

/**
 * @brief      read multiple bytes
 * @param[in]  *handle points to a ttp229 handle structure
 * @param[out] *buf points to a data buffer
 * @param[in]  len is the data length
 * @return     status code
 *             - 0 success
 *             - 1 iic spi read failed
 * @note       none
 */
static uint8_t a_ttp229_iic_spi_read(ttp229_handle_t *handle, uint8_t *buf, uint16_t len)
{
    if (handle->iic_spi == (uint8_t)TTP229_INTERFACE_IIC)               /* iic interface */
    {
        if (handle->iic_read_cmd(TTP229_ADDRESS, buf, len) != 0)        /* iic read */
        {
            return 1;                                                   /* return error */
        }

        return 0;                                                       /* success return 0 */
    }
    else                                                                /* spi interface */
    {
        if (handle->spi_read_cmd(buf, len) != 0)                        /* spi read */
        {
            return 1;                                                   /* return error */
        }

        return 0;                                                       /* success return 0 */
    }
}

/**
 * @brief     set the interface
 * @param[in] *handle points to a ttp229 handle structure
 * @param[in] interface is the chip interface
 * @return    status code
 *            - 0 success
 *            - 2 handle is NULL
 * @note      none
 */
uint8_t ttp229_set_interface(ttp229_handle_t *handle, ttp229_interface_t interface)
{
    if (handle == NULL)                        /* check handle */
    {
        return 2;                              /* return error */
    }

    handle->iic_spi = (uint8_t)interface;      /* set interface */

    return 0;                                  /* success return 0 */
}

/**
 * @brief      get the interface
 * @param[in]  *handle points to a ttp229 handle structure
 * @param[out] *interface points to a chip interface buffer
 * @return     status code
 *             - 0 success
 *             - 2 handle is NULL
 * @note       none
 */
uint8_t ttp229_get_interface(ttp229_handle_t *handle, ttp229_interface_t *interface)
{
    if (handle == NULL)                                        /* check handle */
    {
        return 2;                                              /* return error */
    }

    *interface = (ttp229_interface_t)(handle->iic_spi);        /* get interface */

    return 0;                                                  /* success return 0 */
}

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
uint8_t ttp229_set_active(ttp229_handle_t *handle, ttp229_active_t active_level)
{
    if (handle == NULL)                          /* check handle */
    {
        return 2;                                /* return error */
    }
    if (handle->inited != 1)                     /* check handle initialization */
    {
        return 3;                                /* return error */
    }

    handle->active = (uint8_t)active_level;      /* set active level */

    return 0;                                    /* success return 0 */
}

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
uint8_t ttp229_get_active(ttp229_handle_t *handle, ttp229_active_t *active_level)
{
    if (handle == NULL)                                     /* check handle */
    {
        return 2;                                           /* return error */
    }
    if (handle->inited != 1)                                /* check handle initialization */
    {
        return 3;                                           /* return error */
    }

    *active_level = (ttp229_active_t)(handle->active);      /* set active level */

    return 0;                                               /* success return 0 */
}

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
uint8_t ttp229_init(ttp229_handle_t *handle)
{
    if (handle == NULL)                                               /* check handle */
    {
        return 2;                                                     /* return error */
    }
    if (handle->debug_print == NULL)                                  /* check debug_print */
    {
        return 3;                                                     /* return error */
    }
    if (handle->iic_init == NULL)                                     /* check iic_init */
    {
        handle->debug_print("ttp229: iic_init is null.\n");           /* iic_init is nul */

        return 3;                                                     /* return error */
    }
    if (handle->iic_deinit == NULL)                                   /* check iic_deinit */
    {
        handle->debug_print("ttp229: iic_deinit is null.\n");         /* iic_deinit is null */

        return 3;                                                     /* return error */
    }
    if (handle->iic_read_cmd == NULL)                                 /* check iic_read_cmd */
    {
        handle->debug_print("ttp229: iic_read_cmd is null.\n");       /* iic_read_cmd is null */

        return 3;                                                     /* return error */
    }
    if (handle->spi_init == NULL)                                     /* check spi_init */
    {
        handle->debug_print("ttp229: spi_init is null.\n");           /* spi_init is nul */

        return 3;                                                     /* return error */
    }
    if (handle->spi_deinit == NULL)                                   /* check spi_deinit */
    {
        handle->debug_print("ttp229: spi_deinit is null.\n");         /* spi_deinit is nul */

        return 3;                                                     /* return error */
    }
    if (handle->spi_read_cmd == NULL)                                 /* check spi_read_cmd */
    {
        handle->debug_print("ttp229: spi_read_cmd is null.\n");       /* spi_read_cmd is nul */

        return 3;                                                     /* return error */
    }
    if (handle->delay_ms == NULL)                                     /* check delay_ms */
    {
        handle->debug_print("ttp229: delay_ms is null.\n");           /* delay_ms is null */

        return 3;                                                     /* return error */
    }

    if (handle->iic_spi == (uint8_t)TTP229_INTERFACE_IIC)             /* iic interface */
    {
        if (handle->iic_init() != 0)                                  /* iic init */
        {
            handle->debug_print("ttp229: iic init failed.\n");        /* iic init failed */

            return 1;                                                 /* return error */
        }
    }
    else                                                              /* spi interface */
    {
        if (handle->spi_init() != 0)                                  /* spi init */
        {
            handle->debug_print("ttp229: spi init failed.\n");        /* spi init failed */

            return 1;                                                 /* return error */
        }
    }

    handle->inited = 1;                                               /* flag finish initialization */

    return 0;                                                         /* success return 0 */
}

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
uint8_t ttp229_deinit(ttp229_handle_t *handle)
{
    if (handle == NULL)                                               /* check handle */
    {
        return 2;                                                     /* return error */
    }
    if (handle->inited != 1)                                          /* check handle initialization */
    {
        return 3;                                                     /* return error */
    }

    if (handle->iic_spi == (uint8_t)TTP229_INTERFACE_IIC)             /* iic interface */
    {
        if (handle->iic_init() != 0)                                  /* iic init */
        {
            handle->debug_print("ttp229: iic init failed.\n");        /* iic init failed */

            return 1;                                                 /* return error */
        }
    }
    else                                                              /* spi interface */
    {
        if (handle->spi_init() != 0)                                  /* spi init */
        {
            handle->debug_print("ttp229: spi init failed.\n");        /* spi init failed */

            return 1;                                                 /* return error */
        }
    }
    handle->inited = 0;                                               /* flag close */

    return 0;                                                         /* success return 0 */
}

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
uint8_t ttp229_read_16_keys(ttp229_handle_t *handle, uint8_t keys[16])
{
    uint8_t i;
    uint8_t buf[2];

    if (handle == NULL)                                            /* check handle */
    {
        return 2;                                                  /* return error */
    }
    if (handle->inited != 1)                                       /* check handle initialization */
    {
        return 3;                                                  /* return error */
    }

    if (a_ttp229_iic_spi_read(handle, buf, 2) != 0)                /* read data */
    {
        handle->debug_print("ttp229: read failed.\n");             /* read failed */

        return 1;                                                  /* return error */
    }
    for (i = 0; i < 16; i++)                                       /* loop all */
    {
        keys[i] = (buf[i / 8] >> (7 - i % 8)) & 0x01;              /* get one key */
        if (handle->active == (uint8_t)(TTP229_ACTIVE_LOW))        /* if active low */
        {
            keys[i] = !keys[i];                                    /* revert */
        }
    }

    return 0;                                                      /* success return 0 */
}

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
uint8_t ttp229_read_8_keys(ttp229_handle_t *handle, uint8_t keys[8])
{
    uint8_t i;
    uint8_t buf[1];

    if (handle == NULL)                                            /* check handle */
    {
        return 2;                                                  /* return error */
    }
    if (handle->inited != 1)                                       /* check handle initialization */
    {
        return 3;                                                  /* return error */
    }

    if (a_ttp229_iic_spi_read(handle, buf, 1) != 0)                /* read data */
    {
        handle->debug_print("ttp229: read failed.\n");             /* read failed */

        return 1;                                                  /* return error */
    }
    for (i = 0; i < 8; i++)                                        /* loop all */
    {
        keys[i] = (buf[i / 8] >> (7 - i % 8)) & 0x01;              /* get one key */
        if (handle->active == (uint8_t)(TTP229_ACTIVE_LOW))        /* if active low */
        {
            keys[i] = !keys[i];                                    /* revert */
        }
    }

    return 0;                                                      /* success return 0 */
}

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
uint8_t ttp229_get_reg(ttp229_handle_t *handle, uint8_t *buf, uint16_t len)
{
    if (handle == NULL)                                   /* check handle */
    {
        return 2;                                         /* return error */
    }
    if (handle->inited != 1)                              /* check handle initialization */
    {
        return 3;                                         /* return error */
    }

    return a_ttp229_iic_spi_read(handle, buf, len);       /* read register */
}

/**
 * @brief      get chip's information
 * @param[out] *info points to a ttp229 info structure
 * @return     status code
 *             - 0 success
 *             - 2 handle is NULL
 * @note       none
 */
uint8_t ttp229_info(ttp229_info_t *info)
{
    if (info == NULL)                                               /* check handle */
    {
        return 2;                                                   /* return error */
    }

    memset(info, 0, sizeof(ttp229_info_t));                         /* initialize ttp229 info structure */
    strncpy(info->chip_name, CHIP_NAME, 32);                        /* copy chip name */
    strncpy(info->manufacturer_name, MANUFACTURER_NAME, 32);        /* copy manufacturer name */
    strncpy(info->interface, "IIC SPI", 8);                         /* copy interface name */
    info->supply_voltage_min_v = SUPPLY_VOLTAGE_MIN;                /* set minimal supply voltage */
    info->supply_voltage_max_v = SUPPLY_VOLTAGE_MAX;                /* set maximum supply voltage */
    info->max_current_ma = MAX_CURRENT;                             /* set maximum current */
    info->temperature_max = TEMPERATURE_MAX;                        /* set minimal temperature */
    info->temperature_min = TEMPERATURE_MIN;                        /* set maximum temperature */
    info->driver_version = DRIVER_VERSION;                          /* set driver version */

    return 0;                                                       /* success return 0 */
}
