<?php
require_once 'functions.php';

$matrix = [];
$rowMaxes = [];
$minimax = null;
$error = '';

$n = isset($_POST['rows']) ? (int)$_POST['rows'] : 4;
$m = isset($_POST['cols']) ? (int)$_POST['cols'] : 5;
$minValue = isset($_POST['min_value']) ? (int)$_POST['min_value'] : -10;
$maxValue = isset($_POST['max_value']) ? (int)$_POST['max_value'] : 20;

if ($_SERVER['REQUEST_METHOD'] === 'POST') {
    if ($n < 1 || $n > 20 || $m < 1 || $m > 20) {
        $error = 'Количество строк и столбцов должно быть от 1 до 20.';
    } elseif ($minValue > $maxValue) {
        $error = 'Минимальное значение не должно быть больше максимального.';
    } else {
        for ($i = 0; $i < $n; $i++) {
            $row = [];
            for ($j = 0; $j < $m; $j++) {
                $row[] = random_int($minValue, $maxValue);
            }
            $matrix[] = $row;
            $rowMaxes[] = max($row);
        }
        $minimax = min($rowMaxes);
    }
}

render_header('Задание с матрицей');

echo "<h2>Вариант 11: поиск минимакса</h2>\n";
echo "<p>В матрице требуется найти наибольший элемент в каждой строке, а затем среди найденных максимумов определить наименьший элемент — минимакс.</p>\n";

if ($error !== '') {
    echo "<div class='error'>" . e($error) . "</div>\n";
}

echo "<form class='data-form' method='post' action='matrix.php'>\n";
printf("<div><label>Количество строк</label><input type='number' name='rows' min='1' max='20' value='%d'></div>\n", $n);
printf("<div><label>Количество столбцов</label><input type='number' name='cols' min='1' max='20' value='%d'></div>\n", $m);
printf("<div><label>Минимальное значение</label><input type='number' name='min_value' value='%d'></div>\n", $minValue);
printf("<div><label>Максимальное значение</label><input type='number' name='max_value' value='%d'></div>\n", $maxValue);
echo "<div class='form-actions'><input type='submit' value='Сгенерировать и решить'></div>\n";
echo "</form>\n";

if (count($matrix) > 0) {
    echo "<h2>Сгенерированная матрица</h2>\n";
    echo "<table>\n";
    for ($i = 0; $i < count($matrix); $i++) {
        echo "<tr>\n";
        for ($j = 0; $j < count($matrix[$i]); $j++) {
            $class = '';
            if ($matrix[$i][$j] === $rowMaxes[$i]) {
                $class = ($matrix[$i][$j] === $minimax) ? 'minimax' : 'row-max';
            }
            printf("<td class='matrix-cell %s'>%d</td>\n", $class, $matrix[$i][$j]);
        }
        echo "</tr>\n";
    }
    echo "</table>\n";

    echo "<div class='result-box'>\n";
    echo "<strong>Максимумы по строкам:</strong> " . e(implode(', ', $rowMaxes)) . "<br>\n";
    printf("<strong>Минимакс:</strong> %d\n", $minimax);
    echo "</div>\n";
}

render_footer();
?>
