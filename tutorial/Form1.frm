VERSION 5.00
Begin VB.Form Form1 
   Caption         =   "Mail Tester"
   ClientHeight    =   8445
   ClientLeft      =   1605
   ClientTop       =   1545
   ClientWidth     =   11670
   LinkTopic       =   "Form1"
   ScaleHeight     =   8445
   ScaleWidth      =   11670
   Begin VB.CommandButton Command1 
      Caption         =   "SEND!!!!"
      Default         =   -1  'True
      Height          =   435
      Left            =   9420
      TabIndex        =   14
      Top             =   7920
      Width           =   2055
   End
   Begin VB.TextBox Text1 
      Height          =   315
      Index           =   6
      Left            =   8100
      TabIndex        =   13
      Text            =   "smtp.server.com"
      Top             =   120
      Width           =   3375
   End
   Begin VB.TextBox Text1 
      Height          =   2535
      Index           =   5
      Left            =   960
      MultiLine       =   -1  'True
      TabIndex        =   11
      Top             =   5220
      Width           =   10515
   End
   Begin VB.TextBox Text1 
      Height          =   315
      Index           =   4
      Left            =   960
      TabIndex        =   10
      Text            =   "a.html"
      Top             =   4440
      Width           =   10515
   End
   Begin VB.TextBox Text1 
      Height          =   2535
      Index           =   3
      Left            =   960
      MultiLine       =   -1  'True
      TabIndex        =   9
      Top             =   1440
      Width           =   10515
   End
   Begin VB.TextBox Text1 
      Height          =   315
      Index           =   2
      Left            =   960
      TabIndex        =   8
      Text            =   "This is your lucky day!"
      Top             =   960
      Width           =   10515
   End
   Begin VB.TextBox Text1 
      Height          =   315
      Index           =   1
      Left            =   960
      TabIndex        =   7
      Text            =   "you@yourcompany.com"
      Top             =   540
      Width           =   10515
   End
   Begin VB.TextBox Text1 
      Height          =   315
      Index           =   0
      Left            =   960
      TabIndex        =   6
      Text            =   "me@mycompany.com"
      Top             =   120
      Width           =   6015
   End
   Begin VB.Label Label1 
      Caption         =   "SERVER:"
      Height          =   255
      Index           =   6
      Left            =   7200
      TabIndex        =   12
      Top             =   120
      Width           =   1635
   End
   Begin VB.Label Label1 
      Caption         =   "ATTACHEMENT TEXT:"
      Height          =   255
      Index           =   5
      Left            =   240
      TabIndex        =   5
      Top             =   4920
      Width           =   3315
   End
   Begin VB.Label Label1 
      Caption         =   "ATTACHEMENT NAME:"
      Height          =   255
      Index           =   4
      Left            =   240
      TabIndex        =   4
      Top             =   4140
      Width           =   2895
   End
   Begin VB.Label Label1 
      Caption         =   "BODY:"
      Height          =   255
      Index           =   3
      Left            =   180
      TabIndex        =   3
      Top             =   1440
      Width           =   1635
   End
   Begin VB.Label Label1 
      Caption         =   "SUBJECT:"
      Height          =   255
      Index           =   2
      Left            =   180
      TabIndex        =   2
      Top             =   960
      Width           =   1635
   End
   Begin VB.Label Label1 
      Caption         =   "TO:"
      Height          =   255
      Index           =   1
      Left            =   180
      TabIndex        =   1
      Top             =   540
      Width           =   1635
   End
   Begin VB.Label Label1 
      Caption         =   "FROM:"
      Height          =   255
      Index           =   0
      Left            =   180
      TabIndex        =   0
      Top             =   180
      Width           =   1635
   End
End
Attribute VB_Name = "Form1"
Attribute VB_GlobalNameSpace = False
Attribute VB_Creatable = False
Attribute VB_PredeclaredId = True
Attribute VB_Exposed = False
Option Explicit

Private Sub Command1_Click()
    Dim sError As String * 256
    
    Screen.MousePointer = vbHourglass
    If Not send_mail(sError, Text1(6).Text, Text1(0).Text, Text1(1).Text, Text1(2).Text, Text1(3).Text, Text1(4).Text, Text1(5).Text) Then
        MsgBox sError
    End If
    Screen.MousePointer = vbDefault
End Sub
