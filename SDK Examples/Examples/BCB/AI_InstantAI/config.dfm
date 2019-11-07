object ConfigForm: TConfigForm
  Left = 495
  Top = 228
  BorderStyle = bsDialog
  Caption = 'Instant AI - Configuration'
  ClientHeight = 274
  ClientWidth = 354
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
    Left = 14
    Top = 24
    Width = 43
    Height = 17
    AutoSize = False
    Caption = 'Device:'
  end
  object Label5: TLabel
    Left = 14
    Top = 59
    Width = 43
    Height = 17
    AutoSize = False
    Caption = 'Profile:'
  end
  object cmbDevice: TComboBox
    Left = 64
    Top = 20
    Width = 257
    Height = 21
    Style = csDropDownList
    ImeName = #20013#25991' ('#31616#20307') - '#25628#29399#25340#38899#36755#20837#27861
    ItemHeight = 13
    TabOrder = 0
    OnChange = cmbDeviceChange
  end
  object btnOk: TButton
    Left = 143
    Top = 236
    Width = 81
    Height = 26
    Caption = 'OK'
    TabOrder = 1
    OnClick = btnOkClick
  end
  object btnCancel: TButton
    Left = 245
    Top = 237
    Width = 81
    Height = 26
    Caption = 'Cancel'
    TabOrder = 2
    OnClick = btnCancelClick
  end
  object GroupBox1: TGroupBox
    Left = 16
    Top = 101
    Width = 321
    Height = 124
    Caption = 'Instant AI settings'
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
      Top = 93
      Width = 65
      Height = 17
      AutoSize = False
      Caption = 'Value range:'
    end
    object cmbChannelStart: TComboBox
      Left = 88
      Top = 22
      Width = 209
      Height = 21
      ImeName = #20013#25991' ('#31616#20307') - '#25628#29399#25340#38899#36755#20837#27861
      ItemHeight = 13
      TabOrder = 0
    end
    object cmbChannelCount: TComboBox
      Left = 88
      Top = 55
      Width = 209
      Height = 21
      ImeName = #20013#25991' ('#31616#20307') - '#25628#29399#25340#38899#36755#20837#27861
      ItemHeight = 13
      TabOrder = 1
    end
    object cmbValueRange: TComboBox
      Left = 88
      Top = 90
      Width = 209
      Height = 21
      ImeName = #20013#25991' ('#31616#20307') - '#25628#29399#25340#38899#36755#20837#27861
      ItemHeight = 13
      TabOrder = 2
    end
  end
  object txtProfilePath: TEdit
    Left = 64
    Top = 56
    Width = 185
    Height = 21
    TabOrder = 4
  end
  object btnBrowse: TButton
    Left = 256
    Top = 56
    Width = 65
    Height = 22
    Caption = 'Browse'
    TabOrder = 5
    OnClick = btnBrowseClick
  end
end
