<?php
function e($value) {
    return htmlspecialchars((string)$value, ENT_QUOTES, 'UTF-8');
}

function render_header($title) {
    echo "<!DOCTYPE html>\n";
    echo "<html lang='ru'>\n<head>\n";
    echo "<meta charset='utf-8'>\n";
    echo "<title>" . e($title) . "</title>\n";
    echo "<link rel='stylesheet' href='style.css'>\n";
    echo "</head>\n<body>\n<div class='wrapper'>\n";
    echo "<h1>Лабораторная работа №6</h1>\n";
    echo "<nav>\n";
    echo "<a href='index.php'>База данных</a>\n";
    echo "<a href='matrix.php'>Задание с матрицей</a>\n";
    echo "</nav>\n";
}

function render_footer() {
    echo "</div>\n</body>\n</html>";
}

function get_sections($link) {
    $sql = "SELECT section_id, section_name FROM sections ORDER BY section_name";
    return mysqli_query($link, $sql);
}
?>
