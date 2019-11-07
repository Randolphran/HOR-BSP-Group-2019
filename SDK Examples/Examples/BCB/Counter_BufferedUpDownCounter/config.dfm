object ConfigForm: TConfigForm
  Left = 507
  Top = 111
  BorderStyle = bsDialog
  Caption = 'Buffered Up Down Counter - Configuration'
  ClientHeight = 536
  ClientWidth = 696
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
    Left = 24
    Top = 8
    Width = 45
    Height = 17
    AutoSize = False
    Caption = 'Device:'
  end
  object cmbDevice: TComboBox
    Left = 80
    Top = 8
    Width = 234
    Height = 21
    Style = csDropDownList
    ItemHeight = 13
    TabOrder = 0
    OnChange = cmbDeviceChange
  end
  object btnOk: TButton
    Left = 375
    Top = 487
    Width = 81
    Height = 25
    Caption = 'OK'
    TabOrder = 1
    OnClick = btnOkClick
  end
  object btnCancel: TButton
    Left = 549
    Top = 488
    Width = 81
    Height = 25
    Caption = 'Cancel'
    TabOrder = 2
    OnClick = btnCancelClick
  end
  object GroupBox3: TGroupBox
    Left = 24
    Top = 80
    Width = 377
    Height = 57
    Caption = 'Using Profile to configure the parameters'
    TabOrder = 3
    object Label3: TLabel
      Left = 8
      Top = 24
      Width = 37
      Height = 17
      AutoSize = False
      Caption = 'Profile:'
    end
    object btnBrowse: TButton
      Left = 304
      Top = 16
      Width = 51
      Height = 25
      Caption = 'Browse'
      TabOrder = 0
      OnClick = btnBrowseClick
    end
    object txtProfilePath: TEdit
      Left = 56
      Top = 20
      Width = 233
      Height = 21
      TabOrder = 1
    end
  end
  object radProfile: TRadioButton
    Left = 24
    Top = 48
    Width = 113
    Height = 17
    Caption = 'Load Profile'
    TabOrder = 4
    OnClick = radioBtnClick
  end
  object radManual: TRadioButton
    Left = 168
    Top = 48
    Width = 113
    Height = 17
    Caption = 'Manual Configure'
    Checked = True
    TabOrder = 5
    TabStop = True
    OnClick = radioBtnClick
  end
  object GroupBox5: TGroupBox
    Left = 24
    Top = 160
    Width = 649
    Height = 313
    Caption = 'Manual configure the parameters'
    TabOrder = 6
    object GroupBox1: TGroupBox
      Left = 16
      Top = 24
      Width = 289
      Height = 265
      Caption = 'General Settings'
      TabOrder = 0
      object Label6: TLabel
        Left = 16
        Top = 104
        Width = 75
        Height = 13
        Caption = 'Section Length:'
      end
      object Label7: TLabel
        Left = 16
        Top = 144
        Width = 70
        Height = 13
        Caption = 'Section Count:'
      end
      object Label8: TLabel
        Left = 16
        Top = 216
        Width = 105
        Height = 13
        Caption = 'Sample Clock Source:'
      end
      object Label2: TLabel
        Left = 16
        Top = 184
        Width = 72
        Height = 13
        Caption = 'Counting Type:'
      end
      object Label4: TLabel
        Left = 17
        Top = 48
        Width = 72
        Height = 13
        Caption = 'ChannelEnable'
      end
      object txtSectionLength: TEdit
        Left = 112
        Top = 104
        Width = 153
        Height = 21
        TabOrder = 0
        Text = '1024'
      end
      object txtSectionCount: TEdit
        Left = 112
        Top = 144
        Width = 153
        Height = 21
        TabOrder = 1
        Text = '0'
      end
      object cbxSampleClkSrc: TComboBox
        Left = 16
        Top = 232
        Width = 249
        Height = 21
        ItemHeight = 13
        TabOrder = 2
      end
      object cbxCountingType: TComboBox
        Left = 112
        Top = 184
        Width = 153
        Height = 21
        ItemHeight = 13
        TabOrder = 3
      end
    end
    object GroupBox2: TGroupBox
      Left = 320
      Top = 24
      Width = 305
      Height = 265
      Caption = 'Trigger Settings'
      TabOrder = 1
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
        Top = 200
        Width = 65
        Height = 13
        Caption = 'Trigger Level:'
      end
      object Label13: TLabel
        Left = 248
        Top = 200
        Width = 7
        Height = 13
        Caption = 'V'
      end
      object Label9: TLabel
        Left = 8
        Top = 32
        Width = 73
        Height = 13
        Caption = 'Trigger Source:'
      end
      object cbxTrgSource: TComboBox
        Left = 96
        Top = 32
        Width = 177
        Height = 21
        ItemHeight = 13
        TabOrder = 0
        OnChange = cbxTrgSourceChange
      end
      object cbxTrgAction: TComboBox
        Left = 96
        Top = 88
        Width = 177
        Height = 21
        ItemHeight = 13
        TabOrder = 1
      end
      object cbxTrgEdge: TComboBox
        Left = 96
        Top = 144
        Width = 177
        Height = 21
        ItemHeight = 13
        TabOrder = 2
      end
      object txtTrgLevel: TEdit
        Left = 96
        Top = 200
        Width = 137
        Height = 21
        TabOrder = 3
        Text = '3.0'
      end
    end
  end
  object chkListBox: TCheckListBox
    Left = 152
    Top = 208
    Width = 153
    Height = 57
    OnClickCheck = checkBoxClick
    ItemHeight = 13
    TabOrder = 7
  end
end
