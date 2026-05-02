#!/bin/bash

# 1. Собираем параметры
path=$1
num_subfolders=$2
folder_chars=$3
num_files=$4
file_chars_ext=$5
file_size_param=$6

# Засекаем дату для имен
date_suffix=$(date +%d%m%y)
log_file="file_generator.log"

# 2. Простая валидация (чтобы не упасть от пустых полей)
if [ $# -ne 6 ]; then
    echo "Error: Use 6 parameters. Example: main.sh /opt/test 4 az 5 az.az 3kb"
    exit 1
fi

# Проверка, что путь абсолютный
if [[ "$path" != /* ]]; then echo "Error: Path must be absolute."; exit 1; fi

# Выделяем буквы для имени файла и расширения
file_name_chars=$(echo $file_chars_ext | cut -d'.' -f1)
file_ext_chars=$(echo $file_chars_ext | cut -d'.' -f2)

# 3. Функция генерации "умного" имени
# Она берет строку букв и дублирует последнюю, пока не станет 4 символа
generate_name() {
    local chars=$1
    local name=$chars
    while [ ${#name} -lt 4 ]; do
        name="${name}${chars: -1}" # Дублируем последнюю букву
    done
    echo "${name}_${date_suffix}"
}

# 4. Функция проверки места (стоп, если осталось < 1 ГБ)
check_space() {
    # Берем свободное место в КБ из корня /
    local free_kb=$(df / | tail -1 | awk '{print $4}')
    if [ "$free_kb" -le 1048576 ]; then
        echo "Stop: Not enough space (less than 1GB)."
        exit 1
    fi
}

# Поехали!
echo "Starting prank on Mike..." > "$log_file"

for (( i=0; i<$num_subfolders; i++ )); do
    check_space
    
    # Имя папки: генерируем базу + добавляем счетчик, чтобы имена были разные
    f_name=$(generate_name "$folder_chars")
    current_dir="${path}/${f_name}_${i}"
    
    mkdir -p "$current_dir" 2>/dev/null
    if [ $? -eq 0 ]; then
        echo "DIRECTORY: $current_dir - Created: $(date +%d-%m-%Y)" >> "$log_file"
        
        for (( j=0; j<$num_files; j++ )); do
            check_space
            
            base_filename=$(generate_name "$file_name_chars")
            # Генерируем расширение (минимум 3 символа)
            ext=$file_ext_chars
            while [ ${#ext} -lt 3 ]; do ext="${ext}${file_ext_chars: -1}"; done
            
            full_file_path="${current_dir}/${base_filename}_${j}.${ext}"
            
            # Создаем файл нужного размера (отрезаем 'kb' от параметра)
            size_kb=$(echo $file_size_param | grep -o '[0-9]\+')
            fallocate -l "${size_kb}K" "$full_file_path" 2>/dev/null
            
            if [ $? -eq 0 ]; then
                echo "FILE: $full_file_path - Created: $(date +%d-%m-%Y) - Size: ${size_kb}KB" >> "$log_file"
            fi
        done
    fi
done

echo "Done! Check $log_file for results. Mike will be surprised. "
