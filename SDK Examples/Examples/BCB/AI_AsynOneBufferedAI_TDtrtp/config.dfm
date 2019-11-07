object ConfigForm: TConfigForm
  Left = 306
  Top = 159
  BorderStyle = bsDialog
  Caption = 
    'Asynchronous One Buffered AI with Trigger Delay to Start and to ' +
    'Stop - Configuration'
  ClientHeight = 383
  ClientWidth = 654
  Color = clBtnFace
  Font.Charset = DEFAULT_CHARSET
  Font.Color = clWindowText
  Font.Height = -11
  Font.Name = 'MS Sans Serif'
  Font.Style = []
  OldCreateOrder = False
  OnClose = FormClose
  OnCreate = FormCreate
  PixelsPerInch = 96
  TextHeight = 13
  object Label1: TLabel
    Left = 29
    Top = 24
    Width = 61
    Height = 17
    AutoSize = False
    Caption = 'Device:'
  end
  object Label18: TLabel
    Left = 344
    Top = 24
    Width = 32
    Height = 13
    Caption = 'Profile:'
  end
  object cmbDevice: TComboBox
    Left = 75
    Top = 20
    Width = 214
    Height = 21
    Style = csDropDownList
    ImeName = #20013#25991' ('#31616#20307') - '#25628#29399#25340#38899#36755#20837#27861
    ItemHeight = 13
    TabOrder = 0
    OnChange = cmbDeviceChange
  end
  object btnOk: TButton
    Left = 375
    Top = 343
    Width = 81
    Height = 26
    Caption = 'OK'
    TabOrder = 1
    OnClick = btnOkClick
  end
  object btnCancel: TButton
    Left = 533
    Top = 344
    Width = 81
    Height = 25
    Caption = 'Cancel'
    TabOrder = 2
    OnClick = btnCancelClick
  end
  object GroupBox1: TGroupBox
    Left = 18
    Top = 54
    Width = 303
    Height = 275
    Caption = 'Buffered AI settings'
    TabOrder = 3
    object Label2: TLabel
      Left = 8
      Top = 33
      Width = 65
      Height = 13
      AutoSize = False
      Caption = 'Channel start:'
    end
    object Label3: TLabel
      Left = 8
      Top = 84
      Width = 73
      Height = 17
      AutoSize = False
      Caption = 'Channel count:'
    end
    object Label4: TLabel
      Left = 9
      Top = 134
      Width = 65
      Height = 17
      AutoSize = False
      Caption = 'Value range:'
    end
    object Label7: TLabel
      Left = 16
      Top = 233
      Width = 73
      Height = 17
      AutoSize = False
      Caption = 'Clock rate:'
    end
    object Label8: TLabel
      Left = 247
      Top = 232
      Width = 13
      Height = 13
      Caption = 'Hz'
    end
    object Label5: TLabel
      Left = 9
      Top = 184
      Width = 80
      Height = 17
      AutoSize = False
      Caption = 'Section Length:'
    end
    object cmbChannelStart: TComboBox
      Left = 88
      Top = 30
      Width = 201
      Height = 21
      ImeName = #20013#25991' ('#31616#20307') - '#25628#29399#25340#38899#36755#20837#27861
      ItemHeight = 13
      TabOrder = 0
    end
    object cmbChannelCount: TComboBox
      Left = 88
      Top = 80
      Width = 201
      Height = 21
      ImeName = #20013#25991' ('#31616#20307') - '#25628#29399#25340#38899#36755#20837#27861
      ItemHeight = 13
      TabOrder = 1
    end
    object cmbValueRange: TComboBox
      Left = 88
      Top = 130
      Width = 201
      Height = 21
      ImeName = #20013#25991' ('#31616#20307') - '#25628#29399#25340#38899#36755#20837#27861
      ItemHeight = 13
      TabOrder = 2
    end
    object txtClockRate: TEdit
      Left = 88
      Top = 230
      Width = 153
      Height = 23
      AutoSize = False
      ImeName = #20013#25991' ('#31616#20307') - '#25628#29399#25340#38899#36755#20837#27861
      TabOrder = 3
      Text = '1000'
    end
    object txtSectionLength: TEdit
      Left = 88
      Top = 180
      Width = 153
      Height = 23
      AutoSize = False
      ImeName = #20013#25991' ('#31616#20307') - '#25628#29399#25340#38899#36755#20837#27861
      TabOrder = 4
      Text = '1024'
    end
  end
  object GroupBox2: TGroupBox
    Left = 340
    Top = 55
    Width = 293
    Height = 138
    Caption = 'Trigger settings'
    TabOrder = 4
    object Label6: TLabel
      Left = 10
      Top = 23
      Width = 65
      Height = 13
      AutoSize = False
      Caption = 'Source:'
    end
    object Label9: TLabel
      Left = 10
      Top = 52
      Width = 73
      Height = 17
      AutoSize = False
      Caption = 'Edge:'
    end
    object Label10: TLabel
      Left = 9
      Top = 83
      Width = 65
      Height = 17
      AutoSize = False
      Caption = 'Delay count:'
    end
    object Label11: TLabel
      Left = 8
      Top = 108
      Width = 73
      Height = 17
      AutoSize = False
      Caption = 'Trigger level:'
    end
    object Label12: TLabel
      Left = 272
      Top = 110
      Width = 7
      Height = 13
      Caption = 'V'
    end
    object cmbTriggerSource: TComboBox
      Left = 88
      Top = 22
      Width = 177
      Height = 21
      ImeName = #20013#25991' ('#31616#20307') - '#25628#29399#25340#38899#36755#20837#27861
      ItemHeight = 13
      TabOrder = 0
      OnChange = cmbTriggerSourceChange
    end
    object cmbTriggerEdge: TComboBox
      Left = 88
      Top = 50
      Width = 177
      Height = 21
      ImeName = #20013#25991' ('#31616#20307') - '#25628#29399#25340#38899#36755#20837#27861
      ItemHeight = 13
      TabOrder = 1
    end
    object txtTriggerLevel: TEdit
      Left = 88
      Top = 105
      Width = 176
      Height = 22
      AutoSize = False
      ImeName = #20013#25991' ('#31616#20307') - '#25628#29399#25340#38899#36755#20837#27861
      TabOrder = 2
      Text = '3'
    end
    object txtDelayCount: TEdit
      Left = 88
      Top = 78
      Width = 176
      Height = 22
      AutoSize = False
      ImeName = #20013#25991' ('#31616#20307') - '#25628#29399#25340#38899#36755#20837#27861
      TabOrder = 3
      Text = '500'
    end
  end
  object GroupBox3: TGroupBox
    Left = 340
    Top = 195
    Width = 293
    Height = 134
    Caption = 'Trigger1 settings'
    TabOrder = 5
    object Label13: TLabel
      Left = 10
      Top = 23
      Width = 65
      Height = 13
      AutoSize = False
      Caption = 'Source:'
    end
    object Label14: TLabel
      Left = 10
      Top = 51
      Width = 73
      Height = 17
      AutoSize = False
      Caption = 'Edge:'
    end
    object Label15: TLabel
      Left = 9
      Top = 83
      Width = 65
      Height = 17
      AutoSize = False
      Caption = 'Delay count:'
    end
    object Label16: TLabel
      Left = 8
      Top = 108
      Width = 73
      Height = 17
      AutoSize = False
      Caption = 'Trigger level:'
    end
    object Label17: TLabel
      Left = 272
      Top = 108
      Width = 7
      Height = 13
      Caption = 'V'
    end
    object cmbTrigger1Source: TComboBox
      Left = 88
      Top = 22
      Width = 177
      Height = 21
      ImeName = #20013#25991' ('#31616#20307') - '#25628#29399#25340#38899#36755#20837#27861
      ItemHeight = 13
      TabOrder = 0
      OnChange = cmbTriggerSourceChange
    end
    object cmbTrigger1Edge: TComboBox
      Left = 88
      Top = 50
      Width = 177
      Height = 21
      ImeName = #20013#25991' ('#31616#20307') - '#25628#29399#25340#38899#36755#20837#27861
      ItemHeight = 13
      TabOrder = 1
    end
    object txtTrigger1Level: TEdit
      Left = 88
      Top = 105
      Width = 176
      Height = 22
      AutoSize = False
      ImeName = #20013#25991' ('#31616#20307') - '#25628#29399#25340#38899#36755#20837#27861
      TabOrder = 2
      Text = '3'
    end
    object txtDelayCount1: TEdit
      Left = 88
      Top = 78
      Width = 176
      Height = 22
      AutoSize = False
      ImeName = #20013#25991' ('#31616#20307') - '#25628#29399#25340#38899#36755#20837#27861
      TabOrder = 3
      Text = '500'
    end
  end
  object txtProfilePath: TEdit
    Left = 384
    Top = 20
    Width = 185
    Height = 21
    TabOrder = 6
  end
  object btnBrowse: TButton
    Left = 576
    Top = 20
    Width = 51
    Height = 22
    Caption = 'Browse'
    TabOrder = 7
    OnClick = btnBrowseClick
  end
end
