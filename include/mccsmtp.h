/**
* This file is: 
*
* Copyright (C) 1999, 2002 Stephen Makonin.
* All Rights Reserved.
*
*/

#ifndef _INC_MCCSMTP
#define _INC_MCCSMTP

///#ifdef  __cplusplus
///extern "C" {
///#endif

BOOL _stdcall send_mail(
	char *error,		//must be a preallocated string about 256 characters
	char *address,		//is the address of the (ex. mail.bc.sympatico.ca)
	char *msg_from,		//is the email address of the sender
	char *msg_to,		//is the email address of the receivers ";" delimited
	char *msg_subject,	//is the email subject line
	char *msg_body,		//is the email body text
	char *attch_name,	//is the file name of the attachment
	char *attch_body)	//is the text of the attachment
//
//   If there is no attachment pass in "" into the
//   attch_name and attch_body paramenters.
//
//RETURNS:
//   True will be returned if the message was sent.
//   False will be returned if any errors were encountered.


///#ifdef  __cplusplus
///}
///#endif

#endif  /* _INC_MCCSMTP */