day(monday).
day(tuesday).
day(wednesday).

city(vb).   % Верхний Большеград
city(nm).   % Нижний Малоград
city(pl).   % Плутоград

solve(S_Day, S_City, K_Day, K_City, L_Day, L_City) :-

    day(S_Day), day(K_Day), day(L_Day),
    S_Day \= K_Day, S_Day \= L_Day, K_Day \= L_Day,

    city(S_City), city(K_City), city(L_City),
    S_City \= K_City, S_City \= L_City, K_City \= L_City,

    % жёсткие ограничения

    S_City \= nm,

    K_Day \= tuesday,

    \+ (K_City = vb, K_Day = monday),

    \+ (S_City = nm, S_Day = monday),
    \+ (K_City = nm, K_Day = monday),
    \+ (L_City = nm, L_Day = monday),

    S_City \= vb,

    (S_City = pl -> S_Day \= monday ; true).

main :-
    (   solve(SD, SC, KD, KC, LD, LC)
    ->  format("=== Расписание найдено ===~n"),
        format("Сеель-Хамош : ~w -> ~w~n", [SD, SC]),
        format("Киш-Кираль  : ~w -> ~w~n", [KD, KC]),
        format("Латсатхи    : ~w -> ~w~n", [LD, LC])
    ;
        format("(Мягкое ограничение №6 нарушено — принимаем)~n"),
        solve_relax(SD, SC, KD, KC, LD, LC),
        format("=== Расписание найдено ===~n"),
        format("Сеель-Хамош : ~w -> ~w~n", [SD, SC]),
        format("Киш-Кираль  : ~w -> ~w~n", [KD, KC]),
        format("Латсатхи    : ~w -> ~w~n", [LD, LC])
    ).

solve_relax(SD, SC, KD, KC, LD, LC) :-
    day(SD), day(KD), day(LD),
    SD \= KD, SD \= LD, KD \= LD,
    city(SC), city(KC), city(LC),
    SC \= KC, SC \= LC, KC \= LC,
    SC \= nm,
    KD \= tuesday,
    \+ (KC = vb, KD = monday),
    \+ (SC = nm, SD = monday),
    \+ (KC = nm, KD = monday),
    \+ (LC = nm, LD = monday),
    SC \= vb.