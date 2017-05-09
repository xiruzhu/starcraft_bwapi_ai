#pragma once
#include <BWAPI.h>
class task
{
public:

	/*
	bool 	attack (Position target, bool shiftQueueCommand=false) const
	bool 	attack (Unit target, bool shiftQueueCommand=false) const
	bool 	build (UnitType type, TilePosition target=TilePositions::None) const
	bool 	buildAddon (UnitType type) const
	bool 	train (UnitType type) const
	bool 	morph (UnitType type) const
	bool 	setRallyPoint (Unit target) const
	bool 	setRallyPoint (Position target) const
	bool 	move (Position target, bool shiftQueueCommand=false) const
	bool 	patrol (Position target, bool shiftQueueCommand=false) const
	bool 	holdPosition (bool shiftQueueCommand=false) const
	bool 	stop (bool shiftQueueCommand=false) const
	bool 	follow (Unit target, bool shiftQueueCommand=false) const
	bool 	gather (Unit target, bool shiftQueueCommand=false) const
	bool 	returnCargo (bool shiftQueueCommand=false) const
	bool 	repair (Unit target, bool shiftQueueCommand=false) const
	bool 	burrow () const
	bool 	unburrow () const
	bool 	cloak () const
	bool 	decloak () const
	bool 	siege () const
	bool 	unsiege () const
	bool 	lift () const
	bool 	load (Unit target, bool shiftQueueCommand=false) const
	bool 	unloadAll (bool shiftQueueCommand=false) const
	bool 	unloadAll (Position target, bool shiftQueueCommand=false) const
	bool 	rightClick (Unit target, bool shiftQueueCommand=false) const
	bool 	rightClick (Position target, bool shiftQueueCommand=false) const
	bool 	haltConstruction () const
	bool 	cancelConstruction () const
	bool 	cancelAddon () const
	bool 	cancelTrain (int slot=-2) const
	bool 	cancelMorph () const
	bool 	cancelResearch () const
	bool 	cancelUpgrade () const
	bool 	useTech (TechType tech, Unit target=nullptr) const
	bool 	useTech (TechType tech, Position target) const
	*/
	typedef enum {
		move,
		attack,
		build,
		build_addon,
		train,     
		gather
	}action_descriptor;

	typedef struct {
		BWAPI::TilePosition build_loc;   //Where to build
		BWAPI::UnitType target_building; //What to build
	}build_action;

	typedef struct {
		BWAPI::UnitType target_building; //What to build
	}build_addon_action;

	typedef struct {
		BWAPI::Position target_loc; //Where to move
	}move_action;

	typedef struct {
		BWAPI::Position target_loc; //Where to attack
	}attack_action;

	typedef struct {
		BWAPI::UnitType target_unit; //What to train
	}train_action;

	typedef struct {
		BWAPI::Unit target_resource; //What to gather
	}gather_action;

	
	typedef union action {
		build_action build;
		move_action move;
		attack_action attack;
		train_action train;
		gather_action gather;
		build_addon_action build_addon;

		action() { memset(this, 0, sizeof(action)); }
	};

	std::vector<int> unit_list;       //List of unit instructed with this task
	action unit_group_action;         //Action requested of this unit. 

	bool (*condition)(void *, std::vector<int>);		  //What will be called before execution to check if conditions are met
	void *condition_argument;         //What will be passed to the condition function

	BWAPI::GameWrapper *broodwar;

	task(std::vector<int> unit_group, task::action group_action, BWAPI::GameWrapper *broodwar);
	task(std::vector<int> unit_group, task::action group_action, BWAPI::GameWrapper *broodwar, bool(*condition)(void *, std::vector<int>), void *cond_arg);
	~task();

	int execute_task();            //Execute task. Will return number of failures 
};

