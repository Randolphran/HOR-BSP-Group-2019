object ConfigForm: TConfigForm
  Left = 475
  Top = 230
  BorderStyle = bsDialog
  Caption = 'Asynchronous One Buffered AI - Configuration'
  ClientHeight = 339
  ClientWidth = 345
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
  object Label6: TLabel
    Left = 32
    Top = 60
    Width = 32
    Height = 13
    Caption = 'Profile:'
  end
  object cmbDevice: TComboBox
    Left = 75
    Top = 20
    Width = 238
    Height = 21
    Style = csDropDownList
    ImeName = #20013#25991' ('#31616#20307') - '#25628#29399#25340#38899#36755#20837#27861
    ItemHeight = 13
    TabOrder = 0
    OnChange = cmbDeviceChange
  end
  object btnOk: TButton
    Left = 143
    Top = 303
    Width = 81
    Height = 26
    Caption = 'OK'
    TabOrder = 1
    OnClick = btnOkClick
  end
  object btnCancel: TButton
    Left = 245
    Top = 304
    Width = 81
    Height = 25
    Caption = 'Cancel'
    TabOrder = 2
    OnClick = btnCancelClick
  end
  object GroupBox1: TGroupBox
    Left = 18
    Top = 86
    Width = 311
    Height = 203
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
      Top = 165
      Width = 57
      Height = 17
      AutoSize = False
      Caption = 'Clock rate:'
    end
    object Label8: TLabel
      Left = 247
      Top = 170
      Width = 13
      Height = 13
      Caption = 'Hz'
    end
    object Label5: TLabel
      Left = 9
      Top = 124
      Width = 80
      Height = 17
      AutoSize = False
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
      Top = 162
      Width = 153
      Height = 23
      AutoSize = False
      ImeName = #20013#25991' ('#31616#20307') - '#25628#29399#25340#38899#36755#20837#27861
      TabOrder = 3
      Text = '1000'
    end
    object txtSectionLength: TEdit
      Left = 88
      Top = 122
      Width = 153
      Height = 23
      AutoSize = False
      ImeName = #20013#25991' ('#31616#20307') - '#25628#29399#25340#38899#36755#20837#27861
      TabOrder = 4
      Text = '1024'
    end
  end
  object txtProfilePath: TEdit
    Left = 75
    Top = 56
    Width = 169
    Height = 21
    TabOrder = 4
  end
  object btnBrowse: TButton
    Left = 264
    Top = 56
    Width = 51
    Height = 22
    Caption = 'Browse'
    TabOrder = 5
    OnClick = btnBrowseClick
  end
end
