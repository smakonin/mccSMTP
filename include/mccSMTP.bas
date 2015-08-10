Attribute VB_Name = "mccSMTP"
Option Explicit

Public Declare Function send_mail Lib "mccsmtp.dll" (ByVal error As String, ByVal arrdess As String, ByVal msg_from As String, ByVal msg_to As String, ByVal msg_subject As String, ByVal msg_body As String, ByVal attch_name As String, ByVal attch_body As String) As Boolean

'PARAMS:
'    error As String        -   must be a preallocated string about 256 characters
'    arrdess As String      -   is the address of the (ex. mail.bc.sympatico.ca)
'    msg_from As String     -   is the email address of the sender
'    msg_to As String       -   is the email address of the receivers ";" delimited
'    msg_subject As String  -   is the email subject line
'    msg_body As String     -   is the email body text
'    attch_name As String   -   is the file name of the attachment
'    attch_body As String   -   is the text of the attachment
'
'   If there is no attachment pass in "" into the
'   attch_name and attch_body paramenters.
'
'RETURNS:
'   True will be returned if the message was sent.
'   False will be returned if any errors were encountered.


