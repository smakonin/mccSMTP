/**
* This file is: 
*
* Copyright (C) 1999, 2002 Stephen Makonin.
* All Rights Reserved.
*
*/

#include <windows.h>
#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#include <time.h>
#include <malloc.h>
#include <winsock.h>

#define RECV_LEN 4096

//decode socket error number
char *get_soc_err_desc(long error_no)
{
	switch(error_no)
	{
		case WSAEACCES: //(10013) 
			return "Permission denied.";
			break;

		case WSAEADDRINUSE: //(10048) 
			return "Address already in use.";
			break;

		case WSAEADDRNOTAVAIL: //(10049) 
			return "Cannot assign requested address.";
			break;

		case WSAEAFNOSUPPORT: //(10047) 
			return "Address family not supported by protocol family.";
			break;

		case WSAEALREADY: //(10037) 
			return "Operation already in progress.";
			break;

		case WSAECONNABORTED: //(10053) 
			return "Software caused connection abort."; 
			break;

		case WSAECONNREFUSED: //(10061) 
			return "Connection refused.";
			break;

		case WSAECONNRESET: //(10054) 
			return "Connection reset by peer."; 
			break;

		case WSAEDESTADDRREQ: //(10039) 
			return "Destination address required.";
			break;

		case WSAEFAULT: //(10014) 
			return "Bad address.";
			break;

		case WSAEHOSTDOWN: //(10064) 
			return "Host is down.";
			break;

		case WSAEHOSTUNREACH: //(10065) 
			return "No route to host.";
			break;

		case WSAEINPROGRESS: //(10036) 
			return "Operation now in progress.";
			break;

		case WSAEINTR: //(10004) 
			return "Interrupted function call.";
			break;

		case WSAEINVAL: //(10022) 
			return "Invalid argument.";
			break;

		case WSAEISCONN: //(10056) 
			return "Socket is already connected.";
			break;

		case WSAEMFILE: //(10024) 
			return "Too many open files.";
			break;

		case WSAEMSGSIZE: //(10040) 
			return "Message too long.";
			break;

		case WSAENETDOWN: //(10050) 
			return "Network is down.";
			break;

		case WSAENETRESET: //(10052) 
			return "Network dropped connection on reset.";
			break;

		case WSAENETUNREACH: //(10051) 
			return "Network is unreachable.";
			break;

		case WSAENOBUFS: //(10055) 
			return "No buffer space available.";
			break;

		case WSAENOPROTOOPT: //(10042) 
			return "Bad protocol option.";
			break;

		case WSAENOTCONN: //(10057) 
			return "Socket is not connected.";
			break;

		case WSAENOTSOCK: //(10038) 
			return "Socket operation on non-socket."; 
			break;

		case WSAEOPNOTSUPP: //(10045) 
			return "Operation not supported.";
			break;

		case WSAEPFNOSUPPORT: //(10046) 
			return "Protocol family not supported.";
			break;

		case WSAEPROCLIM: //(10067) 
			return "Too many processes.";
			break;

		case WSAEPROTONOSUPPORT: //(10043) 
			return "Protocol not supported.";
			break;

		case WSAEPROTOTYPE: //(10041) 
			return "Protocol wrong type for socket.";
			break;

		case WSAESHUTDOWN: //(10058) 
			return "Cannot send after socket shutdown.";
			break;

		case WSAESOCKTNOSUPPORT: //(10044) 
			return "Socket type not supported.";
			break;

		case WSAETIMEDOUT: //(10060) 
			return "Connection timed out.";
			break;

		case WSAEWOULDBLOCK: //(10035) 
			return "Resource temporarily unavailable.";
			break;

		case WSAHOST_NOT_FOUND: //(11001) 
			return "Host not found.";
			break;

		case WSANOTINITIALISED: //(10093) 
			return "Successful WSAStartup not yet performed.";
			break;

		case WSANO_DATA: //(11004) 
			return "Valid name, no data record of requested type.";
			break;

		case WSANO_RECOVERY: //(11003) 
			return "This is a non-recoverable error.";
			break;

		case WSASYSNOTREADY: //(10091) 
			return "Network subsystem is unavailable.";
			break;

		case WSATRY_AGAIN: //(11002) 
			return "Non-authoritative host not found.";
			break;

		case WSAVERNOTSUPPORTED: //(10092) 
			return "WINSOCK.DLL version out of range.";
			break;

		case WSAEDISCON: //(10094) 
			return "Graceful shutdown in progress.";
			break;

		default:
			return "An unknown error has occured.";
			break;
	}
}

