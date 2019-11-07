object ConfigForm: TConfigForm
  Left = 187
  Top = 131
  BorderStyle = bsDialog
  Caption = 'Buffered Pulse Width Measurement - Configuration'
  ClientHeight = 498
  ClientWidth = 674
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
    Top = 16
    Width = 45
    Height = 17
    AutoSize = False
    BiDiMode = bdRightToLeft
    Caption = 'Device:'
    ParentBiDiMode = False
  end
  object cmbDevice: TComboBox
    Left = 88
    Top = 16
    Width = 265
    Height = 21
    Style = csDropDownList
    ItemHeight = 13
    TabOrder = 0
    OnChange = cmbDeviceChange
  end
  object btnOk: TButton
    Left = 399
    Top = 447
    Width = 81
    Height = 25
    Caption = 'OK'
    TabOrder = 1
    OnClick = btnOkClick
  end
  object btnCancel: TButton
    Left = 533
    Top = 448
    Width = 81
    Height = 25
    Caption = 'Cancel'
    TabOrder = 2
    OnClick = btnCancelClick
  end
  object radProfile: TRadioButton
    Left = 32
    Top = 56
    Width = 113
    Height = 17
    Caption = 'Load Profile'
    TabOrder = 3
    OnClick = radioBtnClick
  end
  object radManual: TRadioButton
    Left = 176
    Top = 56
    Width = 113
    Height = 17
    Caption = 'Manual Configure'
    Checked = True
    TabOrder = 4
    TabStop = True
    OnClick = radioBtnClick
  end
  object GroupBox3: TGroupBox
    Left = 24
    Top = 88
    Width = 361
    Height = 57
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
    object txtProfilePath: TEdit
      Left = 64
      Top = 20
      Width = 217
      Height = 21
      TabOrder = 0
    end
    object btnBrowse: TButton
      Left = 296
      Top = 16
      Width = 51
      Height = 25
      Caption = 'Browse'
      TabOrder = 1
      OnClick = btnBrowseClick
    end
  end
  object GroupBox5: TGroupBox
    Left = 24
    Top = 160
    Width = 625
    Height = 265
    Caption = 'Manual configure the parameters'
    TabOrder = 6
    object GroupBox1: TGroupBox
      Left = 16
      Top = 32
      Width = 297
      Height = 217
      Caption = 'General Settings'
      TabOrder = 0
      object Label6: TLabel
        Left = 16
        Top = 96
        Width = 75
        Height = 13
        Caption = 'Section Length:'
      end
      object Label7: TLabel
        Left = 16
        Top = 136
        Width = 70
        Height = 13
        Caption = 'Section Count:'
      end
      object Label8: TLabel
        Left = 16
        Top = 168
        Width = 105
        Height = 13
        Caption = 'Sample Clock Source:'
      end
      object Label4: TLabel
        Left = 16
        Top = 40
        Width = 75
        Height = 13
        Caption = 'Channel Enable'
      end
      object txtSectionCount: TEdit
        Left = 104
        Top = 136
        Width = 161
        Height = 21
        TabOrder = 0
        Text = '0'
      end
      object cbxSampleClkSrc: TComboBox
        Left = 16
        Top = 184
        Width = 249
        Height = 21
        ItemHeight = 13
        TabOrder = 1
      end
      object txtSectionLength: TEdit
        Left = 104
        Top = 96
        Width = 161
        Height = 21
        TabOrder = 2
        Text = '1024'
      end
      object chkListBox: TCheckListBox
        Left = 104
        Top = 16
        Width = 161
        Height = 57
        OnClickCheck = checkBoxClick
        ItemHeight = 13
        TabOrder = 3
      end
    end
    object GroupBox2: TGroupBox
      Left = 328
      Top = 32
      Width = 281
      Height = 217
      Caption = 'Trigger Settings'
      TabOrder = 1
      object Label9: TLabel
        Left = 16
        Top = 32
        Width = 76
        Height = 13
        Caption = 'Trigger Sourrce:'
      end
      object Label10: TLabel
        Left = 16
        Top = 80
        Width = 69
        Height = 13
        Caption = 'Trigger Action:'
      end
      object Label11: TLabel
        Left = 16
        Top = 128
        Width = 64
        Height = 13
        Caption = 'Trigger Edge:'
      end
      object Label12: TLabel
        Left = 16
        Top = 176
        Width = 65
        Height = 13
        Caption = 'Trigger Level:'
      end
      object Label2: TLabel
        Left = 232
        Top = 176
        Width = 7
        Height = 13
        Caption = 'V'
      end
      object cbxTrgSource: TComboBox
        Left = 104
        Top = 32
        Width = 145
        Height = 21
        ItemHeight = 13
        TabOrder = 0
        OnChange = cbxTrgSourceChange
      end
      object cbxTrgAction: TComboBox
        Left = 104
        Top = 80
        Width = 145
        Height = 21
        ItemHeight = 13
        TabOrder = 1
      end
      object cbxTrgEdge: TComboBox
        Left = 104
        Top = 128
        Width = 145
        Height = 21
        ItemHeight = 13
        TabOrder = 2
      end
      object txtTrgLevel: TEdit
        Left = 104
        Top = 176
        Width = 121
        Height = 21
        TabOrder = 3
        Text = '3.0'
      end
    end
  end
end
