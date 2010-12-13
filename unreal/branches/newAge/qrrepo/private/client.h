#pragma once

#include "../../qrgui/kernel/definitions.h"
#include "../../qrgui/kernel/ids.h"
#include "classes/object.h"
#include "qrRepoGlobal.h"
#include "serializer.h"

#include <QHash>

namespace qrRepo {

	namespace details {

		class Client
		{
		public:
			QRREPO_EXPORT Client(QString const &workingDirectory);
			QRREPO_EXPORT ~Client();
			qReal::IdList children(const qReal::Id &id) const;
			qReal::IdList parents(const qReal::Id &id) const;
			void addParent(const qReal::Id &id, const qReal::Id &parent);
			void addChild(const qReal::Id &id, const qReal::Id &child);
			void addChild(const qReal::Id &id, const qReal::Id &child, qReal::Id const &logicalId);
			void removeParent(const qReal::Id &id, const qReal::Id &parent);
			void removeChild(const qReal::Id &id, const qReal::Id &child);
			void setProperty(const qReal::Id &id, const QString &name, const QVariant &value);
			QVariant property(const qReal::Id &id, const QString &name) const;
			void removeProperty(const qReal::Id &id, const QString &name);
			bool hasProperty(const qReal::Id &id, const QString &name) const;

			qReal::IdList elements() const;

			void svnUpdate();
			void svnCommit();

			void printDebug() const;

			void exterminate();
			void open(QString const &workingDir);

			bool exist(qReal::Id const &id) const;


			void saveAll() const;
			void save(qReal::IdList list) const;
			void remove(qReal::IdList list) const;
			void setWorkingDir(QString const &workingDir);
			void log(QString const message, const qReal::Id diagram);

			qReal::IdList idsOfAllChildrenOf(qReal::Id id) const;
			QList<Object*> allChildrenOf(qReal::Id id) const;
		private:
			void init();

			void loadFromDisk();
			void addChildrenToRootObject();

			QHash<qReal::Id, Object*> mObjects;
			Serializer serializer;
		};

	}

}
