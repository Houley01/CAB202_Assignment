# *********************************************
# *        Student Name: Ethan Houley         *
# *      Student Number: n10353950            *
# *           File Name: n10353950_bash.sh    *
# *********************************************
#!/bin/bash
test_num=0
REPORT_FILE=n10353950_Ethan_Houley_Test_Report.txt
echo "Remember to do these two commands before running this script:
export COLUMNS
export LINES
"
echo "Test run starting at $(date) " >>${REPORT_FILE}

# *****************************************************************************
#	Function available in the Vacuum Simulation.
# *****************************************************************************

function ReturnToCharger () {
	echo "b "
}

# Drop rubbish functions \/
function DropNoRubbish () {
	echo "0 0 0 "
}

function SpawnRubbish () {
	echo "${1} ${2} ${3} "
}

function DropDust () {
	echo "d${1} ${2} " 
}

function DropSlime () {
	echo "s${1} ${2} "
}

function DropTrash () {
	echo "t${1} ${2} "
}
# Drop rubbish functions /\

# Move the Vacuum By Buttons \/
function MoveUp () {
	echo "i "
}

function MoveDown () {
	echo "k "
}

function MoveLeft () {
	echo "j "
}

function MoveRight () {
	echo "l "
}

function MoveVacuumToNewLocation () {
	echo "v${1} ${2} ${3} "
}
# Move the Vacuum By Buttons /\

# Simiulation Functions \/
function SetTimeout () {
	echo "o${1} "
}

function SwitchPauseStates () {
	echo "p "
}

function QuitSimiulation () {
	echo "q "
}

function Reset () {
	echo "r "
}

function Delay () {
	echo "m${1} "
}

function DisplayHelpScreen () {
	echo "? "
}
# Simiulation Functions /\

# Changing Characteristics Of the Vacuum \/
function ChangeWeightOfVacuum () {
	echo "w${1} "
}

function ChangeBatteryLevel () {
	echo "y${1} "
}
# Changing Characteristics Of the Vacuum /\

function Enter () {
	echo "${1} "
}

