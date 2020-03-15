#if defined _printqueue_included
  #endinput
#endif
#define _printqueue_included

enum 
{
	QPrint_Console,
	QPrint_Chat,

	QPrint_Types
}

/*
* Add message to print queue
* 
* @param client 		Client to send message
* @param message 		Message string
* @param type 			Type of message
* 
* @noreturn
*/
native void QPrintAdd(int client, const char[] mesage, int type);



/*
* Send chat message to a single client
*/
stock void QPrintToChat(int client, const char[] message, any ...)
{
	SetGlobalTransTarget(client);

	int length = strlen(message) + 255;
	char[] buffer = new char[length];
	VFormat(buffer, length, message, 3);

	QPrintAdd(client, buffer, QPrint_Chat);
}

/*
* Send chat message to all clients
*/
stock void QPrintToChatAll(const char[] message, any ...)
{
	for (int i = 1; i <= MaxClients; i++)
	{
		if (lolo_IsClientValid(i))
		{
			SetGlobalTransTarget(i);

			int length = strlen(message) + 255;
			char[] buffer = new char[length];
			VFormat(buffer, length, message, 2);

			QPrintAdd(i, buffer, QPrint_Chat);
		}
	}
}

/*
* Send chat message to all clients except one
*/
stock void QPrintToChatAllExcept(int client, const char[] message, any ...)
{
	for (int i = 1; i <= MaxClients; i++)
	{
		if (i != client && lolo_IsClientValid(i))
		{
			SetGlobalTransTarget(i);

			int length = strlen(message) + 255;
			char[] buffer = new char[length];
			VFormat(buffer, length, message, 2);

			QPrintAdd(i, buffer, QPrint_Chat);
		}
	}
}

/*
* Send console message to a single client
*/
stock void QPrintToConsole(int client, const char[] message, any ...)
{
	SetGlobalTransTarget(client);

	int length = strlen(message) + 255;
	char[] buffer = new char[length];
	VFormat(buffer, length, message, 3);

	QPrintAdd(client, buffer, QPrint_Console);
}

/*
* Send console message to all clients
*/
stock void QPrintToConsoleAll(const char[] message, any ...)
{
	for (int i = 1; i <= MaxClients; i++)
	{
		if (lolo_IsClientValid(i))
		{
			SetGlobalTransTarget(i);

			int length = strlen(message) + 255;
			char[] buffer = new char[length];
			VFormat(buffer, length, message, 2);

			QPrintAdd(i, buffer, QPrint_Console);
		}
	}
}

/*
* Send console message to all clients except one
*/
stock void QPrintToConsoleAllExcept(int client, const char[] message, any ...)
{
	for (int i = 1; i <= MaxClients; i++)
	{
		if (i != client && lolo_IsClientValid(i))
		{
			SetGlobalTransTarget(i);

			int length = strlen(message) + 255;
			char[] buffer = new char[length];
			VFormat(buffer, length, message, 2);

			QPrintAdd(i, buffer, QPrint_Console);
		}
	}
}