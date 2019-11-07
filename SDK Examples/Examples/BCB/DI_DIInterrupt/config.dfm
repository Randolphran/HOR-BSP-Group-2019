object ConfigForm: TConfigForm
  Left = 198
  Top = 138
  BorderStyle = bsDialog
  Caption = 'DI Interrupt - Configuration'
  ClientHeight = 351
  ClientWidth = 333
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
    Top = 14
    Width = 45
    Height = 17
    AutoSize = False
    Caption = 'Device:'
  end
  object labelEnabledCH: TLabel
    Left = 12
    Top = 86
    Width = 89
    Height = 13
    Caption = 'Enabled Channels:'
  end
  object Label2: TLabel
    Left = 17
    Top = 105
    Width = 39
    Height = 13
    Caption = 'Port No.'
  end
  object Label3: TLabel
    Left = 63
    Top = 105
    Width = 18
    Height = 13
    Caption = 'Bit7'
  end
  object Label4: TLabel
    Left = 162
    Top = 105
    Width = 6
    Height = 13
    Caption = '4'
  end
  object Label5: TLabel
    Left = 193
    Top = 105
    Width = 6
    Height = 13
    Caption = '3'
  end
  object Label6: TLabel
    Left = 287
    Top = 105
    Width = 6
    Height = 13
    Caption = '0'
  end
  object Label7: TLabel
    Left = 12
    Top = 51
    Width = 32
    Height = 13
    Caption = 'Profile:'
  end
  object cmbDevice: TComboBox
    Left = 64
    Top = 12
    Width = 250
    Height = 21
    Style = csDropDownList
    ImeName = #20013#25991' ('#31616#20307') - '#25628#29399#25340#38899#36755#20837#27861
    ItemHeight = 13
    TabOrder = 0
    OnChange = cmbDeviceChange
  end
  object btnOk: TButton
    Left = 107
    Top = 312
    Width = 81
    Height = 26
    Caption = 'OK'
    TabOrder = 1
    OnClick = btnOkClick
  end
  object btnCancel: TButton
    Left = 217
    Top = 313
    Width = 81
    Height = 25
    Caption = 'Cancel'
    TabOrder = 2
    OnClick = btnCancelClick
  end
  object ScrollBox1: TScrollBox
    Left = 10
    Top = 124
    Width = 309
    Height = 173
    TabOrder = 3
  end
  object txtProfilePath: TEdit
    Left = 64
    Top = 48
    Width = 169
    Height = 21
    TabOrder = 4
  end
  object btnBrowse: TButton
    Left = 248
    Top = 48
    Width = 65
    Height = 22
    Caption = 'Browse'
    TabOrder = 5
    OnClick = btnBrowseClick
  end
end
