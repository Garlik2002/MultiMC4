// 
//  Copyright 2012 MultiMC Contributors
// 
//    Licensed under the Apache License, Version 2.0 (the "License");
//    you may not use this file except in compliance with the License.
//    You may obtain a copy of the License at
// 
//        http://www.apache.org/licenses/LICENSE-2.0
// 
//    Unless required by applicable law or agreed to in writing, software
//    distributed under the License is distributed on an "AS IS" BASIS,
//    WITHOUT WARRANTIES OR CONDITIONS OF ANY KIND, either express or implied.
//    See the License for the specific language governing permissions and
//    limitations under the License.
//

#pragma once

#include "task.h"

DECLARE_EVENT_TYPE(wxEVT_CHECK_UPDATE, -1)

class CheckUpdateTask : public Task
{
public:
	CheckUpdateTask();
	
	virtual ExitCode TaskStart();
	
	int m_buildNumber;
	wxString m_downloadURL;
	
protected:
	int GetBuildNumber(const wxString &mainPageJSON);
	
	void OnCheckComplete(int buildNumber, wxString downloadURL);
};

struct CheckUpdateEvent : TaskEvent
{
	CheckUpdateEvent(Task* task, const int latestBuildNumber, const wxString downloadURL) 
		: TaskEvent(wxEVT_CHECK_UPDATE, task)
		{ m_latestBuildNumber = latestBuildNumber; m_downloadURL = downloadURL; }
	
	int m_latestBuildNumber;
	wxString m_downloadURL;
	
	virtual wxEvent *Clone() const
	{
		return new CheckUpdateEvent(m_task, m_latestBuildNumber, m_downloadURL);
	}
};

typedef void (wxEvtHandler::*CheckUpdateEventFunction)(CheckUpdateEvent&);

#define EVT_CHECK_UPDATE(fn) EVT_TASK_CUSTOM(wxEVT_CHECK_UPDATE, fn, CheckUpdateEventFunction)
