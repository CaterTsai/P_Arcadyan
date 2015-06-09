#include "GestureSegment.h"

#pragma region OPEN
///////////////////////////////////////
//Gesture:Open
///////////////////////////////////////
eGestureCheckResult	OpenSegment1::CheckGesture(const stSCREEN_SKELETON& stSkeleton)
{
	if(stSkeleton.aJoints[JointType_HandRight].x > stSkeleton.aJoints[JointType_HandLeft].x)
	{
		// Hands between shoulders
		if(stSkeleton.aJoints[JointType_HandLeft].x < stSkeleton.aJoints[JointType_ShoulderRight].x &&
			stSkeleton.aJoints[JointType_HandRight].x < stSkeleton.aJoints[JointType_ShoulderRight].x &&
			stSkeleton.aJoints[JointType_HandLeft].x > stSkeleton.aJoints[JointType_ShoulderLeft].x &&
			stSkeleton.aJoints[JointType_HandRight].x > stSkeleton.aJoints[JointType_ShoulderLeft].x)
		{
			return eGesutreCheck_Success;
		}
		else
		{
			return eGesutreCheck_Pause;
		}
	}
	else
	{
		return eGesutreCheck_Fail;
	}
}

//--------------------------------------------------------------
eGestureCheckResult	OpenSegment2::CheckGesture(const stSCREEN_SKELETON& stSkeleton)
{
	if(stSkeleton.aJoints[JointType_HandRight].x > stSkeleton.aJoints[JointType_HandLeft].x)
	{
			// Hands outside shoulders
		if(stSkeleton.aJoints[JointType_HandLeft].x < stSkeleton.aJoints[JointType_ShoulderLeft].x &&
			stSkeleton.aJoints[JointType_HandRight].x > stSkeleton.aJoints[JointType_ShoulderRight].x)
		{
			return eGesutreCheck_Success;
		}
		else
		{
			return eGesutreCheck_Pause;
		}
	}
	else
	{
		return eGesutreCheck_Fail;
	}
}

//--------------------------------------------------------------
eGestureCheckResult	OpenSegment3::CheckGesture(const stSCREEN_SKELETON& stSkeleton)
{
	if(stSkeleton.aJoints[JointType_HandRight].x > stSkeleton.aJoints[JointType_HandLeft].x)
	{
		// Hands outside elbows
		if(stSkeleton.aJoints[JointType_HandLeft].x < stSkeleton.aJoints[JointType_ElbowLeft].x &&
			stSkeleton.aJoints[JointType_HandRight].x > stSkeleton.aJoints[JointType_ElbowRight].x)
		{
			return eGesutreCheck_Success;
		}
		else
		{
			return eGesutreCheck_Pause;
		}
	}
	else
	{
		return eGesutreCheck_Fail;
	}
}
#pragma endregion

#pragma region Wave Right
///////////////////////////////////////
//Gesture:Wave Right
///////////////////////////////////////
eGestureCheckResult	WaveRightSegment1::CheckGesture(const stSCREEN_SKELETON& stSkeleton)
{
	// Hand above elbow
	if(stSkeleton.aJoints[JointType_HandRight].y < stSkeleton.aJoints[JointType_ElbowRight].y)
	{
		// right hand is right of right elbow || left hand is left of left elbow
		if(stSkeleton.aJoints[JointType_HandRight].x > stSkeleton.aJoints[JointType_ElbowRight].x)
		{
			return eGesutreCheck_Success;
		}
		else
		{
			return eGesutreCheck_Pause;
		}
	}
	else
	{
		return eGesutreCheck_Fail;
	}
}

//--------------------------------------------------------------
eGestureCheckResult	WaveRightSegment2::CheckGesture(const stSCREEN_SKELETON& stSkeleton)
{
	// Hand above elbow
	if(stSkeleton.aJoints[JointType_HandRight].y < stSkeleton.aJoints[JointType_ElbowRight].y)
	{
		// right hand left of right elbow || left hand right of left elbow
		if(stSkeleton.aJoints[JointType_HandRight].x < stSkeleton.aJoints[JointType_ElbowRight].x)
		{
			return eGesutreCheck_Success;
		}
		else
		{
			return eGesutreCheck_Pause;
		}
	}
	else
	{
		return eGesutreCheck_Fail;
	}
}
#pragma endregion

#pragma region Wave Left
///////////////////////////////////////
//Gesture:Wave Left
///////////////////////////////////////
eGestureCheckResult	WaveLeftSegment1::CheckGesture(const stSCREEN_SKELETON& stSkeleton)
{
	// Hand above elbow
	if(stSkeleton.aJoints[JointType_HandLeft].y > stSkeleton.aJoints[JointType_ElbowLeft].y)
	{
		// Hand left of elbow
		if(stSkeleton.aJoints[JointType_HandLeft].x < stSkeleton.aJoints[JointType_ElbowLeft].x)
		{
			return eGesutreCheck_Success;
		}
		else
		{
			return eGesutreCheck_Pause;
		}
	}
	else
	{
		return eGesutreCheck_Fail;
	}
}

