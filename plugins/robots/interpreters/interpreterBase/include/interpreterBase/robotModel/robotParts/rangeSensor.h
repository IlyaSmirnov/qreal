#pragma once

#include "scalarSensor.h"

#include "interpreterBase/interpreterBaseDeclSpec.h"

namespace interpreterBase {
namespace robotModel {
namespace robotParts {

class ROBOTS_INTERPRETER_BASE_EXPORT RangeSensor : public ScalarSensor
{
	Q_OBJECT

public:
	/// @todo: remove it
	static QString friendlyName();
	static DeviceInfo::Direction direction();

	RangeSensor(DeviceInfo const &info, PortInfo const &port);
};

}
}
}
