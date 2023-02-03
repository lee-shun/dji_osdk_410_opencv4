
/** @file dji_flight_link.hpp
 *  @version 4.0.0
 *  @date August 2019
 *
 *  @brief Implementation of flight link
 *
 *  @Copyright (c) 2019 DJI
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
#ifndef DJI_CONTROL_LINK_HPP
#define DJI_CONTROL_LINK_HPP
#include "dji_vehicle_callback.hpp"
#include "osdk_command.h"

namespace DJI {
namespace OSDK {
class FlightLink {
 public:
  FlightLink(Vehicle *vehicle);

  ~FlightLink();

  /*! Used as the type of userData to be passed in the callbackWrapperFunc to
   * wrapper the callback handling.
   *
   */
  typedef struct callbackWarpperHandler {
    void (*cb)(ErrorCode::ErrorCodeType retCode, UserData userData);
    UserData udata;
  } callbackWarpperHandler;
  typedef uint8_t retCodeType;

  void linkSendFCAsync(const uint8_t cmd[], const uint8_t *cmdData, size_t len,
                       Command_SendCallback func,
                       void (*UserCallBack)(ErrorCode::ErrorCodeType retCode, UserData userData),
                       void *userData, uint32_t timeOut, uint16_t retryTimes);

  E_OsdkStat linkSendFCSync(const uint8_t cmd[], const uint8_t *cmdData, size_t len,
                            uint8_t *ackData, uint32_t *ack_len, uint32_t timeOut, uint16_t retryTimes);

  /*! @brief wrapper the sending interface and callback for control. It should
   * be paid attention that this is only a temporary glue class of sending
   * interface and callback.
   * @TODO In the future, it will be replaced by the improvement of the protocol
   * layer.
   *
   *  @param cmd openprotocol cmd ref to DJI::OSDK::OpenProtocolCMD::CMDSet
   *  @param pdata data buf which should be send
   *  @param len the total bytes length of the pdata
   *  @param callBack callback for this send
   *  @param userData userData which will called by callBack
   */
  void sendAsync(const uint8_t cmd[], void *pdata, size_t len, void *callBack,
                 UserData userData, int timeout = 500, int retryTime = 2);
  /*! @brief wrapper the sending interface ,blocking function
   *
   * @TODO In the future, it will be replaced by the improvement of the protocol
   * layer.
   *
   *  @param cmd openprotocol cmd ref to DJI::OSDK::OpenProtocolCMD::CMDSet
   *  @param pdata data buf which should be send
   *  @param len the total bytes length of the pdata
   *  @param timeout blocking time
   */
  void *sendSync(const uint8_t cmd[], void *pdata, size_t len, int timeout);

  void sendDirectly(const uint8_t cmd[], void *pdata, size_t len);
 public:
  Vehicle *getVehicle() const;

  void setVehicle(Vehicle *value);

 private:
  Vehicle *vehicle;

};
}  // namespace OSDK
}  // namespace DJI

#endif  // DJI_CONTROL_LINK_HPP
