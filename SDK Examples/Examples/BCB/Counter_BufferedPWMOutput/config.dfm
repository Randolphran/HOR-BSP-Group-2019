object ConfigForm: TConfigForm
  Left = 367
  Top = 174
  BorderStyle = bsDialog
  Caption = 'Buffered PWM Output - Configuration'
  ClientHeight = 468
  ClientWidth = 692
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
    Top = 16
    Width = 37
    Height = 17
    AutoSize = False
    Caption = 'Device:'
  end
  object cmbDevice: TComboBox
    Left = 72
    Top = 16
    Width = 241
    Height = 21
    Style = csDropDownList
    ItemHeight = 13
    TabOrder = 0
    OnChange = cmbDeviceChange
  end
  object btnOk: TButton
    Left = 368
    Top = 416
    Width = 65
    Height = 25
    Caption = 'OK'
    TabOrder = 1
    OnClick = btnOkClick
  end
  object btnCancel: TButton
    Left = 520
    Top = 416
    Width = 65
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
    Left = 208
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
      Width = 209
      Height = 21
      TabOrder = 0
    end
    object btnBrowse: TButton
      Left = 296
      Top = 16
      Width = 49
      Height = 25
      Caption = 'Browse'
      TabOrder = 1
      OnClick = btnBrowseClick
    end
  end
  object GroupBox4: TGroupBox
    Left = 24
    Top = 160
    Width = 609
    Height = 241
    Caption = 'Manual configure the parameters'
    TabOrder = 6
    object GroupBox1: TGroupBox
      Left = 16
      Top = 24
      Width = 273
      Height = 193
      Caption = 'General Settings'
      TabOrder = 0
      object Label6: TLabel
        Left = 16
        Top = 104
        Width = 69
        Height = 13
        Caption = 'Interval Count:'
      end
      object Label7: TLabel
        Left = 16
        Top = 136
        Width = 105
        Height = 13
        Caption = 'Sample Clock Source:'
      end
      object Label2: TLabel
        Left = 16
        Top = 56
        Width = 75
        Height = 13
        Caption = 'Channel Enable'
      end
      object cbxSampleClkSrc: TComboBox
        Left = 16
        Top = 160
        Width = 233
        Height = 21
        ItemHeight = 13
        TabOrder = 0
      end
      object txtIntervalCount: TEdit
        Left = 104
        Top = 104
        Width = 145
        Height = 21
        TabOrder = 1
        Text = '1024'
      end
      object chkListBox: TCheckListBox
        Left = 104
        Top = 32
        Width = 145
        Height = 57
        OnClickCheck = checkBoxClick
        ItemHeight = 13
        TabOrder = 2
      end
    end
    object GroupBox2: TGroupBox
      Left = 320
      Top = 24
      Width = 273
      Height = 193
      Caption = 'Trigger Settings'
      TabOrder = 1
      object Label8: TLabel
        Left = 16
        Top = 32
        Width = 73
        Height = 13
        Caption = 'Trigger Source:'
      end
      object Label9: TLabel
        Left = 16
        Top = 72
        Width = 69
        Height = 13
        Caption = 'Trigger Action:'
      end
      object Label10: TLabel
        Left = 16
        Top = 112
        Width = 64
        Height = 13
        Caption = 'Trigger Edge:'
      end
      object Label11: TLabel
        Left = 16
        Top = 152
        Width = 65
        Height = 13
        Caption = 'Trigger Level:'
      end
      object Label12: TLabel
        Left = 232
        Top = 152
        Width = 7
        Height = 13
        Caption = 'V'
      end
      object cbxTrgSource: TComboBox
        Left = 96
        Top = 32
        Width = 153
        Height = 21
        ItemHeight = 13
        TabOrder = 0
        OnChange = cbxTrgSourceChange
      end
      object cbxTrgAction: TComboBox
        Left = 96
        Top = 72
        Width = 153
        Height = 21
        ItemHeight = 13
        TabOrder = 1
      end
      object cbxTrgEdge: TComboBox
        Left = 96
        Top = 112
        Width = 153
        Height = 21
        ItemHeight = 13
        TabOrder = 2
      end
      object txtTrgLevel: TEdit
        Left = 96
        Top = 152
        Width = 129
        Height = 21
        TabOrder = 3
        Text = '3.0'
      end
    end
  end
end
