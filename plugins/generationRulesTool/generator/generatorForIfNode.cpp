#include "generatorForIfNode.h"

#include "ast/condition.h"
#include "ast/program.h"

#include "auxiliaryGenerators/generatorForCondition.h"
#include "generatorForProgramNode.h"

using namespace generationRules::generator;
using namespace simpleParser::ast;

QString GeneratorForIfNode::generatedResult(QSharedPointer<IfNode> ifNode, GeneratorConfigurer generatorConfigurer)
{
	const auto condition = qrtext::as<Condition>(ifNode->condition());
	const auto conditionSatisfied = ConditionGenerator::conditionSatisfied(condition, generatorConfigurer);

	const auto trueBranch = qrtext::as<Program>(ifNode->trueBranch());
	const auto falseBranch = qrtext::as<Program>(ifNode->falseBranch());

	if (conditionSatisfied) {
		return GeneratorForProgramNode::generatedResult(trueBranch, generatorConfigurer);
	} else {
		if (falseBranch) {
			return GeneratorForProgramNode::generatedResult(falseBranch, generatorConfigurer);
		}

		return "";
	}
}