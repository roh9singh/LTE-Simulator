/**
 * \file crc24a.c
 * Functions and types for CRC checks.
 * MEXed to LTE_common_crc24a
 *
 * Generated on Wed Jun 04 13:03:51 2008,
 * by pycrc v0.6.5, http://www.tty1.net/pycrc/
 * MEX-ed by Josep Colom Ikuno, TU Wien, INTHFT
 * jcolom@nt.tuwien.ac.at
 * www.nt.tuwien.ac.at
 * using the configuration:
 *    Width        = 24
 *    Poly         = 0x864cfb
 *    XorIn        = 0x000000
 *    ReflectIn    = False
 *    XorOut       = 0x000000
 *    ReflectOut   = False
 *    Algorithm    = table-driven
 *
 * gCRC24A(D) = [D24 + D23 + D18 + D17 + D14 + D11 + D10 + D7 + D6 + D5 + D4 + D3 + D + 1]  for a CRC length L = 24
 * poly = dec2hex(binvec2dec([1 1 0 1 1 1 1 1 0 0 1 1 0 0 1 0 0 1 1 0 0 0 0 1 1 ]))
 
 
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
#include "crc24a.h"
#include "mex.h"
#include <stdlib.h>

/**
 * Static table used for the table_driven implementation.
 *****************************************************************************/
static const crc_t crc_table[256] = {
    0x000000, 0x864cfb, 0x8ad50d, 0x0c99f6, 0x93e6e1, 0x15aa1a, 0x1933ec, 0x9f7f17,
    0xa18139, 0x27cdc2, 0x2b5434, 0xad18cf, 0x3267d8, 0xb42b23, 0xb8b2d5, 0x3efe2e,
    0xc54e89, 0x430272, 0x4f9b84, 0xc9d77f, 0x56a868, 0xd0e493, 0xdc7d65, 0x5a319e,
    0x64cfb0, 0xe2834b, 0xee1abd, 0x685646, 0xf72951, 0x7165aa, 0x7dfc5c, 0xfbb0a7,
    0x0cd1e9, 0x8a9d12, 0x8604e4, 0x00481f, 0x9f3708, 0x197bf3, 0x15e205, 0x93aefe,
    0xad50d0, 0x2b1c2b, 0x2785dd, 0xa1c926, 0x3eb631, 0xb8faca, 0xb4633c, 0x322fc7,
    0xc99f60, 0x4fd39b, 0x434a6d, 0xc50696, 0x5a7981, 0xdc357a, 0xd0ac8c, 0x56e077,
    0x681e59, 0xee52a2, 0xe2cb54, 0x6487af, 0xfbf8b8, 0x7db443, 0x712db5, 0xf7614e,
    0x19a3d2, 0x9fef29, 0x9376df, 0x153a24, 0x8a4533, 0x0c09c8, 0x00903e, 0x86dcc5,
    0xb822eb, 0x3e6e10, 0x32f7e6, 0xb4bb1d, 0x2bc40a, 0xad88f1, 0xa11107, 0x275dfc,
    0xdced5b, 0x5aa1a0, 0x563856, 0xd074ad, 0x4f0bba, 0xc94741, 0xc5deb7, 0x43924c,
    0x7d6c62, 0xfb2099, 0xf7b96f, 0x71f594, 0xee8a83, 0x68c678, 0x645f8e, 0xe21375,
    0x15723b, 0x933ec0, 0x9fa736, 0x19ebcd, 0x8694da, 0x00d821, 0x0c41d7, 0x8a0d2c,
    0xb4f302, 0x32bff9, 0x3e260f, 0xb86af4, 0x2715e3, 0xa15918, 0xadc0ee, 0x2b8c15,
    0xd03cb2, 0x567049, 0x5ae9bf, 0xdca544, 0x43da53, 0xc596a8, 0xc90f5e, 0x4f43a5,
    0x71bd8b, 0xf7f170, 0xfb6886, 0x7d247d, 0xe25b6a, 0x641791, 0x688e67, 0xeec29c,
    0x3347a4, 0xb50b5f, 0xb992a9, 0x3fde52, 0xa0a145, 0x26edbe, 0x2a7448, 0xac38b3,
    0x92c69d, 0x148a66, 0x181390, 0x9e5f6b, 0x01207c, 0x876c87, 0x8bf571, 0x0db98a,
    0xf6092d, 0x7045d6, 0x7cdc20, 0xfa90db, 0x65efcc, 0xe3a337, 0xef3ac1, 0x69763a,
    0x578814, 0xd1c4ef, 0xdd5d19, 0x5b11e2, 0xc46ef5, 0x42220e, 0x4ebbf8, 0xc8f703,
    0x3f964d, 0xb9dab6, 0xb54340, 0x330fbb, 0xac70ac, 0x2a3c57, 0x26a5a1, 0xa0e95a,
    0x9e1774, 0x185b8f, 0x14c279, 0x928e82, 0x0df195, 0x8bbd6e, 0x872498, 0x016863,
    0xfad8c4, 0x7c943f, 0x700dc9, 0xf64132, 0x693e25, 0xef72de, 0xe3eb28, 0x65a7d3,
    0x5b59fd, 0xdd1506, 0xd18cf0, 0x57c00b, 0xc8bf1c, 0x4ef3e7, 0x426a11, 0xc426ea,
    0x2ae476, 0xaca88d, 0xa0317b, 0x267d80, 0xb90297, 0x3f4e6c, 0x33d79a, 0xb59b61,
    0x8b654f, 0x0d29b4, 0x01b042, 0x87fcb9, 0x1883ae, 0x9ecf55, 0x9256a3, 0x141a58,
    0xefaaff, 0x69e604, 0x657ff2, 0xe33309, 0x7c4c1e, 0xfa00e5, 0xf69913, 0x70d5e8,
    0x4e2bc6, 0xc8673d, 0xc4fecb, 0x42b230, 0xddcd27, 0x5b81dc, 0x57182a, 0xd154d1,
    0x26359f, 0xa07964, 0xace092, 0x2aac69, 0xb5d37e, 0x339f85, 0x3f0673, 0xb94a88,
    0x87b4a6, 0x01f85d, 0x0d61ab, 0x8b2d50, 0x145247, 0x921ebc, 0x9e874a, 0x18cbb1,
    0xe37b16, 0x6537ed, 0x69ae1b, 0xefe2e0, 0x709df7, 0xf6d10c, 0xfa48fa, 0x7c0401,
    0x42fa2f, 0xc4b6d4, 0xc82f22, 0x4e63d9, 0xd11cce, 0x575035, 0x5bc9c3, 0xdd8538
};



