CREATE DATABASE IF NOT EXISTS lab6_computer_shop
  DEFAULT CHARACTER SET utf8mb4
  DEFAULT COLLATE utf8mb4_unicode_ci;

USE lab6_computer_shop;

DROP TABLE IF EXISTS products;
DROP TABLE IF EXISTS sections;

CREATE TABLE sections (
    section_id INT AUTO_INCREMENT PRIMARY KEY,
    section_name VARCHAR(80) NOT NULL UNIQUE,
    device_type VARCHAR(80) NOT NULL,
    target_user VARCHAR(80) NOT NULL,
    warranty_months INT NOT NULL,
    section_description VARCHAR(255) NOT NULL,
    manager_name VARCHAR(100) NOT NULL
) ENGINE=InnoDB DEFAULT CHARSET=utf8mb4;

CREATE TABLE products (
    product_id INT AUTO_INCREMENT PRIMARY KEY,
    section_id INT NOT NULL,
    model_name VARCHAR(120) NOT NULL,
    manufacturer VARCHAR(80) NOT NULL,
    price DECIMAL(10,2) NOT NULL,
    stock_count INT NOT NULL,
    performance_level VARCHAR(50) NOT NULL,
    release_year YEAR NOT NULL,
    product_description VARCHAR(255) NOT NULL,
    CONSTRAINT fk_products_sections
        FOREIGN KEY (section_id) REFERENCES sections(section_id)
        ON UPDATE CASCADE
        ON DELETE RESTRICT
) ENGINE=InnoDB DEFAULT CHARSET=utf8mb4;

INSERT INTO sections
(section_name, device_type, target_user, warranty_months, section_description, manager_name)
VALUES
('Ноутбуки', 'Портативная техника', 'Студенты и офисные сотрудники', 24, 'Мобильные компьютеры для учебы, работы и поездок', 'Иванов А. П.'),
('Компьютеры', 'Стационарная техника', 'Геймеры и специалисты', 36, 'Системные блоки для дома, игр и профессиональных задач', 'Петрова Н. С.'),
('Мониторы', 'Устройства вывода', 'Дизайнеры и офисные пользователи', 24, 'Мониторы разных диагоналей для работы и развлечений', 'Сидоров В. И.'),
('Комплектующие', 'Внутренние компоненты', 'Сборщики ПК', 12, 'Процессоры, память и накопители для модернизации компьютеров', 'Кузнецова О. М.');

INSERT INTO products
(section_id, model_name, manufacturer, price, stock_count, performance_level, release_year, product_description)
VALUES
(1, 'IdeaPad Slim 3 15', 'Lenovo', 58990.00, 8, 'Средний', 2024, 'Ноутбук для учебы и офисных задач с SSD-накопителем'),
(1, 'Aspire 5 A515', 'Acer', 63990.00, 5, 'Средний', 2023, 'Универсальный ноутбук с хорошей автономностью'),
(2, 'GameBox RTX 4060', 'DNS', 112990.00, 3, 'Высокий', 2024, 'Игровой компьютер для современных игр в Full HD'),
(2, 'Office PC i5', 'IRU', 52990.00, 12, 'Средний', 2023, 'Стационарный компьютер для документов, браузера и учебных программ'),
(3, 'UltraView 24 IPS', 'Samsung', 15990.00, 14, 'Базовый', 2024, '24-дюймовый IPS-монитор для офиса и учебы'),
(3, 'Creator 27 QHD', 'LG', 32990.00, 6, 'Высокий', 2023, 'Монитор с QHD-разрешением для дизайна и монтажа'),
(4, 'Ryzen 5 5600', 'AMD', 12990.00, 10, 'Средний', 2022, 'Шестиядерный процессор для домашнего и игрового ПК'),
(4, 'SSD NV2 1TB', 'Kingston', 6990.00, 20, 'Средний', 2024, 'Быстрый NVMe-накопитель для системы и программ');
