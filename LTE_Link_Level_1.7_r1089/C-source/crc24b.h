/**
 * \file crc24b.h
 * Functions and types for CRC checks.
 * MEXed to LTE_common_crc24b
 *
 * Generated on Wed Jun 04 13:03:52 2008,
 * by pycrc v0.6.5, http://www.tty1.net/pycrc/
 * MEX-ed by Josep Colom Ikuno, TU Wien, INTHFT
 * jcolom@nt.tuwien.ac.at
 * www.nt.tuwien.ac.at
 * using the configuration:
 *    Width        = 24
 *    Poly         = 0x800063
 *    XorIn        = 0x000000
 *    ReflectIn    = False
 *    XorOut       = 0x000000
 *    ReflectOut   = False
 *    Algorithm    = table-driven
 
 Permission is hereby granted, free of charge, to any person obtaining a copy
of this software and associated documentation files (the "Software"), to deal
in the Software without restriction, including without limitation the rights
to use, copy, modify, merge, publish, distribute, sublicense, and/or sell
copies of the Software, and to permit persons to whom the Software is
furnished to do so, subject to the following conditions:

The above copyright notice and this permission notice shall be included in
all copies or substantial portions of the Software.

THE SOFTWARE IS PROVIDED "AS IS", WITHOUT WARRANTY OF ANY KIND, EXPRESS OR
IMPLIED, INCLUDING BUT NOT LIMITED TO THE WARRANTIES OF MERCHANTABILITY,
FITNESS FOR A PARTICULAR PURPOSE AND NONINFRINGEMENT. IN NO EVENT SHALL THE
AUTHORS OR COPYRIGHT HOLDERS BE LIABLE FOR ANY CLAIM, DAMAGES OR OTHER
LIABILITY, WHETHER IN AN ACTION OF CONTRACT, TORT OR OTHERWISE, ARISING FROM,
OUT OF OR IN CONNECTION WITH THE SOFTWARE OR THE USE OR OTHER DEALINGS IN
THE SOFTWARE.


 *****************************************************************************/
#ifndef __CRC__B_H__
#define __CRC__B_H__

#include <stdlib.h>

#ifdef __cplusplus
extern "C" {
#endif

/**
 * The definition of the used algorithm.
 *****************************************************************************/
#define CRC_ALGO_TABLE_DRIVEN 1

/**
 * The type of the CRC values.
 *
 * This type must be big enough to contain at least 24 bits.
 *****************************************************************************/
typedef unsigned long crc_t;

/**
 * Calculate the initial crc value.
 *
 * \return     The initial crc value.
 *****************************************************************************/
#define crc_init()      (0x000000)

/**
 * Update the crc value with new data.
 *
 * \param crc      The current crc value.
 * \param data     Pointer to a buffer of \a data_len bytes.
 * \param data_len Number of bytes in the \a data buffer.
 * \return         The updated crc value.
 *****************************************************************************/
crc_t crc_update(crc_t crc, const unsigned char *data, size_t data_len);

/**
 * Calculate the final crc value.
 *
 * \param crc  The current crc value.
 * \return     The final crc value.
 *****************************************************************************/
#define crc_finalize(crc)      (crc ^ 0x000000)


#ifdef __cplusplus
}           /* closing brace for extern "C" */
#endif

#endif      /* __CRC__B_H__ */
