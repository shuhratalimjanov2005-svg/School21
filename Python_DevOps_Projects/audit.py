import os
import shutil
import platform
import getpass

def audit_my_repo():
    # 1. Узнаем, кто тут Босс и на чем сидит
    user = getpass.getuser()
    system = platform.system()
    current_dir = os.getcwd()

    # 2. Считаем проекты (твой старый добрый код)
    all_items = os.listdir('.')
    # Оставляем папки, которые не начинаются с точки
    directories = [d for d in all_items if os.path.isdir(d) and not d.startswith('.')]

    # 3. ПРОВЕРКА ЖЕЛЕЗА (Наш новый DevOps-слой)
    # Проверяем диск (корень "/")
    total, used, free = shutil.disk_usage("/")
    free_gb = free // (2**30)  # Конвертируем в Гб

    print(f"\n---  DevOps Audit Report  ---")
    print(f"👤 Пользователь: {user}")
    print(f"💻 Операционка: {system}")
    print(f"📍 Где мы: {current_dir}")
    print(f"📁 Активных проектов: {len(directories)} ({', '.join(directories)})")
    
    print(f"\n--- 💾 Состояние памяти ---")
    print(f"Свободно на диске: {free_gb} GB")

    # 4. АВТО-ДИАГНОСТИКА (Скрипт начинает «думать»)
    if free_gb < 5:
        print("🛑 КРИТИЧЕСКИЙ УРОВЕНЬ: Срочно удаляй мусор!")
    elif free_gb < 20:
        print("⚠️ ПРЕДУПРЕЖДЕНИЕ: Место заканчивается. Будь аккуратнее. ")
    else:
        print("✅ ВСЁ ХОРОШО: Места полно, кодим дальше! ✨")
    print(f"------------------------------\n")

if __name__ == "__main__":
    audit_my_repo()
