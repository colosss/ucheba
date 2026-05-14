<?php
require_once 'db.php';
require_once 'functions.php';

$message = '';
$error = '';
$editProduct = null;

if (isset($_GET['action']) && $_GET['action'] === 'delete' && isset($_GET['id'])) {
    $id = (int)$_GET['id'];
    $stmt = mysqli_prepare($link, "DELETE FROM products WHERE product_id = ?");
    mysqli_stmt_bind_param($stmt, 'i', $id);
    mysqli_stmt_execute($stmt);
    header('Location: index.php?message=deleted');
    exit;
}

if ($_SERVER['REQUEST_METHOD'] === 'POST') {
    $productId = isset($_POST['product_id']) ? (int)$_POST['product_id'] : 0;
    $sectionId = (int)$_POST['section_id'];
    $modelName = trim($_POST['model_name']);
    $manufacturer = trim($_POST['manufacturer']);
    $price = (float)$_POST['price'];
    $stockCount = (int)$_POST['stock_count'];
    $performanceLevel = trim($_POST['performance_level']);
    $releaseYear = (int)$_POST['release_year'];
    $productDescription = trim($_POST['product_description']);

    if ($modelName === '' || $manufacturer === '' || $performanceLevel === '' || $productDescription === '') {
        $error = 'Заполните все текстовые поля формы.';
    } elseif ($price <= 0 || $stockCount < 0 || $releaseYear < 2000) {
        $error = 'Проверьте цену, количество на складе и год выпуска.';
    } else {
        if ($productId > 0) {
            $sql = "UPDATE products
                    SET section_id=?, model_name=?, manufacturer=?, price=?, stock_count=?,
                        performance_level=?, release_year=?, product_description=?
                    WHERE product_id=?";
            $stmt = mysqli_prepare($link, $sql);
            mysqli_stmt_bind_param(
                $stmt,
                'issdisisi',
                $sectionId,
                $modelName,
                $manufacturer,
                $price,
                $stockCount,
                $performanceLevel,
                $releaseYear,
                $productDescription,
                $productId
            );
            mysqli_stmt_execute($stmt);
            header('Location: index.php?message=updated');
            exit;
        } else {
            $sql = "INSERT INTO products
                    (section_id, model_name, manufacturer, price, stock_count,
                     performance_level, release_year, product_description)
                    VALUES (?, ?, ?, ?, ?, ?, ?, ?)";
            $stmt = mysqli_prepare($link, $sql);
            mysqli_stmt_bind_param(
                $stmt,
                'issdisis',
                $sectionId,
                $modelName,
                $manufacturer,
                $price,
                $stockCount,
                $performanceLevel,
                $releaseYear,
                $productDescription
            );
            mysqli_stmt_execute($stmt);
            header('Location: index.php?message=added');
            exit;
        }
    }
}

if (isset($_GET['action']) && $_GET['action'] === 'edit' && isset($_GET['id'])) {
    $id = (int)$_GET['id'];
    $stmt = mysqli_prepare($link, "SELECT * FROM products WHERE product_id = ?");
    mysqli_stmt_bind_param($stmt, 'i', $id);
    mysqli_stmt_execute($stmt);
    $result = mysqli_stmt_get_result($stmt);
    $editProduct = mysqli_fetch_assoc($result);
}

if (isset($_GET['message'])) {
    if ($_GET['message'] === 'added') {
        $message = 'Новая строка добавлена в таблицу базы данных.';
    } elseif ($_GET['message'] === 'updated') {
        $message = 'Строка базы данных отредактирована.';
    } elseif ($_GET['message'] === 'deleted') {
        $message = 'Строка удалена из таблицы базы данных.';
    }
}

render_header('Компьютерная техника');

echo "<h2>Компьютерная техника: разделы и товары</h2>\n";
echo "<p>На странице отображаются данные из двух связанных таблиц. Служебные поля — первичный ключ товара, первичный ключ раздела и внешний ключ — в общей таблице не выводятся.</p>\n";

if ($message !== '') {
    echo "<div class='message'>" . e($message) . "</div>\n";
}
if ($error !== '') {
    echo "<div class='error'>" . e($error) . "</div>\n";
}

$selectedSection = $editProduct ? (int)$editProduct['section_id'] : 1;
$buttonText = $editProduct ? 'Сохранить изменения' : 'Добавить товар';

