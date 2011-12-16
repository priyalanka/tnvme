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

#include "trackable.h"
#include "tnvme.h"


SharedTrackablePtr Trackable::NullTrackablePtr;


Trackable::Trackable(ObjType objBeingCreated)
{
    if (objBeingCreated >= OBJTYPE_FENCE) {
        LOG_DBG("Illegal constructor");
        throw exception();
    }

    mObjType = objBeingCreated;
}


Trackable::~Trackable()
{
    string obj;

    switch (mObjType) {
    case OBJ_MEMBUFFER:     obj = "MemBuffer";          break;
    case OBJ_ACQ:           obj = "ACQ";                break;
    case OBJ_ASQ:           obj = "ASQ";                break;
    case OBJ_IOCQ:          obj = "IOCQ";               break;
    case OBJ_IOSQ:          obj = "IOSQ";               break;
    case OBJ_IDENTIFY:      obj = "Identify";           break;
    case OBJ_CREATEIOCQ:    obj = "CreateIOCQ";         break;
    default:                obj = "unknown";            break;
    }
    LOG_DBG("Destroying trackable obj: %s", obj.c_str());
}