//--------------------------------------------------------------
eGestureCheckResult	WaveLeftSegment2::CheckGesture(const stSCREEN_SKELETON& stSkeleton)
{
	// Hand above elbow
	if(stSkeleton.aJoints[JointType_HandLeft].y > stSkeleton.aJoints[JointType_ElbowLeft].y)
	{
		// Hand right of elbow
		if(stSkeleton.aJoints[JointType_HandLeft].x > stSkeleton.aJoints[JointType_ElbowLeft].x)
		{
			return eGesutreCheck_Success;
		}
		else
		{
			return eGesutreCheck_Pause;
		}
	}
	else
	{
		return eGesutreCheck_Fail;
	}
}
#pragma endregion

#pragma region Right Hand up
///////////////////////////////////////
//Gesture:Hand up
///////////////////////////////////////
eGestureCheckResult	RightHandUpSegment1::CheckGesture(const stSCREEN_SKELETON& stSkeleton)
{
	// Hand down Shoulder
	if(stSkeleton.aJoints[JointType_HandRight].y > stSkeleton.aJoints[JointType_SpineBase].y)
	{
		return eGesutreCheck_Success;
	}
	else
	{
		return eGesutreCheck_Pause;
	}
}

//--------------------------------------------------------------
eGestureCheckResult	RightHandUpSegment2::CheckGesture(const stSCREEN_SKELETON& stSkeleton)
{
	// Hand above Shoulder
	if(stSkeleton.aJoints[JointType_HandRight].y < stSkeleton.aJoints[JointType_SpineBase].y)
	{
		return eGesutreCheck_Success;
	}
	else
	{
		return eGesutreCheck_Pause;
	}
}
#pragma endregion

#pragma region Right Hand down
///////////////////////////////////////
//Gesture:Hand down
///////////////////////////////////////
eGestureCheckResult	RightHandDownSegment1::CheckGesture(const stSCREEN_SKELETON& stSkeleton)
{
	// Hand above Shoulder
	if(stSkeleton.aJoints[JointType_HandRight].y < stSkeleton.aJoints[JointType_SpineBase].y)
	{
		return eGesutreCheck_Success;
	}
	else
	{
		return eGesutreCheck_Pause;
	}
}

//--------------------------------------------------------------
eGestureCheckResult	RightHandDownSegment2::CheckGesture(const stSCREEN_SKELETON& stSkeleton)
{
	// Hand down Shoulder
	if(stSkeleton.aJoints[JointType_HandRight].y > stSkeleton.aJoints[JointType_SpineBase].y)
	{
		return eGesutreCheck_Success;
	}
	else
	{
		return eGesutreCheck_Pause;
	}
}
#pragma endregion

#pragma region Left Hand up
///////////////////////////////////////
//Gesture:Hand up
///////////////////////////////////////
eGestureCheckResult	LeftHandUpSegment1::CheckGesture(const stSCREEN_SKELETON& stSkeleton)
{
	// Hand down Shoulder
	if(stSkeleton.aJoints[JointType_HandLeft].y > stSkeleton.aJoints[JointType_SpineBase].y)
	{
		return eGesutreCheck_Success;
	}
	else
	{
		return eGesutreCheck_Pause;
	}
}

//--------------------------------------------------------------
eGestureCheckResult	LeftHandUpSegment2::CheckGesture(const stSCREEN_SKELETON& stSkeleton)
{
	// Hand above Shoulder
	if(stSkeleton.aJoints[JointType_HandLeft].y < stSkeleton.aJoints[JointType_SpineBase].y)
	{
		return eGesutreCheck_Success;
	}
	else
	{
		return eGesutreCheck_Pause;
	}
}
#pragma endregion

#pragma region Left Hand down
///////////////////////////////////////
//Gesture:Hand down
///////////////////////////////////////
eGestureCheckResult	LeftHandDownSegment1::CheckGesture(const stSCREEN_SKELETON& stSkeleton)
{
	// Hand above Shoulder
	if(stSkeleton.aJoints[JointType_HandLeft].y < stSkeleton.aJoints[JointType_SpineBase].y)
	{
		return eGesutreCheck_Success;
	}
	else
	{
		return eGesutreCheck_Pause;
	}
}

//--------------------------------------------------------------
eGestureCheckResult	LeftHandDownSegment2::CheckGesture(const stSCREEN_SKELETON& stSkeleton)
{
	// Hand down Shoulder
	if(stSkeleton.aJoints[JointType_HandLeft].y > stSkeleton.aJoints[JointType_SpineBase].y)
	{
		return eGesutreCheck_Success;
	}
	else
	{
		return eGesutreCheck_Pause;
	}
}
#pragma endregion