#pragma once

#include <QtCore/QString>
#include <QtCore/QSharedPointer>

#include <qrgui/plugins/interpretedPluginInterface/interpretedPluginInterface.h>

#include "ast/identifier.h"

namespace generationRules {
namespace generator {

class IncomingLinksListGenerator
{
public:
	/// Returns list of links ids by type.
	/// @param linksIdentifierNode - first part (for example, identName in identName.incomingLinks(SpecificType)).
	/// @param linksTypeNode - second part (SpecificType in previous example).
	/// @param logicalModelInterface - information about model.
	/// @param elementId -
	static qReal::IdList generatedList(QSharedPointer<simpleParser::ast::Identifier> linksIdentifierNode
			, QSharedPointer<simpleParser::ast::Identifier> linksTypeNode
			, qReal::LogicalModelAssistInterface *logicalModelInterface
			, const qReal::Id elementId
			);
};
}
}