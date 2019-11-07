object ConfigForm: TConfigForm
  Left = 271
  Top = 143
  BorderStyle = bsDialog
  Caption = 'Buffered Event Counter - Configuration'
  ClientHeight = 503
  ClientWidth = 652
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
    Left = 16
    Top = 8
    Width = 45
    Height = 17
    AutoSize = False
    Caption = 'Device:'
  end
  object cmbDevice: TComboBox
    Left = 64
    Top = 8
    Width = 234
    Height = 21
    Style = csDropDownList
    ItemHeight = 13
    TabOrder = 0
    OnChange = cmbDeviceChange
  end
  object btnOk: TButton
    Left = 327
    Top = 463
    Width = 81
    Height = 25
    Caption = 'OK'
    TabOrder = 1
    OnClick = btnOkClick
  end
  object btnCancel: TButton
    Left = 517
    Top = 464
    Width = 81
    Height = 25
    Caption = 'Cancel'
    TabOrder = 2
    OnClick = btnCancelClick
  end
  object radProfile: TRadioButton
    Left = 32
    Top = 48
    Width = 89
    Height = 17
    Caption = 'Load Profile'
    TabOrder = 3
    OnClick = radioBtnClick
  end
  object radManual: TRadioButton
    Left = 216
    Top = 48
    Width = 113
    Height = 17
    Caption = 'Manual Configure'
    Checked = True
    TabOrder = 4
    TabStop = True
    OnClick = radioBtnClick
  end
  object GroupBox3: TGroupBox
    Left = 25
    Top = 88
    Width = 392
    Height = 65
    Caption = 'Using Profile to configure the parameters'
    TabOrder = 5
    object Label3: TLabel
      Left = 16
      Top = 24
      Width = 37
      Height = 17
      AutoSize = False
      Caption = 'Profile:'
    end
    object btnBrowse: TButton
      Left = 325
      Top = 24
      Width = 51
      Height = 25
      Caption = 'Browse'
      TabOrder = 0
      OnClick = btnBrowseClick
    end
    object txtProfilePath: TEdit
      Left = 64
      Top = 24
      Width = 249
      Height = 21
      TabOrder = 1
    end
  end
  object GroupBox4: TGroupBox
    Left = 24
    Top = 168
    Width = 609
    Height = 273
    Caption = 'Manual configure the parameters'
    TabOrder = 6
    object GroupBox1: TGroupBox
      Left = 16
      Top = 24
      Width = 273
      Height = 233
      Caption = 'General Settings'
      TabOrder = 0
      object Label6: TLabel
        Left = 8
        Top = 112
        Width = 75
        Height = 13
        Caption = 'Section Length:'
      end
      object Label7: TLabel
        Left = 8
        Top = 144
        Width = 70
        Height = 13
        Caption = 'Section Count:'
      end
      object Label8: TLabel
        Left = 8
        Top = 176
        Width = 105
        Height = 13
        Caption = 'Sample Clock Source:'
      end
      object Label2: TLabel
        Left = 8
        Top = 48
        Width = 81
        Height = 17
        Caption = 'Channel Enable'
      end
      object txtSectionLength: TEdit
        Left = 96
        Top = 112
        Width = 153
        Height = 21
        TabOrder = 0
        Text = '1024'
      end
      object txtSectionCount: TEdit
        Left = 96
        Top = 144
        Width = 153
        Height = 21
        TabOrder = 1
        Text = '0'
      end
      object cbxSampleClkSrc: TComboBox
        Left = 8
        Top = 200
        Width = 241
        Height = 21
        ItemHeight = 13
        TabOrder = 2
      end
    end
    object GroupBox2: TGroupBox
      Left = 304
      Top = 24
      Width = 289
      Height = 233
      Caption = 'Trigger Settings'
      TabOrder = 1
      object Label9: TLabel
        Left = 8
        Top = 32
        Width = 73
        Height = 13
        Caption = 'Trigger Source:'
      end
      object Label10: TLabel
        Left = 8
        Top = 88
        Width = 69
        Height = 13
        Caption = 'Trigger Action:'
      end
      object Label11: TLabel
        Left = 8
        Top = 144
        Width = 64
        Height = 13
        Caption = 'Trigger Edge:'
      end
      object Label12: TLabel
        Left = 8
        Top = 192
        Width = 65
        Height = 13
        Caption = 'Trigger Level:'
      end
      object Label13: TLabel
        Left = 232
        Top = 192
        Width = 7
        Height = 13
        Caption = 'V'
      end
      object cbxTrgSource: TComboBox
        Left = 96
        Top = 32
        Width = 169
        Height = 21
        ItemHeight = 13
        TabOrder = 0
        OnChange = cbxTrgSourceChange
      end
      object cbxTrgAction: TComboBox
        Left = 96
        Top = 88
        Width = 169
        Height = 21
        ItemHeight = 13
        TabOrder = 1
      end
      object cbxTrgEdge: TComboBox
        Left = 96
        Top = 144
        Width = 169
        Height = 21
        ItemHeight = 13
        TabOrder = 2
      end
      object txtTrgLevel: TEdit
        Left = 96
        Top = 192
        Width = 121
        Height = 21
        TabOrder = 3
        Text = '3.0'
      end
    end
  end
  object chkListBox: TCheckListBox
    Left = 136
    Top = 224
    Width = 153
    Height = 57
    OnClickCheck = checkBoxClick
    ItemHeight = 13
    TabOrder = 7
  end
end
