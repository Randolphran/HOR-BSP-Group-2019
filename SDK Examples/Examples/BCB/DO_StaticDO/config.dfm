object ConfigForm: TConfigForm
  Left = 374
  Top = 202
  BorderStyle = bsDialog
  Caption = 'Static DO - Configuration'
  ClientHeight = 144
  ClientWidth = 331
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
    Top = 21
    Width = 53
    Height = 17
    AutoSize = False
    Caption = 'Device:'
  end
  object Label2: TLabel
    Left = 16
    Top = 60
    Width = 41
    Height = 13
    Caption = 'Profile:'
  end
  object cmbDevice: TComboBox
    Left = 73
    Top = 17
    Width = 232
    Height = 21
    Style = csDropDownList
    ItemHeight = 13
    TabOrder = 0
  end
  object btnOk: TButton
    Left = 103
    Top = 99
    Width = 81
    Height = 26
    Caption = 'OK'
    TabOrder = 1
    OnClick = btnOkClick
  end
  object btnCancel: TButton
    Left = 229
    Top = 100
    Width = 81
    Height = 25
    Caption = 'Cancel'
    TabOrder = 2
    OnClick = btnCancelClick
  end
  object txtProfilePath: TEdit
    Left = 72
    Top = 56
    Width = 161
    Height = 21
    TabOrder = 3
  end
  object btnBrowse: TButton
    Left = 248
    Top = 56
    Width = 57
    Height = 23
    Caption = 'Browse'
    TabOrder = 4
    OnClick = btnBrowseClick
  end
end
