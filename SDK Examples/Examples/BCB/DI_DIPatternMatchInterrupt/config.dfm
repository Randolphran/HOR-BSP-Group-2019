object ConfigForm: TConfigForm
  Left = 482
  Top = 166
  BorderStyle = bsDialog
  Caption = 'DI Pattern Match Interrupt - Configuration'
  ClientHeight = 326
  ClientWidth = 339
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
    Left = 32
    Top = 21
    Width = 49
    Height = 17
    AutoSize = False
    Caption = 'Device:'
  end
  object Label2: TLabel
    Left = 33
    Top = 101
    Width = 45
    Height = 17
    AutoSize = False
    Caption = 'DI port:'
  end
  object Label3: TLabel
    Left = 33
    Top = 134
    Width = 113
    Height = 17
    AutoSize = False
    Caption = 'Enabled channels:'
  end
  object Label4: TLabel
    Left = 33
    Top = 202
    Width = 113
    Height = 17
    AutoSize = False
    Caption = 'Matched value:'
  end
  object Label5: TLabel
    Left = 32
    Top = 61
    Width = 41
    Height = 17
    AutoSize = False
    Caption = 'Profile:'
  end
  object cmbDevice: TComboBox
    Left = 89
    Top = 17
    Width = 225
    Height = 21
    Style = csDropDownList
    ItemHeight = 13
    TabOrder = 0
    OnChange = cmbDeviceChange
  end
  object btnOk: TButton
    Left = 103
    Top = 275
    Width = 81
    Height = 26
    Caption = 'OK'
    TabOrder = 1
    OnClick = btnOkClick
  end
  object btnCancel: TButton
    Left = 229
    Top = 276
    Width = 81
    Height = 25
    Caption = 'Cancel'
    TabOrder = 2
    OnClick = btnCancelClick
  end
  object cmbDIport: TComboBox
    Left = 89
    Top = 97
    Width = 225
    Height = 21
    Style = csDropDownList
    ItemHeight = 13
    TabOrder = 3
    OnChange = cmbDIportChange
  end
  object GroupBox2: TGroupBox
    Left = 33
    Top = 155
    Width = 100
    Height = 36
    TabOrder = 4
    object Image04: TImage
      Left = 74
      Top = 8
      Width = 23
      Height = 23
      HelpType = htKeyword
      HelpKeyword = '4'
      OnClick = Image0Click
    end
    object Image05: TImage
      Left = 50
      Top = 8
      Width = 23
      Height = 23
      HelpType = htKeyword
      HelpKeyword = '5'
      OnClick = Image0Click
    end
    object Image06: TImage
      Left = 26
      Top = 8
      Width = 23
      Height = 23
      HelpType = htKeyword
      HelpKeyword = '6'
      OnClick = Image0Click
    end
    object Image07: TImage
      Left = 2
      Top = 8
      Width = 23
      Height = 23
      HelpType = htKeyword
      HelpKeyword = '7'
      OnClick = Image0Click
    end
  end
  object enableChan: TEdit
    Left = 264
    Top = 162
    Width = 30
    Height = 28
    AutoSize = False
    Color = clBtnFace
    ReadOnly = True
    TabOrder = 5
  end
  object GroupBox1: TGroupBox
    Left = 147
    Top = 155
    Width = 100
    Height = 36
    TabOrder = 6
    object Image00: TImage
      Left = 74
      Top = 8
      Width = 23
      Height = 23
      HelpType = htKeyword
      HelpKeyword = '0'
      OnClick = Image0Click
    end
    object Image01: TImage
      Left = 50
      Top = 8
      Width = 23
      Height = 23
      HelpType = htKeyword
      HelpKeyword = '1'
      OnClick = Image0Click
    end
    object Image02: TImage
      Left = 26
      Top = 8
      Width = 23
      Height = 23
      HelpType = htKeyword
      HelpKeyword = '2'
      OnClick = Image0Click
    end
    object Image03: TImage
      Left = 2
      Top = 8
      Width = 23
      Height = 23
      HelpType = htKeyword
      HelpKeyword = '3'
      OnClick = Image0Click
    end
  end
  object GroupBo4: TGroupBox
    Left = 33
    Top = 223
    Width = 100
    Height = 36
    TabOrder = 7
    object Image14: TImage
      Left = 74
      Top = 8
      Width = 23
      Height = 23
      HelpType = htKeyword
      HelpKeyword = '4'
      OnClick = Image1Click
    end
    object Image15: TImage
      Left = 50
      Top = 8
      Width = 23
      Height = 23
      HelpType = htKeyword
      HelpKeyword = '5'
      OnClick = Image1Click
    end
    object Image16: TImage
      Left = 26
      Top = 8
      Width = 23
      Height = 23
      HelpType = htKeyword
      HelpKeyword = '6'
      OnClick = Image1Click
    end
    object Image17: TImage
      Left = 2
      Top = 8
      Width = 23
      Height = 23
      HelpType = htKeyword
      HelpKeyword = '7'
      OnClick = Image1Click
    end
  end
  object GroupBox3: TGroupBox
    Left = 147
    Top = 223
    Width = 100
    Height = 36
    TabOrder = 8
    object Image13: TImage
      Left = 2
      Top = 8
      Width = 23
      Height = 23
      HelpType = htKeyword
      HelpKeyword = '3'
      OnClick = Image1Click
    end
    object Image10: TImage
      Left = 74
      Top = 8
      Width = 23
      Height = 23
      HelpType = htKeyword
      HelpKeyword = '0'
      OnClick = Image1Click
    end
    object Image11: TImage
      Left = 50
      Top = 8
      Width = 23
      Height = 23
      HelpType = htKeyword
      HelpKeyword = '1'
      OnClick = Image1Click
    end
    object Image12: TImage
      Left = 26
      Top = 8
      Width = 23
      Height = 23
      HelpType = htKeyword
      HelpKeyword = '2'
      OnClick = Image1Click
    end
  end
  object edtpmValue: TEdit
    Left = 264
    Top = 230
    Width = 30
    Height = 28
    AutoSize = False
    Color = clBtnFace
    ReadOnly = True
    TabOrder = 9
  end
  object txtProfilePath: TEdit
    Left = 88
    Top = 56
    Width = 145
    Height = 21
    TabOrder = 10
  end
  object butBrowse: TButton
    Left = 240
    Top = 56
    Width = 75
    Height = 22
    Caption = 'Browse'
    TabOrder = 11
    OnClick = butBrowseClick
  end
  object ImageList1: TImageList
    Height = 23
    Width = 23
    Left = 24
    Top = 280
    Bitmap = {
      494C010102000400040017001700FFFFFFFFFF10FFFFFFFFFFFFFFFF424D3600
      00000000000036000000280000005C0000001700000001002000000000001021
      000000000000000000000000000000000000D7E8EB00C8D5D700ADB0B000A8A8
      A800A0A0A0009B9B9B009C9C9C009C9C9C009C9C9C009C9C9C009D9D9D009D9D
      9D009D9D9D009D9D9D009D9D9D009C9C9C009C9C9C009C9C9C009C9C9C009D9D
      9D0096969600878787008A8D8D0000000000D6E3E500DDE4E500E2E6E600E3E6
      E600E2E5E500E3E6E600E3E6E600E3E6E600E3E6E600E2E5E500E2E5E500E2E5
      E500E2E5E500E2E5E500E2E5E500E2E5E500E2E5E500E2E5E500E3E6E600DBDF
      DF00C5CCCD00C3D0D20000000000000000000000000000000000000000000000
      0000000000000000000000000000000000000000000000000000000000000000
      0000000000000000000000000000000000000000000000000000000000000000
      0000000000000000000000000000000000000000000000000000000000000000
      0000000000000000000000000000000000000000000000000000000000000000
      0000000000000000000000000000000000000000000000000000000000000000
      0000D3E3E600ADB3B400B7B7B700CDCDCD00D3D3D300D0D0D000CFCFCF00CFCF
      CF00CFCFCF00CFCFCF00CFCFCF00CFCFCF00CFCFCF00CFCFCF00CFCFCF00CFCF
      CF00CFCFCF00CFCFCF00CFCFCF00D1D1D100CACACA00ABABAB0080808000C5D3
      D500C4C8C800DCDDDD00F4F4F400FBFBFB00FBFBFB00FBFBFB00FBFBFB00FBFB
      FB00FBFBFB00FBFBFB00FBFBFB00FBFBFB00FBFBFB00FBFBFB00FBFBFB00FBFB
      FB00FBFBFB00FBFBFB00FCFCFC00FAFAFA00D8D9D9009BA0A000000000000000
      0000000000000000000000000000000000000000000000000000000000000000
      0000000000000000000000000000000000000000000000000000000000000000
      0000000000000000000000000000000000000000000000000000000000000000
      0000000000000000000000000000000000000000000000000000000000000000
      0000000000000000000000000000000000000000000000000000000000000000
      000000000000000000000000000000000000CFDEE100ADAFAF00DEDEDE00F8F8
      F800FAFAFA00F4F4F400F4F4F400F4F4F400F4F4F400F4F4F400F4F4F400F4F4
      F400F4F4F400F4F4F400F4F4F400F4F4F400F4F4F400F4F4F400F4F4F400F5F5
      F500F3F3F300D7D7D7009E9E9E00A6ADAE00A4A5A500B9B9B900ECECEC00FFFF
      FF00FFFFFF00FFFFFF00FFFFFF00FFFFFF00FFFFFF00FFFFFF00FFFFFF00FFFF
      FF00FFFFFF00FFFFFF00FFFFFF00FFFFFF00FFFFFF00FFFFFF00FFFFFF00FFFF
      FF00FCFCFC00BBBCBD0000000000000000000000000000000000000000000000
      0000000000000000000000000000000000000000000000000000000000000000
      0000000000000000000000000000000000000000000000000000000000000000
      0000000000000000000000000000000000000000000000000000000000000000
      0000000000000000000000000000000000000000000000000000000000000000
      0000000000000000000000000000000000000000000000000000000000000000
      0000CFDEE100B3B4B500EAEAEA00FFFFFF00FFFFFF00FFFFFF00FFFFFF00FFFF
      FF00FFFFFF00FFFFFF00FFFFFF00FFFFFF00FFFFFF00FFFFFF00FFFFFF00FFFF
      FF00FFFFFF00FFFFFF00FFFFFF00FFFFFF00FAFAFB00E2E2E200ADADAD009D9F
      A0007B7B7B0080808000C8C8C800FCFCFC00FFFFFF00FFFFFF00FFFFFF00FFFF
      FF00FFFFFF00FFFFFF00FFFFFF00FFFFFF00FFFFFF00FFFFFF00FFFFFF00FFFF
      FF00FFFFFF00FFFFFF00FFFFFF00F8F8F800EEEEEE00C2C2C300000000000000
      0000000000000000000000000000000000000000000000000000000000000000
      0000000000000000000000000000000000000000000000000000000000000000
      0000000000000000000000000000000000000000000000000000000000000000
      0000000000000000000000000000000000000000000000000000000000000000
      0000000000000000000000000000000000000000000000000000000000000000
      000000000000000000000000000000000000CFDEE100B3B4B500E8E8E800FEFE
      FE00FFFFFF00FFFFFF00FFFFFF00FFFFFF00FFFFFF00FFFFFF00FFFFFF00FFFF
      FF00FFFFFF00FFFFFF00FFFFFF00FFFFFF00FFFFFF00FFFFFF00FFFFFF00FFFF
      FF00F9F9FA00E0E0E100ACACAC009D9FA0006565650060606000A5A5A500EBEB
      EB00FFFFFF00FFFFFF00FFFFFF00FFFFFF00FFFFFF00FFFFFF00FFFFFF00FFFF
      FF00FFFFFF00FFFFFF00FFFFFF00FFFFFF00FFFFFF00FFFFFF00FFFFFF00EAEA
      EA00CDCDCD00ACACAC0000000000000000000000000000000000000000000000
      0000000000000000000000000000000000000000000000000000000000000000
      0000000000000000000000000000000000000000000000000000000000000000
      0000000000000000000000000000000000000000000000000000000000000000
      0000000000000000000000000000000000000000000000000000000000000000
      0000000000000000000000000000000000000000000000000000000000000000
      0000CFDEE100B2B4B400E8E8E800FEFEFE00FFFFFF00FFFFFF00FFFFFF00FFFF
      FF00FFFFFF00FFFFFF00FFFFFF00FFFFFF00FFFFFF00FFFFFF00FFFFFF00FFFF
      FF00FFFFFF00FFFFFF00FFFFFF00FFFFFF00F9F9FA00E0E0E100ABABAB009EA0
      A000666666005F5F5F009A9A9A00DDDEDD00FDFDFD00FFFFFF00FFFFFF00FFFF
      FF00FFFFFF00FFFFFF00FFFFFF00FFFFFF00FFFFFF00FFFFFF00FFFFFF00FFFF
      FF00FFFFFF00FFFFFF00FFFFFF00E5E5E500C3C3C300A4A4A300000000000000
      0000000000000000000000000000000000000000000000000000000000000000
      0000000000000000000000000000000000000000000000000000000000000000
      0000000000000000000000000000000000000000000000000000000000000000
      0000000000000000000000000000000000000000000000000000000000000000
      0000000000000000000000000000000000000000000000000000000000000000
      000000000000000000000000000000000000CFDEE100B3B4B500E8E8E800FEFE
      FE00FFFFFF00FFFFFF00FFFFFF00FFFFFF00FFFFFF00FFFFFF00FFFFFF00FFFF
      FF00FFFFFF00FFFFFF00FFFFFF00FFFFFF00FFFFFF00FFFFFF00FFFFFF00FFFF
      FF00F9F9FA00E0E0E100ABABAB009EA0A10068686800626262009E9E9E00DDDC
      DD00FAFAFA00FFFFFF00FFFFFF00FFFFFF00FFFFFF00FFFFFF00FFFFFF00FFFF
      FF00FFFFFF00FFFFFF00FFFFFF00FFFFFF00FFFFFF00FFFFFF00FEFEFE00E7E7
      E700C8C8C800A7A7A70000000000000000000000000000000000000000000000
      0000000000000000000000000000000000000000000000000000000000000000
      0000000000000000000000000000000000000000000000000000000000000000
      0000000000000000000000000000000000000000000000000000000000000000
      0000000000000000000000000000000000000000000000000000000000000000
      0000000000000000000000000000000000000000000000000000000000000000
      0000CFDEE100B4B5B600E8E8E800FEFEFE00FFFFFF00FFFFFF00FFFFFF00FFFF
      FF00FFFFFF00FFFFFF00FFFFFF00FFFFFF00FFFFFF00FFFFFF00FFFFFF00FFFF
      FF00FFFFFF00FFFFFF00FFFFFF00FFFFFF00F9F9FA00E0E0E100ABABAB009EA0
      A10068686800626262009F9F9F00DDDDDD00FAFAFA00FFFFFF00FFFFFF00FFFF
      FF00FFFFFF00FFFFFF00FFFFFF00FFFFFF00FFFFFF00FFFFFF00FFFFFF00FFFF
      FF00FFFFFF00FFFFFF00FEFEFE00E7E7E700C8C8C800A7A7A700000000000000
      0000000000000000000000000000000000000000000000000000000000000000
      0000000000000000000000000000000000000000000000000000000000000000
      0000000000000000000000000000000000000000000000000000000000000000
      0000000000000000000000000000000000000000000000000000000000000000
      0000000000000000000000000000000000000000000000000000000000000000
      000000000000000000000000000000000000CFDEE100B4B5B600E8E8E800FEFE
      FE00FFFFFF00FFFFFF00FFFFFF00FFFFFF00FFFFFF00FFFFFF00FFFFFF00FFFF
      FF00FFFFFF00FFFFFF00FFFFFF00FFFFFF00FFFFFF00FFFFFF00FFFFFF00FFFF
      FF00F9F9FA00E0E0E100ABABAB009EA0A10068686800626262009D9D9D00DDDD
      DD00FAFAFA00FFFFFF00FFFFFF00FFFFFF00FFFFFF00FFFFFF00FFFFFF00FFFF
      FF00FFFFFF00FFFFFF00FFFFFF00FFFFFF00FFFFFF00FFFFFF00FEFEFE00E7E7
      E700C8C8C800A5A5A50000000000000000000000000000000000000000000000
      0000000000000000000000000000000000000000000000000000000000000000
      0000000000000000000000000000000000000000000000000000000000000000
      0000000000000000000000000000000000000000000000000000000000000000
      0000000000000000000000000000000000000000000000000000000000000000
      0000000000000000000000000000000000000000000000000000000000000000
      0000CFDEE100B4B5B600E8E8E800FEFEFE00FFFFFF00FFFFFF00FFFFFF00FFFF
      FF00FFFFFF00FFFFFF00FFFFFF00FFFFFF00FFFFFF00FFFFFF00FFFFFF00FFFF
      FF00FFFFFF00FFFFFF00FFFFFF00FFFFFF00F9F9FA00E0E0E100ABABAB009EA0
      A10068686800626262009D9D9D00DDDDDD00FAFAFA00FFFFFF00FFFFFF00FFFF
      FF00FFFFFF00FFFFFF00FFFFFF00FFFFFF00FFFFFF00FFFFFF00FFFFFF00FFFF
      FF00FFFFFF00FFFFFF00FEFEFE00E7E7E700C8C8C800A5A5A500000000000000
      0000000000000000000000000000000000000000000000000000000000000000
      0000000000000000000000000000000000000000000000000000000000000000
      0000000000000000000000000000000000000000000000000000000000000000
      0000000000000000000000000000000000000000000000000000000000000000
      0000000000000000000000000000000000000000000000000000000000000000
      000000000000000000000000000000000000CFDEE100B4B5B600E9E9E900FFFF
      FF00FFFFFF00FFFFFF00FFFFFF00FFFFFF00FFFFFF00FFFFFF00FFFFFF00FFFF
      FF00FFFFFF00FFFFFF00FFFFFF00FFFFFF00FFFFFF00FFFFFF00FFFFFF00FFFF
      FF00F9F9F900E0E0E100ACACAB009EA0A10068686800626262009D9D9D00DDDD
      DD00FAFAFA00FFFFFF00FFFFFF00FFFFFF00FFFFFF00FFFFFF00FFFFFF00FFFF
      FF00FFFFFF00FFFFFF00FFFFFF00FFFFFF00FFFFFF00FFFFFF00FEFEFE00E7E7
      E700C8C8C800A5A5A50000000000000000000000000000000000000000000000
      0000000000000000000000000000000000000000000000000000000000000000
      0000000000000000000000000000000000000000000000000000000000000000
      0000000000000000000000000000000000000000000000000000000000000000
      0000000000000000000000000000000000000000000000000000000000000000
      0000000000000000000000000000000000000000000000000000000000000000
      0000CFDEE100B4B5B600E9E9E900FFFFFF00FFFFFF00FFFFFF00FFFFFF00FFFF
      FF00FFFFFF00FFFFFF00FFFFFF00FFFFFF00FFFFFF00FFFFFF00FFFFFF00FFFF
      FF00FFFFFF00FFFFFF00FFFFFF00FFFFFF00F8F8F800E0E0E000ACACAC009EA0
      A10067676700616161009D9D9D00DDDDDD00FAFAFA00FFFFFF00FFFFFF00FFFF
      FF00FFFFFF00FFFFFF00FFFFFF00FFFFFF00FFFFFF00FFFFFF00FFFFFF00FFFF
      FF00FFFFFF00FFFFFF00FEFEFE00E7E7E700C7C7C700A6A6A600000000000000
      0000000000000000000000000000000000000000000000000000000000000000
      0000000000000000000000000000000000000000000000000000000000000000
      0000000000000000000000000000000000000000000000000000000000000000
      0000000000000000000000000000000000000000000000000000000000000000
      0000000000000000000000000000000000000000000000000000000000000000
      000000000000000000000000000000000000CFDEE100B5B6B700E9E9E900FFFF
      FF00FFFFFF00FFFFFF00FFFFFF00FFFFFF00FFFFFF00FFFFFF00FFFFFF00FFFF
      FF00FFFFFF00FFFFFF00FFFFFF00FFFFFF00FFFFFF00FFFFFF00FFFFFF00FFFF
      FF00F8F8F800E0E0E000ACACAC009EA0A10067676700616161009D9D9D00DDDD
      DD00FAFAFA00FFFFFF00FFFFFF00FFFFFF00FFFFFF00FFFFFF00FFFFFF00FFFF
      FF00FFFFFF00FFFFFF00FFFFFF00FFFFFF00FFFFFF00FFFFFF00FEFEFE00E7E7
      E700C7C7C700A6A6A60000000000000000000000000000000000000000000000
      0000000000000000000000000000000000000000000000000000000000000000
      0000000000000000000000000000000000000000000000000000000000000000
      0000000000000000000000000000000000000000000000000000000000000000
      0000000000000000000000000000000000000000000000000000000000000000
      0000000000000000000000000000000000000000000000000000000000000000
      0000CFDEE100B5B6B700E9E9E900FFFFFF00FFFFFF00FFFFFF00FFFFFF00FFFF
      FF00FFFFFF00FFFFFF00FFFFFF00FFFFFF00FFFFFF00FFFFFF00FFFFFF00FFFF
      FF00FFFFFF00FFFFFF00FFFFFF00FFFFFF00F8F8F800E0E0E000ACACAC009EA0
      A10067676700616161009D9D9D00DDDDDD00FAFAFA00FFFFFF00FFFFFF00FFFF
      FF00FFFFFF00FFFFFF00FFFFFF00FFFFFF00FFFFFF00FFFFFF00FFFFFF00FFFF
      FF00FFFFFF00FFFFFF00FEFEFE00E7E7E700C7C7C700A6A6A600000000000000
      0000000000000000000000000000000000000000000000000000000000000000
      0000000000000000000000000000000000000000000000000000000000000000
      0000000000000000000000000000000000000000000000000000000000000000
      0000000000000000000000000000000000000000000000000000000000000000
      0000000000000000000000000000000000000000000000000000000000000000
      000000000000000000000000000000000000CFDEE100B5B6B700E9E9E900FFFF
      FF00FFFFFF00FFFFFF00FFFFFF00FFFFFF00FFFFFF00FFFFFF00FFFFFF00FFFF
      FF00FFFFFF00FFFFFF00FFFFFF00FFFFFF00FFFFFF00FFFFFF00FFFFFF00FFFF
      FF00F8F8F800E0E0E000ACACAC009EA0A10067676700616161009D9D9D00DDDD
      DD00FAFAFA00FFFFFF00FFFFFF00FFFFFF00FFFFFF00FFFFFF00FFFFFF00FFFF
      FF00FFFFFF00FFFFFF00FFFFFF00FFFFFF00FFFFFF00FFFFFF00FEFEFE00E7E7
      E700C7C7C700A6A6A60000000000000000000000000000000000000000000000
      0000000000000000000000000000000000000000000000000000000000000000
      0000000000000000000000000000000000000000000000000000000000000000
      0000000000000000000000000000000000000000000000000000000000000000
      0000000000000000000000000000000000000000000000000000000000000000
      0000000000000000000000000000000000000000000000000000000000000000
      0000CFDEE100B5B6B700E9E9E900FFFFFF00FFFFFF00FFFFFF00FFFFFF00FFFF
      FF00FFFFFF00FFFFFF00FFFFFF00FFFFFF00FFFFFF00FFFFFF00FFFFFF00FFFF
      FF00FFFFFF00FFFFFF00FFFFFF00FFFFFF00F8F8F800E0E0E000ACACAC009EA0
      A10067676700616161009D9D9D00DDDDDD00FAFAFA00FFFFFF00FFFFFF00FFFF
      FF00FFFFFF00FFFFFF00FFFFFF00FFFFFF00FFFFFF00FFFFFF00FFFFFF00FFFF
      FF00FFFFFF00FFFFFF00FEFEFE00E7E7E700C7C7C700A6A6A600000000000000
      0000000000000000000000000000000000000000000000000000000000000000
      0000000000000000000000000000000000000000000000000000000000000000
      0000000000000000000000000000000000000000000000000000000000000000
      0000000000000000000000000000000000000000000000000000000000000000
      0000000000000000000000000000000000000000000000000000000000000000
      000000000000000000000000000000000000CFDEE100B5B6B600E9E9E900FFFF
      FF00FFFFFF00FFFFFF00FFFFFF00FFFFFF00FFFFFF00FFFFFF00FFFFFF00FFFF
      FF00FFFFFF00FFFFFF00FFFFFF00FFFFFF00FFFFFF00FFFFFF00FFFFFF00FFFF
      FF00F8F8F800E0E0E000ACACAC009EA0A10067676700616161009D9D9D00DDDD
      DD00FBFBFB00FFFFFF00FFFFFF00FFFFFF00FFFFFF00FFFFFF00FFFFFF00FFFF
      FF00FFFFFF00FFFFFF00FFFFFF00FFFFFF00FFFFFF00FFFFFF00FEFEFE00E6E6
      E600C7C7C700A5A5A50000000000000000000000000000000000000000000000
      0000000000000000000000000000000000000000000000000000000000000000
      0000000000000000000000000000000000000000000000000000000000000000
      0000000000000000000000000000000000000000000000000000000000000000
      0000000000000000000000000000000000000000000000000000000000000000
      0000000000000000000000000000000000000000000000000000000000000000
      0000CFDEE100B3B5B500E8E8E800FFFFFF00FFFFFF00FFFFFF00FFFFFF00FFFF
      FF00FFFFFF00FFFFFF00FFFFFF00FFFFFF00FFFFFF00FFFFFF00FFFFFF00FFFF
      FF00FFFFFF00FFFFFF00FFFFFF00FFFFFF00F9F9F900E0E0E000ABABAB009EA0
      A10067676700616161009D9D9D00DFDFDF00FDFDFD00FFFFFF00FFFFFF00FFFF
      FF00FFFFFF00FFFFFF00FFFFFF00FFFFFF00FFFFFF00FFFFFF00FFFFFF00FFFF
      FF00FFFFFF00FFFFFF00FFFFFF00E7E7E700C7C7C700A4A4A400000000000000
      0000000000000000000000000000000000000000000000000000000000000000
      0000000000000000000000000000000000000000000000000000000000000000
      0000000000000000000000000000000000000000000000000000000000000000
      0000000000000000000000000000000000000000000000000000000000000000
      0000000000000000000000000000000000000000000000000000000000000000
      000000000000000000000000000000000000D0DFE200BEC0C000EDEDED00FFFF
      FF00FFFFFF00FFFFFF00FFFFFF00FFFFFF00FFFFFF00FFFFFF00FFFFFF00FFFF
      FF00FFFFFF00FFFFFF00FFFFFF00FFFFFF00FFFFFF00FFFFFF00FFFFFF00FFFF
      FF00FEFEFE00E8E8E800B1B1B1009C9E9F006767670063636300A2A2A200E1E1
      E100F5F5F500F4F4F400F3F3F300F3F3F300F3F3F300F3F3F300F3F3F300F3F3
      F300F3F3F300F3F3F300F3F3F300F3F3F300F1F1F100F8F8F800FFFFFF00EFEF
      EF00CBCBCB00A5A5A50000000000000000000000000000000000000000000000
      0000000000000000000000000000000000000000000000000000000000000000
      0000000000000000000000000000000000000000000000000000000000000000
      0000000000000000000000000000000000000000000000000000000000000000
      0000000000000000000000000000000000000000000000000000000000000000
      0000000000000000000000000000000000000000000000000000000000000000
      0000D5E5E800D1D6D700FBFBFB00FFFFFF00FFFFFF00FFFFFF00FFFFFF00FFFF
      FF00FFFFFF00FFFFFF00FFFFFF00FFFFFF00FFFFFF00FFFFFF00FFFFFF00FFFF
      FF00FFFFFF00FFFFFF00FFFFFF00FFFFFF00FFFFFF00EFEFEF00B5B5B5009B9D
      9E00626262005D5D5D009A9A9A00CACACA00CFCFCF00CBCBCB00CACACA00CACA
      CA00CACACA00CACACA00CACACA00CACACA00CACACA00CACACA00CACACA00CACA
      CA00C9C9C900CECECE00E0E0E000DFDFDF00C6C6C600A3A3A300000000000000
      0000000000000000000000000000000000000000000000000000000000000000
      0000000000000000000000000000000000000000000000000000000000000000
      0000000000000000000000000000000000000000000000000000000000000000
      0000000000000000000000000000000000000000000000000000000000000000
      0000000000000000000000000000000000000000000000000000000000000000
      000000000000000000000000000000000000D7E8EB00D5E1E300F0F2F200FFFF
      FF00FFFFFF00FFFFFF00FFFFFF00FFFFFF00FFFFFF00FFFFFF00FFFFFF00FFFF
      FF00FFFFFF00FFFFFF00FFFFFF00FFFFFF00FFFFFF00FFFFFF00FFFFFF00FFFF
      FF00FFFFFF00EAEAEA00A3A4A500A9ACAC006B6B6B004E4E4E00737373009191
      9100909090008E8E8E008E8E8E008E8E8E008E8E8E008E8E8E008E8E8E008E8E
      8E008E8E8E008E8E8E008E8E8E008E8E8E008E8E8E008D8D8D00949494009D9D
      9D00A8A7A8009898980000000000000000000000000000000000000000000000
      0000000000000000000000000000000000000000000000000000000000000000
      0000000000000000000000000000000000000000000000000000000000000000
      0000000000000000000000000000000000000000000000000000000000000000
      0000000000000000000000000000000000000000000000000000000000000000
      0000000000000000000000000000000000000000000000000000000000000000
      000000000000D8E8EB00D9E6E800E8EEEF00F2F4F400F3F4F400F2F4F400F2F4
      F400F2F4F400F2F4F400F2F4F400F2F4F400F2F4F400F2F4F400F2F4F400F2F4
      F400F1F3F400F1F3F400F1F3F400F3F5F600E9ECED00D2D8D900C3D0D200C3CA
      CB009C9C9C00696969005F5F5F006A6A6A006D6D6D006C6C6C006C6C6C006C6C
      6C006C6C6C006C6C6C006C6C6C006C6C6C006C6C6C006D6D6D006D6D6D006D6D
      6D006D6D6D006D6D6D0068686800717171009190910088888800000000000000
      0000000000000000000000000000000000000000000000000000000000000000
      0000000000000000000000000000000000000000000000000000000000000000
      0000000000000000000000000000000000000000000000000000000000000000
      0000000000000000000000000000000000000000000000000000000000000000
      0000000000000000000000000000000000000000000000000000000000000000
      000000000000000000000000000000000000000000000000000000000000D8E8
      EB00DAE9EC00DAE9EC00DBEBED00DBEAED00DBEAED00DBEAED00DBEAED00DBEA
      ED00DBEAED00DBEAED00DBEAED00DBEBED00DAE9ED00D9E9ED00D9E9ED00DBEB
      ED00D7E6EA00D2E3E60000000000D3E1E300D3D7D700BCBDBD00989898008E8E
      8E008F8F8F009090900090909000909090009090900090909000909090009090
      90009090900091919100919191009191910091919100909090008F8F8F009B9B
      9B00A5A6A600898B8D0000000000000000000000000000000000000000000000
      0000000000000000000000000000000000000000000000000000000000000000
      0000000000000000000000000000000000000000000000000000000000000000
      0000000000000000000000000000000000000000000000000000000000000000
      0000000000000000000000000000000000000000000000000000000000000000
      0000000000000000000000000000000000000000000000000000000000000000
      0000424D3E000000000000003E000000280000005C0000001700000001000100
      00000000140100000000000000000000000000000000000000000000FFFFFF00
      0000010000000000000000000000000000000000000000000000000000000000
      0000000000000000000000000000000000000000000000000000000000000000
      0000000000000000000000000000000000000000000000000000000000000000
      0000000000000000000000000000000000000000000000000000000000000000
      0000000000000000000000000000000000000000000000000000000000000000
      0000000000000000000000000000000000000000000000000000000000000000
      0000000000000000000000000000000000000000000000000000000000000000
      0000000000000000000000000000000000000000000000000000000080000000
      0000000000000000E00002000000000000000000000000000000000000000000
      00000000000000000000}
  end
end