uses graph, crt, dos;
Const BORDER_COLOR=Black;{梥� �࠭�� ��࡫��}
    BG_COLOR =DarkGray;{梥� 䮭�}
	FG_COLOR=Black;{梥� �����ᥩ}
	FACE_COLOR=LightGray;{梥� ��࡫��}
	MARG_COLOR=White;{梥� ���� � ��ࠬ� � ���堬�}
	HOURHAND_COLOR=Blue;{梥� �ᮢ�� ��५��}
	MINHAND_COLOR=Green;{梥� ����⭮� ��५��}
	SECHAND_COLOR=Black;{梥� ᥪ㭤��� ��५��}

type
	TPoint = record {�窠}
		x, y: Integer; {���न����}
	end;
	TTime=record {�६�}
		ti_hour, ti_min, {���, ������,}
		ti_sec, ti_hund {ᥪ㭤�, �����ᥪ㭤�}
		: Word;
	end;
	
(*
��楤�� Polar2Dec() ��ॢ���� ���न���� �窨 �� ����୮� ��⥬� � �����⮢�.
��窠 �������� 㣫�� Angle � ����ﭨ�� �� 業�� Len � ����୮� ��⥬�,
� ���न��⠬� (P.x;P.y) � �����⮢��.
����� ����୮� ��⥬� �������� ���न��⠬� (P0.x;P0.y).
��ࠬ����:
Ang - 㣮� � ����୮� ��⥬�,
Len - ����ﭨ� �� 業�� � ����୮� ��⥬�, 
P0 - 業�� ����୮� ��⥬� � �����⮢��, 
P - ���न���� �窨 � �����⮢�� ��⥬�.
������� ��६����:
����������.
*)
procedure Polar2Dec(Ang, Len: Real;P0:TPoint; var P: TPoint);
begin
	Ang := Ang - 90; { Correlation for our coord system }
	P.x := Round(P0.x + Len * cos(Ang * Pi / 180));
	P.y := Round(P0.y + Len * sin(Ang * Pi / 180));
end;

(*
��楤�� DrawFace() ���� ��࡫�� � 業�஬ � �窥 P0.
��ࠬ����:
P0 - 業�� ��࡫��.
������� ��६����:
i - ��६�����-���稪 ��� �ᮢ���� ��� �ᮢ � ���客 �����; 
P - 業�� ����-��,
P1,P2 - ���न���� ���殢 ����; 
num - ��ப� � ��ன ��� �뢮��;
OldStyleLine,OldStyleText,
OldStyleFill, OldColor - ������� ��। ��楤�ன �⨫� � 梥�.
*)
procedure DrawFace(P0:TPoint);
var i:byte; P,P1,p2:TPoint; num:string;
    OldStyleLine:LineSettingsType; OldStyleText:TextSettingsType;
    OldStyleFill:FillSettingsType; OldColor:integer;
begin
	GetLineSettings(OldStyleLine); GetTextSettings(OldStyleText);
	GetFillSettings(OldStyleFill); OldColor:=GetColor;
	
	SetColor(BORDER_COLOR);
	SetLineStyle(0,0,3);
	SetFillStyle(SolidFill,MARG_COLOR);
	FillEllipse(P0.x,P0.y,P0.y-30,P0.y-30);
	
	SetColor(BORDER_COLOR);
	SetLineStyle(0,0,2);
	SetFillStyle(SolidFill,FACE_COLOR);
	FillEllipse(P0.x,P0.y,P0.y-70,P0.y-70);
	
	SetColor(BG_COLOR);
	SetFillStyle(HatchFill,BG_COLOR);
	FillEllipse(P0.x, P0.y,3 , 3);
	
	SetTextStyle(GothicFont,HorizDir,4);
	SetTextJustify(CenterText,CenterText);
	SetLineStyle(0,0,2);
	SetColor(FG_COLOR);
	
	for i := 5 to 64 do	begin
		if i mod 5 =0 then begin
		Polar2DEc(i*6, P0.y - 50,P0, P);
		str(i div 5,num);
		OutTextXY(Round(P.x),Round(P.y)-7,num);
		end else begin
		Polar2Dec(i * 6, P0.y - 70,p0, P1);
		Polar2Dec(i * 6, P0.y-60,p0, P2);
		Line(p1.x,p1.y,p2.x,p2.y);
		end;
	end;
	
	with oldStyleLine do
	   setLineStyle(LineStyle,Pattern,Thickness);
	with oldStyleText do begin
	   setTextStyle(Font,Direction,CharSize);
	   setTExtJustify(horiz,vert);
	end;
	with oldStyleFill do
	   setFillStyle(Pattern,Color);
	setColor(OldColor);
end;

