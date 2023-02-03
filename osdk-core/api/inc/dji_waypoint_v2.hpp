/** @file dji_waypoint_v2.hpp
 *  @version 4.0.0
 *  @date April 2019
 *
 *  @brief Implementation of GPS Waypoint Missions for DJI OSDK
 *
 *  @Copyright (c) 2016-2020 DJI
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

#ifndef DJI_WAYPOINT_MISSION_V2_HPP
#define DJI_WAYPOINT_MISSION_V2_HPP

#include <vector>
#include "osdk_command.h"
#include "dji_mission_base.hpp"
#include "dji_waypoint_v2_action.hpp"

namespace DJI
{
namespace OSDK
{
  /*! @brief callback type to get the pushing data from waypoint 2.0
   *
   *  @platforms M300
   */
  typedef E_OsdkStat (*PushCallback)(struct _CommandHandle *cmdHandle,
                                     const T_CmdInfo *cmdInfo,
                                     const uint8_t *cmdData, void *userData);

 /*! The waypoint operator is the only object that controls, runs and monitors
  *  Waypoint v2 Missions.
  */
  class WaypointV2MissionOperator
  {
  public:
    const uint16_t MAX_WAYPOINT_NUM_SIGNAL_PUSH = 260;

    WaypointV2MissionOperator(Vehicle* vehiclePtr);

    ~WaypointV2MissionOperator();

    /*! @brief Init waypoint v2 mission settings
     *
     *  @platforms M300
     *  @param Info init settings struct DJI::OSDK::WayPointV2InitSettings
     *  @param timeout blocking timeout in seconds
     *  @return ErrorCode::ErrorCodeType error code
     */
    ErrorCode::ErrorCodeType init(WayPointV2InitSettings *info, int timeout);

    /*! @brief Download the waypoint v2 init settings
     *
     *  @platforms M300
     *  @param Info init settings struct DJI::OSDK::WayPointV2InitSettingsInternal
     *  @param timeout blocking timeout in seconds
     *  @return ErrorCode::ErrorCodeType error code
     */
    ErrorCode::ErrorCodeType downloadInitSetting(WayPointV2InitSettingsInternal &info, int timeout);

   /*! @brief Start　execute waypoint v2 mission
    *
    *  @platforms M300
    *  @param timeout blocking timeout in seconds
    *  @return ErrorCode::ErrorCodeType error code
    */
    ErrorCode::ErrorCodeType start(int timeout);

   /*! @brief Stop execute waypoint v2 mission
    *
    *  @platforms M300
    *  @param timeout blocking timeout in seconds
    *  @return ErrorCode::ErrorCodeType error code
    */
    ErrorCode::ErrorCodeType stop(int timeout);

   /*! @brief Pause waypoint v2 mission
    *
    *  @platforms M300
    *  @param timeout blocking timeout in seconds
    *  @return ErrorCode::ErrorCodeType error code
    */
    ErrorCode::ErrorCodeType pause(int timeout);

   /*! @brief Resume waypoint v2 mission
    *
    *  @platforms M300
    *  @param timeout blocking timeout in seconds
    *  @return ErrorCode::ErrorCodeType error code
    */
    ErrorCode::ErrorCodeType resume(int timeout);

    /*! @brief Upload all the waypoint v2 mission
     *
    *  @platforms M300
     *  @param mission vector contains of a series of WaypointV2,
     *  refer the definition of DJI::OSDK::WaypointV2
     *  @param timeout blocking timeout in seconds
     *  @return ErrorCode::ErrorCodeType error code
     */
    ErrorCode::ErrorCodeType uploadMission(int timeout);

    /*! @brief Download all the waypoint v2 mission
     *
    *  @platforms M300
     *  @param mission vector contains of a series of WaypointV2,
     *  refer the definition of DJI::OSDK::WaypointV2
     *  @param timeout blocking timeout in seconds
     *  @return ErrorCode::ErrorCodeType error code
     */
    ErrorCode::ErrorCodeType downloadMission(std::vector<WaypointV2> &mission, int timeout);

   /*! @brief Get the global cruise speed setting from flight controller
    *
    *  @platforms M300
    *  @param cruiseSpeed auto cruise speed refer to
    *  definition of DJI::OSDK::GlobalCruiseSpeed,
    *  @param timeout blocking timeout in seconds
    *  @return ErrorCode::ErrorCodeType error code, 0: success, other: fail
    */
    ErrorCode::ErrorCodeType getGlobalCruiseSpeed(GlobalCruiseSpeed &cruiseSpeed, int timeout);

   /*! @brief Set the global cruise speed to flight controller
    *
    *  @platforms M300
    *  @param cruiseSpeed auto cruise speed refer to
    *  definition of DJI::OSDK::GlobalCruiseSpeed,
    *  cruiseSpeed must in the range of [0, WayPointV2InitSettings::maxFlightSpeed]
    *  @param timeout blocking timeout in seconds
    *  @return ErrorCode::ErrorCodeType error code, 0: success, other: fail
    */
    ErrorCode::ErrorCodeType setGlobalCruiseSpeed(const GlobalCruiseSpeed &cruiseSpeed, int timeout);

   /*! @brief Upload all actions to flight controller
    *
    *  @platforms M300
    *  @param actions vector contains of a series of action,
    *  refer for the definition  of DJI::OSDK::DJIWaypointV2Action
    *  @param timeout blocking timeout in seconds
    *  @return ErrorCode::ErrorCodeType error code
    */
    ErrorCode::ErrorCodeType uploadAction(std::vector<DJIWaypointV2Action> &actions, int timeout);

   /*! @brief Get action's remain memory
    *
    *  @platforms M300
    *  @param remainRamAck contains total memory and remain memory
    *  refer to the definition of DJI::OSDK::GetRemainRamAck
    *  @param timeout blocking timeout in seconds
    *  @return ErrorCode::ErrorCodeType error code
    */
    ErrorCode::ErrorCodeType getActionRemainMemory(GetRemainRamAck &remainRamAck, int timeout);

   /*! @brief Get mission's waypoint start index and end index
    *
    *  @platforms M300
    *  @param startEndIndexAck contains start index and end index
    *  refer to the definition of DJI::OSDK::GetWaypontStartEndIndexAck
    *  @param timeout blocking timeout in seconds
    *  @return ErrorCode::ErrorCodeType error code
    */
    ErrorCode::ErrorCodeType getWaypointIndexInList(GetWaypontStartEndIndexAck &startEndIndexAck, int timeout);

   /*! @brief Get current status of the mission executing process
    *
    *  @platforms M300
    *  @return DJIWaypointV2MissionState state
    */
    inline DJIWaypointV2MissionState getCurrentState() { return currentState; }

   /*! @brief Get previous status of the mission executing process
    *
    *  @platforms M300
    *  @return DJIWaypointV2MissionState state
    */
    inline DJIWaypointV2MissionState getPrevState() { return prevState; }

    /*! @brief Set previous status of the mission executing process
     *
     *  @platforms M300
     */
    void setPrevState(DJIWaypointV2MissionState state) {prevState = state; }

    /*! @brief Set current state of the waypoint V2 mission
     *
     *  @platforms M300
     */
    void setCurrentState(DJIWaypointV2MissionState state) {currentState = state; }

    /*! @brief Get the take-off altitude of waypoint V2 mission
     *
     *  @platforms M300
     *  @return Waypoint Mission take-off altitude
     */
    float32_t getTakeoffAltitude(){return takeoffAltitude;};

    /*! @brief set the take-off altitude of waypoint V2 mission
     *
     *  @platforms M300
     */
    void setTakeoffAltitude(float32_t altitude){ takeoffAltitude =  altitude;};

    /*! @brief Subscribe to waypointV2 event with a callback function
    *
    *  @platforms M300
    *  @param cb callback function.default:null
    */
    void RegisterMissionEventCallback(void *userData, PushCallback cb = NULL);

    /*! @brief Subscribe to waypointV2 mission state with a callback function
    *
    *  @platforms M300
    *  @param cb callback function.default:null
    */
    void RegisterMissionStateCallback(void *userData, PushCallback cb = NULL) ;

  private:
    std::vector<WaypointV2> missionV2;
    DJIWaypointV2MissionState currentState;
    DJIWaypointV2MissionState prevState;
    Vehicle *vehiclePtr;

    float32_t takeoffAltitude;

    void RegisterOSDInfoCallback(Vehicle *vehiclePtr);

  };

} // namespace OSDK
} // namespace DJI

#endif // DJI_WAYPOINT_MISSION_V2_HPP
