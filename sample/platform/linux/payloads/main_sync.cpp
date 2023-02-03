/*! @file payloads/main_sync.cpp
 *  @version 4.0.0
 *  @date July 29 2019
 *
 *  @brief
 *  main for CameraManager usage in a Linux environment.
 *  Shows example usage of CameraManager synchronous APIs.
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

#include <dji_linux_helpers.hpp>
#include "camera_manager_sync_sample.hpp"
#include "gimbal_manager_sync_sample.hpp"
#include "dji_linker.hpp"

using namespace DJI::OSDK;
using namespace DJI::OSDK::Telemetry;

int main(int argc, char **argv) {
  /*! Setup the OSDK: Read config file, create vehicle, activate. */
  LinuxSetup linuxEnvironment(argc, argv);
  Vehicle *vehicle = linuxEnvironment.getVehicle();
  if (vehicle == NULL) {
    DERROR("Vehicle not initialized, exiting.");
    return -1;
  }

  /*! Create an example object, which users can modify according to their own needs */
  CameraManagerSyncSample *p = new CameraManagerSyncSample(vehicle);
  GimbalManagerSyncSample *g = new GimbalManagerSyncSample(vehicle);

  /*! check whether enviroment passing valid running parameter or not */
  bool sampleCaseValidFlag = false;
  char inputChar = 0;
  std::string sampleCase = linuxEnvironment.getEnvironment()->getSampleCase();
  if (sampleCase.size() == 1) {
    if ((sampleCase <= "n") && (sampleCase >= "a")) {
      inputChar = sampleCase[0];
    } else {
      inputChar = 0;
      DERROR("sample_case is an invalid string !");
      sleep(2);
    }
  }

  /*! sample loop start */
  while (true) {
    std::cout << std::endl;
    std::cout
        << "| Available commands:                                            |\n"
        << "| [a] Set camera shutter speed                                   |\n"
        << "|     Main camera : X5S, X7, Z30, H20/H20T(zoom mode) etc.       |\n"
        << "| [b] Set camera aperture                                        |\n"
        << "|     Main camera : X5S, X7, Z30, H20/H20T(zoom mode) etc.       |\n"
        << "| [c] Set camera EV value                                        |\n"
        << "|     Main camera : X5S, X7, Z30, H20/H20T(zoom mode) etc.       |\n"
        << "| [d] Set camera ISO value                                       |\n"
        << "|     Main camera : X5S, X7, Z30, H20/H20T(zoom mode) etc.       |\n"
        << "| [e] Set camera focus point                                     |\n"
        << "|     Main camera : X5S, X7, H20/H20T(zoom mode) etc.            |\n"
        << "| [f] Set camera tap zoom point                                  |\n"
        << "|     Vice camera : Z30, H20/H20T(zoom mode) etc.                |\n"
        << "| [g] Set camera zoom parameter                                  |\n"
        << "|     Vice camera : Z30, H20/H20T(zoom mode) etc.                |\n"
        << "| [h] Shoot Single photo Sample                                  |\n"
        << "|     Main camera : X5S, X7, XTS, Z30, H20/H20T etc.             |\n"
        << "| [i] Shoot AEB photo Sample                                     |\n"
        << "|     Main camera : X5S, X7 etc.                                 |\n"
        << "| [j] Shoot Burst photo Sample                                   |\n"
        << "|     Main camera : X5S, X7 etc.                                 |\n"
        << "| [k] Shoot Interval photo Sample                                |\n"
        << "|     Main camera : X5S, X7, XTS, Z30, H20/H20T etc.             |\n"
        << "| [l] Record video Sample                                        |\n"
        << "|     Main camera : X5S, X7, XTS, Z30, H20/H20T etc.             |\n"
        << "| [m] Rotate gimbal sample                                       |\n"
        << "|     Main camera : X5S, X7, XTS, Z30, H20/H20T etc.             |\n"
        << "| [n] Reset gimbal sample                                        |\n"
        << "|     Main camera : X5S, X7, XTS, Z30, H20/H20T etc.             |\n"
        << "| [q] Quit                                                       |\n";

    if (inputChar != 0) {
      sampleCaseValidFlag = true;
      DSTATUS("Get inputChar from argv, case [%c] will be executed", inputChar);
      sleep(3);
    } else {
      std::cin >> inputChar;
    }

    switch (inputChar) {
      case 'a':
        p->setExposureModeSyncSample(
            PAYLOAD_INDEX_0, CameraModule::ExposureMode::SHUTTER_PRIORITY);
        p->setShutterSpeedSyncSample(
            PAYLOAD_INDEX_0, CameraModule::ShutterSpeed::SHUTTER_SPEED_1_100);
        sleep(2);
        break;
      case 'b':
        p->setExposureModeSyncSample(
            PAYLOAD_INDEX_0, CameraModule::ExposureMode::APERTURE_PRIORITY);
        p->setApertureSyncSample(PAYLOAD_INDEX_0,
                                 CameraModule::Aperture::F_4);
        sleep(2);
        break;
      case 'c':
        p->setExposureModeSyncSample(PAYLOAD_INDEX_0,
                                     CameraModule::ExposureMode::PROGRAM_AUTO);
        p->setEVSyncSample(PAYLOAD_INDEX_0,
                           CameraModule::ExposureCompensation::P_0_3);
        sleep(2);
        break;
      case 'd':
        p->setExposureModeSyncSample(
            PAYLOAD_INDEX_0, CameraModule::ExposureMode::EXPOSURE_MANUAL);
        p->setISOSyncSample(PAYLOAD_INDEX_0, CameraModule::ISO::ISO_200);
        sleep(2);
        break;
      case 'e':
        p->setFocusPointSyncSample(PAYLOAD_INDEX_0, 0.8, 0.8);
        break;
      case 'f':
        p->setTapZoomPointSyncSample(PAYLOAD_INDEX_1, 5, 0.3, 0.3);
        sleep(5);
        p->setTapZoomPointSyncSample(PAYLOAD_INDEX_1, 5, 0.8, 0.7);
        sleep(5);
        break;
      case 'g':
        p->setZoomSyncSample(PAYLOAD_INDEX_1, 5);
        sleep(4);
        p->setZoomSyncSample(PAYLOAD_INDEX_1, 10);
        sleep(4);
        p->startZoomSyncSample(PAYLOAD_INDEX_1,
                               CameraModule::ZoomDirection::ZOOM_OUT,
                               CameraModule::ZoomSpeed::FASTEST);
        sleep(8);
        p->stopZoomSyncSample(PAYLOAD_INDEX_1);
        break;
      case 'h':
        p->startShootSinglePhotoSyncSample(PAYLOAD_INDEX_0);
        break;
      case 'i':
        p->startShootAEBPhotoSyncSample(
            PAYLOAD_INDEX_0, CameraModule::PhotoAEBCount::AEB_COUNT_5);
        break;
      case 'j':
        p->startShootBurstPhotoSyncSample(
            PAYLOAD_INDEX_0, CameraModule::PhotoBurstCount::BURST_COUNT_7);
        break;
      case 'k':
        CameraModule::PhotoIntervalData intervalData;
        intervalData.photoNumConticap = 255;
        intervalData.timeInterval = 3;
        p->startShootIntervalPhotoSyncSample(PAYLOAD_INDEX_0, intervalData);
        DSTATUS("Sleep 15 seconds");
        sleep(15);
        p->shootPhotoStopSyncSample(PAYLOAD_INDEX_0);
        break;
      case 'l':
        p->startRecordVideoSyncSample(PAYLOAD_INDEX_0);
        sleep(10);
        p->stopRecordVideoSyncSample(PAYLOAD_INDEX_0);
        break;
      case 'm':
        DSTATUS("Current gimbal %d angle (p,r,y) = (%0.2f°, %0.2f°, %0.2f°)", PAYLOAD_INDEX_0,
                g->getGimbalData(PAYLOAD_INDEX_0).pitch,
                g->getGimbalData(PAYLOAD_INDEX_0).roll,
                g->getGimbalData(PAYLOAD_INDEX_0).yaw);
        GimbalModule::Rotation rotation;
        rotation.roll = 0.0f;
        rotation.pitch = 25.0f;
        rotation.yaw = 90.0f;
        rotation.rotationMode = 0;
        rotation.time = 0.5;
        g->rotateSyncSample(PAYLOAD_INDEX_0, rotation);
        sleep(2);
        DSTATUS("Current gimbal %d angle (p,r,y) = (%0.2f°, %0.2f°, %0.2f°)", PAYLOAD_INDEX_0,
                g->getGimbalData(PAYLOAD_INDEX_0).pitch,
                g->getGimbalData(PAYLOAD_INDEX_0).roll,
                g->getGimbalData(PAYLOAD_INDEX_0).yaw);
        break;
      case 'n':
        DSTATUS("Current gimbal %d angle (p,r,y) = (%0.2f°, %0.2f°, %0.2f°)", PAYLOAD_INDEX_0,
                g->getGimbalData(PAYLOAD_INDEX_0).pitch,
                g->getGimbalData(PAYLOAD_INDEX_0).roll,
                g->getGimbalData(PAYLOAD_INDEX_0).yaw);
        g->resetSyncSample(PAYLOAD_INDEX_0);
        sleep(2);
        DSTATUS("Current gimbal %d angle (p,r,y) = (%0.2f°, %0.2f°, %0.2f°)", PAYLOAD_INDEX_0,
                g->getGimbalData(PAYLOAD_INDEX_0).pitch,
                g->getGimbalData(PAYLOAD_INDEX_0).roll,
                g->getGimbalData(PAYLOAD_INDEX_0).yaw);
        break;
      case 'q':
        DSTATUS("Quit now ...");
        delete p;
        delete g;
        return 0;
      default:
        break;
    }
    DSTATUS("Sample end ...");
    sleep(2);
    if (sampleCaseValidFlag) break;
    inputChar = 0;
  }
  delete p;
  delete g;
  return 0;
}
