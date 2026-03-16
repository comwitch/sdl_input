#pragma once

#include "InputTypes.h"

class IInputBackend{
public:
virtual ~IInputBackend()=default;

virtual bool initialize()=0;
virtual void shutdown()=0;
virtual void update()=0;

virtual std::vector<DeviceId> getConnectedDevices() const=0;
virtual InputDeviceInfo getDeviceInfo(DeviceId id) const=0;
virtual bool getRawState(DeviceId id, RawDeviceState& outState) const=0;

};