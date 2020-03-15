/*
COMPILE OPTIONS
*/

#pragma semicolon 1
#pragma newdecls required

/*
INCLUDES
*/

#include <sourcemod>
#include <lololib>
#include <printqueue>

/*
PLUGIN INFO
*/

public Plugin myinfo = 
{
	name			= "Print queue",
	author			= "Flexlolo",
	description		= "Queue messages to print",
	version			= "1.0.0",
	url				= "github.com/Flexlolo/"
}

/*
GLOBAL VARIABLES
*/

#define LIBRARY_NAME "printqueue"

ArrayList g_hQueue[MAXPLAYERS + 1][QPrint_Types];

/*
NATIVES AND FORWARDS
*/

public void OnClientDisconnect(int client)
{
	for (int type; type < QPrint_Types; type++)
	{
		if (g_hQueue[client][type] != null)
		{
			delete g_hQueue[client][type];
		}
	}
}

public APLRes AskPluginLoad2(Handle myself, bool late, char[] error, int err_max)
{
	CreateNative("QPrintAdd", 					Native_QPrintAdd);
	RegPluginLibrary(LIBRARY_NAME);

	return APLRes_Success;
}

public int Native_QPrintAdd(Handle plugin, int numParams)
{
	int client = GetNativeCell(1);
	int type = GetNativeCell(3);

	char message[QPRINT_STRING_MAXLENGTH + 1];
	GetNativeString(2, message, sizeof(message));

	Queue_Add(client, message, type);
}

/*
STOCKS
*/

stock void Queue_Add(int client, const char[] message, int type)
{
	if (g_hQueue[client][type] == null)
	{
		g_hQueue[client][type] = new ArrayList(QPRINT_STRING_MAXLENGTH);	
	}

	g_hQueue[client][type].PushString(message);
}

stock void Queue_Tick(int client)
{
	for (int type; type < QPrint_Types; type++)
	{
		if (g_hQueue[client][type] != null)
		{
			if (g_hQueue[client][type].Length)
			{
				char message[QPRINT_STRING_MAXLENGTH + 1];
				g_hQueue[client][type].GetString(0, message, sizeof(message));	

				if (type == QPrint_Chat)
				{
					lolo_PrintToChat(client, message);
				}
				else
				{
					PrintToConsole(client, message);
				}

				g_hQueue[client][type].Erase(0);
			}
		}
	}
}

public void OnPlayerRunCmdPost(int client, int buttons, int impulse, float vel[3], float angles[3], int weapon, int subtype, int cmdnum, int tickcount, int seed, int mouse[2])
{
	if (lolo_IsClientValid(client))
	{
		Queue_Tick(client);
	}
}