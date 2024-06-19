#pragma once
#include <iostream>
#include <vector>
#include "Player.hpp"
#include <map>
#include <functional>
#include "../core/Manager/EntityManager.hpp"
/*
*		
		quests could be implemented using a vector since the quests in this game will be sequential
		each element could have a state => locked, inProgress, Completed. 
		Ultimately we want a quest data base to store the information of all these quests such as the objective and any multistep objectives.
*		Once each quest's data has been assigned we can query quests by id and pull all that information through. 



*/



/*
	maybe data base can map these ids to a proccess such as a validate or check on the player e.g bool queryProcess(Quest*  quest)
	that looks up by id and does a check on the player for what needs to be done to complete the quest.

	return _processLookUp[quest->getID()].process(player);

	say the table is like so


	QUEST_ID | POCESSES
	--------------------
	QUEST_1  |  process(player);


	this process will have the necessary checks to determine if the player has complete the quest

	process(player) {
		does player have this specific item ? return true : false;
	}




*/


enum class QuestID {
	QUEST_INVALID = -1,
	QUEST_A_NEW_BEGINNING,

};

struct QuestState {
	bool locked = true;
	bool inProgress = false;
	bool completed = false;
	QuestState() {};

	void unlock() {
		this->locked = false;
		this->inProgress = true;
	};

	void lock() {
		this->locked = true;
		this->inProgress = false;
	}

	void complete() {
		completed = true;
		inProgress = false;
		locked = false;
	}


	bool isLocked() const {
		return locked;
	}

	bool isInProgress() const {
		return inProgress;
	}

	bool isCompleted() const {
		return completed;
	}

	void setInProgress() {
		locked = false;
		inProgress = true;
		completed = false;
		
	}



	~QuestState() = default;
};

class Quest {

	using Process = std::function<bool()>;
	Process process;
	std::string _title = "";
	QuestID _id = QuestID::QUEST_INVALID;


public:
	QuestState state{};
	

	Quest(const std::string& title, QuestID id, const int required, Process processCallback) : _title(title), _id(id), RequiredLevel(required), process(std::move(processCallback)) {};

	int RequiredLevel = 0;

	std::string GetTitle() const {
		return _title;
	}

	bool processed() {
		return process();
	}

	~Quest() {};
};


class QuestDB {

protected:
	std::map<int, Quest*> table;
	Player* player;

	
	void initQuests() {
		table[(int)QuestID::QUEST_A_NEW_BEGINNING] = new Quest("A new Beginning", QuestID::QUEST_A_NEW_BEGINNING, 0, [this]() -> bool {
			
			static size_t __func_calls = 0;

			static Core::Physics::Vec2D plStartingPos;

			if (__func_calls == 0) {
				plStartingPos = player->GetPos();

				__func_calls++;
			}

			Core::Physics::Vec2D plCurrentPos = player->GetPos();

			float x1 = plStartingPos.x;
			float x2 = plCurrentPos.x;
			float y1 = plStartingPos.y;
			float y2 = plCurrentPos.y;
			float dx = x2 - x1;
			float dy = y2 - y1;

			float distance = std::sqrt((dx) * dx + (dy) * dy);


			if (distance >= 500) {
				return true;
			}


			
			return false;
		});
	};

public:
	QuestDB(Player* player) {
		this->player = player;
		initQuests();
	};

	void Update() {
		
		for (auto& pair : table) {
			if (pair.second) {
				
				if (player->CurrentLevel >= pair.second->RequiredLevel && !pair.second->state.isCompleted()) {
					pair.second->state.setInProgress();
				}

				
				
				if (pair.second->state.isInProgress() && !pair.second->state.isCompleted()) {
					
					if (pair.second->processed()) {
						std::cout << pair.second->GetTitle();
						pair.second->state.complete();
					}
				}
			}
		
			
		}
	
		
	}

	[[nodiscard]] std::map<int, Quest*>& GetTable() {
		return table;
	};

	~QuestDB() {};
};