//send a block of data to the server
BOOL send_socket_data(char *error, SOCKET soc, char *data, long len)
{
	long ret_code;
	long error_no;

	if(soc == 0)
	{
		strcpy(error, "Not Connected To Server");
		return FALSE;
	}

	ret_code = send(soc, data, len, 0);
	if(ret_code == SOCKET_ERROR)
	{
		error_no = WSAGetLastError();
		strcpy(error, get_soc_err_desc(error_no));
		return FALSE;
	}

	return TRUE;
}

//get a block of data from the server
BOOL recv_socket_data(char *error, SOCKET soc, char *data, long *len)
{
	long ret_code;
	long error_no;

	if(soc == 0)
	{
		strcpy(error, "Not Connected To Server");
		return FALSE;
	}

	memset(data, 0, *len);
	ret_code = recv(soc, data, *len, 0);
	if(ret_code == SOCKET_ERROR)
	{
		*len = 0;
		error_no = WSAGetLastError();
		strcpy(error, get_soc_err_desc(error_no));
		return FALSE;
	}

	*len = ret_code;
	return TRUE;
}

//create a socket using the winsocket lib
//then connect to a server
SOCKET srv_connect(char *error, char *address)
{
	SOCKET soc;
	WORD ver_request = MAKEWORD(1,1);
	WSADATA data;
	long ret_code;
    LPHOSTENT host_entry;
	SOCKADDR_IN soc_address;
	long error_no;
	char cmd_line[1025];
	long cmd_len;
	char raw_data[RECV_LEN + 1];
	long raw_len;
	char domain[129];

	//start sockets, check version
	ret_code = WSAStartup(ver_request, &data);
	if(data.wVersion != ver_request)
	{	
		error_no = WSAVERNOTSUPPORTED;
		strcpy(error, get_soc_err_desc(error_no));
		return 0;
	}

	//resolve adress
	host_entry = gethostbyname(address);
    if(host_entry == NULL)
    {
		error_no = WSAGetLastError();
		strcpy(error, get_soc_err_desc(error_no));
		return 0;
    }
	strcpy(domain, host_entry->h_name);

	//create tcp/ip conection oriented socket
	soc = socket(AF_INET, SOCK_STREAM, 0);
	if(soc == INVALID_SOCKET)
	{
		error_no = WSAGetLastError();
		strcpy(error, get_soc_err_desc(error_no));
		return 0;
	}

	//connect to server
	soc_address.sin_family = AF_INET;
	soc_address.sin_addr = *((LPIN_ADDR)*host_entry->h_addr_list);
	soc_address.sin_port = htons((unsigned short)25);

	ret_code = connect(soc, (LPSOCKADDR)&soc_address, sizeof(struct sockaddr));
	if(ret_code == SOCKET_ERROR)
	{
		error_no = WSAGetLastError();
		strcpy(error, get_soc_err_desc(error_no));
		return 0;
	}

	raw_len = RECV_LEN;
	if(!recv_socket_data(error, soc, raw_data, &raw_len))
		return 0;

	//say hello
	cmd_len = sprintf(cmd_line, "HELO %s\r\n", domain);
	if(!send_socket_data(error, soc, cmd_line, cmd_len))
		return 0;
	raw_len = RECV_LEN;
	if(!recv_socket_data(error, soc, raw_data, &raw_len))
		return 0;	
	
	return soc;
}

//close the connection
BOOL srv_disconnect(char *error, long soc)
{
	char cmd_line[1025];
	long cmd_len;
	char raw_data[RECV_LEN + 1];
	long raw_len;

	cmd_len = sprintf(cmd_line, "QUIT\r\n");
	if(!send_socket_data(error, soc, cmd_line, cmd_len))
		return FALSE;
	raw_len = RECV_LEN;
	if(!recv_socket_data(error, soc, raw_data, &raw_len))
		;//return FALSE;
		
	shutdown(soc, 0x02);
	raw_len = RECV_LEN;
	if(!recv_socket_data(error, soc, raw_data, &raw_len))
		;//return FALSE;

	closesocket(soc);
	WSACleanup();

	return TRUE;
}

