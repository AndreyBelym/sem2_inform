uses graph, crt, dos;
Const BORDER_COLOR=Black;{цвет границ циферблата}
    BG_COLOR =DarkGray;{цвет фона}
	FG_COLOR=Black;{цвет надписей}
	FACE_COLOR=LightGray;{цвет циферблата}
	MARG_COLOR=White;{цвет поля с цифрами и штрихами}
	HOURHAND_COLOR=Blue;{цвет часовой стрелки}
	MINHAND_COLOR=Green;{цвет минутной стрелки}
	SECHAND_COLOR=Black;{цвет секундной стрелки}

type
	TPoint = record {точка}
		x, y: Integer; {координаты}
	end;
	TTime=record {время}
		ti_hour, ti_min, {часы, минуты,}
		ti_sec, ti_hund {секунды, миллисекунды}
		: Word;
	end;
	
(*
Процедура Polar2Dec() переводит координаты точки из полярной системы в Декартову.
Точка задается углом Angle и расстоянием от центра Len в полярной системе,
и координатами (P.x;P.y) в Декартовой.
Центр полярной системы задается координатами (P0.x;P0.y).
Параметры:
Ang - угол в полярной системе,
Len - расстояние от центра в полярной системе, 
P0 - центр полярной системы в Декартовой, 
P - координаты точки в Декартовой системе.
Локальные переменные:
отсутствуют.
*)
procedure Polar2Dec(Ang, Len: Real;P0:TPoint; var P: TPoint);
begin
	Ang := Ang - 90; { Correlation for our coord system }
	P.x := Round(P0.x + Len * cos(Ang * Pi / 180));
	P.y := Round(P0.y + Len * sin(Ang * Pi / 180));
end;

(*
Процедура DrawFace() рисует циферблат с центром в точке P0.
Параметры:
P0 - центр циферблата.
Локальные переменные:
i - переменная-счетчик для рисования цифр часов и штрихов минут; 
P - центр цифры-часа,
P1,P2 - координаты концов штриха; 
num - строка с цифрой для вывода;
OldStyleLine,OldStyleText,
OldStyleFill, OldColor - заданные перед процедурой стили и цвета.
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
Процедура DrawHands() рисует стрелки часов с центром циферблата в точке P0,
для времени CurrTime, цветами:
hour_color - для часовой стрелки,
min_color - для минутной стрелки,
sec_color - для секундной стрелки.
Параметры:
P0 - центр циферблата,
CurrTime - текущее время,
hour_color - цвет часовой стрелки,
min_color - цвет минутной стрелки,
sec_color - цвет секундной стрелки.
Локальные переменные:
P1,P2 - координаты концов секундной стрелки,
P3,P4 - координаты концов минутной стрелки,
P5,P6 - координаты концов часовой стрелки,
OldStyleLine, OldColor - заданные перед процедурой стили и цвета.
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
Процедура Initialize() устанавливает графический режим 
и находит точку Pcenter - центр экрана.
Параметры:
Pcenter - координаты центра экрана.
Локальные переменные:
GraphDriver,GraphMode - устанавливаемые графический драйвер и графический режим,
gr_code - код ошибки инициализации графического режима.
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
		WriteLn('Ошибка инициализации графического режима #',gr_code);
		Initialize:=false;
	end;
end;

(*
Программа - аналоговые часы.
Переменные:
Pcenter - координаты центра экрана,
CurrTime,DrawTime - текущее время и время последнего перерисовывания стрелок,
Redraw - указывает, нужно ли перерисовать стрелки (true - нужно, false - нет),
ok - флаг отсутствия ошибки (1 - нет ошибки).
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
	end else WriteLn('Программа прервана!');
end.
