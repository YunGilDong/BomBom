object MecaBackF: TMecaBackF
  Left = 0
  Top = 0
  Caption = 'MecaBackF'
  ClientHeight = 641
  ClientWidth = 954
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
  object Label1: TLabel
    Left = 208
    Top = 295
    Width = 44
    Height = 13
    Caption = #51333#47785#53076#46300
  end
  object KHOpenAPI: TKHOpenAPI
    Left = 0
    Top = 542
    Width = 185
    Height = 17
    TabOrder = 0
    OnReceiveTrData = KHOpenAPIReceiveTrData
    OnReceiveChejanData = KHOpenAPIReceiveChejanData
    OnEventConnect = KHOpenAPIEventConnect
    ControlData = {020001001F130000C201000000000000}
  end
  object mmoUserInfo: TMemo
    Left = 0
    Top = 0
    Width = 161
    Height = 126
    TabOrder = 1
  end
  object btnReqStockInfo: TButton
    Left = 364
    Top = 288
    Width = 57
    Height = 25
    Caption = #50836#52397
    TabOrder = 2
    OnClick = btnReqStockInfoClick
  end
  object Button4: TButton
    Left = 208
    Top = 483
    Width = 57
    Height = 25
    Caption = #47588#49688
    TabOrder = 3
    OnClick = Button4Click
  end
  object btnReqAc: TButton
    Left = 897
    Top = 140
    Width = 57
    Height = 25
    Caption = #44228#51340#51092#44256
    TabOrder = 4
    OnClick = btnReqAcClick
  end
  object statusBar: TStatusBar
    Left = 0
    Top = 623
    Width = 954
    Height = 18
    Panels = <
      item
        Width = 150
      end
      item
        Width = 50
      end
      item
        Width = 50
      end
      item
        Width = 50
      end>
    SizeGrip = False
  end
  object mmoAccount: TMemo
    Left = 793
    Top = 8
    Width = 161
    Height = 126
    TabOrder = 6
  end
  object GroupBox1: TGroupBox
    Left = 785
    Top = 192
    Width = 169
    Height = 217
    Caption = #51452#47928
    TabOrder = 7
    object laOrder1: TLabel
      Left = 16
      Top = 22
      Width = 44
      Height = 13
      Caption = #51333#47785#53076#46300
    end
    object laOrder2: TLabel
      Left = 16
      Top = 48
      Width = 44
      Height = 13
      Caption = #47588#47588#44396#48516
    end
    object laOrder3: TLabel
      Left = 16
      Top = 75
      Width = 44
      Height = 13
      Caption = #51452#47928#49688#47049
    end
    object laOrder4: TLabel
      Left = 16
      Top = 106
      Width = 44
      Height = 13
      Caption = #51452#47928#44032#44201
    end
    object laOrder5: TLabel
      Left = 16
      Top = 131
      Width = 44
      Height = 13
      Caption = #44144#47000#44396#48516
    end
    object laOrder6: TLabel
      Left = 16
      Top = 160
      Width = 44
      Height = 13
      Caption = #51452#47928#48264#54840
    end
    object edOrder1: TEdit
      Left = 69
      Top = 17
      Width = 97
      Height = 21
      TabOrder = 0
      OnKeyPress = edOrder1KeyPress
    end
    object edOrder3: TEdit
      Left = 69
      Top = 71
      Width = 97
      Height = 21
      TabOrder = 1
      OnKeyPress = edOrder1KeyPress
    end
    object edOrder4: TEdit
      Left = 69
      Top = 98
      Width = 97
      Height = 21
      TabOrder = 2
      OnKeyPress = edOrder1KeyPress
    end
    object edOrder5: TEdit
      Left = 69
      Top = 125
      Width = 97
      Height = 21
      Enabled = False
      TabOrder = 3
      Text = #51648#51221#44032
    end
    object Edit6: TEdit
      Left = 69
      Top = 152
      Width = 97
      Height = 21
      TabOrder = 4
    end
    object Button1: TButton
      Left = 64
      Top = 189
      Width = 57
      Height = 25
      Caption = #51452#47928
      TabOrder = 5
      OnClick = Button1Click
    end
    object cbOrderType: TComboBox
      Left = 69
      Top = 44
      Width = 96
      Height = 22
      Style = csOwnerDrawFixed
      ItemIndex = 0
      TabOrder = 6
      Text = #49888#44508#47588#49688
      Items.Strings = (
        #49888#44508#47588#49688
        #49888#44508#47588#46020
        #47588#49688#52712#49548
        #47588#46020#52712#49548
        #47588#49688#51221#51221
        #47588#46020#51221#51221)
    end
  end
  object mmoOrderLog: TMemo
    Left = 208
    Top = 16
    Width = 217
    Height = 225
    Lines.Strings = (
      'mmoOrderLog')
    TabOrder = 8
  end
  object mmoCheJanLog: TMemo
    Left = 456
    Top = 16
    Width = 217
    Height = 225
    Lines.Strings = (
      'mmoOrderLog')
    TabOrder = 9
  end
  object mmoStackInfo: TMemo
    Left = 208
    Top = 317
    Width = 409
    Height = 111
    Lines.Strings = (
      '<'#51452#49885#44592#48376#51221#48372'>')
    TabOrder = 10
  end
  object edReqStockInfo: TEdit
    Left = 261
    Top = 290
    Width = 97
    Height = 21
    TabOrder = 11
    OnKeyPress = edOrder1KeyPress
  end
end
