#pragma once

#include <QtCore/QString>
#include <QtCore/QSharedPointer>

#include <qrgui/plugins/interpretedPluginInterface/interpretedPluginInterface.h>

#include "ast/node.h"

#include "variablesTable.h"
#include "generatorConfigurer.h"

namespace generationRules {
namespace generator {

class CommonGenerator
{
public:
	static QString generatedResult(QSharedPointer<simpleParser::ast::Node> node
			, GeneratorConfigurer generatorConfigurer
			, const QString &generatorName = ""
			, const qReal::Id elementId = qReal::Id::rootId()
			, const QString &elementType = ""
			, const QString &elementName = ""
			);
};
}
}