function Loop () {
	if (( $# >= 1 )) && (( $1 > 0 )) 
	then
		for (( i = 0; i < $1; i++ ))
		do
			echo "!"
		done
	else
		echo "!"
	fi
}

# *********************************************
# Run Single Test
# *********************************************

function RunTest () {
	echo ""
	echo ""
	(( test_num ++ ))
	echo "Test    : ${test_num}"
	echo "Category: ${category}"
	echo "Details : ${details}"
	echo "Expect  : ${expect}"
	
	read -p "Press r to run the test or s to skip..." run_or_skip
	
	if [ "${run_or_skip}" == "r" ]
	then
		echo ${cmd} | ./a1_n10353950
		read -p "Did the test pass or fail (p/f)?" result
		echo "Test ${test_num}: ${result}" >>${REPORT_FILE}
	fi
	
}
# *********************************************
category="Test loop "
details="Test that the Vacuum is the only thing drawn on screen."
expect="Vacuum cleaner is in the middle of the room."

cmd=$(
	DropNoRubbish
	SetTimeout 5
	Enter
)

RunTest 

# *********************************************
category="Test Drop Max Dust"
details="Test Spawns the max number of dust on screen."
expect="1000 Pieces Of dust will be spawned, with no overlapping. The rubbish count will say 1000, 0, 0"

cmd=$(
	SpawnRubbish 1000 0 0
	SetTimeout 15
)

RunTest 

# *********************************************
category="Test Drop Max Slime"
details="Test Spawns the max number of slime on screen."
expect="1000 Pieces Of slime will be spawned, with no overlapping. The rubbish count will say 0, 10, 0"

cmd=$(
	SpawnRubbish 0 10 0
	SetTimeout 10
)

RunTest 

# *********************************************
category="Test Drop Max Trash"
details="Test Spawns the max number of trash on screen."
expect="1000 Pieces Of trash will be spawned, with no overlapping. The rubbish count will say 0, 0, 5"

cmd=$(
	SpawnRubbish 0 0 5
	SetTimeout 10
)

RunTest 

# *********************************************
category="Test Drop All Max On screen"
details="Test Spawns the max number of dust, slime and trash on screen."
expect="1000 Pieces Of dust, 10 Pieces of slime and 5 Pieces of trash will be spawned, with no overlapping. The rubbish count will say 1000, 10, 5"

cmd=$(
	SpawnRubbish 1000 10 5
	SetTimeout 15
)

RunTest 

# *********************************************
category="Test: Vacuum Movement"
details="Test the default behavour of the vacuum, having the vaccum bounce off the Left side wall, location being X: 5, Y:10 Direction: 180."
expect="The Vacuum will travel left and hit the left handside wall and pick a new direction."

cmd=$(
	DropNoRubbish
	MoveVacuumToNewLocation 5 10 180
	SwitchPauseStates
	SetTimeout 10
)

RunTest 

# *********************************************
category="Test: Vacuum Movement"
details="Test the default behavour of the vacuum, having the vaccum bounce off the Top wall, location being X: 5, Y:10 Direction: 270."
expect="The Vacuum will travel Up and hit the Top wall and pick a new direction."

cmd=$(
	DropNoRubbish
	MoveVacuumToNewLocation 5 10 270
	SwitchPauseStates
	SetTimeout 10
)

RunTest 

# *********************************************
category="Test: Vacuum Movement"
details="Test the default behavour of the vacuum, having the vaccum bounce off the Bottom wall, location being X: 5, Y:25 Direction: 90."
expect="The Vacuum will travel Down and hit the Bottom wall and pick a new direction."

cmd=$(
	DropNoRubbish
	MoveVacuumToNewLocation 5 25 90
	SwitchPauseStates
	SetTimeout 10
)

RunTest 

# *********************************************
(( x = COLUMNS - 15, y = LINES - 15, z = 0))
category="Test: Vacuum Movement"
details="Test the default behavour of the vacuum, having the vaccum bounce off the Right side wall, location being X: ${x}, Y: ${y} Direction: ${z}."
expect="The Vacuum will travel right and hit the Right wall and pick a new direction."
cmd=$(
	DropNoRubbish
	MoveVacuumToNewLocation ${x} ${y} ${z}
	SwitchPauseStates
	SetTimeout 15
)

RunTest 

# *********************************************
(( x = 2, y = LINES/2-6, z = 0, d = 15))
category="Test: Vacuum Cleaning Power"
details="Moving the vacuum to X: ${x}, Y: ${y} Direction: ${z}. This test is that the vacuum can pick up dust off the ground"
expect="The Vacuum will travel right and Pickup the five (10) pieces dust of the ground"
cmd=$(
	DropNoRubbish
	MoveVacuumToNewLocation ${x} ${y} ${z}
	for (( i = 0; i < 10; i++ ))
		do
			DropDust ${d} ${y}
			((d=d+5))
		done
	
	Delay 10
	SwitchPauseStates
	SetTimeout 7
)
	
RunTest

# *********************************************
(( x = 2, y = LINES/2-6, z = 0, d = 15))
category="Test: Vacuum Cleaning Power"
details="Moving the vacuum to X: ${x}, Y: ${y} Direction: ${z}. This test is that the vacuum can pick up slime off the ground"
expect="The Vacuum will travel right and Pickup the five (5) pieces of slime of the ground"
cmd=$(
	DropNoRubbish
	MoveVacuumToNewLocation ${x} ${y} ${z}
	for (( i = 0; i < 5; i++ ))
		do
			DropSlime ${d} ${y}
			((d=d+10))
		done
	
	Delay 10
	SwitchPauseStates
	SetTimeout 7
)
	
RunTest 

# *********************************************
(( x = 2, y = LINES/2-6, z = 0, d = 15))
category="Test: Vacuum Cleaning Power"
details="Moving the vacuum to X: ${x}, Y: ${y} Direction: ${z}. This test is that the vacuum can pick up trash off the ground, and return to base."
expect="The Vacuum will travel right and Pickup the five (3) pieces of trash of the ground and go to base and empty, leaving minimum at least two (2) pieces of trash on the ground."
cmd=$(
	DropNoRubbish
	MoveVacuumToNewLocation ${x} ${y} ${z}
	for (( i = 0; i < 5; i++ ))
		do
			DropTrash ${d} ${y}
			((d=d+15))
		done
	
	Delay 10
	SwitchPauseStates
	SetTimeout 7
)
	
RunTest

# *********************************************
(( x = COLUMNS/2-5, y = LINES-13, z = 270))
category="Test: Vacuum Cleaning Power"
details="Moving the vacuum to X: ${x}, Y: ${y} Direction: ${z}. This test is that the vacuum can pick up slime off the ground, and bounce of the charging stations and continue cleaning"
expect="The Vacuum will travel Upwards and Pickup four (4) amount pieces of slime off the ground and go towards base and bounce off as the weight is not heavy enough."
cmd=$(
	DropNoRubbish
	MoveVacuumToNewLocation ${x} ${y} ${z}
	for (( i = 0; i < 4; i++ ))
		do
			((y=y-9))
			DropSlime ${x} ${y}
		done
	
	Delay 10
	SwitchPauseStates
	SetTimeout 10
)
	
RunTest

# *********************************************
(( x = 10, y = LINES-13, z = 279))
category="Test: Returning to Base"
details="Moving the vacuum to X: ${x}, Y: ${y} Direction: ${z}. This test is about testing the vacuum cleaner will go back to base after the key 'b' is pressed. After returning to the charging station the vacuum cleaner will go back its default behaviour"
expect="The Vacuum will travel towards the Chargering Station by the quicks path. After docking the battery will go to 100% and it will go back to its default behaviour."
cmd=$(
	DropNoRubbish
	MoveVacuumToNewLocation ${x} ${y} ${z}
	Delay 15
	SwitchPauseStates
	ReturnToCharger
	SetTimeout 10
)
	
RunTest 

# *********************************************
category="Test: Default Behaviour"
details="Vacuum move dowards and bounce off the walls and collect rubbish and returning to charging station and go back to cleanning after the vacuum has been docked. ZERO (0) Pieces of dust, TEN (10) Pieces of Slime And FIVE (5) Pieces of Trash. This test will run for 25 Seconds"
expect="The Vacuum will travel downwards, while picking up rubbish and returning to charging station and returning to cleanning."
cmd=$(
	SpawnRubbish 0 10 5
	Delay 5
	SwitchPauseStates
	SetTimeout 25
)
	
RunTest 

# *********************************************
category="Test: Default Behaviour"
details="Vacuum move dowards and bounce off the walls and collect rubbish and returning to charging station and go back to cleanning after the vacuum has been docked. ONE HUNDRED (100) Pieces of dust, TEN (10) Pieces of Slime And FIVE (5) Pieces of Trash. This test will run for 25 Seconds"
expect="The Vacuum will travel downwards, while picking up rubbish and returning to charging station and returning to cleanning."
cmd=$(
	SpawnRubbish 100 10 5
	Delay 5
	SwitchPauseStates
	SetTimeout 25
)
	
RunTest 

# *********************************************
(( x = 10, y = 6, z = 180))

category="Test: Pixel Level Collision"
details="The Vacuum will be moved to X: ${x}, Y: ${y}, Direction: ${z}, once the vacuum starts moving towards the dust it will not be able to pick up the dust."
expect="The Vacuum will travel towards the dust in the top left hand corner, The Vacuum will not be able to suck the dust up in the corners as the vacuum does not travel over them."
cmd=$(
	DropNoRubbish
	MoveVacuumToNewLocation ${x} ${y} ${z}
	for (( i = 5; i < 16; i++ ))
	do
		for (( j = 1; j < 6; j++ ))
		do
			DropDust $j $i
		done
	done 
	Delay 50
	SwitchPauseStates
	SetTimeout 15
)

# *********************************************
(( x = COLUMNS/2-25, y = 6, z = 0))

category="Test: Bouncing Off The Charger"
details="The Vacuum will be moved to X: ${x}, Y: ${y}, Direction: ${z}. The vacuum will move right towards the charging station and bounce off"
expect="The vacuum Will touch the charger and bounce off andd the battery will not charger."
cmd=$(
	DropNoRubbish
	MoveVacuumToNewLocation ${x} ${y} ${z}
	SwitchPauseStates
	SetTimeout 10
)
	
RunTest 

# *********************************************
(( x = COLUMNS/2+25, y = 6, z = 180))

category="Test: Bouncing Off The Charger"
details="The Vacuum will be moved to X: ${x}, Y: ${y}, Direction: ${z}. The vacuum will move left towards the charging station and bounce off"
expect="The vacuum Will touch the charger and bounce off andd the battery will not charger."
cmd=$(
	DropNoRubbish
	MoveVacuumToNewLocation ${x} ${y} ${z}
	SwitchPauseStates
	SetTimeout 10
)
	
RunTest 
# *********************************************
(( x = COLUMNS/2-5, y = LINES/2-15, z = 270))

category="Test: Bouncing Off The Charger"
details="The Vacuum will be moved to X: ${x}, Y: ${y}, Direction: ${z}. The vacuum will move upwards towards the charging station and bounce off"
expect="The vacuum Will touch the charger and bounce off andd the battery will not charger."
cmd=$(
	DropNoRubbish
	MoveVacuumToNewLocation ${x} ${y} ${z}
	SwitchPauseStates
	SetTimeout 10
)
	
RunTest
# ********************************************* 19


# ********************************************* 20


# ********************************************* 21


# *********************************************


# *********************************************


# *********************************************