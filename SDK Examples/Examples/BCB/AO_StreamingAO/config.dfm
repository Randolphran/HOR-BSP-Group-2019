object ConfigForm: TConfigForm
  Left = 338
  Top = 341
  BorderStyle = bsDialog
  Caption = 'Streaming AO - Configuration'
  ClientHeight = 235
  ClientWidth = 464
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
    Left = 12
    Top = 22
    Width = 61
    Height = 17
    AutoSize = False
    Caption = 'Device:'
  end
  object Label7: TLabel
    Left = 228
    Top = 22
    Width = 45
    Height = 17
    AutoSize = False
    Caption = 'Profile:'
  end
  object cmbDevice: TComboBox
    Left = 58
    Top = 20
    Width = 159
    Height = 21
    Style = csDropDownList
    ImeName = #20013#25991' ('#31616#20307') - '#25628#29399#25340#38899#36755#20837#27861
    ItemHeight = 13
    TabOrder = 0
    OnChange = cmbDeviceChange
  end
  object btnOk: TButton
    Left = 262
    Top = 195
    Width = 81
    Height = 26
    Caption = 'OK'
    TabOrder = 1
    OnClick = btnOkClick
  end
  object btnCancel: TButton
    Left = 364
    Top = 196
    Width = 81
    Height = 25
    Caption = 'Cancel'
    TabOrder = 2
    OnClick = btnCancelClick
  end
  object GroupBox1: TGroupBox
    Left = 9
    Top = 54
    Width = 240
    Height = 131
    Caption = 'Buffered AO settings'
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
      Top = 63
      Width = 73
      Height = 17
      AutoSize = False
      Caption = 'Channel count:'
    end
    object Label4: TLabel
      Left = 9
      Top = 100
      Width = 65
      Height = 17
      AutoSize = False
      Caption = 'Value range:'
    end
    object cmbChannelStart: TComboBox
      Left = 88
      Top = 22
      Width = 137
      Height = 21
      ImeName = #20013#25991' ('#31616#20307') - '#25628#29399#25340#38899#36755#20837#27861
      ItemHeight = 13
      TabOrder = 0
    end
    object cmbChannelCount: TComboBox
      Left = 88
      Top = 59
      Width = 137
      Height = 21
      ImeName = #20013#25991' ('#31616#20307') - '#25628#29399#25340#38899#36755#20837#27861
      ItemHeight = 13
      TabOrder = 1
    end
    object cmbValueRange: TComboBox
      Left = 88
      Top = 97
      Width = 137
      Height = 21
      ImeName = #20013#25991' ('#31616#20307') - '#25628#29399#25340#38899#36755#20837#27861
      ItemHeight = 13
      TabOrder = 2
    end
  end
  object GroupBox2: TGroupBox
    Left = 264
    Top = 54
    Width = 185
    Height = 131
    Caption = 'Output wave settings'
    TabOrder = 4
    object Label5: TLabel
      Left = 24
      Top = 17
      Width = 145
      Height = 17
      AutoSize = False
      Caption = 'Points for each waveform:'
    end
    object Label6: TLabel
      Left = 24
      Top = 72
      Width = 137
      Height = 17
      AutoSize = False
      Caption = 'Waveform out frequency:'
    end
    object Label8: TLabel
      Left = 145
      Top = 97
      Width = 13
      Height = 13
      Caption = 'Hz'
    end
    object txtPointCount: TEdit
      Left = 24
      Top = 38
      Width = 113
      Height = 25
      AutoSize = False
      ImeName = #20013#25991' ('#31616#20307') - '#25628#29399#25340#38899#36755#20837#27861
      TabOrder = 0
      Text = '400'
    end
    object txtClockRate: TEdit
      Left = 25
      Top = 91
      Width = 112
      Height = 25
      AutoSize = False
      ImeName = #20013#25991' ('#31616#20307') - '#25628#29399#25340#38899#36755#20837#27861
      TabOrder = 1
      Text = '1000'
    end
  end
  object txtProfilePath: TEdit
    Left = 272
    Top = 20
    Width = 121
    Height = 21
    TabOrder = 5
  end
  object btnBrowse: TButton
    Left = 400
    Top = 18
    Width = 49
    Height = 25
    Caption = 'Browse'
    TabOrder = 6
    OnClick = btnBrowseClick
  end
end
