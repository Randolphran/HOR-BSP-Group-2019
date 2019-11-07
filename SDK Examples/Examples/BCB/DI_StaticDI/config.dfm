object ConfigForm: TConfigForm
  Left = 517
  Top = 240
  BorderStyle = bsDialog
  Caption = 'Static DI - Configuration'
  ClientHeight = 143
  ClientWidth = 313
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
    Top = 15
    Width = 45
    Height = 17
    AutoSize = False
    Caption = 'Device:'
  end
  object Label2: TLabel
    Left = 12
    Top = 58
    Width = 32
    Height = 13
    Caption = 'Profile:'
  end
  object cmbDevice: TComboBox
    Left = 65
    Top = 12
    Width = 225
    Height = 21
    Style = csDropDownList
    ItemHeight = 13
    TabOrder = 0
  end
  object btnOk: TButton
    Left = 79
    Top = 99
    Width = 81
    Height = 26
    Caption = 'OK'
    TabOrder = 1
    OnClick = btnOkClick
  end
  object btnCancel: TButton
    Left = 205
    Top = 100
    Width = 81
    Height = 25
    Caption = 'Cancel'
    TabOrder = 2
    OnClick = btnCancelClick
  end
  object txtProfilePath: TEdit
    Left = 65
    Top = 56
    Width = 161
    Height = 21
    TabOrder = 3
  end
  object btnBrowse: TButton
    Left = 240
    Top = 56
    Width = 49
    Height = 22
    Caption = 'Browse'
    TabOrder = 4
    OnClick = btnBrowseClick
  end
end