/**
 * Update the crc value with new data.
 *
 * \param crc      The current crc value.
 * \param data     Pointer to a buffer of \a data_len bytes.
 * \param data_len Number of bytes in the \a data buffer.
 * \return         The updated crc value.
 *****************************************************************************/
crc_t crc_update(crc_t crc, const unsigned char *data, size_t data_len)
{
    unsigned int tbl_idx;

    while (data_len--) {
        tbl_idx = ((crc >> 16) ^ *data) & 0xff;
        crc = (crc_table[tbl_idx] ^ (crc << 8)) & 0xffffff;

        data++;
    }
    return crc & 0xffffff;
}




/* #include <stdio.h> */
/* #define DEBUG */

void mexFunction(
    int nlhs, mxArray *plhs[],
    int nrhs, const mxArray *prhs[])
{
    crc_t crc;
    unsigned char *msg;
    mwSize input_length;
    mwSize i;
    unsigned char *output_bytes;
    const mwSize dims[]={1,3};
    
    /* check for proper number of arguments */
    if(nrhs!=1)
        mexErrMsgTxt("One input required.");
    else if(nlhs > 1)
        mexErrMsgTxt("Too many output arguments.");
    
    /* input must be a string */
    if ( mxIsUint8(prhs[0]) != 1)
        mexErrMsgTxt("Input must be uint8.");
    
    /* Get the input size */
    input_length = mxGetN(prhs[0]); /* The number of columns */
    
    /* Get the input data */
    msg = (unsigned char **)mxGetPr(prhs[0]);
    
    /* call the C subroutine */
    crc = crc_init();
    crc = crc_update(crc, msg, input_length);
    crc = crc_finalize(crc);
    
    /* Return output */
    plhs[0] = mxCreateNumericArray(2,dims,mxUINT8_CLASS,mxREAL);
    output_bytes    = (unsigned char *) mxGetData(plhs[0]);
    output_bytes[0] = (unsigned char)(crc  & 0x000000ff);
    output_bytes[1] = (unsigned char)((crc & 0x0000ff00) >> 8);
    output_bytes[2] = (unsigned char)((crc & 0x00ff0000) >> 16);
    
    #ifdef DEBUG
    /* Print some debug output */
    mexPrintf("LTE CRC24A\n");
    mexPrintf("Message: 0x");
    for(i=0;i<input_length;i++) {
        mexPrintf("%2x",msg[i]);
    }
    mexPrintf("\n");
    mexPrintf("Length:  %d\n",input_length);
    mexPrintf("Poly:    %#x\n",crc_table[1]);
    mexPrintf("CRC:     %#x\n",crc);
    mexPrintf("CRC:     '%#x' '%x' '%x'\n",output_bytes[0],output_bytes[1],output_bytes[2]);
    mexPrintf("CRC:     '%d' '%d' '%d'\n",output_bytes[0],output_bytes[1],output_bytes[2]);
    #endif
}