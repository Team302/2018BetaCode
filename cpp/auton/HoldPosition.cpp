/*
 * HoldPosition.cpp
 *
 *  Created on: Jan 20, 2018
 *      Author: jonah
 */

//includes
#include <cmath>
#include <frc/SmartDashboard/SmartDashboard.h>
//team302 includes
#include <auton/HoldPosition.h>
#include <auton/PrimitiveParams.h>
#include <auton/PrimitiveFactory.h>
#include <auton/IPrimitive.h>
#include <subsys/ChassisFactory.h>

HoldPosition::HoldPosition() :
		m_chassis(ChassisFactory::GetIChassis()), //Get chassis from chassis factory
		m_placeCube(new LiftElevator()),
		m_grabCube( new GrabCube() ),
		m_timeRemaining(0.0)       //Value will be changed in init
{
}

void HoldPosition::Init(PrimitiveParams* params) {
//	printf("Hold position Init\n");
	//Get timeRemaining from m_params
	m_timeRemaining = params->GetTime();
	m_chassis->SetTalonMode(DragonTalon::POSITION);
	m_chassis->EnableBrakeMode(true);
	m_placeCube->Init(params); //todo: lift
	m_grabCube->Init(params);
	//Set params
	m_chassis->SetVelocityParams(kP, kI, kD, kF, 0, 0);
	m_chassis->SetLeftRightMagnitudes(m_chassis->GetLeftMasterMotorRotationCount(), m_chassis->GetRightMasterMotorRotationCount());
}

void HoldPosition::Run() {
	//Decrement time remaining
	m_timeRemaining -= IPrimitive::LOOP_LENGTH;
	m_placeCube->Run();
	m_grabCube->Run();
}

bool HoldPosition::IsDone() {
	//Return true when the time runs out
	bool holdDone = ((m_timeRemaining <= (IPrimitive::LOOP_LENGTH / 2.0)));
//	return holdDone && m_placeCube->IsDone();
	return holdDone;
}
