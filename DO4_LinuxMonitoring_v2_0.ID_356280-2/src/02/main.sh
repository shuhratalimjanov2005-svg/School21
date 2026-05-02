#!/bin/bash

start_time_sec=$(date +%s)
start_time=$(date +"%Y-%m-%d %H:%M:%S")

# Проверка параметров
if [ $# -ne 3 ]; then
    echo "Error: Need 3 parameters (folders_chars, files_chars.ext, size_Mb)"
    exit 1
fi

folder_chars=$1
file_chars_ext=$2
file_size_mb=$(echo $3 | sed 's/Mb//')
date_suffix=$(date +%d%m%y)
log_file="file_clogging.log"

# Находим список всех папок, кроме bin и sbin
# Чтобы не ждать вечно, ограничим поиск по глубине
all_dirs=$(find / -type d \( -path "*/bin" -o -path "*/sbin" -o -path "*/proc" -o -path "*/dev" -o -path "*/sys" \) -prune -o -type d -perm -u+w -print 2>/dev/null | shuf -n 100)

check_space() {
    free_space_kb=$(df / | tail -1 | awk '{print $4}')
    if [ "$free_space_kb" -le 1048576 ]; then
        echo "Error: Less than 1GB free space left. Stopping..."
        return 1
    fi
    return 0
}

generate_name() {
    local chars=$1
    local min_len=5
    local name=$chars
    while [ ${#name} -lt $min_len ]; do
        name="${name}${chars: -1}"
    done
    echo "${name}_${date_suffix}"
}

# Очистка/создание лога
echo "Script started at: $start_time" > "$log_file"

for dir in $all_dirs; do
    if ! check_space; then break; fi

    folder_name=$(generate_name "$folder_chars")
    current_path="${dir}/${folder_name}"
    
    mkdir -p "$current_path" 2>/dev/null
    if [ $? -eq 0 ]; then
        echo "DIR: $current_path - Created: $(date +%d.%m.%y)" >> "$log_file"
        
        # Рандомное количество файлов в каждой папке
        num_files=$(( 1 + RANDOM % 50 )) 
        
        f_name_chars=$(echo $file_chars_ext | cut -d'.' -f1)
        f_ext_chars=$(echo $file_chars_ext | cut -d'.' -f2)

        for (( j=0; j<$num_files; j++ )); do
            if ! check_space; then break 2; fi
            
            f_base=$(generate_name "$f_name_chars")
            ext=$f_ext_chars
            while [ ${#ext} -lt 3 ]; do ext="${ext}${f_ext_chars: -1}"; done
            
            full_file="${current_path}/${f_base}_${j}.${ext}"
            
            fallocate -l "${file_size_mb}M" "$full_file" 2>/dev/null
            if [ $? -eq 0 ]; then
                echo "FILE: $full_file - Date: $(date +%d.%m.%y) - Size: ${file_size_mb}MB" >> "$log_file"
            fi
        done
    fi
done

end_time=$(date +"%Y-%m-%d %H:%M:%S")
end_time_sec=$(date +%s)
diff=$(( end_time_sec - start_time_sec ))

# Вывод и запись финальных данных
summary="Start: $start_time | End: $end_time | Total: $diff seconds"
echo "$summary"
echo "$summary" >> "$log_file"
