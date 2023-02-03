
/** @file dji_mop_pipeline_manager_base.cpp
 *  @version 4.0.0
 *  @date January 2020
 *
 *  @brief Implementation of mop pipeline manager base
 *
 *  @Copyright (c) 2020 DJI
 *
 * Permission is hereby granted, free of charge, to any person obtaining a copy
 * of this software and associated documentation files (the "Software"), to deal
 * in the Software without restriction, including without limitation the rights
 * to use, copy, modify, merge, publish, distribute, sublicense, and/or sell
 * copies of the Software, and to permit persons to whom the Software is
 * furnished to do so, subject to the following conditions:
 *
 * The above copyright notice and this permission notice shall be included in
 * all copies or substantial portions of the Software.
 *
 * THE SOFTWARE IS PROVIDED "AS IS", WITHOUT WARRANTY OF ANY KIND, EXPRESS OR
 * IMPLIED, INCLUDING BUT NOT LIMITED TO THE WARRANTIES OF MERCHANTABILITY,
 * FITNESS FOR A PARTICULAR PURPOSE AND NONINFRINGEMENT. IN NO EVENT SHALL THE
 * AUTHORS OR COPYRIGHT HOLDERS BE LIABLE FOR ANY CLAIM, DAMAGES OR OTHER
 * LIABILITY, WHETHER IN AN ACTION OF CONTRACT, TORT OR OTHERWISE, ARISING FROM,
 * OUT OF OR IN CONNECTION WITH THE SOFTWARE OR THE USE OR OTHER DEALINGS IN THE
 * SOFTWARE.
 *
 */

#include "dji_mop_pipeline_manager_base.hpp"
#include "mop.h"
#include "mop_entry_osdk.h"
#include "osdk_command.h"
#include <map>
#include <atomic>

map<PipelineID, MopPipeline*> pipelineMap;
static std::atomic<uint16_t> mopObjectCnt(0);

MopPipelineManagerBase::MopPipelineManagerBase() {
  pipelineMap.clear();
}

MopPipelineManagerBase::~MopPipelineManagerBase() {
  if (mopObjectCnt) {
    mopObjectCnt--;
    OsdkCommand_DestroyMopTask();
    DSTATUS("MOP background task now is deleted.");
  }
  pipelineMap.clear();
}

MopErrCode MopPipelineManagerBase::create(PipelineID id, MopPipeline *&p) {
  /*! Check the entry env */
  checkEntry();
  p = new MopPipeline(id, UNRELIABLE);
  if (p) {
    pipelineMap.insert(map<PipelineID, MopPipeline *>::value_type(id, p));
    return MOP_PASSED;
  } else {
    return MOP_NOMEM;
  }
}

MopErrCode MopPipelineManagerBase::destroy(PipelineID id) {
  /*! Check the entry env */
  checkEntry();
  if (pipelineMap.find(id)!=pipelineMap.end()) {
    delete pipelineMap[id];
    pipelineMap.erase(id);
  }

  return MOP_PASSED;
}

void MopPipelineManagerBase::checkEntry() {
  if (!mopObjectCnt) {
    mopObjectCnt++;
    OsdkCommand_CreateMopTask();
    //DSTATUS("MOP background task now is created .");
  }
}