(*
��楤�� DrawHands() ���� ��५�� �ᮢ � 業�஬ ��࡫�� � �窥 P0,
��� �६��� CurrTime, 梥⠬�:
hour_color - ��� �ᮢ�� ��५��,
min_color - ��� ����⭮� ��५��,
sec_color - ��� ᥪ㭤��� ��५��.
��ࠬ����:
P0 - 業�� ��࡫��,
CurrTime - ⥪�饥 �६�,
hour_color - 梥� �ᮢ�� ��५��,
min_color - 梥� ����⭮� ��५��,
sec_color - 梥� ᥪ㭤��� ��५��.
������� ��६����:
P1,P2 - ���न���� ���殢 ᥪ㭤��� ��५��,
P3,P4 - ���न���� ���殢 ����⭮� ��५��,
P5,P6 - ���न���� ���殢 �ᮢ�� ��५��,
OldStyleLine, OldColor - ������� ��। ��楤�ன �⨫� � 梥�.
*)
Procedure DrawHands(P0:TPoint;CurrTime:TTime;hour_color,min_color,sec_color:word);
var P1,p2,p3,p4,p5,p6:TPoint;
OldStyleLine:LineSettingsType; oldColor:integer;
begin

	GetLineSettings(OldStyleLine); OldColor:=GetColor;
	SetLineStyle(0,0,3);
	{ Second arrow }
	Polar2Dec((CurrTime.ti_sec + CurrTime.ti_hund/100) * 6, p0.y - 72,p0, P1);
	Polar2Dec((CurrTime.ti_sec + CurrTime.ti_hund/100) * 6, 5,p0, P2);

	{ Minute arrow }
	Polar2Dec((CurrTime.ti_min + CurrTime.ti_sec/60) * 6, p0.y - 120,p0, P3);
	Polar2Dec((CurrTime.ti_min + CurrTime.ti_sec/60) * 6, 5,p0, P4);

	{ Hour arrow }
	Polar2Dec((CurrTime.ti_hour + CurrTime.ti_min/60) * 30, p0.y - 150,p0, P5);
	Polar2Dec((CurrTime.ti_hour + CurrTime.ti_min/60) * 30, 5,p0, P6);

	{ Draw }
	SetColor(sec_color);
	SetColor(sec_color);
	Line(P2.x, P2.y, P1.x, P1.y);

	SetColor(min_color);
	Line(P4.x, P4.y, P3.x, P3.y);

	SetColor(hour_color);
	Line(P6.x, P6.y, P5.x, P5.y);
	
	with oldStyleLine do
	   setLineStyle(LineStyle,Pattern,Thickness);
	SetColor(oldColor);
end;

(*
��楤�� Initialize() ��⠭�������� ����᪨� ०�� 
� ��室�� ��� Pcenter - 業�� ��࠭�.
��ࠬ����:
Pcenter - ���न���� 業�� ��࠭�.
������� ��६����:
GraphDriver,GraphMode - ��⠭��������� ����᪨� �ࠩ��� � ����᪨� ०��,
gr_code - ��� �訡�� ���樠����樨 ����᪮�� ०���.
*)
function Initialize(var Pcenter:TPoint):boolean;
var GraphDriver,GraphMode,gr_code:integer;
begin
	GraphDriver:=DETECT;
	InitGraph(GraphDriver, GraphMode, '');
	gr_code:=GraphResult;
	if gr_code=grOK then begin
		ClearDevice;
		SetFillStyle(SolidFill,BG_COLOR);
		floodfill(0,0,BG_COLOR);
		Pcenter.x := GetMaxX div 2;
		PCenter.y := GetMaxY div 2;
		Initialize:=true;
	end else begin
		WriteLn('�訡�� ���樠����樨 ����᪮�� ०��� #',gr_code);
		Initialize:=false;
	end;
end;

(*
�ணࠬ�� - ��������� ���.
��६����:
Pcenter - ���न���� 業�� ��࠭�,
CurrTime,DrawTime - ⥪�饥 �६� � �६� ��᫥����� ����ᮢ뢠��� ��५��,
Redraw - 㪠�뢠��, �㦭� �� ����ᮢ��� ��५�� (true - �㦭�, false - ���),
ok - 䫠� ������⢨� �訡�� (1 - ��� �訡��).
*)
var ok:boolean;
	Pcenter:TPoint;
	Redraw:boolean;
	CurrTime,DrawTime:TTime;
begin
	ok:=Initialize(Pcenter);

	if ok then begin
		SetTextStyle(GothicFont,HorizDir,4);
		SetTextJustify(CenterText,CenterText);
		SetColor(FG_COLOR);
		OutTextXY(Pcenter.x,7, 'Press any key to exit');
		OutTextXY(Pcenter.x,GetMaxY-21, 'Press any key to exit');

		DrawFace(Pcenter);

		GetTime(DrawTime.ti_hour, DrawTime.ti_min, DrawTime.ti_sec, DrawTime.ti_hund);
		DrawHands(Pcenter,DrawTime,HOURHAND_COLOR,MINHAND_COLOR,SECHAND_COLOR);
		Redraw:=false;

		while not keypressed do begin
			if Redraw then begin
				{ Erase }
				DrawHands(Pcenter,DrawTime,FACE_COLOR,FACE_COLOR,FACE_COLOR);

				GetTime(DrawTime.ti_hour, DrawTime.ti_min, DrawTime.ti_sec, DrawTime.ti_hund);
				DrawHands(Pcenter,DrawTime,HOURHAND_COLOR,MINHAND_COLOR,SECHAND_COLOR);

				Redraw:=False;
			end else begin
				GetTime(CurrTime.ti_hour, CurrTime.ti_min, CurrTime.ti_sec, CurrTime.ti_hund);
				Redraw:=((CurrTime.ti_hour-DrawTime.ti_hour)<>0) or((CurrTime.ti_min-DrawTime.ti_min)<>0)
						   or ((CurrTime.ti_sec-DrawTime.ti_sec)<>0)
							 or(abs(CurrTime.ti_hund- DrawTime.ti_hund)>4);
			end;
		end;
		CloseGraph;
	end else WriteLn('�ணࠬ�� ��ࢠ��!');
end.
