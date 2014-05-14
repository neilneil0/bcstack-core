/*
  Copyright 2013-2014 bcstack.org

   Licensed under the Apache License, Version 2.0 (the "License");
   you may not use this file except in compliance with the License.
   You may obtain a copy of the License at

       http://www.apache.org/licenses/LICENSE-2.0

   Unless required by applicable law or agreed to in writing, software
   distributed under the License is distributed on an "AS IS" BASIS,
   WITHOUT WARRANTIES OR CONDITIONS OF ANY KIND, either express or implied.
   See the License for the specific language governing permissions and
   limitations under the License.
*/

#ifdef EXPERIMENTAL

#include "bluetooth.h"

#define RFCOMM_SEND_UA_FLAG    0x01

static struct {
    u8 output_mask;
    struct {
        u8 initiator;
        u8 dlci;
        u8 flags;
    } channels[CFG_RFCOMM_NUM_CHANNELS];
} rfcomm;

#define RFCOMM_MARK_OUTPUT(ch, flag)            \
    do {                                        \
    rfcomm.channels[ch].flags |= flag;          \
    rfcomm.output_mask |= (1 << ch);            \
    } while(0)

static void rfcomm_input_sabm(u8* input, u16 isize);
static void rfcomm_input_ua(u8* input, u16 isize);
static void rfcomm_input_disc(u8* input, u16 isize);
static void rfcomm_input_dm(u8* input, u16 isize);
static void rfcomm_input_uih(u8* input, u16 isize);

static void rfcomm_output_sabm(u8 ch, u8* output, u16 osize);
static void rfcomm_output_ua(u8 ch, u8* output, u16 osize);
static void rfcomm_output_disc(u8 ch, u8* output, u16 osize);
static void rfcomm_output_dm(u8 ch, u8* output, u16 osize);
static void rfcomm_output_uih(u8 ch, u8* output, u16 osize);

u8 rfcomm_input(u8* input, u16 isize)
{
    u8 type = input[1];

    switch (type) {
    case RFCOMM_SABM: rfcomm_input_sabm(input, isize); break;
    case RFCOMM_UA:   rfcomm_input_ua(input, isize);   break;
    case RFCOMM_DISC: rfcomm_input_disc(input, isize); break;
    case RFCOMM_DM:   rfcomm_input_dm(input, isize);   break;
    case RFCOMM_UIH:  rfcomm_input_uih(input, isize);  break;
    }

    if (rfcomm.output_mask) return 1;
    else return 0;
}

static void rfcomm_input_sabm(u8* input, u16 isize)
{
    u8 dlci = input[0] >> 2;
    u8 ch = dlci >> 1;

    if (dlci == 0) {
        RFCOMM_MARK_OUTPUT(0, RFCOMM_SEND_UA_FLAG);
        return;
    }

    if (ch == 1) {
        RFCOMM_MARK_OUTPUT(0, RFCOMM_SEND_UA_FLAG);
        return;
    }
}

static void rfcomm_input_ua(u8* input, u16 isize)
{
}

static void rfcomm_input_disc(u8* input, u16 isize)
{
}

static void rfcomm_input_dm(u8* input, u16 isize)
{
}

static void rfcomm_input_uih(u8* input, u16 isize)
{
}

u8 rfcomm_output(u8 ch, u8* output, u16* osize)
{
    u8 ch;

    if (rfcomm.output_mask & 1) ch = 0;
    else ch = 1;

    if (rfcomm.channels[ch].flags & RFCOMM_SEND_UA_FLAG) {
        rfcomm.channels[ch].flags &= ~RFCOMM_SEND_UA_FLAG;
        rfcomm_output_ua(ch, output, osize);
    }

    if (rfcomm.output_mask) return 1;
    else return 0;
}

static void rfcomm_output_sabm(u8 ch, u8* output, u16 osize)
{
}

static void rfcomm_output_ua(u8 ch, u8* output, u16 osize)
{
	output[0] = 1 | ((!s->initiator) << 1) | (rfcomm.channels[ch].dlci << 2);
	output[1] = RFCOMM_UA;
	output[2]  = 0;
	output[3]  = __fcs2((u8 *) &cmd);
}

static void rfcomm_output_disc(u8 ch, u8* output, u16 osize)
{
}

static void rfcomm_output_dm(u8 ch, u8* output, u16 osize)
{
}

static void rfcomm_output_uih(u8 ch, u8* output, u16 osize)
{
}

#endif // EXPERIMENTAL
