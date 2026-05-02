#!/bin/bash

# Массивы данных для генерации
methods=("GET" "POST" "PUT" "PATCH" "DELETE")
# Коды ответа и их значения:
# 200 - OK (Успех)
# 201 - Created (Создано)
# 400 - Bad Request (Ошибка запроса)
# 401 - Unauthorized (Не авторизован)
# 403 - Forbidden (Доступ запрещен)
# 404 - Not Found (Не найдено)
# 500 - Internal Server Error (Ошибка сервера)
# 501 - Not Implemented (Не реализовано)
# 502 - Bad Gateway ( Ошибка шлюза)
# 503 - Service Unavailable (Сервис недоступен)
codes=(200 201 400 401 403 404 500 501 502 503)

agents=("Mozilla" "Google Chrome" "Opera" "Safari" "Internet Explorer" "Microsoft Edge" "Crawler and bot" "Library and net tool")

urls=("/index.html" "/main.php" "/api/v1/data" "/img/logo.png" "/login" "/search?q=s23+ultra")

# Генерация случайного IP
gen_ip() {
    echo "$((RANDOM % 256)).$((RANDOM % 256)).$((RANDOM % 256)).$((RANDOM % 256))"
}

# Генерация логов для 5 дней
for (( day=1; day<=5; day++ )); do
    log_file="access_log_$day.log"
    num_entries=$((RANDOM % 901 + 100)) # От 100 до 1000 записей
    
    # Дата в формате [DD/Month/YYYY:HH:MM:SS +0000]
    current_date=$(date -d "-$day days" +"%d/%b/%Y")
    
    for (( entry=0; entry<$num_entries; entry++ )); do
        ip=$(gen_ip)
        code=${codes[$RANDOM % ${#codes[@]}]}
        method=${methods[$RANDOM % ${#methods[@]}]}
        agent=${agents[$RANDOM % ${#agents[@]}]}
        url=${urls[$RANDOM % ${#urls[@]}]}
        
        # Время в течение дня в порядке возрастания (условно)
        hour=$(printf "%02d" $((entry * 24 / num_entries)))
        min=$(printf "%02d" $((RANDOM % 60)))
        sec=$(printf "%02d" $((RANDOM % 60)))
        
        echo "$ip - - [$current_date:$hour:$min:$sec +0000] \"$method $url HTTP/1.1\" $code $((RANDOM % 5000)) \"-\" \"$agent\"" >> "$log_file"
    done
    # Сортируем по времени, чтобы было по фэншую
    sort -k4 -o "$log_file" "$log_file"
done

echo "5 log files generated successfully! 👄💅"
