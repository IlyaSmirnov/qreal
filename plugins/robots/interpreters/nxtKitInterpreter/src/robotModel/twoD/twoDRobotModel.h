#pragma once

#include <robotModel/nxtRobotModelBase.h>

namespace nxtKitInterpreter {
namespace robotModel {
namespace real {

class TwoDRobotModel : public NxtRobotModelBase
{
	Q_OBJECT

public:
	QString name() const override;
	QString friendlyName() const override;
};

}
}
}