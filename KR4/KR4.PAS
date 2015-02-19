Program FreqDict;
CONST  WordLen = 31;
TYPE  TextWord = string[WordLen];
    Node= RECORD
            key: TextWord;
            count:longint;
            left, right: LongInt
         END;
    TreeFile=file of Node;
(*+++++++ПРОЦЕДУРЫ И ФУНКЦИИ+++++++*)
    
	(*
	Функция GetReqResult позволяет получить ответ "да" или "нет" от пользователя.
	Возвращает true в случае согласия пользователя, false - в случае несогласия.
	Параметры:
	отсутствуют.
	Локальные переменные:
	answer - текущий ответ пользователя.
	*)
	function GetReqReslt:boolean;
	var answer:char;
	begin
		ReadLn(answer);
		while (UpCase(answer)<>'Y')
			   and(UpCase(answer)<>'N') do begin
			WriteLn('Неправильный ответ! Допустимо:',#13#10,'Y - да; N - нет.');
			ReadLn(answer);
		end;
		GetReqReslt:=UpCase(answer)='Y';
	end;
	(*
	Функция IsLetter проверяет, является ли символ ch буквой.
	Если да, возвращает true, иначе - false.
	Параметры:
	ch - символ для проверки.
	Локальные переменные:
	отсутствуют.
	*)
	function IsLetter(ch:char):boolean;
    begin
         if ('A'<=ch) and (ch<='Z') or
            ('a'<=ch) and (ch<='z') or
            ('А'<=ch) and (ch<='п') or
            ('р'<=ch) and (ch<='ё')
               then IsLetter:=true
               else IsLetter:=false;
    end;
	
	(*
	Функция IsInWordSymbol проверяет, является ли символ ch допустимым для использования внутри слова.
	Если да, возвращает true, иначе - false.
	Параметры:
	ch - символ для проверки.
	Локальные переменные:
	отсутствуют.
	*)
    function IsInWordSymbol(ch:char):boolean;
    begin
         if ('0'<=ch) and (ch<='9')
            or (ch='''')  or (ch='-') or (ch='_')
                then IsInWordSymbol:=true
                else IsInWordSymbol:=false;
    end;

	(*
	Функция cap возвращает заглавную букву,соответствующей строчной букве ch.
	Если ch уже заглавная буква или вообще не буква, то возвращается значение  ch.
	Параметры:
	ch - символ для конвертации.
	Локальные переменные:
	отсутствуют.
	*)
    function cap(const ch:char):char;
    begin
        case ch of
         'a'..'z':cap:=UpCase(ch);
         'а'..'п':cap:=chr(ord(ch)-32);
         'р'..'я':cap:=chr(ord(ch)-80);
         'ё':cap:='Ё';
         else cap:=ch;
         end;
    end;
	
	(*
	Функция Compare сравнивает 2 строки a и b лекико графически.
	Если a<b, возвращается -1; если равны - возвращается 0;
		если больше - 1.
	Параметры:
	a,b - строки для сравнения.
	Локальные переменные:
	lena,lenb,len - длина строки a/строки b/наименьшая из них;
    i - переменная счетчик;
	*)
    function Compare(const a,b:string):shortint;
    var lena,lenb,len:byte;
       i:byte;
    begin
         lena:=length(a); lenb:=length(b);
         if lena > lenb then len:=lenb else len:=lena;
         i:=1;
         while (i<=len) and (a[i]=b[i]) do begin
               inc(i);
         end;

         if i>len then begin
            if lena=lenb then
               Compare:=0
            else if lena<lenb then
                    Compare:=-1
                  else Compare:=1;
         end else begin
             if a[i] <>'Ё' then
                if a[i]<b[i] then
                    Compare:=-1
                  else Compare:=1
             else
                 if b[i]<='Е' then
                    Compare:=1
                 else
                     Compare:=-1;
         end;

    end;
    
	(*
	Процедура PrintTree печатает дерево словоформ в файле Tree в текстовый файл outFile.
	Является "оберткой" к функции рекурсивной печати RecPrint.
	Параметры:
	outFile - текстовый файл для вывода.
	Tree - типизированный файл Tree с деревом словоформ.
    Локальные переменные:
	отсутствуют.
	*)
	PROCEDURE PrintTree(var Tree:TreeFile; var outFile:Text);
        
		(*
		Процедура RecPrint с помощью рекурсии печатает дерево словоформ
		в файле Tree (определенный глобально) в текстовый файл outFile (определенный глобально).
		Функция печатает элемент с номером Number: 
		сначала его левое поддерево, затем сам элемент, затем его правое поддерево/
		Параметры:
		Number - номер текущего элемента для печати.
		Локальные переменные:
		Current - текущий элемент для печати.
		*)
        procedure RecPrint(Number: Longint);
        var Current:Node;
        BEGIN
            seek(Tree,Number); Read(Tree,Current);

            IF  Current.left>0 Then begin
                RecPrint(Current.left);
            end;
            WriteLn( outFile, Current.key,' ',Current.count);
            IF  Current.right>0 Then begin
                RecPrint(Current.right);
        end;
        END {RecPrint};
        
    begin
         recprint(0);
    end {PrintTree};
	
	(*
	Процедура GetWord получает из файла inFile следующее слово, если оно есть.
	Иначе возвращается пустая строка.
	Параметры:
	inFile - файл с исходным текстом.
	Локальные переменные:
	temp - текущее извлеченное слово;
	i - длина извлеченного слова;
	ch - текущий извлеченный символ;
	founded - показывает, было ли найдено слово.
	*)
    function GetWord(var inFile:text):TextWord;
    var temp:TextWord;founded:boolean;ch:char;i:integer;
    begin
        temp:='';
        founded:=false;i:=0;
        while not (eof(inFile) or founded) do begin
            Read(inFile,ch);
            IF IsLetter(ch) THEN BEGIN
                founded:=true;inc(i); temp[i] := cap(ch);Read(inFile,ch);

                while not eof(inFile) and (i <= WordLen)
                      and (IsLetter(ch) or IsInWordSymbol(ch)) do begin
                    inc(i); temp[i] := cap(ch);
                    Read(inFile,ch);

                end;
                if  IsLetter(ch) or IsInWordSymbol(ch) then begin
                    inc(i); temp[i] := cap(ch);
                end;
                temp[0] := chr(i); (* конец цепочки литер *)
            END;

        end;
        if founded then
            GetWord:=temp
        else
            GetWord:='';

    end;
	
	(*
	Процедура MergeTree создает в типизированном файле Tree дерево словоформ,
	находящихся в файле-источнике inFile.
	Параметры:
	inFile - файл с исходным текстом.
	Tree - типизированный файл Tree с деревом словоформ.
	Локальные переменные:
	key - текущее извлеченное слово; 
	fileinit - показывает, было ли инициализировано дерево в файле Tree(true - да);
	FreeIndex - номер незанятого элемента в файле Tree;
	*)
    PROCEDURE MergeTree( VAR inFile: text; var Tree:TreeFile );
		
		(*
		Процедура AddKey добавляет в дерево Tree ключ key,
		при этом учитывается возможная необходимость инициализации файла(fileinit),
		и номер свободного для записи блока в файле(FreeIndex).
		Параметры:
		key - ключ, вставляемый в дерево,
		fileinit - показывает, было ли инициализировано дерево в файле Tree(true - да);
		FreeIndex - номер незанятого элемента в файле Tree;
		Tree - типизированный файл Tree с деревом словоформ.
		Локальные переменные:
		TempNode - создаваемый и вставляемый в дерево узел;
        Rider,PrevRider - текущий и предыдущий номера просматриваемых узлов дерева; 
		founded - показывает, был ли найден в дереве вставляемый ключ(т.е. существует ли он уже);
		status - показывает отошение сравниваемых ключей
					(1 - вставляемый больше;
					 0 - равны;
					 -1 - вставляемый меньше;)
		*)
        PROCEDURE AddKey(var Tree:TreeFile; const key: TextWord;var FreeIndex:longint;var fileinit:boolean);
        var TempNode:Node;
            Rider,PrevRider:longint; founded:boolean;status:shortint;
        BEGIN
            {**Root node position**}
            if FileInit then begin {**File initialized**}
                {**Read root node**}
                Rider:=0;
                repeat
                    PrevRider:=Rider;
                    seek(Tree,Rider);Read(Tree,TempNode);
                    status:=Compare(key,TempNode.key);
                    Case status of
                        1:Rider:=TempNode.right;
                        -1:Rider:=TempNode.left;
                        0:begin
                            Rider:=0;
                        end;
                    end;
                until Rider<=0;
                if Rider=0 then begin
                    inc(TempNode.Count);
                    seek(Tree,PrevRider);write(Tree,TempNode);
                end else begin
                    {**Prepare and write parent node**}
                    
                    Case Rider of
                        -1:TempNode.right:=FreeIndex;
                        -2:TempNode.left:=FreeIndex;
                    End;
                    seek(Tree,PrevRider);write(Tree,TempNode);
                    {**Prepare and write new child node**}
                    TempNode.key:=key; TempNode.count:=1;
                    TempNode.right:=-1; TempNode.left:=-2;
                    seek(Tree,FreeIndex);write(Tree,TempNode);
                    inc(FreeIndex);
                end;
            end else begin
                {**Prepare and write root node**}
                
                TempNode.key:=key; TempNode.count:=1;
                TempNode.right:=-1; TempNode.left:=-2;
                seek(Tree,0);write(Tree,TempNode);
                FreeIndex:=1; fileinit:=true;
            end;
        END {AddKey};

    VAR
        key: TextWord; fileinit:boolean;FreeIndex:longint;
    BEGIN
        FreeIndex:=0;Fileinit:=false;
        key:=GetWord(inFile);
        WHILE (key<>'') DO begin
            AddKey(Tree,key,FreeIndex,fileinit);
            key:=GetWord(inFile);
        END;
    END {MergeTree};


    function TreeFileExists(var f:TreeFile):boolean;
    begin
         {$I-}
              Reset(f);
         {$I+}
         if ioresult=0 then begin

            TreeFileExists:=true;
            Close(f);
         end else TreeFileExists:=false
    end {FileExist};
	
	function FileExists(var f:text):boolean;
	var exist:boolean;
	begin
		{$I-}
			ReSet(f);
		{$I+}
		exist:=ioresult=0;
		if exist then close(f);
		FileExists:=exist;
	end;
	(*
	Функция GetFiles получает файл и исходным текстом inFile,
	временный файл для дерева Tree,
	и файл для вывода outFile.
	Возвращает true, если операция прошла успешно, иначе возвращается false.
	Параметры:
	inFile - файл с исходным текстом.
	outFile - текстовый файл для вывода.
	Tree - типизированный файл с деревом словоформ.
	Локальные переменные:
	ok - флаг отсутствия ошибки (true - нет ошибки).
	*)
    function GetFiles(var inFile:text; var Tree:TreeFile; var outFile:text):boolean;
		(*
		Функция GetInFile() получает файл f для чтения.
		Возвращает true, если операция прошла успешно, иначе возвращается false.
		Параметры:
		f - запрашиваемый файл.
		Локальные переменные:
		error - флаг ошибки (true - ошибка);
		req_rslt - флаг ответа пользователя (true - согласие пользователя).
		*)
		function GetInFile(var f:text):boolean;
		var error,req_rslt:boolean;
			fileName:string;
		begin
			error:=false; req_rslt:=false;
			repeat
				WriteLn('Введите имя файла с текстом для анализа.');
				Write('Файл:');ReadLn(fileName);
				Assign(f,fileName);
				{$I-}
					Reset(f);
				{$I+}
				error:=(ioresult<>0)or(fileName='');
				if error then begin
					WriteLn('Неправильное имя файла! Повторить ввод? <Y>/<N>');
					req_rslt:=GetReqReslt;
				end;
			until not error or not req_rslt;
			GetInFile:=not error;
		end;
		
		(*
		Функция GetTmpFile() получает временный типизированный файл f.
		Возвращает true, если операция прошла успешно, иначе возвращается false.
		Параметры:
		f - запрашиваемый файл.
		Локальные переменные:
		error - флаг ошибки (true - ошибка);
		req_rslt - флаг ответа пользователя (true - согласие пользователя).
		*)
        function GetTmpFile(var f:TreeFile):boolean;
        const DefaultName='$temp.tmp';
        var ch:char; error,req_rslt:boolean;
            fileName:string;
        begin
            FileName:=DefaultName;
            repeat
                assign(f,fileName);
                If TreeFileExists(f) then begin
                   WriteLn('Введите имя временного файла');
                   Write('Файл:');ReadLn(fileName);
                end else begin
                   {$I-}
                        ReWrite(f);
                   {$I+}
                   error:=(ioresult<>0)or(fileName='');
                   if error then begin
                       WriteLn('Ошибка при создании файла! Повторить ввод? <Y>/<N>');
                       req_rslt:=GetReqReslt;
                   end;
                end;
            until not req_rslt or not error;
            GetTmpFile:= not error;
        end {GetTmpFile};
		
		(*
		Функция GetOutFile() получает файл f для записи.
		Возвращает true, если операция прошла успешно, иначе возвращается false.
		Параметры:
		f - запрашиваемый файл.
		Локальные переменные:
		error - флаг ошибки (true - ошибка);
		req_rslt - флаг ответа пользователя (true - согласие пользователя).
		*)
		function GetOutFile(var f:text):boolean;
		var error,req_rslt:boolean;
			fileName:string;
		begin
			error:=false; req_rslt:=false;
			repeat
				WriteLn('Введите имя файла для частотного словаря.');
				Write('Файл:');ReadLn(fileName);
				Assign(f,fileName);
				if FileExists(f) then begin
					error:=true;
					WriteLn('Указанный файл сушествует! Перезаписать? (Y/N)');
					error:=not GetReqReslt;
				end;
				if not error then begin
					{$I-}
					ReWrite(f);
					{$I+}
					error:=(ioresult<>0)or(fileName='');
				end;
				if error then begin
					WriteLn('Ошибка при создании файла! Повторить ввод? <Y>/<N>');
					req_rslt:=GetReqReslt;
				end;
			until not error or not req_rslt;
			GetOutFile:=not error;
		end;

    var ok:boolean;
    begin
        ok:=GetInFile(inFile);
        if ok then
            ok:=GetTmpFile(Tree);
        if ok then
            ok:=GetOutFile(outFile);
        GetFiles:=ok;
    end;
(*-------ПРОЦЕДУРЫ И ФУНКЦИИ-------*)
(*
Основная часть программы получения частотного словаря.
Переменные:
inFile - файл с исходным текстом.
outFile - текстовый файл для вывода.
Tree - типизированный файл с деревом словоформ.
ok - флаг отсутствия ошибки (true - нет ошибки);
*)
VAR  inFile, outFile: Text;
     Tree: TreeFile; ok:boolean;
BEGIN
    WriteLn('Программа составляет алфавитный частотный словарь');
    WriteLn('из файла, записанного в текстовом файле,');
    WriteLn('и выводит словарь в выходной текстовый файл');
    ok:=GetFiles(inFile, Tree, outFile);
    if ok then begin
       writeln('Обработка входного текста... ');
       writeln('Пожалуйста, подождите...');
       MergeTree(InFile,Tree);
       WriteLn;
       writeLn('Запись результатов...');
       writeln('Пожалуйста, подождите...');
       PrintTree(Tree,outFile);
       Close(inFile); close(outFile);
       close(Tree); Erase(Tree);
       WriteLn;
       WriteLn('Все операции завершены успешно!')
    end else
       WriteLn('Работа программы прервана...');
    WriteLn('Нажмите <Enter>...');Readln;
END.
