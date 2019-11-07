object ConfigForm: TConfigForm
  Left = 559
  Top = 199
  BorderStyle = bsDialog
  Caption = 'PulseOutputwithTimerInterrupt - Configuration'
  ClientHeight = 184
  ClientWidth = 330
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
    Top = 13
    Width = 45
    Height = 17
    AutoSize = False
    Caption = 'Device:'
  end
  object Label2: TLabel
    Left = 10
    Top = 78
    Width = 42
    Height = 26
    Caption = 'Counter Channel:'
    WordWrap = True
  end
  object Label3: TLabel
    Left = 11
    Top = 110
    Width = 38
    Height = 26
    Caption = 'Module Index:'
    WordWrap = True
  end
  object Label4: TLabel
    Left = 12
    Top = 45
    Width = 45
    Height = 17
    AutoSize = False
    Caption = 'Profile:'
  end
  object cmbDevice: TComboBox
    Left = 72
    Top = 9
    Width = 242
    Height = 21
    Style = csDropDownList
    ItemHeight = 13
    TabOrder = 0
    OnChange = cmbDeviceChange
  end
  object cmbCounterChannel: TComboBox
    Left = 72
    Top = 81
    Width = 241
    Height = 21
    Style = csDropDownList
    ItemHeight = 13
    TabOrder = 1
  end
  object btnOk: TButton
    Left = 87
    Top = 148
    Width = 81
    Height = 25
    Caption = 'OK'
    TabOrder = 2
    OnClick = btnOkClick
  end
  object btnCancel: TButton
    Left = 213
    Top = 148
    Width = 81
    Height = 25
    Caption = 'Cancel'
    TabOrder = 3
    OnClick = btnCancelClick
  end
  object cmbModuleIndex: TComboBox
    Left = 72
    Top = 114
    Width = 241
    Height = 21
    Style = csDropDownList
    ItemHeight = 13
    TabOrder = 4
    OnChange = cmbModuleIndexChange
  end
  object txtProfilePath: TEdit
    Left = 72
    Top = 44
    Width = 185
    Height = 21
    TabOrder = 5
  end
  object btnBrowse: TButton
    Left = 272
    Top = 42
    Width = 43
    Height = 25
    Caption = 'Browse'
    TabOrder = 6
    OnClick = btnBrowseClick
  end
end
