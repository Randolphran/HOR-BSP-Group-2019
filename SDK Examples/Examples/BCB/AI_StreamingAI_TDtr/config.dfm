object ConfigForm: TConfigForm
  Left = 284
  Top = 297
  BorderStyle = bsDialog
  Caption = 'Streaming AI with Trigger Delay to Start - Configuration'
  ClientHeight = 272
  ClientWidth = 660
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
  object Label12: TLabel
    Left = 344
    Top = 23
    Width = 41
    Height = 13
    Caption = 'Profile:'
  end
  object cmbDevice: TComboBox
    Left = 75
    Top = 20
    Width = 198
    Height = 21
    Style = csDropDownList
    ImeName = #20013#25991' ('#31616#20307') - '#25628#29399#25340#38899#36755#20837#27861
    ItemHeight = 13
    TabOrder = 0
    OnChange = cmbDeviceChange
  end
  object btnOk: TButton
    Left = 385
    Top = 229
    Width = 81
    Height = 26
    Caption = 'OK'
    TabOrder = 1
    OnClick = btnOkClick
  end
  object btnCancel: TButton
    Left = 543
    Top = 230
    Width = 81
    Height = 25
    Caption = 'Cancel'
    TabOrder = 2
    OnClick = btnCancelClick
  end
  object GroupBox1: TGroupBox
    Left = 18
    Top = 54
    Width = 311
    Height = 195
    Caption = 'Buffered AI settings'
    TabOrder = 3
    object Label2: TLabel
      Left = 8
      Top = 23
      Width = 65
      Height = 13
      AutoSize = False
      Caption = 'Channel start:'
    end
    object Label3: TLabel
      Left = 8
      Top = 59
      Width = 73
      Height = 17
      AutoSize = False
      Caption = 'Channel count:'
    end
    object Label4: TLabel
      Left = 9
      Top = 91
      Width = 65
      Height = 17
      AutoSize = False
      Caption = 'Value range:'
    end
    object Label7: TLabel
      Left = 8
      Top = 127
      Width = 65
      Height = 17
      AutoSize = False
      Caption = 'Clock rate:'
    end
    object Label8: TLabel
      Left = 247
      Top = 128
      Width = 13
      Height = 13
      Caption = 'Hz'
    end
    object Label13: TLabel
      Left = 8
      Top = 160
      Width = 75
      Height = 13
      Caption = 'Section Length:'
    end
    object cmbChannelStart: TComboBox
      Left = 88
      Top = 22
      Width = 201
      Height = 21
      ImeName = #20013#25991' ('#31616#20307') - '#25628#29399#25340#38899#36755#20837#27861
      ItemHeight = 13
      TabOrder = 0
    end
    object cmbChannelCount: TComboBox
      Left = 88
      Top = 55
      Width = 201
      Height = 21
      ImeName = #20013#25991' ('#31616#20307') - '#25628#29399#25340#38899#36755#20837#27861
      ItemHeight = 13
      TabOrder = 1
    end
    object cmbValueRange: TComboBox
      Left = 88
      Top = 88
      Width = 201
      Height = 21
      ImeName = #20013#25991' ('#31616#20307') - '#25628#29399#25340#38899#36755#20837#27861
      ItemHeight = 13
      TabOrder = 2
    end
    object txtClockRate: TEdit
      Left = 88
      Top = 121
      Width = 153
      Height = 23
      AutoSize = False
      ImeName = #20013#25991' ('#31616#20307') - '#25628#29399#25340#38899#36755#20837#27861
      TabOrder = 3
      Text = '1000'
    end
    object txtSectionLength: TEdit
      Left = 88
      Top = 156
      Width = 153
      Height = 21
      TabOrder = 4
      Text = '1024'
    end
  end
  object GroupBox2: TGroupBox
    Left = 340
    Top = 55
    Width = 293
    Height = 163
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
      Top = 59
      Width = 73
      Height = 17
      AutoSize = False
      Caption = 'Edge:'
    end
    object Label9: TLabel
      Left = 9
      Top = 91
      Width = 65
      Height = 17
      AutoSize = False
      Caption = 'Delay count:'
    end
    object Label10: TLabel
      Left = 8
      Top = 127
      Width = 73
      Height = 17
      AutoSize = False
      Caption = 'Trigger level:'
    end
    object Label11: TLabel
      Left = 272
      Top = 128
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
      Top = 55
      Width = 177
      Height = 21
      ImeName = #20013#25991' ('#31616#20307') - '#25628#29399#25340#38899#36755#20837#27861
      ItemHeight = 13
      TabOrder = 1
    end
    object txtTriggerLevel: TEdit
      Left = 88
      Top = 121
      Width = 176
      Height = 24
      AutoSize = False
      ImeName = #20013#25991' ('#31616#20307') - '#25628#29399#25340#38899#36755#20837#27861
      TabOrder = 2
      Text = '3'
    end
    object txtDelayCount: TEdit
      Left = 88
      Top = 85
      Width = 176
      Height = 27
      AutoSize = False
      ImeName = #20013#25991' ('#31616#20307') - '#25628#29399#25340#38899#36755#20837#27861
      TabOrder = 3
      Text = '500'
    end
  end
  object txtProfilePath: TEdit
    Left = 384
    Top = 20
    Width = 177
    Height = 21
    TabOrder = 5
  end
  object btnBrowse: TButton
    Left = 576
    Top = 18
    Width = 55
    Height = 22
    Caption = 'Browse'
    TabOrder = 6
    OnClick = btnBrowseClick
  end
end
