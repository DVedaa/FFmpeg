/*
 * Copyright (c) 2004 Michael Niedermayer <michaelni@gmx.at>
 *
 * This file is part of FFmpeg.
 *
 * FFmpeg is free software; you can redistribute it and/or
 * modify it under the terms of the GNU Lesser General Public
 * License as published by the Free Software Foundation; either
 * version 2.1 of the License, or (at your option) any later version.
 *
 * FFmpeg is distributed in the hope that it will be useful,
 * but WITHOUT ANY WARRANTY; without even the implied warranty of
 * MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the GNU
 * Lesser General Public License for more details.
 *
 * You should have received a copy of the GNU Lesser General Public
 * License along with FFmpeg; if not, write to the Free Software
 * Foundation, Inc., 51 Franklin Street, Fifth Floor, Boston, MA 02110-1301 USA
 */

#include <stdint.h>

#include "libavutil/avassert.h"
#include "libavutil/integer.h"
#include "libavutil/intmath.h"

int test(int64_t a, int64_t b) {
    AVInteger ai= av_int2i(a);
    AVInteger bi= av_int2i(b);

    av_assert0(av_i2int(ai) == a);
    av_assert0(av_i2int(bi) == b);
    av_assert0(av_i2int(av_add_i(ai,bi)) == a+b);
    av_assert0(av_i2int(av_sub_i(ai,bi)) == a-b);
    av_assert0(av_i2int(av_mul_i(ai,bi)) == a*b);
    av_assert0(av_i2int(av_shr_i(ai, 9)) == a>>9);
    av_assert0(av_i2int(av_shr_i(ai,-9)) == a<<9);
    av_assert0(av_i2int(av_shr_i(ai, 17)) == a>>17);
    av_assert0(av_i2int(av_shr_i(ai,-17)) == a<<17);
    av_assert0(av_log2_i(ai) == av_log2(a));
    av_assert0(av_i2int(av_div_i(ai,bi)) == a/b);
}

int LLVMTestOneInput( const uint8_t *data, size_t size ) {
    if (size < 2 * sizeof(int64_t))
        return 1;

    int64_t a,b;
    memcpy(&a,data,sizeof(int64_t));
    memcpy(&b,&(data[sizeof(int64_t)]),sizeof(int64_t));
    test(a,b);
    return 0;
}
