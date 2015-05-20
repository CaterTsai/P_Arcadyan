#include "GestureSegment.h"

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

///////////////////////////////////////
//Gesture:Wave Right
///////////////////////////////////////
eGestureCheckResult	WaveRightSegment1::CheckGesture(const stSCREEN_SKELETON& stSkeleton)
{
	// Hand above elbow
	if(stSkeleton.aJoints[JointType_HandRight].y < stSkeleton.aJoints[JointType_ElbowRight].y)
	{
		// Hand right of elbow
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
		// Hand left of elbow
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