//create a message and mail it
BOOL _stdcall send_mail(char *error, char *address, char *msg_from, char *msg_to, char *msg_subject, char *msg_body, char *attch_name, char *attch_body)
{
	char cmd_line[1025];
	long cmd_len;
	long t_time;
	struct tm *t_today;
	char raw_data[RECV_LEN + 1];
	long raw_len;
	char *send_token;
	char to_buf[1025];
	long part_no;
	SOCKET soc;
	BOOL is_attach;

	if(attch_name == NULL)
		is_attach = FALSE;
	else
		if(!strlen(attch_name))
			is_attach = FALSE;
		else
			is_attach = TRUE;

	//connect to server
	soc = srv_connect(error, address);
	if(soc == 0)
		return 0;

	//start sending mail
	cmd_len = sprintf(cmd_line, "MAIL FROM:<%s>\r\n", msg_from);
	if(!send_socket_data(error, soc, cmd_line, cmd_len))
		return 0;
	raw_len = RECV_LEN;
	if(!recv_socket_data(error, soc, raw_data, &raw_len))
		return 0;

	//send to all in to list
	strcpy(to_buf, msg_to);
	send_token = strtok(to_buf, "; ");
	while(send_token != NULL)
	{
		cmd_len = sprintf(cmd_line, "RCPT TO:<%s>\r\n", send_token);
		if(!send_socket_data(error, soc, cmd_line, cmd_len))
			return 0;
		raw_len = RECV_LEN;
		if(!recv_socket_data(error, soc, raw_data, &raw_len))
			return 0;
      
		send_token = strtok(NULL, "; ");
	}

	//send the data
	cmd_len = sprintf(cmd_line, "DATA\r\n");
	if(!send_socket_data(error, soc, cmd_line, cmd_len))
		return 0;
	raw_len = RECV_LEN;
	if(!recv_socket_data(error, soc, raw_data, &raw_len))
		return 0;
	
	//send header
	time(&t_time);
	t_today = localtime(&t_time);
	strftime(raw_data, RECV_LEN, "%d %b %Y %H:%M:%S", t_today);
	cmd_len = sprintf(cmd_line, "Date: %s\r\nFrom: %s\r\nSubject: %s\r\nTo: %s\r\n", raw_data, msg_from, msg_subject, msg_to);
	if(!send_socket_data(error, soc, cmd_line, cmd_len))
		return 0;

	//send multi-part headers
	if(is_attach)
	{
		part_no = 0;
		cmd_len = sprintf(cmd_line, "MIME-Version: 1.0\r\nContent-Type: multipart/mixed;\r\n\tboundary=\"----=_NextPart_%03u_002E_01BEA08A.56FFFAA0\"\r\n\r\n", part_no);	
		if(!send_socket_data(error, soc, cmd_line, cmd_len))
			return 0;
	
		//body part info
		cmd_len = sprintf(cmd_line, "This is a multi-part message in MIME format.\r\n\r\n------=_NextPart_%03u_002E_01BEA08A.56FFFAA0\r\nContent-Type: text/plain;\r\n\tcharset=\"iso-8859-1\"\r\nContent-Transfer-Encoding: 7bit\r\n\r\n", part_no);
		if(!send_socket_data(error, soc, cmd_line, cmd_len))
			return 0;
	}

	//send body
	if(!send_socket_data(error, soc, msg_body, strlen(msg_body)))
		return 0;

	if(is_attach)
	{
		//send part header
		cmd_len = sprintf(cmd_line, "\r\n\r\n------=_NextPart_%03u_002E_01BEA08A.56FFFAA0\r\nContent-Type: text/html;\r\n\tname=\"%s\"\r\nContent-Transfer-Encoding: quoted-printable\r\nContent-Disposition: attachment;\r\n\tfilename=\"%s\"\r\n\r\n", part_no, attch_name, attch_name);
		if(!send_socket_data(error, soc, cmd_line, cmd_len))
			return 0;

		//send part body
		if(!send_socket_data(error, soc, attch_body, strlen(attch_body)))
			return 0;

		//send part trailer
		cmd_len = sprintf(cmd_line, "------=_NextPart_%03u_002E_01BEA08A.56FFFAA0--", part_no);
		if(!send_socket_data(error, soc, cmd_line, cmd_len))
			return 0;
	}
	//send end of data
	cmd_len = sprintf(cmd_line, "\r\n.\r\n");
	if(!send_socket_data(error, soc, cmd_line, cmd_len))
		return 0;
	raw_len = RECV_LEN;
	if(!recv_socket_data(error, soc, raw_data, &raw_len))
		return 0;

	//disconnect from server
	srv_disconnect(error, soc);

	memset(cmd_line, 0, sizeof(cmd_line));

	return -1;
}
