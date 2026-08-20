/*
				Copyright <SWGEmu>
		See file COPYING for copying conditions.*/

#ifndef STATMIGRATIONTARGETSMESSAGE_H_
#define STATMIGRATIONTARGETSMESSAGE_H_

#include "engine/service/proto/BaseMessage.h"

class StatMigrationTargetsMessage : public BaseMessage {
public:
	StatMigrationTargetsMessage(CreatureObject* creo) : BaseMessage() {
		insertShort(0x09);
		insertInt(0xEFAC38C4);  // CRC

		const DeltaVector<int>* baseHam = creo->getBaseHAM();

		int pointsRemaining = PlayerCreationManager::instance()->getTotalAttributeLimit(creo->getSpeciesName());

		for (int i = 0; i < 9; ++i) {
			int value = baseHam->get(i);

			insertInt(value);
			pointsRemaining -= value;
		}

		insertInt(pointsRemaining);

		setCompression(true);
	}

	StatMigrationTargetsMessage(CreatureObject* creo, MigrateStatsSession* stats) {
		insertShort(0x09);
		insertInt(0xEFAC38C4);  // CRC

		int totalLimit = PlayerCreationManager::instance()->getTotalAttributeLimit(creo->getSpeciesName());

		for (int i = 0; i < 9; ++i) {
			int val = stats->getAttribtueToModify(i);

			totalLimit -= val;

			insertInt(val);
		}

		insertInt(totalLimit);

		setCompression(true);
	}

};

#endif /*STATMIGRATIONTARGETSMESSAGE_H_*/
