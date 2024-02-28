#pragma once
// represents the status of a system.
/*
* Unknown = 0 and represents an unknown status (Default value).
* Online = 1 and represents an online and running status.
* Reserved = 2 and represents the system is reserved by a manager or secretary.
* Closed = 3 and represents the system is closed, does not mean offline, but rather means
* it is finishing it's task(s), and will not accept any new task(s), then it shuts down.
* Error = 4 and represents an error status (Something has went wrong!).
* Offline = 5 and represents an offline status.
*/
typedef enum ESystemStatus {
	ESYSTEMSTATUS_UNKNOWN = 0,
	ESYSTEMSTATUS_ONLINE,
	ESYSTEMSTATUS_RESERVED,
	ESYSTEMSTATUS_CLOSED,
	ESYSTEMSTATUS_ERROR,
	ESYSTEMSTATUS_OFFLINE
};

/*
* Unknown = 0 and represents an unknown status (Default value).
* Idle = 1 and represents an idle status and is awaiting work.
* Busy = 2 and represents a busy status and is working on a task.
*/
typedef enum ESystemWorkStatus {
	ESYSTEMWORKSTATUS_UNKNOWN = 0,
	ESYSTEMWORKSTATUS_IDLE,
	ESYSTEMWORKSTATUS_BUSY
};

/*
* Unknown = 0 and represents an unknown status (Default value).
* low = 1 and represents a low workload.
* medium = 2 and represents a medium workload (The system is running normally ).
* high = 3 and represents a high workload (The system is overloaded or is at max capacity, and/or the queue is backed up).
* this system will only accept high-priority tasks.
*/
typedef enum ESystemWorkLoadStatus {
	ESYSTEMWORKLOADSTATUS_UNKNOWN = 0,
	ESYSTEMWORKLOADSTATUS_LOW,
	ESYSTEMWORKLOADSTATUS_MEDIUM,
	ESYSTEMWORKLOADSTATUS_HIGH
};
