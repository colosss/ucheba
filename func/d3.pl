% ============================================================
%  Задача о Кати Неверной
% ============================================================

solve(Schedule) :-
    % Четверг зафиксирован: Усл.5 (Шари на пляже Пн-Ср) + Усл.8 (парикмахерская только Чт)
    Schedule = [day(mon, F_mon, A_mon),
                day(tue, F_tue, dressmaker),   % Усл.7: во вторник — портниха
                day(wed, F_wed, A_wed),
                day(thu, shari, hairdresser)],

    % Усл.7: Ольга во вторник была в кино с Мишкой — не с Кати
    F_tue \= olga,

    % Усл.9: Пири и Рози не в библиотеке => библиотека только у Ольги
    % Усл.6: Пири и Рози не в парикмахерской (уже у Шари, ок)
    % => Ольга занимает Пн или Ср с занятием библиотека
    ( F_mon = olga, A_mon = library,
      F_wed \= olga,
      permutation([piri, rozi], [F_tue, F_wed]),
      A_wed = boat
    ;
      F_wed = olga, A_wed = library,
      F_mon \= olga,
      permutation([piri, rozi], [F_tue, F_mon]),
      A_mon = boat
    ).

% --- Вывод ---
day_ru(mon, 'Понедельник').
day_ru(tue, 'Вторник').
day_ru(wed, 'Среда').
day_ru(thu, 'Четверг').

act_ru(hairdresser, 'парикмахерская').
act_ru(dressmaker,  'портниха').
act_ru(library,     'библиотека').
act_ru(boat,        'лодочная станция').

friend_ru(olga,  'Ольга').
friend_ru(piri,  'Пири').
friend_ru(rozi,  'Рози').
friend_ru(shari, 'Шари').

print_schedule([]).
print_schedule([day(D,F,A)|T]) :-
    day_ru(D, DR), friend_ru(F, FR), act_ru(A, AR),
    format("  ~w: ~w — ~w~n", [DR, FR, AR]),
    print_schedule(T).

main :-
    writeln('=== Расписание Кати Неверной ==='), nl,
    forall(solve(S), (print_schedule(S), nl)),
    writeln('ВЫВОД: Кати солгала!'),
    writeln('Во вторник она не была ни с Ольгой (та в кино с Мишкой),'),
    writeln('ни у портнихи (туда шла другая девушка без неё).').

:- initialization(main, main).