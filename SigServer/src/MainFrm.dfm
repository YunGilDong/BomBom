object MainF: TMainF
  Left = 0
  Top = 0
  Caption = 'MainF'
  ClientHeight = 201
  ClientWidth = 447
  Color = clBtnFace
  Font.Charset = DEFAULT_CHARSET
  Font.Color = clWindowText
  Font.Height = -11
  Font.Name = 'Tahoma'
  Font.Style = []
  OldCreateOrder = False
  OnShow = FormShow
  PixelsPerInch = 96
  TextHeight = 13
  object Edit1: TEdit
    Left = 32
    Top = 24
    Width = 65
    Height = 21
    TabOrder = 0
    Text = 'Edit1'
  end
  object Edit2: TEdit
    Left = 32
    Top = 51
    Width = 65
    Height = 21
    TabOrder = 1
    Text = 'Edit1'
  end
  object Edit3: TEdit
    Left = 32
    Top = 78
    Width = 65
    Height = 21
    TabOrder = 2
    Text = 'Edit1'
  end
  object Edit4: TEdit
    Left = 32
    Top = 105
    Width = 65
    Height = 21
    TabOrder = 3
    Text = 'Edit1'
  end
  object Edit5: TEdit
    Left = 32
    Top = 132
    Width = 65
    Height = 21
    TabOrder = 4
    Text = 'Edit1'
  end
  object tmClock: TTimer
    Enabled = False
    OnTimer = tmClockTimer
    Left = 403
    Top = 95
  end
end
