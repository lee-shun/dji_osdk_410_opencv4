/** @file dji_mfio.cpp
 *  @version 4.0.0
 *  @date April 2017
 *
 *  @brief
 *  MFIO API for DJI OSDK library
 *
 *  @Copyright (c) 2017 DJI
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

#include "dji_mfio.hpp"
#include "dji_vehicle.hpp"

using namespace DJI;
using namespace DJI::OSDK;

MFIO::MFIO(Vehicle* vehicle)
{
  this->vehicle = vehicle;
  channelUsage  = 0;
}

MFIO::~MFIO()
{
}

void
MFIO::config(MFIO::MODE mode, CHANNEL channel, uint32_t defaultValue,
             uint16_t freq, VehicleCallBack callback, UserData userData)
{
  VehicleCallBack cb = NULL;
  UserData udata = NULL;
  InitData data;

  if ((channelUsage & (1 << channel)) == 0)
  {
    // channelUsage |= (1 << channel);
    data.channel = channel;
    data.mode    = mode;
    data.value   = defaultValue;
    data.freq    = freq;

    if (callback)
    {
      cb = callback;
      udata = userData;
    }
    else
    {
      cb = initCallback;
      udata = NULL;
    }

    vehicle->legacyLinker->sendAsync(OpenProtocolCMD::CMDSet::MFIO::init,
                                     &data, sizeof(data), 500, 2, cb, udata);
  }
  else
  {
    DERROR("channel already used 0x%X,0x%X", channelUsage, 1 << channel);
  }
}

ACK::ErrorCode
MFIO::config(MFIO::MODE mode, CHANNEL channel, uint32_t defaultValue,
             uint16_t freq, int wait_timeout)
{
  ACK::ErrorCode ack;
  InitData       data;

  if ((channelUsage & (1 << channel)) == 0)
  {
    // channelUsage |= (1 << channel);
    data.channel = channel;
    data.mode    = mode;
    data.value   = defaultValue;
    data.freq    = freq;
    DSTATUS("sent");
    return *(ACK::ErrorCode *) vehicle->legacyLinker->sendSync(
        OpenProtocolCMD::CMDSet::MFIO::init, &data, sizeof(data),
        wait_timeout * 1000 / 2, 2);
  }
  else
  {
    DERROR("Channel already used 0x%X,0x%X", channelUsage, 1 << channel);
    ack.info.cmd_set = OpenProtocolCMD::CMDSet::mfio;
    ack.data         = 0xFF;
    return ack;
  }
}

void
MFIO::initCallback(Vehicle* vehicle, RecvContainer recvFrame, UserData data)
{
  /* Comment out API_LOG until we have a nicer solution, or we update calback
   * prototype
   * DSTATUS( "MFIO initMFIOCallback");
   */
  uint16_t ack_length =
    recvFrame.recvInfo.len - static_cast<uint16_t>(OpenProtocol::PackageMin);
  uint8_t* ackPtr = recvFrame.recvData.raw_ack_array;

  uint8_t errorFlag;

  memcpy((uint8_t*)&errorFlag, ackPtr, 1);
}

void
MFIO::setValue(MFIO::CHANNEL channel, uint32_t value, VehicleCallBack callback,
               UserData userData)
{

  SetData data;
  data.channel = channel;
  data.value   = value;
  VehicleCallBack cb = NULL;
  UserData udata = NULL;

  if (callback)
  {
    cb = callback;
    udata = userData;
  }
  else
  {
    cb = setValueCallback;
    udata = NULL;
  }

  vehicle->legacyLinker->sendAsync(OpenProtocolCMD::CMDSet::MFIO::set, &data,
                                   sizeof(data), 500, 2, cb, udata);
}

ACK::ErrorCode
MFIO::setValue(CHANNEL channel, uint32_t value, int wait_timeout)
{

  ACK::ErrorCode ack;
  SetData        data;
  data.channel = channel;
  data.value   = value;

  return *(ACK::ErrorCode *) vehicle->legacyLinker->sendSync(
      OpenProtocolCMD::CMDSet::MFIO::set, &data, sizeof(data),
      wait_timeout * 1000 / 2, 2);
}

void
MFIO::setValueCallback(Vehicle* vehicle, RecvContainer recvFrame, UserData data)
{

  uint16_t ack_length =
    recvFrame.recvInfo.len - static_cast<uint16_t>(OpenProtocol::PackageMin);
  uint8_t* ackPtr = recvFrame.recvData.raw_ack_array;

  uint8_t errorFlag;

  memcpy((uint8_t*)&errorFlag, ackPtr, 1);
}

void
MFIO::getValue(MFIO::CHANNEL channel, VehicleCallBack callback,
               UserData userData)
{

  GetData data;
  data = channel;
  VehicleCallBack cb = NULL;
  UserData udata = NULL;

  if (callback)
  {
    cb = callback;
    udata = userData;
  }
  else
  {
    cb = getValueCallback;
    udata = NULL;
  }

  vehicle->legacyLinker->sendAsync(OpenProtocolCMD::CMDSet::MFIO::get, &data,
                                   sizeof(data), 500, 3, cb, udata);
}

ACK::MFIOGet
MFIO::getValue(CHANNEL channel, int wait_timeout)
{
  ACK::MFIOGet ack;

  GetData data;
  data = channel;

  return *(ACK::MFIOGet *) vehicle->legacyLinker->sendSync(
      OpenProtocolCMD::CMDSet::MFIO::get, &data, sizeof(data),
      wait_timeout * 1000 / 3, 3);
}

void
MFIO::getValueCallback(Vehicle* vehicle, RecvContainer recvFrame, UserData data)
{
  uint16_t ack_length =
    recvFrame.recvInfo.len - static_cast<uint16_t>(OpenProtocol::PackageMin);
  uint8_t* ackPtr = recvFrame.recvData.raw_ack_array;

  uint8_t  result;
  uint32_t value;

  memcpy((uint8_t*)&result, ackPtr, 1);
  memcpy((uint8_t*)&value, ackPtr + 1, 4);

  DSTATUS("\n status: %d\n", result);
  DSTATUS("\n value: %d\n", value);
}
