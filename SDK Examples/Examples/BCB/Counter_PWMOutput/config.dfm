object ConfigForm: TConfigForm
  Left = 347
  Top = 138
  BorderStyle = bsDialog
  Caption = 'PWM Output - Configuration'
  ClientHeight = 155
  ClientWidth = 303
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
    Top = 11
    Width = 45
    Height = 17
    AutoSize = False
    Caption = 'Device:'
  end
  object Label2: TLabel
    Left = 10
    Top = 80
    Width = 42
    Height = 26
    Caption = 'Counter Channel:'
    WordWrap = True
  end
  object Label3: TLabel
    Left = 12
    Top = 51
    Width = 37
    Height = 17
    AutoSize = False
    Caption = 'Profile:'
  end
  object cmbDevice: TComboBox
    Left = 56
    Top = 9
    Width = 225
    Height = 21
    Style = csDropDownList
    ItemHeight = 13
    TabOrder = 0
    OnChange = cmbDeviceChange
  end
  object cmbCounterChannel: TComboBox
    Left = 56
    Top = 85
    Width = 225
    Height = 21
    Style = csDropDownList
    ItemHeight = 13
    TabOrder = 1
  end
  object btnOk: TButton
    Left = 63
    Top = 119
    Width = 81
    Height = 25
    Caption = 'OK'
    TabOrder = 2
    OnClick = btnOkClick
  end
  object btnCancel: TButton
    Left = 189
    Top = 120
    Width = 81
    Height = 25
    Caption = 'Cancel'
    TabOrder = 3
    OnClick = btnCancelClick
  end
  object txtProfilePath: TEdit
    Left = 56
    Top = 46
    Width = 169
    Height = 21
    TabOrder = 4
  end
  object btnBrowse: TButton
    Left = 232
    Top = 44
    Width = 51
    Height = 25
    Caption = 'Browse'
    TabOrder = 5
    OnClick = btnBrowseClick
  end
end
