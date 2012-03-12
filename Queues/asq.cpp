/*
 * Copyright (c) 2011, Intel Corporation.
 *
 *  Licensed under the Apache License, Version 2.0 (the "License");
 *  you may not use this file except in compliance with the License.
 *  You may obtain a copy of the License at
 *
 *      http://www.apache.org/licenses/LICENSE-2.0
 *
 *  Unless required by applicable law or agreed to in writing, software
 *  distributed under the License is distributed on an "AS IS" BASIS,
 *  WITHOUT WARRANTIES OR CONDITIONS OF ANY KIND, either express or implied.
 *  See the License for the specific language governing permissions and
 *  limitations under the License.
 */

#include "asq.h"
#include "globals.h"
#include "../Cmds/createIOCQ.h"

SharedASQPtr ASQ::NullASQPtr;
const uint16_t ASQ::IDEAL_ELEMENT_SIZE = 64;


ASQ::ASQ() : SQ(0, Trackable::OBJTYPE_FENCE)
{
    // This constructor will throw
}


ASQ::ASQ(int fd) : SQ(fd, Trackable::OBJ_ASQ)
{
}


ASQ::~ASQ()
{
}


void
ASQ::Init(uint16_t numEntries)
{
    SQ::Init(0, IDEAL_ELEMENT_SIZE, numEntries, 0);
}


void
ASQ::Send(SharedCmdPtr cmd)
{
    // Detect if doing something that looks suspicious/incorrect/illegal
    if ((cmd->GetCmdSet() == CMD_ADMIN) &&
        (cmd->GetOpcode() == CreateIOCQ::Opcode) &&
        cmd->GetBit(11, 1) &&                     // if IOCQ is using IRQ's, but
        (gCtrlrConfig->IrqsEnabled() == false)) { // dnvme is NOT using IRQ's

        LOG_ERR("Invoking IOCQ with IRQ's, but dnvme disabled IRQ's");
        throw FrmwkEx("Rethink test case, see gCtrlrConfig->SetIrqScheme()");
    }

    SQ::Send(cmd);
}
