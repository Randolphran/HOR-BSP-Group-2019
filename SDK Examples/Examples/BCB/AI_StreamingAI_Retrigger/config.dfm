object ConfigForm: TConfigForm
  Left = 229
  Top = 195
  BorderStyle = bsDialog
  Caption = 'Streaming AI with Retrigger - Configuration'
  ClientHeight = 395
  ClientWidth = 652
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
    Left = 21
    Top = 24
    Width = 61
    Height = 17
    AutoSize = False
    Caption = 'Device:'
  end
  object Label20: TLabel
    Left = 333
    Top = 24
    Width = 44
    Height = 17
    AutoSize = False
    Caption = 'Profile:'
  end
  object cmbDevice: TComboBox
    Left = 67
    Top = 20
    Width = 206
    Height = 21
    Style = csDropDownList
    ImeName = #20013#25991' ('#31616#20307') - '#25628#29399#25340#38899#36755#20837#27861
    ItemHeight = 13
    TabOrder = 0
    OnChange = cmbDeviceChange
  end
  object btnOk: TButton
    Left = 369
    Top = 357
    Width = 81
    Height = 26
    Caption = 'OK'
    TabOrder = 1
    OnClick = btnOkClick
  end
  object btnCancel: TButton
    Left = 511
    Top = 358
    Width = 81
    Height = 25
    Caption = 'Cancel'
    TabOrder = 2
    OnClick = btnCancelClick
  end
  object GroupBox1: TGroupBox
    Left = 18
    Top = 56
    Width = 311
    Height = 289
    Caption = 'Streaming AI settings'
    TabOrder = 3
    object Label2: TLabel
      Left = 8
      Top = 31
      Width = 65
      Height = 13
      AutoSize = False
      Caption = 'Channel start:'
    end
    object Label3: TLabel
      Left = 8
      Top = 75
      Width = 73
      Height = 17
      AutoSize = False
      Caption = 'Channel count:'
    end
    object Label4: TLabel
      Left = 9
      Top = 115
      Width = 65
      Height = 17
      AutoSize = False
      Caption = 'Value range:'
    end
    object Label7: TLabel
      Left = 8
      Top = 159
      Width = 97
      Height = 17
      AutoSize = False
      Caption = 'Clock rate:'
    end
    object Label8: TLabel
      Left = 255
      Top = 160
      Width = 13
      Height = 13
      Caption = 'Hz'
    end
    object Label12: TLabel
      Left = 8
      Top = 207
      Width = 89
      Height = 17
      AutoSize = False
      Caption = 'Section Length:'
    end
    object Label14: TLabel
      Left = 8
      Top = 255
      Width = 97
      Height = 17
      AutoSize = False
      Caption = 'Cycles:'
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
      Top = 71
      Width = 201
      Height = 21
      ImeName = #20013#25991' ('#31616#20307') - '#25628#29399#25340#38899#36755#20837#27861
      ItemHeight = 13
      TabOrder = 1
    end
    object cmbValueRange: TComboBox
      Left = 88
      Top = 112
      Width = 201
      Height = 21
      ImeName = #20013#25991' ('#31616#20307') - '#25628#29399#25340#38899#36755#20837#27861
      ItemHeight = 13
      TabOrder = 2
    end
    object txtClockRate: TEdit
      Left = 88
      Top = 152
      Width = 153
      Height = 27
      AutoSize = False
      ImeName = #20013#25991' ('#31616#20307') - '#25628#29399#25340#38899#36755#20837#27861
      TabOrder = 3
      Text = '10000'
    end
    object txtSectionLength: TEdit
      Left = 88
      Top = 201
      Width = 153
      Height = 27
      AutoSize = False
      ImeName = #20013#25991' ('#31616#20307') - '#25628#29399#25340#38899#36755#20837#27861
      TabOrder = 4
      Text = '10240'
    end
    object txtCycles: TEdit
      Left = 88
      Top = 249
      Width = 153
      Height = 27
      AutoSize = False
      ImeName = #20013#25991' ('#31616#20307') - '#25628#29399#25340#38899#36755#20837#27861
      TabOrder = 5
      Text = '2'
    end
  end
  object GroupBox2: TGroupBox
    Left = 340
    Top = 55
    Width = 293
    Height = 142
    Caption = 'Trigger settings'
    TabOrder = 4
    object Label5: TLabel
      Left = 10
      Top = 23
      Width = 65
      Height = 13
      AutoSize = False
      Caption = 'Source:'
    end
    object Label6: TLabel
      Left = 10
      Top = 52
      Width = 39
      Height = 17
      AutoSize = False
      Caption = 'Edge:'
    end
    object Label9: TLabel
      Left = 9
      Top = 85
      Width = 65
      Height = 17
      AutoSize = False
      Caption = 'Delay count:'
    end
    object Label10: TLabel
      Left = 8
      Top = 120
      Width = 73
      Height = 17
      AutoSize = False
      Caption = 'Trigger level:'
    end
    object Label11: TLabel
      Left = 272
      Top = 115
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
      Top = 110
      Width = 176
      Height = 22
      AutoSize = False
      ImeName = #20013#25991' ('#31616#20307') - '#25628#29399#25340#38899#36755#20837#27861
      TabOrder = 2
      Text = '3'
    end
    object txtDelayCount: TEdit
      Left = 88
      Top = 80
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
    Top = 207
    Width = 293
    Height = 138
    Caption = 'Trigger 1settings'
    TabOrder = 5
    object Label15: TLabel
      Left = 10
      Top = 23
      Width = 65
      Height = 13
      AutoSize = False
      Caption = 'Source:'
    end
    object Label16: TLabel
      Left = 10
      Top = 52
      Width = 73
      Height = 17
      AutoSize = False
      Caption = 'Edge:'
    end
    object Label17: TLabel
      Left = 9
      Top = 85
      Width = 65
      Height = 17
      AutoSize = False
      Caption = 'Delay count:'
    end
    object Label18: TLabel
      Left = 8
      Top = 115
      Width = 73
      Height = 17
      AutoSize = False
      Caption = 'Trigger level:'
    end
    object Label19: TLabel
      Left = 272
      Top = 115
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
      Top = 110
      Width = 176
      Height = 22
      AutoSize = False
      ImeName = #20013#25991' ('#31616#20307') - '#25628#29399#25340#38899#36755#20837#27861
      TabOrder = 2
      Text = '3'
    end
    object txtTrigger1DelayCount: TEdit
      Left = 88
      Top = 80
      Width = 176
      Height = 22
      AutoSize = False
      ImeName = #20013#25991' ('#31616#20307') - '#25628#29399#25340#38899#36755#20837#27861
      TabOrder = 3
      Text = '500'
    end
  end
  object txtProfileName: TEdit
    Left = 376
    Top = 20
    Width = 185
    Height = 21
    AutoSize = False
    ImeName = #20013#25991' ('#31616#20307') - '#25628#29399#25340#38899#36755#20837#27861
    TabOrder = 6
  end
  object btnBrowse: TButton
    Left = 576
    Top = 17
    Width = 51
    Height = 23
    Caption = 'Browse'
    TabOrder = 7
    OnClick = btnBrowseClick
  end
end