printf("<h2>%s</h2>\n", $editProduct ? 'Редактирование строки' : 'Добавление новой строки');
echo "<form class='data-form' method='post' action='index.php'>\n";
echo "<input type='hidden' name='product_id' value='" . e($editProduct['product_id'] ?? 0) . "'>\n";
echo "<div><label>Раздел сайта</label><select name='section_id'>\n";
$sections = get_sections($link);
while ($section = mysqli_fetch_assoc($sections)) {
    $selected = ((int)$section['section_id'] === $selectedSection) ? 'selected' : '';
    printf(
        "<option value='%d' %s>%s</option>\n",
        $section['section_id'],
        $selected,
        e($section['section_name'])
    );
}
echo "</select></div>\n";
printf("<div><label>Модель</label><input type='text' name='model_name' value='%s'></div>\n", e($editProduct['model_name'] ?? ''));
printf("<div><label>Производитель</label><input type='text' name='manufacturer' value='%s'></div>\n", e($editProduct['manufacturer'] ?? ''));
printf("<div><label>Цена</label><input type='number' step='0.01' name='price' value='%s'></div>\n", e($editProduct['price'] ?? ''));
printf("<div><label>Количество на складе</label><input type='number' name='stock_count' value='%s'></div>\n", e($editProduct['stock_count'] ?? ''));
printf("<div><label>Уровень производительности</label><input type='text' name='performance_level' value='%s'></div>\n", e($editProduct['performance_level'] ?? ''));
printf("<div><label>Год выпуска</label><input type='number' name='release_year' value='%s'></div>\n", e($editProduct['release_year'] ?? ''));
printf("<div><label>Описание товара</label><textarea name='product_description'>%s</textarea></div>\n", e($editProduct['product_description'] ?? ''));
echo "<div class='form-actions'>\n";
printf("<input type='submit' value='%s'>\n", e($buttonText));
if ($editProduct) {
    echo "<a class='button' href='index.php'>Отменить редактирование</a>\n";
}
echo "</div>\n</form>\n";

$sql = "SELECT
            s.section_name,
            s.device_type,
            s.target_user,
            s.warranty_months,
            s.section_description,
            s.manager_name,
            p.product_id,
            p.model_name,
            p.manufacturer,
            p.price,
            p.stock_count,
            p.performance_level,
            p.release_year,
            p.product_description
        FROM products p
        INNER JOIN sections s ON p.section_id = s.section_id
        ORDER BY s.section_name, p.model_name";
$result = mysqli_query($link, $sql);

echo "<h2>Общая таблица данных</h2>\n";
echo "<div class='table-scroll'>\n";
echo "<table>\n";
echo "<tr>\n";
echo "<th>Раздел</th><th>Тип устройства</th><th>Целевая аудитория</th><th>Гарантия, мес.</th><th>Описание раздела</th><th>Ответственный</th>\n";
echo "<th>Модель</th><th>Производитель</th><th>Цена</th><th>На складе</th><th>Уровень</th><th>Год</th><th>Описание товара</th><th>Действия</th>\n";
echo "</tr>\n";

while ($row = mysqli_fetch_assoc($result)) {
    printf(
        "<tr>\n" .
        "<td>%s</td><td>%s</td><td>%s</td><td>%d</td><td>%s</td><td>%s</td>\n" .
        "<td>%s</td><td>%s</td><td>%.2f</td><td>%d</td><td>%s</td><td>%d</td><td>%s</td>\n" .
        "<td class='actions'><a href='index.php?action=edit&id=%d'>Редактировать</a><br><a href='index.php?action=delete&id=%d' onclick=\"return confirm('Удалить строку?')\">Удалить</a></td>\n" .
        "</tr>\n",
        e($row['section_name']),
        e($row['device_type']),
        e($row['target_user']),
        $row['warranty_months'],
        e($row['section_description']),
        e($row['manager_name']),
        e($row['model_name']),
        e($row['manufacturer']),
        $row['price'],
        $row['stock_count'],
        e($row['performance_level']),
        $row['release_year'],
        e($row['product_description']),
        $row['product_id'],
        $row['product_id']
    );
}

echo "</table>\n</div>\n";

mysqli_free_result($result);
mysqli_close($link);
render_footer();
?>
