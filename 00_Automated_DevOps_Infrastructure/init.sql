CREATE TABLE IF NOT EXISTS ram_alerts (
    id SERIAL PRIMARY KEY,
    alert_time TIMESTAMP DEFAULT CURRENT_TIMESTAMP,
    ram_usage FLOAT,
    cpu_usage FLOAT DEFAULT 0.0,  -- Добавляем новую колонку здесь!
    hdd_usage FLOAT DEFAULT 0.0,
    message TEXT
);
